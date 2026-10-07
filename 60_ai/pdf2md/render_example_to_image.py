#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
把《奥数教程·一年级》第 1 讲的最后一道例题（只保留题干，去掉“解”和“提示”）
渲染成一张 PNG 图片。

实现要点：
  1. 在 Markdown 中定位指定讲，取该讲的最后一道【例 N】题干；
  2. 题干中的本地图片内嵌为 data URI，保证图片一定能显示；
  3. 若题干含 $...$ / $$...$$ 公式，则引入 MathJax 渲染公式；
  4. 用 Chromium(headless) 先量出内容尺寸，再按该尺寸以 2 倍分辨率截图，
     所以输出图片紧贴内容、没有多余白边。

用法：
  python render_example_to_image.py                 # 第 1 讲最后一道例题
  python render_example_to_image.py --lecture 2     # 第 2 讲最后一道例题
  python render_example_to_image.py --out D:/a.png  # 指定输出
"""

import argparse
import base64
import glob
import mimetypes
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
DEFAULT_MD = os.path.join(HERE, "book_math_1.md")


# --------------------------------------------------------------------------
# 1. 找到可用的 Chromium
# --------------------------------------------------------------------------
def find_browser() -> str:
    candidates = []
    if os.environ.get("CHROME_PATH"):
        candidates.append(os.environ["CHROME_PATH"])

    local = os.environ.get("LOCALAPPDATA", "")
    if local:
        pw = os.path.join(local, "ms-playwright")
        # 优先使用旧版 headless shell（支持 --dump-dom / --screenshot）
        candidates += sorted(glob.glob(os.path.join(pw, "**", "chrome-headless-shell.exe")))
        candidates += sorted(glob.glob(os.path.join(pw, "**", "chrome.exe")))

    for name in ("chrome-headless-shell", "chromium", "chrome"):
        p = shutil.which(name)
        if p:
            candidates.append(p)

    candidates += [
        r"C:\Program Files\Google\Chrome\Application\chrome.exe",
        r"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe",
    ]

    for c in candidates:
        if c and os.path.isfile(c):
            return c
    raise FileNotFoundError("找不到 Chrome/Chromium，可用环境变量 CHROME_PATH 指定。")


# --------------------------------------------------------------------------
# 2. 抽取题干
# --------------------------------------------------------------------------
EXAMPLE_RE = re.compile(r"^【例\s*(\d+)\s*】")
STOP_RE = re.compile(r"^(解|提示|分析|证明)\b")


def extract_last_example(md_text: str, lecture_no: int):
    """返回 (例题编号, 题干 markdown)。"""
    lines = md_text.splitlines()

    # 定位讲的范围
    head_re = re.compile(r"^##\s*第\s*%d\s*讲" % lecture_no)
    start = next((i for i, ln in enumerate(lines) if head_re.match(ln.strip())), None)
    if start is None:
        raise ValueError("在 Markdown 中找不到第 %d 讲" % lecture_no)

    end = len(lines)
    for j in range(start + 1, len(lines)):
        if lines[j].startswith("## "):
            end = j
            break

    block = lines[start + 1:end]

    # 该讲中所有例题的起始行
    starts = [k for k, ln in enumerate(block) if EXAMPLE_RE.match(ln.strip())]
    if not starts:
        raise ValueError("第 %d 讲中没有找到例题" % lecture_no)

    s = starts[-1]
    e = len(block)
    for k in range(s + 1, len(block)):
        t = block[k].strip()
        if not t:
            continue
        if t.startswith("###") or t.startswith("##") or EXAMPLE_RE.match(t) or STOP_RE.match(t):
            e = k
            break

    chunk = block[s:e]
    while chunk and not chunk[-1].strip():
        chunk.pop()
    no = int(EXAMPLE_RE.match(block[s].strip()).group(1))
    return no, "\n".join(chunk).strip()


# --------------------------------------------------------------------------
# 3. Markdown -> HTML
# --------------------------------------------------------------------------
def image_to_data_uri(path: str) -> str:
    abs_path = path if os.path.isabs(path) else os.path.join(HERE, path)
    if not os.path.isfile(abs_path):
        raise FileNotFoundError("找不到图片: %s" % abs_path)
    mime = mimetypes.guess_type(abs_path)[0] or "image/jpeg"
    with open(abs_path, "rb") as f:
        data = base64.b64encode(f.read()).decode("ascii")
    return "data:%s;base64,%s" % (mime, data)


def escape_html(text: str) -> str:
    return text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")


def md_to_html(chunk: str) -> str:
    out = []
    for raw in chunk.splitlines():
        line = raw.strip()
        if not line:
            continue
        line = escape_html(line)
        line = re.sub(r"!\[([^\]]*)\]\(([^)]+)\)",
                      lambda m: '<img class="ex-img" src="%s" alt="%s">'
                                % (image_to_data_uri(m.group(2)), m.group(1)),
                      line)
        line = re.sub(r"\*\*(.+?)\*\*", r"<strong>\1</strong>", line)
        if line.startswith("<img"):
            out.append('<div class="img-wrap">%s</div>' % line)
        else:
            out.append("<p>%s</p>" % line)
    return "\n".join(out)


def build_html(body_html: str, need_math: bool) -> str:
    mathjax = "" if not need_math else """
