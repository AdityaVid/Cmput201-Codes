#include <stdio.h>

// Define constants for sale prices
#define CARROT_PRICE 0.50
#define TURNIP_PRICE 1.25
#define PUMPKIN_PRICE 3.00
#define LETTUCE_PRICE 1.00

// Define constants for purchase prices
#define CARROT_SEED_PRICE 0.05
#define TURNIP_SEED_PRICE 0.25
#define PUMPKIN_SEED_PRICE 0.70
#define LETTUCE_SEED_PRICE 0.30

// Function to calculate the price for vegetables sold and subtract the cost of seeds
double calculatePrice(int sold, int lost, double seedPrice, double cropPrice) {
    double revenue = sold * cropPrice;
    double cost = (sold + lost) * seedPrice; 
    return revenue - cost; 
}

int main() {
    // Initialize counters for C, T, P, and L
    int countC = 0, countT = 0, countP = 0, countL = 0, countClost = 0, countTlost = 0, countPlost = 0, countLlost = 0;

    printf("Enter the input string: ");
    
    // Read characters from stdin
    int ch;
    while ((ch = getchar()) != '\n') {
        switch (ch) {
            case '/':
                // Count of crop sold
                ch = getchar(); // Read the next character
                switch (ch) {
                    case 'C':
                        countC++;
                        break;
                    case 'T':
                        countT++;
                        break;
                    case 'P':
                        countP++;
                        break;
                    case 'L':
                        countL++;
                        break;
                    default:
                        // Handle invalid input if needed
                        break;
                }
                break;
            case '#':
                // Count of crop lost
                ch = getchar(); // Read the next character
                switch (ch) {
                    case 'C':
                        countClost++;
                        break;
                    case 'T':
                        countTlost++;
                        break;
                    case 'P':
                        countPlost++;
                        break;
                    case 'L':
                        countLlost++;
                        break;
                    default:
                        // Handle invalid input if needed
                        break;
                }
                break;
            default:
                // Handle other characters if needed
                break;
        }
    }

    // Calculate the total revenue and total profit
    double totalRevenue = calculatePrice(countC, countClost, CARROT_SEED_PRICE, CARROT_PRICE)
                        + calculatePrice(countT, countTlost, TURNIP_SEED_PRICE, TURNIP_PRICE)
                        + calculatePrice(countP, countPlost, PUMPKIN_SEED_PRICE, PUMPKIN_PRICE)
                        + calculatePrice(countL, countLlost, LETTUCE_SEED_PRICE, LETTUCE_PRICE);

    // Print the total revenue and total profit
    printf("Net profit: $%.2f\n", totalRevenue);

    return 0;
}
