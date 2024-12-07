import re

def solve(memory):
    pattern = r"mul\((\d+),(\d+)\)"
    matches = re.findall(pattern, memory)
    total = sum(int(x) * int(y) for x, y in matches)
    
    return total

def read_memory(file_path):
    with open(file_path, 'r') as file:
        return file.read()

memory = read_memory("input.txt")
result = solve(memory)
print(result)