#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    unsigned short int num_aisles;
    char ***aisles;

    // Read the number of aisles from stdin
    scanf("%hu", &num_aisles);

    // Allocate memory for the aisles array
    aisles = (char ***)malloc(num_aisles * sizeof(char **));

    for (unsigned short i = 0; i < num_aisles; i++) {
        aisles[i] = (char **)malloc(1 * sizeof(char *));
        aisles[i][0] = (char *)malloc(1);
        aisles[i][0][0] = '\0'; // Initialize with an empty string
    }

    unsigned short int aisle;
    unsigned int id;
    char item;

    while (1) {
        if (scanf("%u", &id) == 1) {
            if (id == 0) {
                // Print the contents of an aisle
                scanf("%hu", &aisle);
                printf("%s\n", aisles[aisle][0]);
            } else {
                // Read the item information
                scanf(" %c", &item);
                // Calculate the aisle using the modulo of the ID
                aisle = id % num_aisles;
                // Append the item character to the correct aisle
                unsigned short int len = strlen(aisles[aisle][0]);
                aisles[aisle][0] = (char *)realloc(aisles[aisle][0], len + 2); // +2 for item and null-terminator
                aisles[aisle][0][len] = item;
                aisles[aisle][0][len + 1] = '\0';
            }
        } else {
            break; // End of input
        }
    }

    // Free allocated memory
    for (unsigned short int i = 0; i < num_aisles; i++) {
        free(aisles[i][0]);
        free(aisles[i]);
    }
    free(aisles);

    return 0;
}
