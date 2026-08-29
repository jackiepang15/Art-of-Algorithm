import os
from PIL import Image, ImageDraw, ImageFont

# Paths
md_dir = r'D:\Jackie\Art\wiki\3_Work_Experience\3_3_Study_Notes'
wall_img_path = os.path.join(md_dir, 'images', 'math_1_3', '7c80905e8e4cd4636f839fb7251b9627eff052d83397b2ceff444f884a7d0d78.jpg')
output_path = os.path.join(md_dir, 'life_math_1_example5_v2.jpg')

# Load the wall image
wall_img = Image.open(wall_img_path)
wall_width, wall_height = wall_img.size

# Set up fonts
# Try to find a Chinese font
font_paths = [
    r'C:\Windows\Fonts\msyh.ttc',      # Microsoft YaHei
    r'C:\Windows\Fonts\simhei.ttf',    # SimHei
    r'C:\Windows\Fonts\simsun.ttc',    # SimSun
    r'C:\Windows\Fonts\simkai.ttf',    # KaiTi
]

font = None
for fp in font_paths:
    if os.path.exists(fp):
        try:
            font = ImageFont.truetype(fp, 28)
            break
        except Exception:
            continue

if font is None:
    font = ImageFont.load_default()

# Title text
title_text = '【例 5】'
question_text = '数一数，需要多少块砖才能把坏了的墙补好?'

# Calculate text dimensions by creating a temporary image
temp_img = Image.new('RGB', (1, 1))
draw = ImageDraw.Draw(temp_img)

# Measure title
title_bbox = draw.textbbox((0, 0), title_text, font=font)
title_width = title_bbox[2] - title_bbox[0]
title_height = title_bbox[3] - title_bbox[1]

# Measure question question
question_bbox = draw.textbbox((0, 0), question_text, font=font)
question_width = question_bbox[2] - question_bbox[0]
question_height = question_bbox[3] - question_bbox[1]

max_text_width = max(title_width, question_width)

# Set margins
margin_top = 40
margin_bottom = 40
margin_side = 40
text_spacing = 15

# Calculate total image size
total_text_height = title_height + question_height + text_spacing
img_width = max(wall_width, max_text_width) + 2 * margin_side
img_height = margin_top + total_text_height + 20 + wall_height + margin_bottom

# Create the final image
result_img = Image.new('RGB', (img_width, img_height), 'white')
draw = ImageDraw.Draw(result_img)

# Draw title (centered)
title_x = (img_width - title_width) // 2
draw.text((title_x, margin_top), title_text, font=font, fill='black')

# Draw question (centered)
question_y = margin_top + title_height + text_spacing
question_x = (img_width - question_width) // 2
draw.text((question_x, question_y), question_text, font=font, fill='black')

# Draw wall image
wall_x = (img_width - wall_width) // 2
wall_y = question_y + question_height + 20
result_img.paste(wall_img, (wall_x, wall_y))

# Save as JPEG
result_img.save(output_path, 'JPEG', quality=95)
print(f'Generated image: {output_path}')
print(f'Size: {result_img.size}')
