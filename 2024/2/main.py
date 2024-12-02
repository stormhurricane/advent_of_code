import time

def is_safe_report(report: list[int]) -> bool:
    """
        Checks a report for validty.
        Each level is checked with its next neighbor for the difference. Difference needs to be 1 <= x <= 3 in a absolute ascending or descending order
    """
    return all(((report[i] - report[i+1]) <= 3 and (report[i] - report[i+1]) >=1 for i in range(len(report) -1 ))) or \
        all(((report[i+1] - report[i]) <= 3 and (report[i+1] - report[i]) >=1 for i in range(len(report) -1 )))

def check_report(report: list[int]) -> tuple[bool, bool]:
    # first check for simple validity, without removing levels
    simple_safe = is_safe_report(report)
    complex_safe = False

    if simple_safe:
        return simple_safe, complex_safe
    
    # if not simple, need to look if any combination exists where the report is safe.
    for j in range(len(report)):
        new_list = report[:j] + report[j+1:]
        complex_safe = is_safe_report(new_list)
        if complex_safe:
            break

    return simple_safe, complex_safe

def main(filename: str ="input.txt") -> None:
    with open(filename, "r") as f:
        input = f.read().split("\n")

    start_time = time.time()

    safe_reports = 0
    dampened_safe_reports = 0

    for report in input:
        numbers = [int(x) for x in report.split(" ")]

        is_safe, is_complex_safe = check_report(numbers)

        if is_safe:
            safe_reports += 1
            dampened_safe_reports += 1
        elif is_complex_safe:
            dampened_safe_reports += 1

    end_time = time.time()
    
    print(f"Number of safe reports: {safe_reports}")
    print(f"Number of safe reports after dampening: {dampened_safe_reports}")
    print(f"Needed {end_time - start_time} seconds")

if __name__ == "__main__":
    main("input.txt")