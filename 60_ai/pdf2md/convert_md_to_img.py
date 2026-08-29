import asyncio
from playwright.async_api import async_playwright
import markdown
import os

async def md_to_image(md_content, output_path, base_url):
    # Convert markdown to HTML
    # We need to handle math and images. 
    # For math, we can use MathJax.
    # For images, we need to ensure the base_url is correctly set.
    
    html_content = markdown.markdown(md_content)
    
    # Add MathJax and some basic styling for better rendering
    full_html = f"""
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="utf-8">
        <script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
        <script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>
        <style>
            body {{
                font-family: sans-serif;
                padding: 20px;
                background-color: white;
                display: inline-block;
            }}
            img {{
                max-width: 100%;
                display: block;
                margin: 10px 0;
            }}
            table {{
                border-collapse: collapse;
                margin: 10px 0;
            }}
            td, th {{
                border: 1px solid black;
                padding: 5px;
            }}
        </style>
    </head>
    <body>
        {html_content}
    </body>
    </html>
    """
    
    # Note: The 'base_url' in playwright helps resolve relative image paths.
    # However, the markdown-it or standard markdown might not use base_url directly in the HTML.
    # We'll manually fix image paths for this specific task.
    
    # Basic image path fixing: if path starts with 'images/', prepend base_url/
    # But base_url should be the directory of the md file.
    
    async with async_playwright() as p:
        browser = await p.chromium.launch()
        page = await browser.new_page()
        
        # Set content and wait for MathJax to render
        await page.set_content(full_html)
        
        # Wait for MathJax to finish rendering math
        await page.evaluate("window.MathJax.typesetPromise()")
        
        # Wait for images to load
        await page.wait_for_load_state("networkidle")
        
        # Find the element that contains the content
        element = await page.query_selector("body")
        
        # Take a screenshot of the element
        await element.screenshot(path=output_path)
        await browser.close()

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 4:
        print("Usage: python script.py <md_content_file> <output_image_path> <base_dir>")
        sys.exit(1)
        
    with open(sys.argv[1], 'r', encoding='utf-8') as f:
        content = f.read()
    
    output = sys.argv[2]
    base_dir = sys.argv[3]
    
    # Fix relative image paths in the markdown content to absolute before converting
    # to ensure playwright can find them.
    import re
    def fix_img_path(match):
        img_path = match.group(1)
        if not img_path.startswith(('http', '/', '.')):
            # Prepend base_dir
            return f'![]( {os.path.join(base_dir, img_path)} )'
        return match.group(0)

    # This regex is simple, might need adjustment if there are many formats
    content = re.sub(r'!\[.*?\]\((.*?)\)', fix_img_path, content)

    asyncio.run(md_to_image(content, output, base_dir))
