import re

def define_signs(file_path: str) -> set:
    with open(file_path, "r") as f:
        return {char for char in set(f.read()) if not char.isalnum() and char not in {".", "\n"}}


def check_position(x_low, x_high, row, lines, signs):
    row_value = max(0, row - 1)
    x_start = max(0, x_low - 1)

    relevant_lines = lines[row_value:row + 2]
    relevant_chars = (char for line in relevant_lines for char in line[x_start:x_high + 1])

    return any(char in signs for char in relevant_chars)

            

def main():
    file_path = "input.txt"
    lines = []

    with open(file_path, "r") as f:
        lines = [line.rstrip() for line in f]

    signs = define_signs(file_path)
    total_sum = 0
    num_list = []

    for i, row in enumerate(lines):
        for m in re.finditer(r"\d+", row):
            if check_position(m.start(), m.end(), i, lines, signs):
                total_sum += int(m.group(0))
                num_list.append(int(m.group(0)))

    print(total_sum)

    print(signs)



# First and last line have no symbols

if __name__ == "__main__":
    main()
    #print(board)