#!/usr/bin/env python3
"""
Sudoku Image Solver

This script reads an image file that contains a Sudoku puzzle, detects the board,
extracts the digits from each cell, solves the puzzle with a backtracking algorithm,
and prints the final solved board.

Usage:
    python sudoku_image_solver.py path/to/sudoku_image.png
    python sudoku_image_solver.py path/to/sudoku_image.png --show
    python sudoku_image_solver.py path/to/sudoku_image.png --ocr-engine paddle

Digit recognition engines:
    auto       Prefer PaddleOCR-VL-1.6 and fall back to Tesseract (default)
    paddle     Use PaddleOCR-VL-1.6 only
    tesseract  Use Tesseract only (fastest; in-process via tesserocr if installed)

Required Python packages:
    pip install opencv-python numpy pytesseract python-dotenv

Recommended for speed (in-process Tesseract, avoids one process per cell):
    pip install tesserocr

Optional PaddleOCR-VL-1.6 support (requires Python 3.8-3.13, not 3.14):
    pip install paddleocr paddlepaddle

Important:
    Tesseract OCR must be installed and available in the system PATH.
    Download it from: https://github.com/tesseract-ocr/tesseract

English comments are included throughout the code for easier maintenance.
"""

import argparse
import os
import sys
from pathlib import Path

import cv2
import numpy as np
from dotenv import load_dotenv

try:
    import pytesseract
except ImportError as exc:
    raise SystemExit(
        "Missing dependency: pytesseract. Install it with: pip install pytesseract"
    ) from exc

try:
    import tesserocr as _tesserocr
except ImportError:
    # Optional: in-process Tesseract avoids a process/model load per cell.
    _tesserocr = None


load_dotenv(Path(__file__).resolve().with_name(".env"))


def find_tesseract_executable():
    """Resolve the Tesseract binary from environment settings or common install paths."""
    candidates = []

    configured = os.getenv("TESSERACT_CMD")
    if configured:
        candidates.append(configured)

    candidates.extend(
        [
            r"C:\Program Files\Tesseract-OCR\tesseract.exe",
            r"C:\Program Files (x86)\Tesseract-OCR\tesseract.exe",
            r"D:\portable\msys64\usr\bin\tesseract.exe",
            r"D:\portable\msys64\ucrt64\bin\tesseract.exe",
            "/usr/bin/tesseract",
            "/usr/local/bin/tesseract",
        ]
    )

    for candidate in candidates:
        path = Path(candidate).expanduser()
        if path.exists() and path.is_file():
            return str(path)

    return None


tesseract_cmd = find_tesseract_executable()
if tesseract_cmd is not None:
    pytesseract.pytesseract.tesseract_cmd = tesseract_cmd


def find_board_contour(image: np.ndarray):
    """Find the largest quadrilateral contour that looks like the Sudoku board."""
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5, 5), 0)
    edged = cv2.Canny(blur, 50, 150)

    contours, _ = cv2.findContours(edged, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    contours = sorted(contours, key=cv2.contourArea, reverse=True)

    for contour in contours[:10]:
        perimeter = cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, 0.02 * perimeter, True)
        if len(approx) == 4:
            return approx

    return None


def four_point_transform(image: np.ndarray, contour):
    """Warp the detected board into a top-down view."""
    points = contour.reshape(4, 2)
    rect = np.zeros((4, 2), dtype="float32")

    s = points.sum(axis=1)
    rect[0] = points[np.argmin(s)]
    rect[2] = points[np.argmax(s)]

    diff = np.diff(points, axis=1)
    rect[1] = points[np.argmin(diff)]
    rect[3] = points[np.argmax(diff)]

    (tl, tr, br, bl) = rect
    width_top = np.linalg.norm(tr - tl)
    width_bottom = np.linalg.norm(br - bl)
    height_left = np.linalg.norm(bl - tl)
    height_right = np.linalg.norm(br - tr)

    max_width = max(int(width_top), int(width_bottom))
    max_height = max(int(height_left), int(height_right))

    destination = np.array(
        [
            [0, 0],
            [max_width - 1, 0],
            [max_width - 1, max_height - 1],
            [0, max_height - 1],
        ],
        dtype="float32",
    )

    matrix = cv2.getPerspectiveTransform(rect, destination)
    warped = cv2.warpPerspective(image, matrix, (max_width, max_height))
    return warped


