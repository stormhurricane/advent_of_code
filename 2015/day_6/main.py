import time

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()
    input = input.split("\n")

    # create the grid by double list comprehension
    on_grid = [[False for i in range(1000)] for i in range(1000)]
    brightness_grid = [[0 for i in range(1000)] for i in range(1000)]
    
    for line in input:
        # split input into words and get necessary information
        line = line.split(" ")
        if line[0] == "toggle":
            start = line[1].split(",")
            command = "toggle"
        else:
            start = line[2].split(",")
            command = line[1]
        
        end = line[-1].split(",")
        x1 = int(start[0])
        y1 = int(start[1])
        x2 = int(end[0])
        y2 = int(end[1])

        # iterate over the grid and change values
        while x1 <= x2:
            j = y1
            while j <= y2:
                if command == "toggle":
                    val = on_grid[x1][j]
                    on_grid[x1][j] = not val
                    brightness_grid[x1][j] += 2
                elif command == "on":
                    on_grid[x1][j] = True
                    brightness_grid[x1][j] += 1
                elif command == "off":
                    on_grid[x1][j] = False
                    brightness_grid[x1][j] -= 1 if brightness_grid[x1][j] > 0 else 0
                j += 1
            x1 +=1

    count_on_lights = sum([x.count(True) for x in on_grid])
    count_on_brightness = sum([sum(x) for x in brightness_grid])

    end = time.time()
    
    print(f"{count_on_lights} lights are on according to santas plan")
    print(f"{count_on_brightness} is the brightness on according to santas plan")
    print(f"Needed {end - start_time} seconds")