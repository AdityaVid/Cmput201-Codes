#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to roll three dice
void rollDice(int dice[3]) {
    for (int i = 0; i < 3; i++) {
        dice[i] = rand() % 6 + 1;
    }
}

// Function to calculate points for a roll
int calculatePoints(int dice[3]) {
    int points = 0;
    int sortedDice[3];

    for (int i = 0; i < 3; i++) {
        sortedDice[i] = dice[i];
    }

    // Sort the dice in ascending order using bubble sort taught in class
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (sortedDice[j] > sortedDice[j + 1]) {
                int temp = sortedDice[j];
                sortedDice[j] = sortedDice[j + 1];
                sortedDice[j + 1] = temp;
            }
        }
    }

    if (sortedDice[0] == 4 && sortedDice[1] == 5 && sortedDice[2] == 6) {
        points = 1000;
    } else if (sortedDice[0] == 1 && sortedDice[1] == 1 && sortedDice[2] == 1) {
        points = 999;
    } else if (sortedDice[0] == 2 && sortedDice[1] == 2 && sortedDice[2] == 2) {
        points = 998;
    } else if (sortedDice[0] == 3 && sortedDice[1] == 3 && sortedDice[2] == 3) {
        points = 997;
    } else if (sortedDice[0] == 4 && sortedDice[1] == 4 && sortedDice[2] == 4) {
        points = 996;
    } else if (sortedDice[0] == 5 && sortedDice[1] == 5 && sortedDice[2] == 5) {
        points = 995;
    } else if (sortedDice[0] == 6 && sortedDice[1] == 6 && sortedDice[2] == 6) {
        points = 994;
    } else if (sortedDice[0] == 1 && sortedDice[1] == 2 && sortedDice[2] == 3) {
        points = 993;
    } else {
        points = 100 * sortedDice[0] + 10 * sortedDice[1] + sortedDice[2];
    }

    return points;
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    int player1_lives = 3;
    int player2_lives = 3;
    int currentRound = 1; // Renamed 'round' to 'currentRound'

    while (player1_lives > 0 && player2_lives > 0) {
        int totalPoints1 = 0;
        int numRolls1 = 0;

        int totalPoints2 = 0;
        int numRolls2 = 0;

        while (numRolls1 < 3 && numRolls2 < 3) {
            char choice;
            printf("Turn %d player 1: ", numRolls1 + 1);
            scanf(" %c", &choice);

            if (choice == 'r') {
                int dice[3];
                rollDice(dice);
                printf("You rolled: %d %d %d = ", dice[0], dice[1], dice[2]);
                int points = calculatePoints(dice);
                printf("%d points\n", points);
                totalPoints1 += points;
                numRolls1++;
            } else if (choice == 's') {
                break;
            }
        }

        while (numRolls2 < 3 && numRolls1 < 3) {
            char choice;
            printf("Turn %d player 2: ", numRolls2 + 1);
            scanf(" %c", &choice);

            if (choice == 'r') {
                int dice[3];
                rollDice(dice);
                printf("You rolled: %d %d %d = ", dice[0], dice[1], dice[2]);
                int points = calculatePoints(dice);
                printf("%d points\n", points);
                totalPoints2 += points;
                numRolls2++;
            } else if (choice == 's') {
                break;
            }
        }

        if (totalPoints1 > totalPoints2) {
            player2_lives--;
            printf("Player 1 wins this round!\n");
        } else if (totalPoints2 > totalPoints1) {
            player1_lives--;
            printf("Player 2 wins this round!\n");
        } else {
            printf("Both players tied this round with %d points\n", totalPoints1);
        }

        printf("Player 1 lives = %d\n", player1_lives);
        printf("Player 2 lives = %d\n\n", player2_lives);
        currentRound++;
    }

    if (player1_lives == 0 && player2_lives == 0) {
        printf("It's a tie!\n");
    } else if (player1_lives == 0) {
        printf("Player 2 wins!\n");
    } else {
        printf("Player 1 wins!\n");
    }

    return 0;
}
