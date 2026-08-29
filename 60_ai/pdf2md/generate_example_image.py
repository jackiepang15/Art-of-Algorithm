import base64
from pathlib import Path
from playwright.sync_api import sync_playwright

# Paths
img_path = Path(r"D:\Jackie\Art\Art-of-Algorithm\60_ai\pdf2md\images\math_1_3\7c80905e8e4cd4636f839fb7251b9627eff052d83397b2ceff444f884a7d0d78.jpg")
output_path = Path(r"D:\Jackie\Art\Art-of-Algorithm\60_ai\pdf2md\example_5.png")

# Read image and encode to base64
img_data = base64.b64encode(img_path.read_bytes()).decode('utf-8')

# Build HTML content
html_content = f"""
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<style>
  body {{
    margin: 0;
    padding: 40px;
    font-family: "Noto Sans CJK SC", "Microsoft YaHei", "SimHei", sans-serif;
    font-size: 20px;
    line-height: 1.8;
    color: #000;
    background: #fff;
  }}
  .example {{
    max-width: 800px;
    margin: 0 auto;
  }}
  p {{
    margin: 0 0 16px 0;
  }}
  img {{
    display: block;
    max-width: 100%;
    height: auto;
    margin-top: 10px;
  }}
</style>
</head>
<body>
<div class="example">
  <p><strong>【例 5】</strong>数一数, 需要多少块砖才能把坏了的墙补好?</p>
  <img src="data:image/jpeg;base64,{img_data}">
</div>
</body>
</html>
"""

# Write temporary HTML file
temp_html = Path(r"D:\Jackie\Art\Art-of-Algorithm\60_ai\pdf2md\temp_example_5.html")
temp_html.write_text(html_content, encoding='utf-8')

# Use playwright to take screenshot
with sync_playwright() as p:
    browser = p.chromium.launch()
    page = browser.new_page(viewport={"width": 900, "height": 600})
    page.goto(temp_html.as_uri())
    # Wait for image to load
    page.wait_for_timeout(500)
    # Get the bounding box of the content
    element = page.query_selector('.example')
    element.screenshot(path=str(output_path))
    browser.close()

print(f"Screenshot saved to: {output_path}")
