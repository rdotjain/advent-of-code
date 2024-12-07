def read_puzzle(file_path):
    """Reads the puzzle from a text file and returns it as a 2D list."""
    with open(file_path, "r") as file:
        return [line.strip() for line in file]


def count_word_in_directions(grid, word):
    """Counts occurrences of a word in all 8 directions in a grid."""
    rows, cols = len(grid), len(grid[0])
    word_len = len(word)
    directions = [
        (0, 1),  # Horizontal right
        (0, -1),  # Horizontal left
        (1, 0),  # Vertical down
        (-1, 0),  # Vertical up
        (1, 1),  # Diagonal down-right
        (-1, -1),  # Diagonal up-left
        (1, -1),  # Diagonal down-left
        (-1, 1),  # Diagonal up-right
    ]

    def is_valid(x, y):
        """Checks if a position is within the grid bounds."""
        return 0 <= x < rows and 0 <= y < cols

    def matches(x, y, dx, dy):
        """Checks if the word matches starting at (x, y) in direction (dx, dy)."""
        for i in range(word_len):
            nx, ny = x + i * dx, y + i * dy
            if not is_valid(nx, ny) or grid[nx][ny] != word[i]:
                return False
        return True

    def match_mas(x, y):
        if not (1 <= x < rows - 1 and 1 <= y < cols - 1):
            return 0
        if (
            (grid[x - 1][y - 1] == "M" and grid[x + 1][y + 1] == "S")
            or (grid[x - 1][y - 1] == "S" and grid[x + 1][y + 1] == "M")
        ) and (
            (grid[x - 1][y + 1] == "M" and grid[x + 1][y - 1] == "S")
            or (grid[x - 1][y + 1] == "S" and grid[x + 1][y - 1] == "M")
        ):
            return 1

    def solve_part1():
        count = 0
        for r in range(rows):
            for c in range(cols):
                for dx, dy in directions:
                    if matches(r, c, dx, dy):
                        count += 1
        return count

    def solve_part2():
        count = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == "A":
                    if match_mas(r, c):
                        count += 1
        return count

    print(solve_part1())
    print(solve_part2())


# File path to the puzzle
file_path = "input.txt"
grid = read_puzzle(file_path)
word_to_find = "XMAS"

# Count occurrences of the word
count = count_word_in_directions(grid, word_to_find)