def extract_digit_mask(cell: np.ndarray):
    """Return a cleaned, black-on-white image of the digit, or None if empty."""
    gray = cv2.cvtColor(cell, cv2.COLOR_BGR2GRAY)
    height, width = gray.shape
    if height < 10 or width < 10:
        return None

    # Remove a thin border so the cell's grid lines do not reach the digit.
    margin = max(2, int(round(0.06 * min(height, width))))
    inner = gray[margin:height - margin, margin:width - margin]
    if inner.size == 0:
        return None

    blurred = cv2.GaussianBlur(inner, (3, 3), 0)

    # Threshold into "bright" pixels, then decide which side is the background.
    # Most cells have dark digits on a light background, but highlighted cells can
    # hold light digits on a dark (for example blue) background.
    threshold, bright = cv2.threshold(
        blurred, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU
    )
    background = int(np.bincount(blurred.ravel()).argmax())
    ink = cv2.bitwise_not(bright) if background > threshold else bright
    ink = cv2.morphologyEx(ink, cv2.MORPH_CLOSE, np.ones((3, 3), np.uint8))

    # Drop grid-line remnants (components touching the border) and small specks.
    count, labels, stats, _ = cv2.connectedComponentsWithStats(ink, connectivity=8)
    ink_height, ink_width = ink.shape
    min_area = max(20, int(0.004 * ink_height * ink_width))
    cleaned = np.zeros_like(ink)
    for index in range(1, count):
        x, y, box_width, box_height, area = stats[index]
        touches_border = (
            x <= 1
            or y <= 1
            or x + box_width >= ink_width - 1
            or y + box_height >= ink_height - 1
        )
        if touches_border or area < min_area:
            continue
        cleaned[labels == index] = 255

    ys, xs = np.nonzero(cleaned)
    if len(xs) == 0:
        return None

    # Crop tightly to the ink and put it on a padded white canvas for OCR.
    digit = 255 - cleaned[ys.min():ys.max() + 1, xs.min():xs.max() + 1]
    padding = max(4, int(0.35 * max(digit.shape)))
    return cv2.copyMakeBorder(
        digit, padding, padding, padding, padding, cv2.BORDER_CONSTANT, value=255
    )


def ocr_digit(digit_image: np.ndarray, config: str):
    """Return (digits, confidence) for the most confident digit token found."""
    data = pytesseract.image_to_data(
        digit_image, config=config, output_type=pytesseract.Output.DICT
    )
    best_digits = ""
    best_confidence = -1.0
    for text, confidence in zip(data["text"], data["conf"]):
        digits = "".join(ch for ch in text.strip() if ch.isdigit())
        try:
            score = float(confidence)
        except (TypeError, ValueError):
            continue
        if digits and score > best_confidence:
            best_digits, best_confidence = digits, score
    return best_digits, best_confidence


def disambiguate_one_seven(digit: int, digit_image: np.ndarray) -> int:
    """Resolve a 1/7 confusion from the glyph shape.

    A printed 7 starts with a top bar that spans nearly the full glyph width,
    while a 1 has a short flag in the upper right and its leftmost ink lies below
    the top edge. Only override OCR when the shape is clearly one of the two.
    """
    if digit not in (1, 7):
        return digit

    ys, xs = np.nonzero(255 - digit_image)
    if len(xs) == 0:
        return digit

    x0, x1 = xs.min(), xs.max()
    y0, y1 = ys.min(), ys.max()
    width = x1 - x0 + 1
    height = y1 - y0 + 1
    if width < 3 or height < 3:
        return digit

    ys = ys - y0
    xs = xs - x0

    top_band = ys <= max(1, int(0.03 * height))
    if not top_band.any():
        return digit
    top_left = xs[top_band].min() / (width - 1)

    top_run = 0.0
    for row in range(max(1, int(0.05 * height))):
        row_xs = xs[ys == row]
        if len(row_xs):
            top_run = max(top_run, (row_xs.max() - row_xs.min() + 1) / width)

    # Full-width top bar with ink at the top-left corner: it is a 7.
    if top_left <= 0.15 and top_run >= 0.8:
        return 7
    # Short flag in the upper right, leftmost ink below the top: it is a 1.
    if top_left >= 0.45 and top_run <= 0.7:
        return 1
    return digit


