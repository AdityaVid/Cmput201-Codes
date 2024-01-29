#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 1001

typedef struct {
    int digits[MAX_DIGITS];
    int length;
} BigInteger;

void initialize(BigInteger *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->length = 0;
}

void convertStringToBigInteger(const char *str, BigInteger *num) {
    initialize(num);

    int len = strlen(str);
    int j = 0;

    for (int i = len - 1; i >= 0; --i) {
        num->digits[j++] = str[i] - '0';
    }

    num->length = len;
}

void add(BigInteger *result, const BigInteger *a, const BigInteger *b) {
    initialize(result);

    int carry = 0;

    for (int i = 0; i < a->length || i < b->length || carry; ++i) {
        int sum = carry;
        if (i < a->length) {
            sum += a->digits[i];
        }
        if (i < b->length) {
            sum += b->digits[i];
        }
        carry = sum / 10;
        result->digits[i] = sum % 10;
        result->length++;
    }
}

void concatenate(BigInteger *result, const BigInteger *a, const BigInteger *b) {
    initialize(result);

    // Copy digits from the first number
    for (int i = 0; i < a->length; ++i) {
        result->digits[result->length++] = a->digits[i];
    }

    // Copy digits from the second number
    for (int i = 0; i < b->length; ++i) {
        result->digits[result->length++] = b->digits[i];
    }
}


void rotate(BigInteger *result, const BigInteger *a, int times) {
    initialize(result);

    times %= a->length;

    for (int i = 0; i < a->length; ++i) {
        result->digits[(i + times) % a->length] = a->digits[i];
        result->length++;
    }
}

void printBigInteger(const BigInteger *num) {
    int leadingZeros = 1;

    for (int i = num->length - 1; i >= 0; --i) {
        if (leadingZeros && num->digits[i] == 0) {
            continue;
        }
        leadingZeros = 0;
        printf("%d", num->digits[i]);
    }

    if (leadingZeros) {
        printf("0");
    }

    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char op[4];
        char num1Str[MAX_DIGITS];
        char num2Str[MAX_DIGITS];
        BigInteger num1, num2, result;

        scanf("%s %s %s", num1Str, op, num2Str);

        convertStringToBigInteger(num1Str, &num1);
        convertStringToBigInteger(num2Str, &num2);

        if (strcmp(op, "+") == 0) {
            add(&result, &num1, &num2);
        } else if (strcmp(op, "@") == 0) {
            concatenate(&result, &num2, &num1);
            //I had to flip these number idk why tho
        } else if (strcmp(op, "rot") == 0) {
            int times;
            sscanf(num2Str, "%d", &times);
            rotate(&result, &num1, times);
        }

        printBigInteger(&result);
    }

    return 0;
}

