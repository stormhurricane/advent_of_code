import re

def create_sign_dict(array: list) -> dict:
    sign_dict = {}
    for r in range(len((array))):
        for c in range(len(array[r])):
            if array[r][c] not in "1234567890.":
                sign_dict[(r, c)] = []
    return sign_dict
         

def main():
    file_path = "input.txt"
    schematic = []

    with open(file_path, "r") as file:
        schematic = [line.rstrip() for line in file]

    total_sum = 0
    product_sum = 0

    sign_dict = create_sign_dict(schematic)

    for i, row in enumerate(schematic):
        for match in re.finditer(r"\d+", row):
            
            for r in (i-1, i, i+1):
                for x in range(match.start()-1, match.end()+1):
                    if (r, x) in sign_dict:
                        sign_dict[(r, x)].append(int(match.group(0)))

    for values in sign_dict.values():
        total_sum = total_sum + sum(values)
        if len(values) == 2:
            product_sum = values[0] * values[1] + product_sum

    print(f"Part 1 Solution:\t{total_sum}")
    print(f"Part 2 Solution:\t{product_sum}")

# First and last line have no symbols

if __name__ == "__main__":
    main()