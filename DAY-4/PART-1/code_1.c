#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_BUFFER_SIZE 10000 // Adjust this size based on file size

int main() {
    FILE *file;
    char *filename = "E:\\ADVENT OF CODE\\DAY-3\\PART-1\\code_1.txt";
    char buffer[MAX_BUFFER_SIZE];

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    // Read the file contents into buffer
    fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    fclose(file);

    // Regular expression for pattern `mul(x, y)`
    const char *pattern = "mul\\(([0-9]+),([0-9]+)\\)";
    regex_t regex;
    regmatch_t matches[3]; // Array to hold match groups (full match + 2 groups)
    int ret;

    // Compile the regex
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        printf("Error: Could not compile regex\n");
        return 1;
    }

    char *cursor = buffer;
    int total_sum = 0;

    // Execute the regex
    while (!regexec(&regex, cursor, 3, matches, 0)) {
        // Extract numbers from the match
        char num1[10] = {0}, num2[10] = {0};

        // Get the first number
        int start = matches[1].rm_so;
        int end = matches[1].rm_eo;
        strncpy(num1, cursor + start, end - start);

        // Get the second number
        start = matches[2].rm_so;
        end = matches[2].rm_eo;
        strncpy(num2, cursor + start, end - start);

        // Convert to integers and calculate product
        int x = atoi(num1);
        int y = atoi(num2);
        total_sum += x * y;

        // Move cursor forward to process the next match
        cursor += matches[0].rm_eo;
    }

    // Free the regex memory
    regfree(&regex);

    // Print the result
    printf("Answer: %d\n", total_sum);

    return 0;
}
