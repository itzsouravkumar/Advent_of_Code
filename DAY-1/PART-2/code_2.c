#include <stdio.h>
#include <stdlib.h>

// Function to count occurrences of a number in an array
int count_occurrences(int *arr, int size, int num) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            count++;
        }
    }
    return count;
}

int main() {
    FILE *file = fopen("code_2.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    int list1[1000], list2[1000]; // Assuming a maximum of 1000 lines
    int num1, num2, idx1 = 0, idx2 = 0;
    char line[100]; // Buffer for each line

    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %d", &num1, &num2) == 2) {
            list1[idx1++] = num1;
            list2[idx2++] = num2;
        }
    }

    fclose(file);

    // Calculate similarity score
    int similarity_score = 0;
    for (int i = 0; i < idx1; i++) {
        int count_in_list2 = count_occurrences(list2, idx2, list1[i]);
        similarity_score += list1[i] * count_in_list2;
    }

    printf("Answer: %d\n", similarity_score);

    return 0;
}
