

if __name__ == "__main__":
    input = open("input.txt", "r").read()

    location = {
        "^": (1, 0),
        "v": (-1, 0),
        ">": (0, 1),
        "<": (0, -1)
    }

    coordinates = [(0,0)]

    for char in input:
        new_coordinates = tuple(map(lambda x, y: x - y, coordinates[-1], location[char]))
        coordinates.append(new_coordinates)

    unique_coordinates = set(coordinates)
    print(f"Santa visits {len(unique_coordinates)} unique houses!")

    