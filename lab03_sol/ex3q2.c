#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int numbers[22];
    int x, y;
    int max = INT_MIN; // Initialize max to the minimum possible integer
    int min = INT_MAX; // Initialize min to the maximum possible integer
    
    // Read 22 integers from the user
    printf("Enter 22 integers: ");
    for (int i = 0; i < 20; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            printf("Error: Input is not a valid integer.\n");
            return 1; // Terminate with a non-zero exit code for invalid input
        }

        // Update max and min
        if (numbers[i] > max) {
            max = numbers[i];
        }
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }

    // Read additional integers x and y
    if (scanf("%d %d", &x, &y) != 2) {
        printf("Error: Input is not a valid integer.\n");
        return 1; // Terminate with a non-zero exit code for invalid input
    }

    // Calculate and print the result
    printf("x * max + y * min: %d\n", x * max + y * min);

    return 0; // Terminate with a zero exit code for successful execution
}
