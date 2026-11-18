# Sudoku Image Solver

This folder includes a Python utility that detects a Sudoku board from an image, extracts the numbers, solves the puzzle, and prints the final result.

## File

- `sudoku_image_solver.py`

## Requirements

Install the required packages:

```bash
pip install opencv-python numpy pytesseract
```

Also install Tesseract OCR and make sure the `tesseract` command is available in your PATH.

- Windows: https://github.com/UB-Mannheim/tesseract/wiki
- macOS: `brew install tesseract`
- Linux: `sudo apt-get install tesseract-ocr`

## Usage

```bash
python sudoku_image_solver.py path/to/your_sudoku_image.png
```

Optional debug window:

```bash
python sudoku_image_solver.py path/to/your_sudoku_image.png --show
```

## Notes

- The image should contain a clear, nearly rectangular Sudoku grid.
- A straight-on photo with good contrast produces the best result.
- If the board is not detected well, try cropping the image or improving the contrast before running the script.

## Example output

```text
Original board:
5 3 0 | 0 7 0 | 0 0 0
6 0 0 | 1 9 5 | 0 0 0
0 9 8 | 0 0 0 | 0 6 0
...

Solved board:
5 3 4 | 6 7 8 | 9 1 2
6 7 2 | 1 9 5 | 3 4 8
1 9 8 | 3 4 2 | 5 6 7
...
```
