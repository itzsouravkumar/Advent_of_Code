#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void process_mul_operations(const char *filename) {
    FILE *file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[1024];
    regex_t regex;
    regmatch_t matches[3];

    // Compile regular expression to match mul(a, b)
    if (regcomp(&regex, "mul\\((\\d+),(\\d+)\\)", REG_EXTENDED)) {
        perror("Could not compile regex");
        fclose(file);
        return;
    }

    printf("Results of mul(a, b):\n");

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        int start = 0;
        // Search for the pattern mul(a, b)
        while (regexec(&regex, line + start, 3, matches, 0) == 0) {
            // Extract numbers a and b
            char a_str[64], b_str[64];
            int a, b;
            
            // Extract matched substrings
            snprintf(a_str, matches[1].rm_eo - matches[1].rm_so + 1, "%s", line + start + matches[1].rm_so);
            snprintf(b_str, matches[2].rm_eo - matches[2].rm_so + 1, "%s", line + start + matches[2].rm_so);
            
            // Convert extracted strings to integers
            a = atoi(a_str);
            b = atoi(b_str);
            
            // Print the multiplication result
            printf("mul(%d, %d) = %d\n", a, b, a * b);
            
            // Move the starting position to the next character after the current match
            start += matches[2].rm_eo;
        }
    }

    regfree(&regex);  // Free compiled regex
    fclose(file);     // Close the file
}

int main() {
    const char *filename = "code_2.txt";  // Specify the path to the input file
    process_mul_operations(filename);   // Call the function to process the file
    return 0;
}
