"""Generate a Chinese or multilingual image description with a local Ollama model.

Usage:
    python describe_image_with_ollama.py photo.jpg \
        --context '{"country":"Japan","nearby_attractions":["Kiyomizu-dera"]}' \
        --instruction "Write a concise travel-photo caption in Chinese."

    python describe_image_with_ollama.py photo.jpg \
        --context-file photo_context.json \
        --instruction "Describe the scene in one paragraph."

The generated description is written to standard output. Ollama must be running
locally, and the selected model must support image input.
"""

import argparse
import base64
import json
import sys
import threading
import time
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen


DEFAULT_MODEL = "modelscope.cn/unsloth/qwen3.6:35b"
DEFAULT_OLLAMA_URL = "http://localhost:11434"


def parse_args():
    parser = argparse.ArgumentParser(
        description="Describe a local image with a vision-capable Ollama model."
    )
    parser.add_argument("image", type=Path, help="Path to the image file.")
    context_group = parser.add_mutually_exclusive_group()
    context_group.add_argument(
        "--context",
        help='Context as a JSON object, for example \'{"country":"Japan"}\'.',
    )
    context_group.add_argument(
        "--context-file",
        type=Path,
        help="Path to a UTF-8 file containing a JSON object.",
    )
    parser.add_argument(
        "--instruction",
        required=True,
        help="Requirements for the generated description.",
    )
    parser.add_argument(
        "--model",
        default=DEFAULT_MODEL,
        help=f"Ollama model tag (default: {DEFAULT_MODEL}).",
    )
    parser.add_argument(
        "--ollama-url",
        default=DEFAULT_OLLAMA_URL,
        help=f"Ollama server URL (default: {DEFAULT_OLLAMA_URL}).",
    )
    parser.add_argument(
        "--timeout",
        type=float,
        default=600,
        help="Request timeout in seconds (default: 600).",
    )
    return parser.parse_args()


def load_context(args):
    if args.context_file:
        context_text = args.context_file.read_text(encoding="utf-8")
    elif args.context:
        context_text = args.context
    else:
        return {}

    try:
        context = json.loads(context_text)
    except json.JSONDecodeError as error:
        raise ValueError(f"Invalid context JSON: {error}") from error
    if not isinstance(context, dict):
        raise ValueError("The context JSON must be an object.")
    return context


def read_image(image_path):
    if not image_path.is_file():
        raise FileNotFoundError(f"Image file does not exist: {image_path}")

    if image_path.suffix.lower() not in {".heic", ".heif"}:
        return image_path.read_bytes()

    try:
        from PIL import Image
        from pillow_heif import register_heif_opener
    except ImportError as error:
        raise RuntimeError(
            "HEIC/HEIF images require Pillow and pillow-heif: "
            "python -m pip install Pillow pillow-heif"
        ) from error

    register_heif_opener()
    with Image.open(image_path) as image:
        image.load()
        if image.mode not in {"RGB", "RGBA"}:
            image = image.convert("RGB")
        from io import BytesIO

        buffer = BytesIO()
        image.save(buffer, format="PNG")
        return buffer.getvalue()


def build_prompt(context, instruction):
    context_json = json.dumps(context, ensure_ascii=False, indent=2)
    return (
        "请根据图片生成描述。上下文信息是辅助线索；请以图片中实际可见的内容为准，"
        "不要把无法从图片确认的地点或细节写成确定事实。\n\n"
        f"上下文 JSON：\n{context_json}\n\n"
        f"描述要求：\n{instruction}"
    )


def _report_progress(stop_event, progress, started_at):
    while not stop_event.wait(1):
        elapsed = time.monotonic() - started_at
        print(
            f"\rOllama {progress['phase']} | 已等待 {elapsed:.0f}s | "
            f"收到 {progress['chunks']} 个文本片段、{progress['characters']} 个字符",
            end="",
            file=sys.stderr,
            flush=True,
        )


def _duration_seconds(result, field):
    nanoseconds = result.get(field)
    if not isinstance(nanoseconds, (int, float)):
        return None
    return nanoseconds / 1_000_000_000


