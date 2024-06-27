import time

   
def calculate_value(name):
    try:
        return int(name)
    except ValueError:
        pass

    if name in wire_values:
        return int(wire_values[name])
        
    instruction = instruction_values.get(name)

    if len(instruction) == 1:
        res = calculate_value(instruction[0])
    elif instruction[0] == "NOT":
                # bitflip using the XOR operation with max value
        res =  calculate_value(instruction[1]) ^ 0xffff
    elif instruction[1] == "AND":
        res = calculate_value(instruction[0]) & calculate_value(instruction[2])
    elif instruction[1] == "OR":
        res = calculate_value(instruction[0]) | calculate_value(instruction[2])
    elif instruction[1] == "LSHIFT":
        res = calculate_value(instruction[0]) << calculate_value(instruction[2])
    elif instruction[1] == "RSHIFT":
        res = calculate_value(instruction[0]) >> calculate_value(instruction[2])

    wire_values[name] = res
    return res
    
def create_dicts(input):
    input = input.split("\n")

    instruction_values = dict()
    wire_values = dict()
    
    for line in input:
        if not line:
            continue
        # find wire
        wire, instruction = line.split("->")[1].strip(), line.split("->")[0].strip()

        # handle instructions
        if instruction.isnumeric():
            wire_values[wire] = instruction
        else:
            instruction = instruction.split(" ")
            instruction_values[wire] = instruction

    return instruction_values, wire_values



if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    instruction_values, wire_values = create_dicts(input)
    

    old_a = calculate_value("a")        

    instruction_values, wire_values = create_dicts(input)
    wire_values["b"] = old_a

    a = calculate_value("a")
    
    end_time = time.time()

    print(f"old_a: {old_a}")
    print(f"new a: {a}")
    print(f"Needed {end_time - start_time} seconds")
