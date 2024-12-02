def is_safe(report):
    # Check if the report is monotonic (either increasing or decreasing)
    increasing = all(report[i] <= report[i + 1] for i in range(len(report) - 1))
    decreasing = all(report[i] >= report[i + 1] for i in range(len(report) - 1))
    
    # Check if adjacent numbers differ by at least 1 and at most 3
    valid_differences = all(1 <= abs(report[i] - report[i + 1]) <= 3 for i in range(len(report) - 1))
    
    # The report is safe if it satisfies both conditions
    return (increasing or decreasing) and valid_differences


def is_safe_after_removal(report):
    # Check if the original report is safe
    if is_safe(report):
        return True
    
    # Check if removing any single number makes the report safe
    for i in range(len(report)):
        modified_report = report[:i] + report[i + 1:]
        if is_safe(modified_report):
            return True
    
    return False


def count_safe_reports(file_path):
    # Read the input file and count the number of safe reports
    safe_count = 0
    with open(file_path, 'r') as file:
        for line in file:
            # Convert the line to a list of integers
            report = list(map(int, line.strip().split()))
            if is_safe_after_removal(report):
                safe_count += 1
    return safe_count


# Define the file path
file_path = 'E:/ADVENT OF CODE/DAY-2/PART-2/code_2.txt'

# Count the safe reports
safe_reports_count = count_safe_reports(file_path)
print(f"Number of safe reports (after possible removal): {safe_reports_count}")
