import sys

def can_tile(grid, tiles, h, w):
    # Check if the grid is fully tiled
    if all(all(cell != 0 for cell in row) for row in grid):
        return True

    # Find the first empty cell
    for i in range(h):
        for j in range(w):
            if grid[i][j] == 0:
                for k, (a, b) in enumerate(tiles):
                    # Try placing the tile in both orientations
                    for _ in range(2):
                        a, b = b, a  # Swap dimensions for rotation
                        if i + a <= h and j + b <= w and all(grid[x][y] == 0 for x in range(i, i + a) for y in range(j, j + b)):
                            # Place the tile
                            for x in range(i, i + a):
                                for y in range(j, j + b):
                                    grid[x][y] = 1
                            
                            # Try to tile the rest
                            if can_tile(grid, tiles[:k] + tiles[k+1:], h, w):
                                return True
                            
                            # Backtrack
                            for x in range(i, i + a):
                                for y in range(j, j + b):
                                    grid[x][y] = 0
                return False  # No tile fits in this cell
    return False  # Should not reach here if grid is not fully tiled

def solve_tiling_problem(n, h, w, tiles):
    grid = [[0 for _ in range(w)] for _ in range(h)]
    return "Yes" if can_tile(grid, tiles, h, w) else "No"


line = sys.stdin.readline().strip()
n, h, w = map(int, line.split())
tiles = []
for _ in range(n):
    a, b = map(int, input().split())
    tiles.append((a, b))
result = solve_tiling_problem(n, h, w, tiles)
print(result)
