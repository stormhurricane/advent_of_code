import time

def look_and_say(input):
    string_input = str(input)

    string_length = len(string_input)

    output = ""

    i = 0

    # because only for loops are translated to C...
    while i in range(string_length):
        current_char = string_input[i]
        current_count = 1

        # for a char, look if the following chars are the same char
        for j in range(i + 1, string_length):
            if string_input[j] == current_char:
                current_count += 1
            else:
                break
          
        output += str(current_count) + current_char
        i+= current_count

    return output


if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    length_after_forty_times = 0

    for i in range(50):
        input = look_and_say(input)
        if i == 39:
            length_after_forty_times = len(input)
        
    end_time = time.time()

    print(f"After 40 repititions, result has length of {length_after_forty_times}")
    print(f"After 50 repititions, result has length of {len(input)}")

    print(f"needed {end_time-start_time} seconds")
