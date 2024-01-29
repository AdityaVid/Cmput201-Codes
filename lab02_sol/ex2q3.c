#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int Hardcover = 15, Softcover = 12, Ebook = 7;
    int num_books[3] = {0};

    printf("How many hardcover books are you buying? ");
    if (scanf("%d", &num_books[0]) != 1 || num_books[0] < 0 || num_books[0] > 100000) {
        printf("Invalid input. Please enter a non-negative integer less than or equal to 100,000.\n");
        return 1;  // Terminate with a non-zero exit code for invalid input.
    }

    printf("How many softcover books are you buying? ");
    if (scanf("%d", &num_books[1]) != 1 || num_books[1] < 0 || num_books[1] > 100000) {
        printf("Invalid input. Please enter a non-negative integer less than or equal to 100,000.\n");
        return 1;  // Terminate with a non-zero exit code for invalid input.
    }

    printf("How many ebooks are you buying? ");
    if (scanf("%d", &num_books[2]) != 1 || num_books[2] < 0 || num_books[2] > 100000) {
        printf("Invalid input. Please enter a non-negative integer less than or equal to 100,000.\n");
        return 1;  // Terminate with a non-zero exit code for invalid input.
    }

    float total_cost = num_books[0] * Hardcover + num_books[1] * Softcover + num_books[2] * Ebook;
    int coupon_discount = 0;

    // Apply coupon discounts
    if (num_books[0] + num_books[1] >= 6) {
        // $20 off on purchases of any mix of 6 or more hard or softcover books
        coupon_discount += 20;
    }
    if (num_books[0] >= 2) {
        // $5 off on purchases of 2 or more hardcover books
        coupon_discount += 5;
    }
    if (num_books[1] >= 4) {
        // $10 off on purchases of 4 or more softcover books
        coupon_discount += 10;
    }

    // Calculate the total cost after applying coupon discounts
    float discounted_total = total_cost - coupon_discount;

    int percent_total = 0;

    // Apply percentage discounts
    if (num_books[0] >= 1 && num_books[1] >= 1 && num_books[2] >= 1) {
        // 1 of each book: 3% discount
        percent_total += 3;
    }
    if (num_books[2] >= 3) {
        // 3 or more ebooks: 4% discount
        percent_total += 4;
    }
    
    // Check if the total cost falls within a certain range and apply discounts accordingly
    if (discounted_total > 75) {
        // 10% off the final discounted total, on orders over $75
        percent_total += 10;
    }
    if (discounted_total > 150) {
        // 15% off the final discounted total, on orders over $150
        percent_total += 15;
    }

    // Calculate the percentage discount as a decimal
    float percent_discount = (1.0 - (percent_total / 100.0));

    // Calculate the final total cost after applying percentage discounts
    total_cost = discounted_total * percent_discount;

    printf("Order total: $%.2f\n", total_cost);

    return 0;
}
