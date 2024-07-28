import time
from itertools import permutations


# https://stackoverflow.com/a/64004484
def insert(val, index, arr):
    while index >= len(arr):
        arr.append([])
    arr[index].append(val)

# inefficient piece, doubled 
def find_max_happiness(names, adj_matrix):
    max_happiness = 0

    for items in permutations(names):
        
        happiness_change = 0
        for i in range(len(items)):
            
            src_index = names.index(items[i])
            dst_index = names.index(items[(i+1) % len(items)])
            
            distance = adj_matrix[src_index][dst_index]
            distance_2 = adj_matrix[dst_index][src_index]
            happiness_change += (distance)
            happiness_change += (distance_2)

        if happiness_change > max_happiness:
            max_happiness = happiness_change
        
    return max_happiness

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = input.split("\n")

    name_list = []
    adj_matrix = [ [], [] ]

    # stolen from day 9
    for line in input:
        src, _, sth, value, _, _, _, _, _, _, dst = line.split(" ")
        dst = dst[:-1]

        if sth == "gain":
            value = int(value)
        else:
            value = -1 * int(value)

        if src in name_list:
            src_index = name_list.index(src)
        else:
            name_list.append(src)
            src_index = name_list.index(src)

        if dst in name_list:
            dst_index = name_list.index(dst)
        else:
            name_list.append(dst)
            dst_index = name_list.index(dst)

        try:
            adj_matrix[src_index][dst_index] = value
        except IndexError:
            insert(value, src_index, adj_matrix)

    # insert the appropriate zeroes
    for i in range(len(name_list)):
        adj_matrix[i].insert(i, 0)
    
    # for part 1
    max_happiness = find_max_happiness(name_list, adj_matrix)

    # add me
    name_list.append("me")
    # and add the values
    for line in adj_matrix:
        line.append(0)

    adj_matrix.append([0] * (len(adj_matrix) + 1))

    # stupid shit times two
    max_happiness_with_me = find_max_happiness(name_list, adj_matrix)

    end_time = time.time()


    print(f"Maximum hapiness is {max_happiness}")
    print(f"Maximum hapiness with me is {max_happiness_with_me}")

    print(f"Needed {end_time - start_time} seconds")
