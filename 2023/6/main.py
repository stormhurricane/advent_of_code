import re


def find_number_of_solutions(time, distance):
    high, low = 0, 0
    for i in range(1, time - 1):
        if i * (time - i) > distance:
            low = i
            break
    for i in range(time - 1, low, -1):
        if i * (time - i) > distance:
            high = i
            break
    return high - low + 1


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

        possible_solutions.append(find_number_of_solutions(time, distance))

    prod = 1
    for val in possible_solutions:
        prod = prod * val

    time = int(lines[0].split(":")[1].replace(" ", ""))
    distance = int(lines[1].split(":")[1].replace(" ", ""))

    print(f"Product of number of possible solutions: {prod}")
    print(
        f"Solutions for big race: {find_number_of_solutions(time, distance)}")


if __name__ == "__main__":
    main("input.txt")
