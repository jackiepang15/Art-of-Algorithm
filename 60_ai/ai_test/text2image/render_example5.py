# Render Example 5 as JPEG using Pillow
import os
from PIL import Image, ImageDraw, ImageFont

# Paths
md_dir = r"D:\Jackie\Art\wiki\3_Work_Experience\3_3_Study_Notes"
img_path = os.path.join(md_dir, r"images/math_1_3/7c80905e8e4cd4636f839fb7251b9627eff052d83397b2ceff444f884a7d0d78.jpg")
out_path = os.path.join(md_dir, "life_math_1_example5.jpg")

# Verify image exists
if not os.path.exists(img_path):
    raise FileNotFoundError(f"Image not found: {img_path}")

# Load the brick wall image
img = Image.open(img_path).convert("RGBA")
img_w, img_h = img.size
print(f"Image size: {img_w}x{img_h}")

# Calculate output dimensions with padding for text
text_padding_x = 40
text_padding_y_top = 20
text_height = 80
output_w = img_w + 2 * text_padding_x
output_h = img_h + text_padding_y_top + text_height

# Create output canvas (white background)
canvas = Image.new("RGBA", (output_w, output_h), (255, 255, 255, 255))
draw = ImageDraw.Draw(canvas)

# Try to find a Chinese-supporting font
font_sizes = {
    "example_num": 28,
    "example_text": 24,
}

# Font search for Chinese text support
import subprocess
try:
    result = subprocess.run(
        ["where", "fonts"],
        capture_output=True, text=True, timeout=5
    )
except:
    result = None

# Try common Chinese font paths on Windows
font_paths = [
    # Common Microsoft Chinese fonts
    r"C:\Windows\Fonts\simhei.ttf",          # SimHei (黑体)
    r"C:\Windows\Fonts\simsun.ttc",          # SimSun (宋体)
    r"C:\Windows\Fonts\msyh.ttc",            # Microsoft YaHei (微软雅黑)
    r"C:\Windows\Fonts\msyhbd.ttc",          # Microsoft YaHei Bold
    r"C:\Windows\Fonts\simkai.ttf",          # KaiTi (楷体)
    # Fallback: any available font
    r"C:\Windows\Fonts\arial.ttf",
]

chinese_font = None
for fp in font_paths:
    try:
        chinese_font = ImageFont.truetype(fp, font_sizes["example_text"])
        print(f"Loaded font: {fp}")
        break
    except:
        continue

if chinese_font is None:
    # Last resort: try TrueFont with a size
    try:
        chinese_font = ImageFont.truetype("C:\\Windows\\Fonts\\msyh.ttc", font_sizes["example_text"])
        print("Loaded msyh.ttc with TrueFont")
    except:
        chinese_font = ImageFont.load_default()
        print("Using default font (Chinese may not render correctly)")

# Example text
example_title = "【例 5】数一数，需要多少块砖才能把坏了的墙补好?"

# Measure text to center it
bbox = draw.textbbox((0, 0), example_title, font=chinese_font)
text_w = bbox[2] - bbox[0]
text_h = bbox[3] - bbox[1]
text_x = (output_w - text_w) // 2
text_y = text_padding_y_top + (text_height - text_h) // 2

# Draw text with shadow for better readability
shadow_offset = 2
draw.text((text_x + shadow_offset, text_y + shadow_offset), example_title, font=chinese_font, fill=(0, 0, 0, 180))
draw.text((text_x, text_y), example_title, font=chinese_font, fill=(0, 0, 0, 255))

# Paste the brick wall image below the text
canvas.paste(img, (text_padding_x, text_padding_y_top + text_height), img)

# Convert to RGB for JPEG saving
jpeg_canvas = canvas.convert("RGB")
jpeg_canvas.save(out_path, "JPEG", quality=95)
print(f"Saved: {out_path}")
print(f"Output size: {output_w}x{output_h}")
