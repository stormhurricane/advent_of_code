import re

def main(filename: str):
    with open(filename, "r") as file:
        scratchcards = [line.rstrip() for line in file]

    copies = {i: 1 for i in range(len(scratchcards))}
    #print(copies)

    score = 0
    for i, card in enumerate(scratchcards):
        for r in range(copies[i]):
            winning_numbers, owned_numbers = card.split(":")[1].split("|")
            winning_numbers = [number for number in winning_numbers.split(" ") if number.isdigit()]
            owned_numbers = [number for number in owned_numbers.split(" ") if number.isdigit()]
            matches = sum(1 for number in owned_numbers if number in winning_numbers)
            worth = int(2 ** (matches - 1))
           # print(f"Card {i + 1} matches {matches}")
            for x in range(i+1, i+1+matches):
                copies[x] = copies[x] + 1
        score += worth
        #print(copies)



    print(f"Number of Scratchcards: {sum(copies.values())}")
    print(f"Score: {score}")

if __name__ == "__main__":
    filename = "input.txt"
    main(filename)