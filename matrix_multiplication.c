#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void multiplyMatrices(float matrix1[][MAX_SIZE], float matrix2[][MAX_SIZE], float result[][MAX_SIZE], int rows1, int cols1, int cols2) {
    int i, j, k;

    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void readMatrixFromCSV(const char* fileName, float matrix[][MAX_SIZE], int* rows, int* cols) {
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

    *rows = row;
    *cols = col;

    fclose(file);
}

void writeMatrixToCSV(const char* fileName, float matrix[][MAX_SIZE], int rows, int cols) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        exit(1);
    }

    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols - 1; j++) {
            fprintf(file, "%.2f,", matrix[i][j]);
        }
        fprintf(file, "%.2f\n", matrix[i][j]);
    }

    fclose(file);
}

int main() {
    float matrix1[MAX_SIZE][MAX_SIZE], matrix2[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];
    int rows1, cols1, rows2, cols2;

    // Read the first matrix from CSV
    readMatrixFromCSV("matrix1.csv", matrix1, &rows1, &cols1);

    // Read the second matrix from CSV
    readMatrixFromCSV("matrix2.csv", matrix2, &rows2, &cols2);

    // Check if the matrices can be multiplied
    if (cols1 != rows2) {
        printf("Error: Matrices cannot be multiplied.\n");
        return 1;
    }

    // Multiply the matrices
    multiplyMatrices(matrix1, matrix2, result, rows1, cols1, cols2);

    // Write the result to CSV
    writeMatrixToCSV("result.csv", result, rows1, cols2);

    printf("Matrix multiplication completed. Result stored in 'result.csv'\n");

    return 0;
}
