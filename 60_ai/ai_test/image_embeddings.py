"""Extract OpenCLIP image embeddings and write them to a JSON file.

Requirements:
    Install PyTorch, OpenCLIP, and Pillow in the active Python environment.
    HEIC/HEIF images additionally require ``pillow-heif``.

Usage:
    # Process one image.
    python image_embeddings.py -i path/to/image.jpg -o embeddings.json

    # Process multiple images and recursively scan a directory.
    python image_embeddings.py -i path/to/image1.jpg path/to/images -o embeddings.json

    # Override the model checkpoint, select a device, and enable debug logs.
    python image_embeddings.py -i path/to/images -o embeddings.json \
        --pretrained path/to/checkpoint.bin --device cuda --debug

Each JSON record contains an absolute ``image_path`` and a normalized ``embedding``
vector. The default model is ViT-B-32, and the default checkpoint path is defined
by ``DEFAULT_PRETRAINED`` below. Use ``python image_embeddings.py --help`` for all
available command-line options.
"""

import argparse
import json
import logging
from pathlib import Path

import open_clip
import torch
from PIL import Image

try:
    from pillow_heif import register_heif_opener
except ImportError:
    HEIC_SUPPORT_AVAILABLE = False
else:
    # Register the optional HEIC/HEIF decoder with Pillow.
    register_heif_opener()
    HEIC_SUPPORT_AVAILABLE = True


LOGGER = logging.getLogger("image_embeddings")
IMAGE_EXTENSIONS = {".bmp", ".gif", ".jpeg", ".jpg", ".png", ".tif", ".tiff", ".webp", ".heic"}
DEFAULT_PRETRAINED = (
    r"E:\Models\open_clip\open_clip_pytorch_model "
    r"laion CLIP-ViT-B-32-laion2B-s34B-b79K.bin"
)


def parse_args():
    parser = argparse.ArgumentParser(
        description="Extract normalized OpenCLIP image embeddings and save them as JSON."
    )
    parser.add_argument(
        "-i",
        "--input",
        nargs="+",
        required=True,
        metavar="PATH",
        help="One or more image paths and/or directories (directories are searched recursively).",
    )
    parser.add_argument(
        "-o",
        "--output",
        required=True,
        type=Path,
        help="Destination JSON file.",
    )
    parser.add_argument(
        "--model",
        default="ViT-B-32",
        help="OpenCLIP model name (default: ViT-B-32).",
    )
    parser.add_argument(
        "--pretrained",
        default=DEFAULT_PRETRAINED,
        help="OpenCLIP pretrained tag or checkpoint path.",
    )
    parser.add_argument(
        "--device",
        choices=("auto", "cpu", "cuda"),
        default="auto",
        help="Inference device (default: auto).",
    )
    parser.add_argument(
        "--debug",
        action="store_true",
        help="Enable detailed debug logging.",
    )
    return parser.parse_args()


def collect_images(inputs):
    """Resolve image files from paths and recursively scanned directories."""
    images = set()
    for input_path in inputs:
        path = Path(input_path).expanduser()
        if not path.exists():
            raise FileNotFoundError(f"Input path does not exist: {path}")
        if path.is_dir():
            candidates = path.rglob("*")
        elif path.is_file():
            candidates = (path,)
        else:
            raise ValueError(f"Input path is not a file or directory: {path}")

        for candidate in candidates:
            if candidate.is_file() and candidate.suffix.lower() in IMAGE_EXTENSIONS:
                images.add(candidate.resolve())

    if not images:
        raise ValueError("No supported image files were found in the input paths.")
    return sorted(images, key=lambda image: str(image).lower())


def validate_image_support(images):
    """Fail early with installation guidance when HEIC support is unavailable."""
    if not HEIC_SUPPORT_AVAILABLE:
        heic_images = [image for image in images if image.suffix.lower() in {".heic", ".heif"}]
        if heic_images:
            raise RuntimeError(
                f"Cannot read HEIC/HEIF image: {heic_images[0]}. "
                "Install the optional decoder in this Python environment with: "
                "python -m pip install pillow-heif"
            )


def select_device(requested_device):
    if requested_device == "auto":
        return torch.device("cuda" if torch.cuda.is_available() else "cpu")
    if requested_device == "cuda" and not torch.cuda.is_available():
        raise RuntimeError("CUDA was requested, but no CUDA device is available.")
    return torch.device(requested_device)


def main():
    args = parse_args()
    logging.basicConfig(
        level=logging.DEBUG if args.debug else logging.INFO,
        format="%(asctime)s %(levelname)s: %(message)s",
    )

    try:
        images = collect_images(args.input)
        validate_image_support(images)
        device = select_device(args.device)
        LOGGER.info("Found %d image(s); using %s.", len(images), device)

        model, _, preprocess = open_clip.create_model_and_transforms(
            args.model,
            pretrained=args.pretrained,
        )
        model = model.to(device).eval()
        results = []

        for image_path in images:
            LOGGER.debug("Encoding %s", image_path)
            with Image.open(image_path) as image:
                image_tensor = preprocess(image.convert("RGB")).unsqueeze(0).to(device)

            with torch.inference_mode():
                if device.type == "cuda":
                    with torch.autocast(device_type="cuda"):
                        features = model.encode_image(image_tensor)
                else:
                    features = model.encode_image(image_tensor)

                # Normalize vectors so their magnitudes do not affect similarity comparisons.
                features = torch.nn.functional.normalize(features.float(), dim=-1)

            results.append(
                {
                    "image_path": str(image_path),
                    "embedding": features[0].cpu().tolist(),
                }
            )

        args.output.parent.mkdir(parents=True, exist_ok=True)
        with args.output.open("w", encoding="utf-8") as output_file:
            json.dump(results, output_file, ensure_ascii=False, indent=2)
            output_file.write("\n")

        LOGGER.info("Wrote %d embedding(s) to %s.", len(results), args.output.resolve())
        return 0
    except Exception:
        LOGGER.exception("Failed to extract image embeddings.")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())