class TesseractDigitReader:
    """Recognize a single cell digit with Tesseract."""

    # Tesseract 5 is inconsistent here: the whitelist helps with most digits but
    # sometimes suppresses a valid 9, and single-character mode (psm 10) can
    # return nothing or a low-confidence result for a clear 4. Try the modes in
    # order and keep the first confident digit.
    _CONFIGS = (
        "--psm 10 --oem 3 -c tessedit_char_whitelist=123456789",
        "--psm 8 --oem 3 -c tessedit_char_whitelist=123456789",
        "--psm 10 --oem 3",
        "--psm 8 --oem 3",
    )

    def read(self, digit_image: np.ndarray) -> int:
        image = cv2.resize(digit_image, (64, 64), interpolation=cv2.INTER_AREA)
        for config in self._CONFIGS:
            digits, confidence = ocr_digit(image, config)
            if digits and confidence >= 50:
                return int(digits[0])
        return 0


class TesserocrDigitReader:
    """Fast in-process Tesseract backend: one engine load for all cells."""

    # (page segmentation mode, use character whitelist)
    _CONFIGS = ((10, True), (8, True), (10, False), (8, False))

    def __init__(self):
        from PIL import Image
        from tesserocr import OEM, PSM, PyTessBaseAPI

        options = {"psm": PSM.SINGLE_CHAR, "oem": OEM.LSTM_ONLY, "lang": "eng"}
        tessdata = os.getenv("TESSDATA_PREFIX")
        if tessdata:
            options["path"] = tessdata

        self._image = Image
        self._psm = PSM
        self._api = PyTessBaseAPI(**options)

    def read(self, digit_image: np.ndarray) -> int:
        image = self._image.fromarray(
            cv2.resize(digit_image, (64, 64), interpolation=cv2.INTER_AREA)
        )
        modes = {10: self._psm.SINGLE_CHAR, 8: self._psm.SINGLE_WORD}

        for psm_value, use_whitelist in self._CONFIGS:
            self._api.SetPageSegMode(modes[psm_value])
            self._api.SetVariable(
                "tessedit_char_whitelist", "123456789" if use_whitelist else ""
            )
            self._api.SetImage(image)
            text = self._api.GetUTF8Text()
            digits = "".join(ch for ch in text if ch.isdigit())
            if digits and self._api.MeanTextConf() >= 50:
                return int(digits[0])
        return 0


class PaddleVLDigitReader:
    """Recognize a single cell digit with PaddleOCR-VL (pipeline version 1.6)."""

    def __init__(self, device=None, pipeline_version="v1.6"):
        self._device = device
        self._pipeline_version = pipeline_version
        self._pipeline = None

    def ensure_ready(self):
        """Import PaddleOCR and create its pipeline on first use."""
        if self._pipeline is not None:
            return

        try:
            from paddleocr import PaddleOCRVL
        except ImportError as exc:
            raise RuntimeError(
                "PaddleOCR-VL is not installed. Install it with "
                "`pip install paddleocr paddlepaddle` in a Python 3.8-3.13 "
                "environment (PaddlePaddle has no Python 3.14 wheels)."
            ) from exc

        options = {"pipeline_version": self._pipeline_version}
        if self._device:
            options["device"] = self._device
        try:
            self._pipeline = PaddleOCRVL(**options)
        except Exception as exc:
            raise RuntimeError(f"Could not initialize PaddleOCR-VL: {exc}") from exc

    def read(self, digit_image: np.ndarray) -> int:
        self.ensure_ready()
        image = cv2.resize(digit_image, (224, 224), interpolation=cv2.INTER_CUBIC)
        image = cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)

        results = self._pipeline.predict(
            image,
            use_doc_orientation_classify=False,
            use_doc_unwarping=False,
            use_layout_detection=False,
            use_chart_recognition=False,
            use_seal_recognition=False,
            prompt_label="ocr",
        )
        text = "".join(self._block_text(result) for result in results)
        digits = "".join(ch for ch in text if ch.isdigit())
        return int(digits[0]) if digits else 0

    @staticmethod
    def _block_text(result) -> str:
        """Collect recognized text from a PaddleOCR-VL result object."""
        blocks = None
        try:
            blocks = result["parsing_res_list"]
        except (KeyError, TypeError):
            pass

        if blocks is None:
            data = getattr(result, "json", None)
            if callable(data):
                data = data()
            if isinstance(data, dict):
                data = data.get("res", data)
                if isinstance(data, dict):
                    blocks = data.get("parsing_res_list")

        parts = []
        for block in blocks or []:
            content = getattr(block, "content", None)
            if content is None and isinstance(block, dict):
                content = block.get("block_content")
            if content:
                parts.append(str(content))
        return "\n".join(parts)


