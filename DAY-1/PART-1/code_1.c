#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    FILE *file = fopen("code_1.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    int list1[1000], list2[1000]; // Assuming a maximum of 1000 lines
    int num1, num2, idx = 0;
    char line[100]; // Buffer for each line

    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %d", &num1, &num2) == 2) {
            list1[idx] = num1;
            list2[idx] = num2;
            idx++;
        }
    }

    fclose(file);

    // Sort the arrays
    qsort(list1, idx, sizeof(int), compare);
    qsort(list2, idx, sizeof(int), compare);

    // Calculate total distance
    int total_distance = 0;
    for (int i = 0; i < idx; i++) {
        total_distance += abs(list1[i] - list2[i]);
    }

    printf("Answer: %d\n", total_distance);

    return 0;
}
