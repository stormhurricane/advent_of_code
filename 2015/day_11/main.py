import time

# increase the rightmost character, with overhang if it is a 'z'
def increase_password(pw):
    new_password = pw

    for i in range(len(pw) -1, 0, -1):
        current_char = pw[i]
        next_char = chr(ord(current_char) + 1)

        # how am I supposed to know the order of unicode?
        if current_char == 'z':
            next_char = 'a'
            new_password = pw[:i] + next_char + new_password[i + 1:]
        else:
            new_password = pw[:i] + next_char + new_password[i + 1:]
            break

    return new_password

def is_valid_password(pw):
    pair_counter = 0
    has_three_street = False

    length = len(pw)

    for i, char in enumerate(pw):
        # check for invalid characters
        if char == 'l' or char == 'o' or char == 'l':
            return False
        
        # try to find a three part street (abc)
        if not has_three_street and i + 2 < length:
            first = ord(pw[i])
            second = ord(pw[i + 1])
            third = ord(pw[i + 2])
            has_three_street = (second == first + 1) and (third == first + 2)

        # try to find a pair
        if pair_counter < 2 and i + 1  < length:
            if pw[i] == pw[i - 1]:
                continue
            
            if pw[i] == pw[i + 1]:
                pair_counter += 1

    return pair_counter >= 2 and has_three_street


if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = increase_password(input)

    while not is_valid_password(input):
        input = increase_password(input)

    first_new_valid_pw = input

    input = increase_password(input)

    while not is_valid_password(input):
        input = increase_password(input)


    end_time = time.time()

    print(f"First next valid password is {first_new_valid_pw}")
    print(f"Second next valid password is {input}")

    print(f"needed {end_time-start_time} seconds")