class FallbackDigitReader:
    """Try the preferred reader first and fall back to another one."""

    def __init__(self, primary, fallback):
        self._primary = primary
        self._fallback = fallback
        self._primary_failed = False

    def read(self, digit_image: np.ndarray) -> int:
        if not self._primary_failed:
            try:
                digit = self._primary.read(digit_image)
                if digit:
                    return digit
            except Exception as exc:
                self._primary_failed = True
                print(
                    f"Warning: PaddleOCR-VL unavailable ({exc}); using Tesseract OCR.",
                    file=sys.stderr,
                )
        return self._fallback.read(digit_image)


def create_tesseract_reader():
    """Use in-process Tesseract when available, else fall back to pytesseract."""
    if _tesserocr is not None:
        try:
            return TesserocrDigitReader()
        except Exception as exc:
            print(
                f"Warning: tesserocr unavailable ({exc}); using pytesseract.",
                file=sys.stderr,
            )
    return TesseractDigitReader()


def build_digit_reader(engine_name: str, paddle_device=None):
    """Create the digit reader selected on the command line."""
    tesseract_reader = create_tesseract_reader()
    if engine_name == "tesseract":
        return tesseract_reader

    paddle_reader = PaddleVLDigitReader(device=paddle_device)
    if engine_name == "paddle":
        return paddle_reader
    return FallbackDigitReader(paddle_reader, tesseract_reader)


def read_cell_digit(cell: np.ndarray, digit_reader) -> int:
    """Return the digit in a cell. Empty cells return 0."""
    digit_image = extract_digit_mask(cell)
    if digit_image is None:
        return 0
    digit = digit_reader.read(digit_image)
    return disambiguate_one_seven(digit, digit_image)


def extract_board(image_path: str, digit_reader):
    """Detect the board and extract a 9x9 grid as a numeric matrix."""
    image = cv2.imread(image_path)
    if image is None:
        raise FileNotFoundError(f"Could not read image: {image_path}")

    board_contour = find_board_contour(image)
    if board_contour is None:
        raise ValueError(
            "No Sudoku board was detected. Please provide a clear image with a visible 9x9 grid."
        )

    warped = four_point_transform(image, board_contour)
    height, width = warped.shape[:2]
    cell_size = min(height, width) / 9

    board = np.zeros((9, 9), dtype=int)
    for row in range(9):
        for col in range(9):
            y_start = int(row * cell_size)
            y_end = int((row + 1) * cell_size)
            x_start = int(col * cell_size)
            x_end = int((col + 1) * cell_size)

            cell_crop = warped[y_start:y_end, x_start:x_end]
            digit = read_cell_digit(cell_crop, digit_reader)
            board[row][col] = digit

    return board


