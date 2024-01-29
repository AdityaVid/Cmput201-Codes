#include <stdio.h>
#include <stdbool.h>

// Function to check if a Sudoku row is valid
bool isRowValid(int sudoku[9][9], int row) {
    bool used[10] = {false}; // Array to keep track of used digits (0-9)
    for (int i = 0; i < 9; i++) {
        int num = sudoku[row][i];
        if (num < 1 || num > 9 || used[num]) {
            return false; // Invalid digit or duplicate in the row
        }
        used[num] = true;
    }
    return true; // Row is valid
}

// Function to check if a Sudoku column is valid
bool isColumnValid(int sudoku[9][9], int col) {
    bool used[10] = {false}; // Array to keep track of used digits (0-9)
    for (int i = 0; i < 9; i++) {
        int num = sudoku[i][col];
        if (num < 1 || num > 9 || used[num]) {
            return false; // Invalid digit or duplicate in the column
        }
        used[num] = true;
    }
    return true; // Column is valid
}

// Function to check if a 3x3 sub-grid is valid
bool isSubgridValid(int sudoku[9][9], int startRow, int startCol) {
    bool used[10] = {false}; // Array to keep track of used digits (0-9)
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || used[num]) {
                return false; // Invalid digit or duplicate in the sub-grid
            }
            used[num] = true;
        }
    }
    return true; // Sub-grid is valid
}

int main() {
    int sudoku[9][9];

    // Read the Sudoku grid from stdin
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num;
            if (scanf("%1d", &num) != 1) {
                printf("Invalid input. Please enter a digit for each cell.\n");
                return 1;
            }
            sudoku[i][j] = num;
        }
    }

    // Check if each row, column, and sub-grid is valid
    for (int i = 0; i < 9; i++) {
        if (!isRowValid(sudoku, i) || !isColumnValid(sudoku, i)) {
            printf("Invalid\n");
            return 0;
        }
    }

    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!isSubgridValid(sudoku, i, j)) {
                printf("Invalid\n");
                return 0;
            }
        }
    }

    printf("Valid\n");

    return 0;
}
