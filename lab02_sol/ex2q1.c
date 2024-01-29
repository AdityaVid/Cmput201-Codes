#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {// This program finds the maximum element in an array
    int length = 0, index = 0;
    scanf("%d", &length);
    if (length != 1) {
        int array[length];
        for (int i = 0; i < length; i++) {
            if (scanf("%d", &array[i]) != 1)
                exit(100);
            if (array[index] < array[i])
                index = i;
        }
        printf("The maximum element is %d\n", array[index]);
    }
    return 0;
}