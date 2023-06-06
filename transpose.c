#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

void transposeMatrix(float matrix[][MAX_SIZE], float result[][MAX_SIZE], int rows, int cols) {
    int i, j;

    for (i = 0; i < cols; i++) {
        for (j = 0; j < rows; j++) {
            result[i][j] = matrix[j][i];
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
    float matrix[MAX_SIZE][MAX_SIZE], transpose[MAX_SIZE][MAX_SIZE];
    int rows, cols;

    // Read the matrix from CSV
    readMatrixFromCSV("matrix.csv", matrix, &rows, &cols);

    // Compute the transpose
    transposeMatrix(matrix, transpose, rows, cols);

    // Write the transpose to CSV
    writeMatrixToCSV("transpose.csv", transpose, cols, rows);

    printf("Matrix transpose completed. Result stored in 'transpose.csv'\n");

    return 0;
}
