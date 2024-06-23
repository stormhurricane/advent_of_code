import time

if __name__ == "__main__":
    input = open("input.txt", "r").read()

    start = time.time()

    location = {
        "^": (1, 0),
        "v": (-1, 0),
        ">": (0, 1),
        "<": (0, -1)
    }

    coordinates = {
        "santa": [(0,0)],
        "robo-santa": [(0, 0)],
        "all": [(0, 0)]
        }
    
    for i, char in enumerate(input):
        if i % 2 == 0:
            key = "santa"
        else:
            key = "robo-santa"

        new_coordinates = tuple(map(lambda x, y: x - y, coordinates[key][-1], location[char]))
        coordinates[key].append(new_coordinates)

        new_coordinates = tuple(map(lambda x, y: x - y, coordinates["all"][-1], location[char]))
        coordinates["all"].append(new_coordinates)
        

    unique_coordinates_of_santa = set(coordinates["all"])

    combined_list = coordinates["santa" ] + coordinates["robo-santa"]
    unique_coordinates_of_both = set(combined_list)

    end = time.time()

    print(f"Santa visited {len(unique_coordinates_of_santa)} unique houses in the previous year!")
    print(f"Santa and Robo-Santa visited {len(unique_coordinates_of_both)} unique houses!")
    print(f"needed {end - start} seconds")

    