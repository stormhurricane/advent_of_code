import time

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = input.split("\n")

    # values that can be hexadecimal
    hexadecimals = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']

    total_number_of_memory_characters = 0
    total_number_of_string_characters = 0
    total_number_of_integral_characters = 0

    for line in input:
        if not line:
            continue

        total_number_of_integral_characters += 2 + len(line) + line.count("\"") + line.count("\\")

        total_number_of_memory_characters += len(line)
        # remove leading and trailing quotations, and remove escapes part 1
        changed_line = line[1:-1].replace("\\\"", "\"")

        # loop because more possible hexadecimal values
        while changed_line.find("\\x") != -1:
            index = changed_line.find("\\x")

            # is it even supposed to be hexadecimal? otherwise, make it obvious
            if changed_line[index + 2] not in hexadecimals or changed_line[index + 3] not in hexadecimals:
                changed_line = changed_line.replace("\\x", "\\a", 1)
                continue

            # is there another \ before? make magic
            if changed_line[index-1] == "\\": 
                if changed_line.find("\\") == index-1:
                    changed_line.replace("\\\\", "", 1)
                    changed_line = "\\\\" + changed_line
                    continue
            
            # if true hexadecimal, just replface it with F.
            removable_string = changed_line[index:index+4]
            changed_line = changed_line.replace(removable_string, "F")

        changed_line = changed_line.replace("\\\\", "\\")

        total_number_of_string_characters += len(changed_line)

    end_time = time.time()

    print(f"Eval Difference is: {total_number_of_memory_characters - total_number_of_string_characters}")
    print(f"Integration Difference is: {total_number_of_integral_characters - total_number_of_memory_characters}")


    print(f"Needed {end_time - start_time} seconds")
