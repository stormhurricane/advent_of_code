import time

def main(filename="input.txt"):
    with open(filename, "r") as f:
        input = f.readlines()

    start_time = time.time()

    left_list = []
    right_list = []

    # create two lists
    for line in input:
        line = " ".join(line.strip().split())
        line = line.split(" ")

        left_list.append(int(line[0]))
        right_list.append(int(line[1]))

    # sort lists
    left_list.sort()
    right_list.sort()

    total_distance = 0

    # measure distance
    for pair in zip(left_list, right_list):
        distance = abs(pair[0] - pair[1])
        total_distance += distance

    similarity_values = []

    for location_id in left_list:
        occurences = 0
        for i in right_list:
            if i == location_id:
                occurences += 1
            elif i > location_id:
                break

        similarity_values.append(occurences)
    
    similarity_score = 0

    for pair in zip(left_list, similarity_values):
        value = pair[0] * pair[1]
        similarity_score += value


    end_time = time.time()

    print(f"Total Distance between lists is {total_distance}")
    print(f"Similarity Score is {similarity_score}")

    print(f"Needed {end_time - start_time} seconds")

if __name__ == "__main__":
    main("input.txt")