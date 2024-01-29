#include "ex8q1.h"

int main(void) {
    int is_print, value;
    float index;

    int array_size = 0;
    float* indices = NULL;
    int* values = NULL;

    while (!feof(stdin)) {
        // Use the read_line function from ex7q1.h to get input
        read_line(&is_print, &index, &value);

        if (is_print) {
            // Print the entire array
            printf("[");
            for (int i = 0; i < array_size; i++) {
                printf("%d", values[i]);
                if (i < array_size - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        } else {
            // Search for the index in the indices array
            int found = -1;
            for (int i = 0; i < array_size; i++) {
                if (indices[i] == index) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                // Update the existing value
                values[found] = value;
            } else {
                // Expand the arrays and insert the new index and value
                array_size++;
                indices = (float*)realloc(indices, array_size * sizeof(float));
                values = (int*)realloc(values, array_size * sizeof(int));

                // Find the position to insert the new index
                int insert_position = 0;
                while (insert_position < array_size - 1 && indices[insert_position] < index) {
                    insert_position++;
                }

                // Shift larger indices to make space for the new index
                for (int i = array_size - 1; i > insert_position; i--) {
                    indices[i] = indices[i - 1];
                    values[i] = values[i - 1];
                }

                // Insert the new index and value
                indices[insert_position] = index;
                values[insert_position] = value;
            }
        }
    }

    // Free dynamically allocated memory
    free(indices);
    free(values);

    return 0;
}