def is_valid(board: np.ndarray, row: int, col: int, num: int):
    """Check whether placing num at (row, col) is legal in the current Sudoku board."""
    for i in range(9):
        if board[row][i] == num and i != col:
            return False
        if board[i][col] == num and i != row:
            return False

    start_row = (row // 3) * 3
    start_col = (col // 3) * 3
    for i in range(start_row, start_row + 3):
        for j in range(start_col, start_col + 3):
            if board[i][j] == num and (i, j) != (row, col):
                return False
    return True


def find_empty_location(board: np.ndarray):
    """Return the next empty cell or None when the board is complete."""
    for row in range(9):
        for col in range(9):
            if board[row][col] == 0:
                return row, col
    return None


def solve_sudoku(board: np.ndarray):
    """Solve the board with constraint bitmasks and a minimum-candidates heuristic."""
    all_digits = (1 << 9) - 1
    rows = [0] * 9
    cols = [0] * 9
    boxes = [0] * 9

    for row in range(9):
        for col in range(9):
            value = int(board[row][col])
            if value:
                bit = 1 << (value - 1)
                rows[row] |= bit
                cols[col] |= bit
                boxes[(row // 3) * 3 + col // 3] |= bit

    def search():
        best_row = best_col = -1
        best_options = 0
        best_count = 10

        # Pick the empty cell with the fewest legal candidates (MRV).
        for row in range(9):
            for col in range(9):
                if board[row][col] != 0:
                    continue
                box = (row // 3) * 3 + col // 3
                options = all_digits & ~(rows[row] | cols[col] | boxes[box])
                count = options.bit_count()
                if count == 0:
                    return False
                if count < best_count:
                    best_count = count
                    best_row, best_col, best_options = row, col, options
                    if count == 1:
                        break
            if best_count == 1:
                break

        if best_row == -1:
            return True

        box = (best_row // 3) * 3 + best_col // 3
        while best_options:
            bit = best_options & -best_options
            best_options &= ~bit
            value = bit.bit_length()

            board[best_row][best_col] = value
            rows[best_row] |= bit
            cols[best_col] |= bit
            boxes[box] |= bit

            if search():
                return True

            board[best_row][best_col] = 0
            rows[best_row] &= ~bit
            cols[best_col] &= ~bit
            boxes[box] &= ~bit

        return False

    return search()


def print_board(board: np.ndarray):
    """Print a nicely formatted 9x9 board."""
    for row in range(9):
        if row % 3 == 0 and row != 0:
            print("-" * 21)
        line = []
        for col in range(9):
            if col % 3 == 0 and col != 0:
                line.append(" | ")
            line.append(str(board[row][col]))
        print(" ".join(line))


def main():
    """Command-line entry point."""
    parser = argparse.ArgumentParser(description="Solve a Sudoku puzzle from an image file.")
    parser.add_argument("image_path", help="Path to the Sudoku image file.")
    parser.add_argument(
        "--show",
        action="store_true",
        help="Show the detected board image in a window after reading it.",
    )
    parser.add_argument(
        "--ocr-engine",
        choices=("auto", "paddle", "tesseract"),
        default="auto",
        help=(
            "Digit recognition engine (default: auto). 'auto' prefers "
            "PaddleOCR-VL-1.6 and falls back to Tesseract."
        ),
    )
    parser.add_argument(
        "--paddle-device",
        default=None,
        help="Device for PaddleOCR-VL, for example cpu or gpu:0 (default: automatic).",
    )
    args = parser.parse_args()

    image_path = Path(args.image_path)
    if not image_path.exists():
        print(f"Error: file not found: {image_path}", file=sys.stderr)
        print("Usage: python sudoku_image_solver.py path/to/sudoku_image.png", file=sys.stderr)
        raise SystemExit(1)

    if args.ocr_engine != "paddle" and tesseract_cmd is None:
        print(
            "Tesseract OCR is not available. Set TESSERACT_CMD in .env or install Tesseract first.",
            file=sys.stderr,
        )
        raise SystemExit(1)

    digit_reader = build_digit_reader(args.ocr_engine, args.paddle_device)
    if args.ocr_engine == "paddle":
        try:
            digit_reader.ensure_ready()
        except RuntimeError as exc:
            print(f"Error: {exc}", file=sys.stderr)
            raise SystemExit(1)

    try:
        board = extract_board(str(image_path), digit_reader)
    except Exception as exc:
        print(f"Error while parsing the Sudoku image: {exc}", file=sys.stderr)
        print("Tips:", file=sys.stderr)
        print("  1. Use a high-contrast image with a clear 9x9 Sudoku grid.", file=sys.stderr)
        print("  2. Keep the board nearly rectangular and without heavy shadows.", file=sys.stderr)
        print("  3. Make sure the puzzle digits are clearly visible.", file=sys.stderr)
        raise SystemExit(1)

    print("Original board:")
    print_board(board)

    if not solve_sudoku(board):
        print("No valid solution was found for this puzzle.", file=sys.stderr)
        raise SystemExit(1)

    print("\nSolved board:")
    print_board(board)

    if args.show:
        image = cv2.imread(str(image_path))
        if image is not None:
            cv2.imshow("Detected Sudoku", image)
            cv2.waitKey(0)
            cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