<script>
window.MathJax = {
  tex: {inlineMath: [['$','$'],['\\\\(','\\\\)']], displayMath: [['$$','$$'],['\\\\[','\\\\]']]},
  svg: {fontCache: 'global'}
};
</script>
<script src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js" id="MathJax-script"></script>
"""
    return """<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<title>SIZE:pending</title>
<style>
  html, body { margin: 0; padding: 0; background: #ffffff; }
  body { font-family: "Microsoft YaHei", "PingFang SC", "Hiragino Sans GB",
                      "Noto Sans CJK SC", "Source Han Sans SC", sans-serif;
         color: #1f2328; }
  .wrap { display: inline-block; box-sizing: content-box; padding: 34px 40px; background: #fff; }
  p { margin: 0; font-size: 24px; line-height: 1.75; }
  .img-wrap { margin: 20px 0 0 0; }
  .ex-img { display: block; max-width: 100%; height: auto; }
</style>
__MATHJAX__
<script>
async function measure() {
  try {
    if (window.MathJax && MathJax.startup && MathJax.startup.promise) {
      await MathJax.startup.promise;
    }
  } catch (e) {}
  const r = document.querySelector('.wrap').getBoundingClientRect();
  document.title = 'SIZE:' + Math.ceil(r.width) + 'x' + Math.ceil(r.height);
}
window.addEventListener('load', measure);
</script>
</head>
<body>
<div class="wrap">__BODY__</div>
</body>
</html>""".replace("__MATHJAX__", mathjax).replace("__BODY__", body_html)


# --------------------------------------------------------------------------
# 4. 调用 Chromium
# --------------------------------------------------------------------------
def run_chrome(browser: str, args, timeout=120):
    cmd = [browser, "--headless", "--disable-gpu", "--no-sandbox",
           "--hide-scrollbars"] + args
    return subprocess.run(cmd, capture_output=True, text=True,
                          encoding="utf-8", errors="replace", timeout=timeout)


def measure_size(browser: str, url: str):
    # 用一个足够大的窗口量尺寸，避免文字被换行
    res = run_chrome(browser, ["--window-size=1920,1600",
                               "--virtual-time-budget=10000", "--dump-dom", url])
    m = re.search(r"<title>SIZE:(\d+)x(\d+)</title>", res.stdout or "")
    if not m:
        raise RuntimeError("无法测量页面尺寸。\nSTDERR:\n" + (res.stderr or "")[-1500:])
    return int(m.group(1)), int(m.group(2))


def screenshot(browser: str, url: str, out: str, w: int, h: int):
    run_chrome(browser, ["--force-device-scale-factor=2",
                         "--window-size=%d,%d" % (w, h),
                         "--virtual-time-budget=10000",
                         "--screenshot=" + out, url])
    if not os.path.isfile(out):
        raise RuntimeError("截图失败，未生成文件: " + out)


# --------------------------------------------------------------------------
def main(argv=None):
    ap = argparse.ArgumentParser(description="把指定讲的最后一道例题渲染成图片")
    ap.add_argument("--md", default=DEFAULT_MD, help="Markdown 源文件")
    ap.add_argument("--lecture", type=int, default=1, help="第几讲（默认 1）")
    ap.add_argument("--out", default=None, help="输出 PNG 路径")
    args = ap.parse_args(argv)

    with open(args.md, "r", encoding="utf-8") as f:
        md_text = f.read()

    no, chunk = extract_last_example(md_text, args.lecture)
    print("第 %d 讲最后一道例题：【例 %d】" % (args.lecture, no))
    print("-" * 46)
    print(chunk)
    print("-" * 46)

    need_math = bool(re.search(r"\$", chunk))
    html = build_html(md_to_html(chunk), need_math)

    out = args.out or os.path.join(HERE, "output", "lecture%d_example%d.png" % (args.lecture, no))
    os.makedirs(os.path.dirname(os.path.abspath(out)), exist_ok=True)

    tmp_dir = tempfile.mkdtemp(prefix="example_render_")
    html_path = os.path.join(tmp_dir, "example.html")
    with open(html_path, "w", encoding="utf-8") as f:
        f.write(html)
    url = "file:///" + html_path.replace("\\", "/")

    browser = find_browser()
    print("使用浏览器:", browser)

    w, h = measure_size(browser, url)
    print("内容尺寸: %d x %d (CSS px)" % (w, h))
    screenshot(browser, url, os.path.abspath(out), w, h)
    shutil.rmtree(tmp_dir, ignore_errors=True)

    print("已生成: %s  (%.1f KB)" % (out, os.path.getsize(out) / 1024))
    return 0


if __name__ == "__main__":
    sys.exit(main())
