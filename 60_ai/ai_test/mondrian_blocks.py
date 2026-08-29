from itertools import product

# Board: 8x8, rows 0-7, cols 0-7 (display as 1-indexed)
obstacles = set([
    (3, 0), (3, 1),       # row 4, cols 1-2
    (4, 2),               # row 5, col 3
    (5, 7), (6, 7), (7, 7),  # rows 6-8, col 8
])

pieces = [
    ("B", 4, 3),    # blue 4x3
    ("W", 5, 2),    # white 5x2
    ("w", 4, 2),    # white 4x2
    ("n", 3, 2),    # white 3x2
    ("R", 3, 3),    # red 3x3
    ("r", 2, 2),    # red 2x2
    ("Y", 5, 1),    # yellow 5x1
    ("y", 4, 1),    # yellow 4x1
]

total_area = sum(r*c for _,r,c in pieces)
print(f"Pieces: {total_area}, Obstacles: {len(obstacles)}, Free: {64-len(obstacles)}")

def solve(board, idx, solutions, limit=10):
    if len(solutions) >= limit:
        return
    if idx == len(pieces):
        # Check all non-obstacle cells are filled
        for r in range(8):
            for c in range(8):
                if (r,c) not in obstacles and board[r][c] == 0:
                    return  # leftover cell - not valid if no empty cell allowed
        solutions.append([row[:] for row in board])
        return

    name, ph, pw = pieces[idx]

    for orient in ([0,1] if ph != pw else [0]):
        h, w = (ph, pw) if orient == 0 else (pw, ph)
        for r in range(8 - h + 1):
            for c in range(8 - w + 1):
                ok = True
                for dr in range(h):
                    for dc in range(w):
                        nr, nc = r+dr, c+dc
                        if (nr,nc) in obstacles or board[nr][nc] != 0:
                            ok = False
                            break
                    if not ok: break
                if not ok: continue
                # Place
                for dr in range(h):
                    for dc in range(w):
                        board[r+dr][c+dc] = name
                solve(board, idx+1, solutions, limit)
                for dr in range(h):
                    for dc in range(w):
                        board[r+dr][c+dc] = 0

board = [[0]*8 for _ in range(8)]
solutions = []
solve(board, 0, solutions, limit=5)
print(f"\nFound {len(solutions)} solution(s)\n")

for i, sol in enumerate(solutions):
    print(f"=== Solution {i+1} ===")
    for r in range(8):
        row = ""
        for c in range(8):
            if (r,c) in obstacles:
                row += "X"
            else:
                row += sol[r][c] if sol[r][c] else "."
        print(f"  {row}  |{r+1}")
    print("  " + "-"*16)
    print("  12345678")
    print()