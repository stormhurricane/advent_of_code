import time

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    input = input.split("\n")

    ingridients = []

    for line in input:
        name, _, capacity, _, durability, _, flavor, _, texture, _, calories = line.split(" ")
        name = name[:-1]
        capacity = capacity[:-1]
        durability = durability[:-1]
        flavor = flavor[:-1]
        texture = texture[:-1]

        ingridients.append({
            "name": name,
            "capacity": int(capacity),
            "durability": int(durability),
            "flavor": int(flavor),
            "texture": int(texture),
            "calories": int(calories)
        })

    high_score = 0
    calorie_count_score = 0

    CALORIE_GOAL = 500

    # O(n^3)...
    for first_ingridient in range(0, 101):
        for second_ingridient in range(0, 101 - first_ingridient):
            for third_ingridient in range(0, 101 - first_ingridient - second_ingridient):
                fourth_ingridient = 100 - first_ingridient - second_ingridient - third_ingridient
                
                capacity = ingridients[0]["capacity"] * first_ingridient + ingridients[1]["capacity"] * second_ingridient \
                    + ingridients[2]["capacity"] * third_ingridient + ingridients[3]["capacity"] * fourth_ingridient
                
                # if i separate the if checks, I may be saving some seconds
                if capacity <= 0:
                    continue
                
                durability = ingridients[0]["durability"] * first_ingridient + ingridients[1]["durability"] * second_ingridient \
                    + ingridients[2]["durability"] * third_ingridient + ingridients[3]["durability"] * fourth_ingridient
                
                if durability <= 0:
                    continue

                flavor = ingridients[0]["flavor"] * first_ingridient + ingridients[1]["flavor"] * second_ingridient \
                    + ingridients[2]["flavor"] * third_ingridient + ingridients[3]["flavor"] * fourth_ingridient
                
                if flavor <= 0:
                    continue
                
                texture = ingridients[0]["texture"] * first_ingridient + ingridients[1]["texture"] * second_ingridient \
                    + ingridients[2]["texture"] * third_ingridient + ingridients[3]["texture"] * fourth_ingridient
                
                if texture <= 0:
                    continue
                
                calories = ingridients[0]["calories"] * first_ingridient + ingridients[1]["calories"] * second_ingridient \
                    + ingridients[2]["calories"] * third_ingridient + ingridients[3]["calories"] * fourth_ingridient
                
                score = capacity * durability * flavor * texture
                if score > high_score:
                    high_score = score

                if calories == CALORIE_GOAL and score > calorie_count_score:
                    calorie_count_score = score


    end_time = time.time()

    print(f"High Score for Cookies: {high_score}")
    print(f"High Score under calorie limit: {calorie_count_score}")

    print(f"Needed {end_time - start_time} seconds")