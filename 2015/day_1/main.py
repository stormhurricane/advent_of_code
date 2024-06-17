
def find_floor():
    with open("input.txt", "r") as f:
        floor_instructions = f.read()

    floor_count = 0
    for instruction in floor_instructions:
        if instruction == "(":
            floor_count += 1
        elif instruction == ")":
            floor_count -= 1
    
    print(f"Santa is taken to floor {floor_count}")


if __name__ == "__main__":
    find_floor()