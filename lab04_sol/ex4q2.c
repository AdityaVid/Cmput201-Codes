#include <stdio.h>
#include <stdlib.h>

#define MAX_BOXES 2000
#define MAX_MAX_WEIGHTS 100000

int main() {
    int n;
    scanf("%d", &n);

    double boxes[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &boxes[i]);
    }

    // Sort the array of box weights in non-decreasing order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (boxes[i] > boxes[j]) {
                double temp = boxes[i];
                boxes[i] = boxes[j];
                boxes[j] = temp;
            }
        }
    }

    double maxWeight;
    while (scanf("%lf", &maxWeight) == 1) {
        int count = 0;
        double currentWeight = 0.0;

        for (int k = 0; k < n; k++) {
            if (currentWeight + boxes[k] <= maxWeight) {
                currentWeight += boxes[k];
                count++;
            } else {
                break; // Stop if the current box cannot fit
            }
        }
        printf("%d\n", count);
    }

    return 0;
}
