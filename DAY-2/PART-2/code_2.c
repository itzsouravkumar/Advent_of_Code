#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to check if a report is monotonic and has valid differences
bool is_safe(int report[], int size) {
    bool increasing = true, decreasing = true, valid_differences = true;

    for (int i = 0; i < size - 1; i++) {
        if (report[i] > report[i + 1])
            increasing = false;
        if (report[i] < report[i + 1])
            decreasing = false;
        if (abs(report[i] - report[i + 1]) < 1 || abs(report[i] - report[i + 1]) > 3)
            valid_differences = false;
    }

    return (increasing || decreasing) && valid_differences;
}

// Function to check if the report becomes safe after removing one number
bool is_safe_after_removal(int report[], int size) {
    if (is_safe(report, size)) {
        return true;
    }

    for (int i = 0; i < size; i++) {
        int modified_report[100], k = 0;

        // Create a new report excluding the i-th number
        for (int j = 0; j < size; j++) {
            if (j != i) {
                modified_report[k++] = report[j];
            }
        }

        // Check if the modified report is safe
        if (is_safe(modified_report, size - 1)) {
            return true;
        }
    }

    return false;
}

// Function to count safe reports from a file
int count_safe_reports(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char line[1024];
    int safe_count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Parse the line into an array of integers
        int report[100], size = 0;
        char *token = strtok(line, " ");
        while (token != NULL) {
            report[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Check if the report is safe or can be made safe
        if (is_safe_after_removal(report, size)) {
            safe_count++;
        }
    }

    fclose(file);
    return safe_count;
}

// Main function
int main() {
    const char *file_path = "E:/ADVENT OF CODE/DAY-2/PART-2/code_2.txt";

    int safe_reports_count = count_safe_reports(file_path);
    if (safe_reports_count != -1) {
        printf("Number of safe reports (after possible removal): %d\n", safe_reports_count);
    }

    return 0;
}
