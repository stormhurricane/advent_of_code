import time
import re

def main(filename:str = "input.txt") -> None:
    with open(filename, "r") as f:
        input = f.read()

    start = time.time()
    
    overall_pattern = "mul\\([0-9]+,[0-9]+\\)"
    matches = re.findall(overall_pattern, input)

    valid_multiplication_sum = 0

    wild_pattern = r"don\'t\(\)|do\(\)|" + overall_pattern

    matches = re.findall(wild_pattern, input)

    updated_valid_multiplication_sum = 0
    enabled = True

    for match in matches:
        if match == "don't()":
            enabled = False
        elif match == "do()":
            enabled = True
        else:
            numbers_pattern = "[0-9]+"
            numbers = re.findall(numbers_pattern, match)
            numbers = [int(x) for x in numbers]

            multiplication = numbers[0] * numbers[1]

            valid_multiplication_sum += multiplication

            if enabled: 
                updated_valid_multiplication_sum += (numbers[0] * numbers[1])


    end = time.time()

    print(f"Valid Multiplication Sum is {valid_multiplication_sum}")
    print(f"Updated Valid Multiplication Sum is {updated_valid_multiplication_sum}")
    print(f"Needed {end - start} seconds")

if __name__ == "__main__":
    main("input.txt")