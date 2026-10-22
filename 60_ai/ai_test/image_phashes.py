"""Generate perceptual hashes for images and save them to a JSON file.

Requirements:
    Install imagededup in the active Python environment:
    python -m pip install imagededup
    HEIC/HEIF images additionally require pillow-heif:
    python -m pip install pillow-heif

Usage:
    # Recursively process all images in a directory.
    python image_phashes.py -i path/to/images -o phashes.json

    # Process several individual images and a directory together.
    python image_phashes.py -i image1.jpg image2.png path/to/images -o phashes.json

Each JSON record contains an absolute ``image_path`` and its ``phash`` string.
Use ``python image_phashes.py --help`` for all available command-line options.
"""

import argparse
import json
import logging
from pathlib import Path


LOGGER = logging.getLogger("image_phashes")
IMAGE_EXTENSIONS = {
    ".bmp",
    ".gif",
    ".heic",
    ".heif",
    ".jpeg",
    ".jpg",
    ".png",
    ".tif",
    ".tiff",
    ".webp",
}


def parse_args():
    parser = argparse.ArgumentParser(
        description="Generate image perceptual hashes and save them as JSON."
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
        "--debug",
        action="store_true",
        help="Enable detailed debug logging.",
    )
    return parser.parse_args()


def collect_images(inputs):
    """Resolve image files from explicit paths and recursively scanned directories."""
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
    """Register the optional Pillow decoder when HEIC/HEIF images are present."""
    heif_images = [image for image in images if image.suffix.lower() in {".heic", ".heif"}]
    if not heif_images:
        return

    try:
        from pillow_heif import register_heif_opener
    except ImportError as error:
        raise RuntimeError(
            f"Cannot read HEIC/HEIF image: {heif_images[0]}. Install the decoder with: "
            "python -m pip install pillow-heif"
        ) from error

    register_heif_opener()


def main():
    args = parse_args()
    logging.basicConfig(
        level=logging.DEBUG if args.debug else logging.INFO,
        format="%(asctime)s %(levelname)s: %(message)s",
    )

    try:
        # Import lazily so --help remains available even before installing imagededup.
        try:
            from imagededup.methods import PHash
        except ImportError as error:
            raise RuntimeError(
                "imagededup is required. Install it with: "
                "python -m pip install imagededup"
            ) from error

        images = collect_images(args.input)
        validate_image_support(images)
        LOGGER.info("Found %d image(s).", len(images))

        # Disable the library's progress bar because this script logs each image itself.
        phasher = PHash(verbose=False)
        results = []
        for image_path in images:
            LOGGER.debug("Encoding %s", image_path)
            if image_path.suffix.lower() in {".heic", ".heif"}:
                # imagededup rejects HEIF in its file loader; give it decoded RGB pixels instead.
                import numpy as np
                from PIL import Image

                with Image.open(image_path) as image:
                    image_array = np.asarray(image.convert("RGB"))
                image_hash = phasher.encode_image(image_array=image_array)
            else:
                image_hash = phasher.encode_image(image_file=str(image_path))
            if image_hash is None:
                LOGGER.warning("Could not generate a hash for %s; skipping.", image_path)
                continue
            results.append({"image_path": str(image_path), "phash": image_hash})

        if not results:
            raise ValueError("No perceptual hashes could be generated.")

        args.output.parent.mkdir(parents=True, exist_ok=True)
        with args.output.open("w", encoding="utf-8") as output_file:
            json.dump(results, output_file, ensure_ascii=False, indent=2)
            output_file.write("\n")

        LOGGER.info("Wrote %d perceptual hash(es) to %s.", len(results), args.output.resolve())
        return 0
    except Exception:
        LOGGER.exception("Failed to generate image perceptual hashes.")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())