def print_statistics(result, elapsed):
    prompt_tokens = result.get("prompt_eval_count")
    output_tokens = result.get("eval_count")
    prompt_seconds = _duration_seconds(result, "prompt_eval_duration")
    generation_seconds = _duration_seconds(result, "eval_duration")

    print("\nOllama 调用统计：", file=sys.stderr)
    print(f"  模型：{result.get('model', 'unknown')}", file=sys.stderr)
    print(f"  输入 token：{prompt_tokens if prompt_tokens is not None else 'n/a'}", file=sys.stderr)
    print(f"  输出 token：{output_tokens if output_tokens is not None else 'n/a'}", file=sys.stderr)
    print(f"  客户端总等待：{elapsed:.2f}s", file=sys.stderr)

    load_seconds = _duration_seconds(result, "load_duration")
    total_seconds = _duration_seconds(result, "total_duration")
    if load_seconds is not None:
        print(f"  模型加载：{load_seconds:.2f}s", file=sys.stderr)
    if prompt_seconds is not None:
        print(f"  输入处理：{prompt_seconds:.2f}s", file=sys.stderr)
    if generation_seconds is not None:
        print(f"  文本生成：{generation_seconds:.2f}s", file=sys.stderr)
    if total_seconds is not None:
        print(f"  Ollama 总耗时：{total_seconds:.2f}s", file=sys.stderr)
    if prompt_tokens is not None and prompt_seconds and prompt_seconds > 0:
        print(f"  输入处理速度：{prompt_tokens / prompt_seconds:.2f} token/s", file=sys.stderr)
    if output_tokens is not None and generation_seconds and generation_seconds > 0:
        print(f"  输出生成速度：{output_tokens / generation_seconds:.2f} token/s", file=sys.stderr)


def generate_description(image_bytes, context, instruction, model, ollama_url, timeout):
    payload = {
        "model": model,
        "prompt": build_prompt(context, instruction),
        "images": [base64.b64encode(image_bytes).decode("ascii")],
        "stream": True,
    }
    request = Request(
        f"{ollama_url.rstrip('/')}/api/generate",
        data=json.dumps(payload, ensure_ascii=False).encode("utf-8"),
        headers={"Content-Type": "application/json"},
        method="POST",
    )

    started_at = time.monotonic()
    progress = {"phase": "等待首个响应", "chunks": 0, "characters": 0}
    stop_event = threading.Event()
    reporter = threading.Thread(
        target=_report_progress,
        args=(stop_event, progress, started_at),
        daemon=True,
    )
    reporter.start()

    result = None
    response_parts = []
    try:
        with urlopen(request, timeout=timeout) as response:
            for line in response:
                if not line.strip():
                    continue
                chunk = json.loads(line)
                if chunk.get("error"):
                    raise RuntimeError(f"Ollama error: {chunk['error']}")

                text = chunk.get("response", "")
                if text:
                    response_parts.append(text)
                    progress["phase"] = "正在生成"
                    progress["chunks"] += 1
                    progress["characters"] += len(text)
                if chunk.get("done"):
                    result = chunk
                    break
    except HTTPError as error:
        detail = error.read().decode("utf-8", errors="replace")
        raise RuntimeError(f"Ollama returned HTTP {error.code}: {detail}") from error
    except URLError as error:
        raise RuntimeError(
            f"Could not connect to Ollama at {ollama_url}: {error.reason}"
        ) from error
    except TimeoutError as error:
        raise RuntimeError(f"Ollama request timed out after {timeout:g} seconds.") from error
    finally:
        stop_event.set()
        reporter.join()
        print(file=sys.stderr)

    if result is None:
        raise RuntimeError("Ollama closed the response without a final result.")
    description = "".join(response_parts).strip()
    if not description:
        raise RuntimeError(f"Ollama returned no description: {result}")
    return description, result, time.monotonic() - started_at


def main():
    args = parse_args()
    try:
        context = load_context(args)
        image_bytes = read_image(args.image)
        description, result, elapsed = generate_description(
            image_bytes,
            context,
            args.instruction,
            args.model,
            args.ollama_url,
            args.timeout,
        )
    except (OSError, ValueError, RuntimeError) as error:
        print(f"Error: {error}", file=sys.stderr)
        return 1

    print(description)
    print_statistics(result, elapsed)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())