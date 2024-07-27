import time
import json
import numbers

# magic that this works
def iterate_over_json(json_obj):

    if not json_obj:
        return 0, 0
    
    val = 0
    red_val = 0

    # if dict, let's go deeper
    if isinstance(json_obj, dict):
        is_red = False
        # disregeard redvalue
        if "red" in json_obj.values():
            is_red = True
        for value in json_obj.values():
            obj_val, red_obj = iterate_over_json(value)
            val += obj_val
            if not is_red:
                red_val += red_obj
    # iterate over list
    elif isinstance(json_obj, list):
        for value in json_obj:
            next_val, red_valv = iterate_over_json(value)
            val += next_val
            red_val += red_valv

    # just number
    elif isinstance(json_obj, numbers.Number):
        val += json_obj
        red_val += json_obj

    return val, red_val

                
if __name__ == "__main__":
    with open("input.txt", "r") as f:
        input = f.read()

    start_time = time.time()

    json_object = json.loads(input)

    ret_val, red_val = iterate_over_json(json_object)

    end_time = time.time()

    print(f"Sum of all Numbers in Json is {ret_val}")
    print(f"Sum of non-red Numbers in Json is {red_val}")


    print(f"needed {end_time-start_time} seconds")
