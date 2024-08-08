import time
from itertools import combinations

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = input.split("\n")
    buckets = [int(bucket) for bucket in input]
    buckets.sort(reverse= True)

    LITERS_OF_EGGNOG = 150

    possible_combinations = 0
    min_num_of_containers = -1
    combinations_with_min_containers = 0
    
    for i in range(len(buckets) + 1):
        for perm in combinations(buckets, i):
            if sum(perm) == LITERS_OF_EGGNOG:
                possible_combinations += 1
                length = len(perm)

                if min_num_of_containers == -1:
                    min_num_of_containers = length
                    combinations_with_min_containers = 1
                elif min_num_of_containers == length:
                    combinations_with_min_containers += 1
                elif min_num_of_containers > length:
                    combinations_with_min_containers = 1
                    min_num_of_containers = length


    end_time = time.time()

    print(f"{possible_combinations} combinations of buckets can be combined for {LITERS_OF_EGGNOG}l of Eggnog")
    print(f"{min_num_of_containers} containers are used {combinations_with_min_containers} times for {LITERS_OF_EGGNOG}l of Eggnog")

    print(f"Needed {end_time - start_time} seconds")