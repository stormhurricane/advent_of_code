import re

def main(filename: str):
    with open(filename, "r") as file:
       scratchcards = [line.rstrip() for line in file]

    score = 0
    for game in scratchcards:
        winning_numbers, owned_numbers = game.split(":")[1].split("|")
        winning_numbers = re.findall(r'(\d+)', winning_numbers)
        owned_numbers = re.findall(r'(\d+)', owned_numbers)
        # print(f"Winning: {winning_numbers}\tOwned: {owned_numbers}")
        matches = [1 if number in winning_numbers else 0 for number in owned_numbers]
        #print(matches)
        worth = int(2 ** (sum(matches) -1 ))
        score = score + worth
    
    #print(scratchcards)

    print(f"Score: {score}")

if __name__ == "__main__":
    filename = "input.txt"
    main(filename)