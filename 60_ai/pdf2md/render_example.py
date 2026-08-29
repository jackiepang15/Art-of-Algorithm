#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
将 markdown 例题（不含解答与提示）渲染为图片。
使用 Playwright 渲染 HTML，MathJax 渲染公式，本地图片直接嵌入。
"""

import os
import re
import sys
import base64
import mimetypes
from playwright.sync_api import sync_playwright

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# 第一讲最后一道例题（不包含解答过程和提示）
EXAMPLE_MARKDOWN = r"""【例 5】数一数, 需要多少块砖才能把坏了的墙补好?

![](images/math_1_3/7c80905e8e4cd4636f839fb7251b9627eff052d83397b2ceff444f884a7d0d78.jpg)
"""


def image_to_data_uri(img_path: str) -> str:
    """将本地图片转为 data URI，避免 file:// 路径与跨域问题。"""
    abs_path = os.path.join(BASE_DIR, img_path) if not os.path.isabs(img_path) else img_path
    mime, _ = mimetypes.guess_type(abs_path)
    if mime is None:
        mime = "image/jpeg"
    with open(abs_path, "rb") as f:
        data = base64.b64encode(f.read()).decode("ascii")
    return f"data:{mime};base64,{data}"


def md_to_html(md: str) -> str:
    """简易 markdown -> html：处理图片与段落，保留 $ 公式给 MathJax。"""
    lines = md.splitlines()
    out = []
    for line in lines:
        stripped = line.strip()
        if not stripped:
            out.append("")
            continue
        # 图片 ![alt](path)
        def repl_img(m):
            alt = m.group(1)
            path = m.group(2)
            uri = image_to_data_uri(path)
            return f'<img src="{uri}" alt="{alt}" />'
        html_line = re.sub(r'!\[([^\]]*)\]\(([^)]+)\)', repl_img, stripped)
        # 普通文本包裹为段落
        if html_line.startswith("<img"):
            out.append(f'<div class="img-wrap">{html_line}</div>')
        else:
            out.append(f'<p>{html_line}</p>')
    return "\n".join(out)


def build_html(body_html: str) -> str:
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<style>
  @font-face {{
    font-family: 'LocalChinese';
    src: local('Microsoft YaHei'), local('SimHei'), local('PingFang SC'), local('Noto Sans CJK SC');
  }}
  html, body {{
    margin: 0;
    padding: 0;
    background: #ffffff;
  }}
  body {{
    font-family: 'LocalChinese', 'Microsoft YaHei', 'SimHei', 'PingFang SC', sans-serif;
    color: #222;
    padding: 36px 44px;
    box-sizing: border-box;
    display: inline-block;
  }}
  .example-title {{
    font-size: 22px;
    font-weight: 700;
    line-height: 1.6;
    margin: 0 0 18px 0;
  }}
  p {{
    margin: 0 0 14px 0;
    font-size: 19px;
    line-height: 1.7;
  }}
  .img-wrap {{
    margin: 8px 0 12px 0;
    text-align: left;
  }}
  img {{
    max-width: 100%;
    height: auto;
    display: inline-block;
  }}
</style>
<script>
window.MathJax = {{
  tex: {{
    inlineMath: [['$', '$'], ['\\\\(', '\\\\)']],
    displayMath: [['$$', '$$'], ['\\\\[', '\\\\]']]
  }},
  svg: {{ fontCache: 'global' }},
  startup: {{
    typeset: true
  }}
}};
</script>
<script src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js" async></script>
</head>
<body>
<div class="example">{body_html}</div>
</body>
</html>"""


def main():
    body_html = md_to_html(EXAMPLE_MARKDOWN)
    html = build_html(body_html)
    html_path = os.path.join(BASE_DIR, "_example_render.html")
    with open(html_path, "w", encoding="utf-8") as f:
        f.write(html)

    output_path = os.path.join(BASE_DIR, "example_5_question.png")

    with sync_playwright() as p:
        browser = p.chromium.launch()
        context = browser.new_context(
            viewport={"width": 900, "height": 1200},
            device_scale_factor=2,
        )
        page = context.new_page()
        page.goto("file:///" + html_path.replace("\\", "/"))

        # 等待 MathJax 渲染完成（若有公式）；无公式时也安全
        try:
            page.wait_for_function(
                "window.MathJax && window.MathJax.startup && window.MathJax.startup.promise",
                timeout=8000,
            )
            page.evaluate("() => window.MathJax.startup.promise")
            page.wait_for_timeout(1500)
        except Exception as e:
            print(f"[warn] MathJax 等待超时或无网络，按原文渲染: {e}")

        # 等待图片加载
        page.wait_for_function(
            """() => Array.from(document.images).every(img => img.complete && img.naturalWidth > 0)""",
            timeout=10000,
        )

        # 截取例题内容元素（自动裁剪到内容边界，避免多余空白）
        loc = page.locator(".example")
        loc.screenshot(path=output_path, omit_background=False)
        browser.close()

    size = os.path.getsize(output_path)
    print(f"已保存例题图片: {output_path} ({size/1024:.1f} KB)")


if __name__ == "__main__":
    main()
