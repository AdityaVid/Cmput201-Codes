/* Purpose: Solving magic square
 * Author: Aditya 
 * Date: 10/10/23
 * References: https://stanford.edu/class/cs106x/res/handouts/11-Recursive-Backtracking-I.pdf - Recursive Backtracking
 */

#include "lab05.h"

// Do not touch anything in this main function (used for testing purposes)
int main(void) {
    return test_magic(magic);
}

// Function to check if a filled grid is a magic square
int check(int n, int grid[n][n]) {
    int numUsed[n * n + 1];
    int sum = n * (n * n + 1) / 2;
    for (int i = 0; i <= n * n; i++) {
        numUsed[i] = 0;
    }
    // Check rows and columns
    for (int i = 0; i < n; i++) {
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < n; j++) {
            if (grid[i][j] < 1 || grid[i][j] > n * n || numUsed[grid[i][j]]) {
                return 0; // Invalid number or duplicate
            }
            numUsed[grid[i][j]] = 1;
            rowSum += grid[i][j];
            colSum += grid[j][i];
        }
        if (rowSum != sum || colSum != sum) {
            return 0; // Not a magic square
        }
    }

    // Check diagonals
    int diagSum1 = 0, diagSum2 = 0;
    for (int i = 0; i < n; i++) {
        diagSum1 += grid[i][i];
        diagSum2 += grid[i][n - 1 - i];
    }
    if (diagSum1 != sum || diagSum2 != sum) {
        return 0; // Not a magic square
    }

    return 1; // It's a valid magic square
}

// Recursive function to solve a given grid as a magic square
int magic(int n, int grid[n][n]) {
    // Find the next empty cell
    int row = -1, col = -1;
    for (int i = 0; i < n && row == -1; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                break;
            }
        }
    }

    // If no empty cell is found, check if it's a valid magic square
    if (row == -1) {
        return check(n, grid);
    }

    // Try filling the empty cell with numbers from 1 to n*n
    for (int num = 1; num <= n * n; num++) {
        // Check if the number is not already used in the same row or column
        int valid = 1;
        for (int i = 0; i < n; i++) {
            if (grid[row][i] == num || grid[i][col] == num) {
                valid = 0;
                break;
            }
        }

        if (valid) {
            grid[row][col] = num;
            // Recursively try filling the next empty cell
            if (magic(n, grid)) {
                return 1;
            }
            // If the recursive call didn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return 0; // No solution found
}
