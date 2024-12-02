#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to check if a report is safe
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

        // Check if the report is safe
        if (is_safe(report, size)) {
            safe_count++;
        }
    }

    fclose(file);
    return safe_count;
}

// Main function
int main() {
    const char *file_path = "E:/ADVENT OF CODE/DAY-2/PART-1/code_1.txt";

    int safe_reports_count = count_safe_reports(file_path);
    if (safe_reports_count != -1) {
        printf("Number of safe reports: %d\n", safe_reports_count);
    }

    return 0;
}
