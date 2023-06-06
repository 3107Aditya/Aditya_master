#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void readMatrixFromCSV(const char* fileName, float matrix[][MAX_SIZE], int* size) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        exit(1);
    }

    char line[MAX_SIZE];
    int row = 0, col = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        col = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            matrix[row][col++] = atof(token);
            token = strtok(NULL, ",");
        }
        row++;
    }

    *size = row;

    fclose(file);
}

void writeMatrixToCSV(const char* fileName, float matrix[][MAX_SIZE], int size) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        exit(1);
    }

    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            fprintf(file, "%.2f,", matrix[i][j]);
        }
        fprintf(file, "%.2f\n", matrix[i][j]);
    }

    fclose(file);
}

void swapRows(float matrix[][MAX_SIZE], int size, int row1, int row2) {
    int j;
    float temp;
    for (j = 0; j < size; j++) {
        temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}

void multiplyRow(float matrix[][MAX_SIZE], int size, int row, float factor) {
    int j;
    for (j = 0; j < size; j++) {
        matrix[row][j] *= factor;
    }
}

void addRows(float matrix[][MAX_SIZE], int size, int destRow, int srcRow, float factor) {
    int j;
    for (j = 0; j < size; j++) {
        matrix[destRow][j] += factor * matrix[srcRow][j];
    }
}

void invertMatrix(float matrix[][MAX_SIZE], float inverse[][MAX_SIZE], int size) {
    int i, j;

    // Initialize the identity matrix
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            inverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Apply Gauss-Jordan elimination
    for (i = 0; i < size; i++) {
        if (matrix[i][i] == 0.0) {
            // Find a non-zero pivot
            int pivotRow = i + 1;
            while (pivotRow < size && matrix[pivotRow][i] == 0.0) {
                pivotRow++;
            }

            if (pivotRow == size) {
                // Matrix is not invertible
                printf("Matrix is not invertible\n");
                exit(1);
            }

            swapRows(matrix, size, i, pivotRow);
            swapRows(inverse, size, i, pivotRow);
        }

        float pivot = matrix[i][i];
        multiplyRow(matrix, size, i, 1.0 / pivot);
        multiplyRow(inverse, size, i, 1.0 / pivot);

        for (j = 0; j < size; j++) {
            if (j != i) {
                float factor = -matrix[j][i];
                addRows(matrix, size, j, i, factor);
                addRows(inverse, size, j, i, factor);
            }
        }
    }
}

int main() {
    float matrix[MAX_SIZE][MAX_SIZE], inverse[MAX_SIZE][MAX_SIZE];
    int size;

    // Read the matrix from CSV
    readMatrixFromCSV("matrix.csv", matrix, &size);

    // Compute the inverse
    invertMatrix(matrix, inverse, size);

    // Write the inverse to CSV
    writeMatrixToCSV("inverse.csv", inverse, size);

    printf("Matrix inverse completed. Result stored in 'inverse.csv'\n");

    return 0;
}
