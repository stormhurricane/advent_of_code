import re

red_cubes = 12
green_cubes = 13
blue_cubes = 14

def process_line(line):
    match = re.match(r"Game (\d+):", line)
    game_id = int(match.group(1))
   # print(f"Game {game_id}")

    sets = line.split(":")[1].split(";")
    error_found = False
    minimal_cubes = {"red": 0, "green": 0, "blue": 0}

    for game_set in sets:
        process_set(game_set, minimal_cubes)

    power_of_game = 1
    for value in minimal_cubes.values():
        power_of_game *= value

    return not error_found, game_id, power_of_game

def process_set(game_set, minimal_cubes):
    global error_found
    draws = re.findall(r'(\d+) (red|green|blue)', game_set)

    for draw in draws:
        count, color = draw
        count = int(count)
        #print(f"  Draw: {count} {color}")

        if minimal_cubes[color] < count:
            minimal_cubes[color] = count

        if color == "red" and count > red_cubes:
                error_found = True
        elif color == "green" and count > green_cubes:
                error_found = True
        elif color == "blue" and count > blue_cubes:
                error_found = True

def main():
    global error_found
    lines = []

    with open("input.txt", "r") as f:
        lines = f.readlines()

    sum_of_ids = 0
    sum_of_cube_power= 0

    for line in lines:
        error_found = False
        valid, game_id, power = process_line(line)

        sum_of_cube_power += power

        if not error_found and valid:
            sum_of_ids += game_id

    print(f"Sum of correct game ids: {sum_of_ids}")
    print(f"Sum of cube power: {sum_of_cube_power}")

if __name__ == "__main__":
    main()
