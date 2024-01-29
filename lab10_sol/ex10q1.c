#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* head;    // Start of dynamic storage
    int* start;   // Index 0 of ring buffer
    int* end;     // One after the last element in the ring buffer
    int length;   // Number of elements currently stored in the ring buffer
    int capacity; // Maximum number of elements this ring buffer can hold

} VecDeque;

VecDeque* initializeVecDeque(int capacity) {
    VecDeque* deque = (VecDeque*)malloc(sizeof(VecDeque));
    deque->head = (int*)malloc(capacity * sizeof(int));
    deque->start = deque->head;
    deque->end = deque->head;
    deque->length = 0;
    deque->capacity = capacity;
    return deque;
}

void resize(VecDeque* deque) {
    VecDeque* deque_new = initializeVecDeque(deque->length * 2);

    deque_new->head = realloc(deque_new->head, deque_new->capacity * sizeof(int));
    deque_new->length = deque->length;


    int* start_new = deque->start; 

    for(int i = 0; i < deque->length; i++) {
        *deque_new->end = * start_new;
        deque_new->end++;
        start_new++;
        if(start_new == (deque->head + deque->capacity)) {
            start_new = deque->head;
        }
    }

    free(deque->head);

    deque->head = deque_new->head;
    deque->start = deque_new->head;
    deque->end = deque_new->end;
    deque->capacity = deque_new->capacity;

    start_new = deque->end;
    for(int i = 0; i < deque->length; i ++) {
        *start_new = 0;
        start_new++;
    }

    //With help of neoki saito, thanks!!!
}


void pushFront(VecDeque* deque, int value) {
    if (deque->length > 1 && deque->start ==  deque->end) {
        resize(deque);
    }

    deque->start--;
    if (deque->start < deque->head) {
        deque->start = deque->head + deque->capacity;
    }

    *(deque->start) = value;

    deque->length++;
}

void pushBack(VecDeque* deque, int value) {
    if (deque->length > 1 && deque->start ==  deque->end) {
        resize(deque);
    }

    *(deque->end) = value;
    deque->end++;
    if (deque->end == deque->head + deque->capacity - 1) {
        deque->end = deque->head;
    }

    deque->length++;
}

int popFront(VecDeque* deque) {
    if (deque->length == 0) {
        return -1;  // None equivalent for this example
    }

    int value = *(deque->start);
    deque->start++;
    deque->length--;

    if (deque->start >= deque->head + deque->capacity) {
        deque->start = deque->head;
    }

    return value;
}


int popBack(VecDeque* deque) {
    if (deque->length == 0) {
        return -1;  // None equivalent for this example
    }

    deque->end--;
    if (deque->end < deque->head) {
        deque->end = deque->head + deque->capacity - 1;
    }

    int value = *(deque->end);
    deque->length--;

    return value;
}


void freeVecDeque(VecDeque* deque) {
    free(deque->head);
    free(deque);
}

void rebalance(VecDeque* frontDeque, VecDeque* backDeque) {
    int diff = frontDeque->length - backDeque->length;

    if (diff <= -1) {
        int value = popFront(backDeque);
        pushBack(frontDeque, value); 
    }

    if (diff > 1) {
        int value = popBack(frontDeque);
        pushFront(backDeque, value);
    }
}

//void displayVecDeque(VecDeque* deque){}

int main() {
    char action;
    int x, student_id;

    VecDeque* frontDeque = initializeVecDeque(4);
    VecDeque* backDeque = initializeVecDeque(4);
    
    while (scanf(" %c", &action) != EOF) {
        switch (action) {
        case 'N':
            scanf("%d %d", &x, &student_id);
            if ((frontDeque->length + backDeque->length) < x) {
                if (frontDeque->length == 0) {
                    pushBack(frontDeque, student_id);
                    //displayVecDeque(frontDeque);
                } else {
                    pushBack(backDeque, student_id);
                }
                rebalance(frontDeque, backDeque);
            }
            break;

        case 'C':
            scanf("%d %d", &x, &student_id);

            if(frontDeque->length < x) {
                if (frontDeque->length > backDeque->length) {
                    pushFront(backDeque, student_id);
                    //displayVecDeque(frontDeque);
                } else {
                    pushBack(frontDeque, student_id);
                    //displayVecDeque(backDeque);
                }
                rebalance(frontDeque, backDeque);
            }

            break;
            

        case 'F':
            if (frontDeque->length > 0) {
                printf("%d\n", popFront(frontDeque));
                //displayVecDeque(frontDeque);
            } else if (backDeque->length > 0) {
                printf("%d\n", popFront(backDeque));
                //displayVecDeque(backDeque);
            } else {
                printf("empty\n");
            }
            break;

        case 'L':
            if (backDeque->length > 0) {
                popBack(backDeque);
                //displayVecDeque(frontDeque);
            } else if (frontDeque->length > 0) {
                popBack(frontDeque);
                //displayVecDeque(backDeque);
            }
            break;
        }
    }

    freeVecDeque(frontDeque);
    freeVecDeque(backDeque);

    return 0;
}
