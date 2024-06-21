from hashlib import md5
from itertools import count

import time

if __name__ == "__main__":
    with (open("input.txt", "r")) as f:
        input = f.read()

    start = time.time()
    five_found = False
    for i in count(1):
        combined = input + str(i)
        hash = md5(combined.encode("utf-8")).hexdigest()

        if hash[:5] == "00000" and not five_found:
            print(f"Shortest integer is {i} for 5 zeroes starting. \nCombined input {combined}\nHash is {hash}")
            five_found = True

        if hash[:6] == "000000":
            print(f"Shortest integer is {i} for 6 zeroes starting.\ncombined input {combined}\nHash is {hash}")
            break

    end = time.time()
    print(f"Needed {end - start} seconds")

