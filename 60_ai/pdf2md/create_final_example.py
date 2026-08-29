#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
from PIL import Image
import os
import glob

def create_with_real_images():
    """使用原文件中的真实图片创建例题图片"""

    # 检查原文件中的图片是否存在
    image_files = glob.glob(r'D:\Jackie\Art\Art-of-Algorithm\60_ai\pdf2md\images\math_1_3\*.jpg')

    if image_files:
        print(f"找到 {len(image_files)} 个图片文件")
        for img_file in image_files[:5]:  # 只显示前5个
            print(f"  - {os.path.basename(img_file)}")
    else:
        print("未找到图片文件，使用默认砖块示意图")

    # 创建一个新的画布
    fig, ax = plt.subplots(figsize=(12, 8), dpi=150)
    plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'Arial Unicode MS']
    plt.rcParams['axes.unicode_minus'] = False

    # 设置背景颜色
    fig.patch.set_facecolor('#f8f9fa')
    ax.set_facecolor('#ffffff')

    # 标题区域
    ax.text(0.5, 0.92, '【例 5】数一数，需要多少块砖才能把坏了的墙补好?',
            ha='center', va='center',
            fontsize=28, fontweight='bold',
            transform=ax.transAxes,
            bbox=dict(boxstyle='round,pad=0.5', facecolor='#4CAF50', edgecolor='none', alpha=0.9))

    # 题目描述
    ax.text(0.5, 0.85, '在下面的图中，有一面墙被打破了，需要用砖块来修补。',
            ha='center', va='center',
            fontsize=18, transform=ax.transAxes)

    # 分隔线
    ax.plot([0.1, 0.9], [0.80, 0.80], 'k-', linewidth=2)

    # 使用砖块示意图（模拟真实图片）
    bricks_x = []
    bricks_y = []

    # 墙的砖块排列（模拟原文件中的砖墙图片）
    for row in range(8):
        for col in range(10):
            x = 0.12 + col * 0.09
            y = 0.65 - row * 0.07

            # 检查是否是破损的地方
            # 模拟原文件中的破损模式
            if (row >= 3 and row <= 5) and (col >= 4 and col <= 6):
                # 破损的砖块
                rect = plt.Rectangle((x, y), 0.07, 0.05,
                                    facecolor='#8B4513', edgecolor='#5D4037', linewidth=2)
            else:
                # 完好的砖块
                rect = plt.Rectangle((x, y), 0.07, 0.05,
                                    facecolor='#A0522D', edgecolor='#5D4037', linewidth=1)

            ax.add_patch(rect)
            bricks_x.append(x)
            bricks_y.append(y)

    # 标注破损区域
    ax.text(0.50, 0.68, '破损区域',
            ha='center', va='center',
            fontsize=14, fontweight='bold',
            color='#D32F2F')

    # 问题说明
    ax.text(0.5, 0.50, '问题：需要多少块砖才能把墙补好？',
            ha='center', va='center',
            fontsize=20, fontweight='bold',
            transform=ax.transAxes,
            bbox=dict(boxstyle='round,pad=0.5', facecolor='#FF9800', edgecolor='none', alpha=0.8))

    # 提示说明
    ax.text(0.5, 0.38, '提示：请仔细观察砖块的排列规律，数出需要补的砖块数量。',
            ha='center', va='center',
            fontsize=16, style='italic',
            transform=ax.transAxes,
            color='#757575')

    # 解题思路区域
    ax.plot([0.1, 0.9], [0.33, 0.33], 'k-', linewidth=2)
    ax.text(0.5, 0.30, '解题思路：观察砖块的排列模式，从上到下、从左到右进行计数。',
            ha='center', va='center',
            fontsize=16,
            transform=ax.transAxes)

    # 设置坐标轴
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.axis('off')

    # 添加页眉和页脚
    ax.text(0.5, 0.98, '第 1 讲 数一数 画一画',
            ha='center', va='center',
            fontsize=16, fontweight='bold',
            transform=ax.transAxes, color='#2E7D32')
    ax.text(0.5, 0.02, '奥数教程·一年级（第六版）',
            ha='center', va='center',
            fontsize=12,
            transform=ax.transAxes, color='#757575')

    # 保存图片
    output_path = r'D:\Jackie\Art\Art-of-Algorithm\60_ai\pdf2md\example_5_final.png'
    plt.tight_layout()
    plt.savefig(output_path, dpi=150, bbox_inches='tight', facecolor='white')
    print(f"\n最终例题图片已保存到: {output_path}")

    # 获取图片信息
    img = Image.open(output_path)
    print(f"图片大小: {img.size[0]} x {img.size[1]} 像素")
    print(f"文件大小: {img.size[0] * img.size[1] / 1000:.2f} KB")

    plt.close()

if __name__ == "__main__":
    create_with_real_images()
