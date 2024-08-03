import time

# https://www.reddit.com/r/adventofcode/comments/3x1i26/comment/cy0plrf/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
def check_info(key, value):
    if key == "cats" or key == "trees":
        return sue_to_search[key] < value
    elif key == "pomeranians" or key == "goldfish":
        return sue_to_search[key] > value
    
    return sue_to_search[key] == value

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = input.split("\n")
    
    sue_to_search = {
        "children" : 3,
        "cats" : 7,
        "samoyeds": 2,
        "pomeranians" : 3,
        "akitas" : 0,
        "vizslas" : 0,
        "goldfish" : 5,
        "trees" : 3,
        "cars" : 2,
        "perfumes" : 1 
    }

    number_to_search = -1
    number_two = -1
    part_one = False
    part_two = False

    less_than = ["cats", "trees"]
    greater_than = ["pomeranians", "goldfish"]

    for line in input:

        _, number, key_one, value_one, key_two, value_two, key_three, value_three = line.split(" ")
        number = number[:-1]
        value_one = int(value_one[:-1])
        value_two = int(value_two[:-1])
        value_three = int(value_three)
        key_one = key_one[:-1]
        key_two = key_two[:-1]
        key_three = key_three[:-1]

        # this works for part one
        if sue_to_search[key_one] == value_one and sue_to_search[key_two] == value_two and sue_to_search[key_three] == value_three:
            number_to_search = number
            part_one = True

        # this works for part two
        if check_info(key_one, value_one) and check_info(key_two, value_two) and check_info(key_three, value_three):
            number_two = number
            part_two = True

        if part_one and part_two:
            break

        
    end_time = time.time()

    print(f"It was Aunt Sue {number_to_search}")
    print(f"Rather, it was rather Aunt Sue {number_two}")

    print(f"Needed {end_time - start_time} seconds")