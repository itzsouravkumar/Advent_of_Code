#include <stdio.h>
#include <string.h>

int count_xmas_crosses(char matrix[][100], int rows, int cols) {
    int numb_x_mas = 0;
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if (matrix[i][j] == 'A') {
                char tl_lr[3], ll_tr[3];
                tl_lr[0] = matrix[i-1][j-1];
                tl_lr[1] = matrix[i+1][j+1];
                tl_lr[2] = '\0';
                ll_tr[0] = matrix[i+1][j-1];
                ll_tr[1] = matrix[i-1][j+1];
                ll_tr[2] = '\0';
                
                if ((strcmp(tl_lr, "SM") == 0 || strcmp(tl_lr, "MS") == 0) && 
                    (strcmp(ll_tr, "SM") == 0 || strcmp(ll_tr, "MS") == 0)) {
                    numb_x_mas++;
                }
            }
        }
    }
    return numb_x_mas;
}

int main() {
    FILE *file = fopen("E:\\ADVENT OF CODE\\DAY-4\\PART-2\\code_2.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char matrix[100][100];
    int rows = 0;
    
    while (fgets(matrix[rows], sizeof(matrix[0]), file)) {
        matrix[rows][strcspn(matrix[rows], "\n")] = 0;
        rows++;
    }
    
    fclose(file);
    
    int cols = strlen(matrix[0]);
    int result = count_xmas_crosses(matrix, rows, cols);

    printf("The number of X-MAS patterns in the grid is %d.\n", result);

    return 0;
}
