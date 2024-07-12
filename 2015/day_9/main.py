from itertools import permutations
import time

# https://stackoverflow.com/a/64004484
def insert(val, index, arr):
    while index >= len(arr):
        arr.append([])
    arr[index].append(val)


if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = input.split("\n")[:-1]

    # a dict for key to index
    cord_to_int_dict = dict()
    i = 0
    adjacency_mat = [[], []]

    for line in input:
        src, _, dst, _ , distance = line.split()
        
        # is already in the dict?
        if src in cord_to_int_dict:
            src_index = cord_to_int_dict.get(src)
        else:
            cord_to_int_dict[src] = i
            src_index = i
            i += 1

        if dst in cord_to_int_dict:
            dst_index = cord_to_int_dict.get(dst)
        else:
            cord_to_int_dict[dst] = i
            dst_index = i
            i += 1

        # yeah, not the fine way
        try:
            adjacency_mat[src_index][dst_index] = distance
        except IndexError:
            insert(distance, src_index, adjacency_mat)

        try:
            adjacency_mat[dst_index][src_index] = distance
        except IndexError:
            insert(distance, dst_index, adjacency_mat)
        

    # we need the zero values
    for i in cord_to_int_dict.values():
        adjacency_mat[i].insert(i, 0)
    

    places = list(cord_to_int_dict.keys())
    max_route = -1
    min_route = -1

    i = 0

    # TODO optimise this brute force shit
    for items in permutations(places):
        route_distance = 0
        for i in range(len(items) -1):
            src_index = cord_to_int_dict[items[i]]
            dst_index = cord_to_int_dict[items[i+1]]
            
            distance = adjacency_mat[src_index][dst_index]
            route_distance += int(distance)

        if route_distance > max_route:
            max_route = route_distance
        
        if route_distance < min_route:
            min_route = route_distance
        elif min_route == -1:
            min_route = route_distance


    end_time = time.time()

    print(f"Shortest route is {min_route}")
    print(f"Longest route is {max_route}")
    print(f"needed {end_time-start_time} seconds")
