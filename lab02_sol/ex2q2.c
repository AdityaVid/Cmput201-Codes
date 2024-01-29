#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int CAD, USD, Remainder;
    const float CAD_to_USD = 0.75;
    int denominations[] = {100, 50, 20, 10, 5, 2, 1};
    int num_bills[7] = {0}; 

    printf("Enter CAD amount: ");
    scanf("%d", &CAD);

    USD = (int)(CAD * CAD_to_USD + 0.5);  // Round to nearest integer
    printf("Converted USD amount: $%d\n", USD);

    Remainder = USD;

    for (int i = 0; i < 7; i++) {
        num_bills[i] = Remainder / denominations[i];
        Remainder = Remainder - (denominations[i] * num_bills[i]);
    }

    for (int i = 0; i < 7; i++) {
        if (i == 0) {
            printf("$%d bills: %d\n", denominations[i], num_bills[i]);
        }
        else if (i < 4) {
            printf("%2s%d bills: %d\n", "$", denominations[i], num_bills[i]);
        }
        else {
            printf("%3s%d bills: %d\n", "$", denominations[i], num_bills[i]);
        }
        
    }

    return 0;
}
