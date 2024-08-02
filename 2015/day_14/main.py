import time

if __name__ == "__main__":

    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = input.split("\n")

    animals = []

    # input parsing
    for line in input:
        name, _, _, speed, _, _, run_time, _, _, _, _, _, _, rest_time, _ = line.split(" ")
        animal = [name, int(speed), int(run_time), int(rest_time), False, 0, 0]
        animals.append(animal)

    TIME_TO_TRAVEL = 2503

    traveled_distances = []
    distances = [0] * len(animals)
    points = [0] * len(distances)

    # O(n^2)
    for t in range(0, TIME_TO_TRAVEL):
        for i, animal in enumerate(animals):
            # for each second, add to each animal the times it rested or run, and add to distance
            speed = animal[1]
            travel = animal[2]
            rest = animal[3]

            is_resting = animal[4]

            if is_resting:
                animal[6] += 1
                if animal[6] >= rest:
                    animal[4] = False
                    animal[6] = 0

            else:
                animal[5] += 1
                distances[i] += speed

                if animal[5] >= travel:
                    animal[4] = True
                    animal[5] = 0

        # find current leader, add the point
        max_dist = max(distances)
        index = distances.index(max_dist)
        points[index] += 1


    max_distance = max(distances)
    max_points = max(points)

    end_time = time.time()

    print(f"Maximum Travelled distance is {max_distance}")
    print(f"Maximum points is {max_points}")

    print(f"Needed {end_time - start_time} seconds")