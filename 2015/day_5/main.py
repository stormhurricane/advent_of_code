import time

def part_one(input):
    disallowed_strings = ["ab", "cd", "pq", "xy"]
    vowels = ["a", "e", "i", "o", "u"]
    nice_string_count = 0
    for line in input:
        res = [dis for dis in disallowed_strings if (dis in line)]
        if res:
            continue

        vowels_in_line = "".join([vow for vow in line if (vow in vowels)])
        if len(vowels_in_line) < 3:
            continue

        for i, char in enumerate(line):
            if (i+1 < len(line)):
                if char == line[i+1]:
                    nice_string_count += 1
                    break    
    return nice_string_count


def part_two(input):
    nice_string_count = 0
    for line in input:
        rule_of_xyx = False
        rule_of_pair = False
        for i, char in enumerate(line):
            if i+2 < len(line) and not rule_of_xyx:
                if char == line[i+2]:
                    rule_of_xyx = True
            if not rule_of_pair:
                j = i + 2
                while (j + 1 < len(line)):
                    if f"{char}{line[i+1]}" == f"{line[j:j+2]}":
                        rule_of_pair = True
                    j += 1
            
            if rule_of_pair and rule_of_xyx:
                break

        if rule_of_pair and rule_of_xyx:
            nice_string_count += 1
    
    return nice_string_count


if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read().split("\n")

    start = time.time()

    old_nice_string_count = part_one(input)
    new_nice_string_count = part_two(input)
    
    end = time.time()

    print(f"{old_nice_string_count} number of nice strings in the old counting")
    print(f"{new_nice_string_count} number of nice strings in the new counting")
    print(f"Needed time: {end - start} seconds")