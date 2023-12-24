import re
import math


def main(filename):
    with open(filename, "r") as file:
        lines = file.readlines()

    times = [int(num) for num in re.findall("\d+", lines[0])]
    distances = [int(num) for num in re.findall("\d+", lines[1])]
    races = (list(zip(times, distances)))

    possible_solutions = []

    for race in races:
        (time, distance) = race
        print(f"Race: {time} with {distance}")
        high, low = 0, 0
        for i in range(1, time - 1):
            if i * (time - i) > distance:
                low = i
                break
        for i in range(time - 1, low, -1):
            if i * (time - i) > distance:
                high = i
                break

        possible_solutions.append(high - low + 1)
    prod = 1
    for val in possible_solutions:
        prod = prod * val

    print(f"Product of number of possible solutions: {prod}")
    print(possible_solutions)


if __name__ == "__main__":
    main("input.txt")
