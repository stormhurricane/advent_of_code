
def find_floor():
    with open("input.txt", "r") as f:
        floor_instructions = f.read()

    floor_count = 0
    entered_basement = False

    # linear time
    for i, instruction in enumerate(floor_instructions):
        if instruction == "(":
            floor_count += 1
        elif instruction == ")":
            floor_count -= 1

        if floor_count < 0 and not entered_basement:
            basement_index = i
            entered_basement = True

    print(f"Santa entered the basement first at instruction {basement_index + 1 }")
    print(f"Santa is taken to floor {floor_count}")


if __name__ == "__main__":
    find_floor()