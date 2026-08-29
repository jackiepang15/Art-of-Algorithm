import re
import argparse
from bs4 import BeautifulSoup


def clean_markdown_file(input_path: str, output_path: str, tags_to_remove: list):
    """Removes specified HTML tags and their inner contents from a Markdown file

    without corrupting any LaTeX math formulas.
    """
    with open(input_path, "r", encoding="utf-8") as f:
        md_content = f.read()

    # --- STEP 1: Protect Math Formulas ---
    # Regular expression to catch $$ blocks, $ blocks, and \begin{env}...\end{env} blocks
    math_pattern = re.compile(
        r"(\$\$.*?\$\$|\$.*?\$|\\begin\{[a-zA-Z\*]+\}.*?\\end\{[a-zA-Z\*]+\})",
        re.DOTALL,
    )

    math_blocks = []

    def save_math(match):
        # Store the formula text and replace it with a unique placeholder
        math_blocks.append(match.group(1))
        return f"__MATH_BLOCK_PLACEHOLDER_{len(math_blocks) - 1}__"

    # Swap out formulas temporarily
    protected_content = math_pattern.sub(save_math, md_content)

    # --- STEP 2: Use BeautifulSoup to Erase Targeted HTML Tags ---
    # We use 'html.parser' which handles multi-line blocks and Chinese characters smoothly
    soup = BeautifulSoup(protected_content, "html.parser")

    for tag_name in tags_to_remove:
        for tag in soup.find_all(tag_name):
            # .decompose() deletes the tag AND everything nested inside it
            tag.decompose()

    # Convert back to a clean string
    cleaned_content = str(soup)

    # --- STEP 3: Restore Math Formulas ---
    def restore_math(match):
        index = int(match.group(1))
        return math_blocks[index]

    restored_content = re.sub(
        r"__MATH_BLOCK_PLACEHOLDER_(\d+)__", restore_math, cleaned_content
    )

    # --- STEP 4: Write Out Cleaned Content ---
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(restored_content)

    print(
        f"✓ Successfully processed! Removed {tags_to_remove} from {input_path} -> {output_path}"
    )


# ==========================================
# COMMAND LINE INTERFACE
# ==========================================
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Remove specified HTML tags from Markdown files without corrupting LaTeX formulas."
    )
    parser.add_argument("--input_path", help="Path to the input Markdown file")
    parser.add_argument(
        "--output_path", help="Path to the output cleaned Markdown file"
    )
    parser.add_argument(
        "--tags",
        type=str,
        default="details,summary,div,p",
        help="Comma-separated list of HTML tags to remove (default: details,summary,div,p)",
    )

    args, _ = parser.parse_known_args()

    # Parse tags from comma-separated string
    tags_to_remove = [tag.strip() for tag in args.tags.split(",")]

    # Run the cleaning function
    clean_markdown_file(
        input_path=args.input_path,
        output_path=args.output_path,
        tags_to_remove=tags_to_remove,
    )
