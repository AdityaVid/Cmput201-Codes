#include "ex11q1.h"

// ############################################################################
// Vector
// ############################################################################

Vec* vec_create(void) {
    Vec* vec = (Vec*)malloc(sizeof(Vec));
    if (vec == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    vec->length = 0;
    vec->capacity = 10;
    vec->storage = (int*)malloc(vec->capacity * sizeof(int));
    if (vec->storage == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return vec;
}

void vec_insert_at(Vec* vec, int at, int item) {
    if (at < 0) {
        fprintf(stderr, "Invalid index\n");
        exit(EXIT_FAILURE);
    }

    // If the insert position is greater than the current length,
    // dynamically reallocate memory to accommodate the new position
    while (at >= vec->capacity) {
        vec->capacity += 2;
        vec->storage = realloc(vec->storage, vec->capacity * sizeof(int));
        if (vec->storage == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    // If the insert position is within the current length, replace the element
    if (at < vec->length) {
        vec->storage[at] = item;
    } else {
        // Otherwise, insert the new item at the specified position
        vec->storage[at] = item;
        vec->length = at + 1;
    }
}

void vec_print(Vec* vec) {
    printf("[");
    for (int k = 0; k < vec->length; k++) {
        printf("%d", vec->storage[k]);

        // Add a comma and space if it's not the last element
        if (k < vec->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void vec_free(Vec* vec) {
    free(vec->storage);
    free(vec);
}

// ############################################################################
// Linked List
// ############################################################################


// ############################################################################
// Doubly Linked List
// ############################################################################


// ############################################################################
// Main
// ############################################################################
int main(void) {
    char line[1000];
    // Uncomment each for loop as you implement that part

    clock_t begin_vec = clock();
    Vec* v = vec_create();

    for (int i = 0; i < 100000; i++) {
        int a, b;
        if (getchar() == 'i') {
            scanf("%s %d %s %d\n", line, &a, line, &b);
            vec_insert_at(v, b, a);
        } else {
            scanf("%s\n", line);
            vec_print(v);
        }
    }

    vec_free(v);
    clock_t end_vec = clock();

    clock_t begin_list = clock();
    //LinkedList* l = list_create();

    //for (int i = 0; i < 100000; i++) {
    //    int a, b;
    //    if (getchar() == 'i') {
    //        scanf("%s %d %s %d\n", line, &a, line, &b);
    //        list_insert_at(l, b, a);
    //    } else {
    //        scanf("%s\n", line);
    //        list_print(l);
    //    }
    //}

    //list_free(l);
    clock_t end_list = clock();

    clock_t begin_dlist = clock();
    //DoublyLinkedList* dlist = dlist_create();

    //for (int i = 0; i < 100000; i++) {
    //    int a, b;
    //    if (getchar() == 'i') {
    //        scanf("%s %d %s %d\n", line, &a, line, &b);
    //        dlist_insert_at(dlist, b, a);
    //    } else {
    //        scanf("%s\n", line);
    //        dlist_print(dlist);
    //    }
    //}

    //dlist_free(dlist);
    clock_t end_dlist = clock();

    fprintf(stderr, "Vector: %gs\n", (double)(end_vec - begin_vec) / CLOCKS_PER_SEC);
    fprintf(stderr, "Linked List: %gs\n", (double)(end_list - begin_list) / CLOCKS_PER_SEC);
    fprintf(stderr, "Doubly Linked List: %gs\n", (double)(end_dlist - begin_dlist) / CLOCKS_PER_SEC);
}
