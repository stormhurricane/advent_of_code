import time

def main():
    with open("input.txt", "r") as f:
        input = f.read()

    start = time.time()

    input = input.split("\n")

    total_sqft_of_wrapping_paper = 0
    total_feet_of_ribbon = 0
    
    for line in input:
        if not line:
            continue

        # split input into the measurements and SORT ascendingly
        int_measurement = sorted([int(x) for x in line.split('x')])
        # calculation according to formulae
        surface_areas = [2 * int_measurement[0] * int_measurement[1], 2 * int_measurement[1] * int_measurement[2], 2 * int_measurement[0] * int_measurement[2]]

        sqft_of_wrapping_paper = sum(surface_areas) + int(min(surface_areas) / 2)
        total_sqft_of_wrapping_paper += sqft_of_wrapping_paper

        feet_of_ribbon = 2 * int_measurement[0] + 2 * int_measurement[1] + (int_measurement[0] * int_measurement[1] * int_measurement[2])
        total_feet_of_ribbon += feet_of_ribbon

    end = time.time()

    return total_sqft_of_wrapping_paper, total_feet_of_ribbon, end - start


if __name__ == "__main__":

    total_sqft_of_wrapping_paper, total_feet_of_ribbon, _time = main()

    print(f"The elves need {total_sqft_of_wrapping_paper} square feet of wrapping paper")  
    print(f"The elves need {total_feet_of_ribbon} feet of ribbon")  
    print(f"Needed {_time} seconds")
