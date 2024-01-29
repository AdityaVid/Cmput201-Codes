#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint32_t NewFloat;

NewFloat bits_string_to_nfloat(const char s[40]);

void nfloat_debug(NewFloat f); // part 1

NewFloat float_to_nfloat(float f); // part 2

void nfloat_print(NewFloat f); // part 3

NewFloat nfloat_double(NewFloat f); // part 4

NewFloat nfloat_add(NewFloat a, NewFloat b);

void printBits(uint64_t value);

int main(void)
{
    int part_num;
    char s1[40];
    float f1, f2;
    NewFloat n1, n2;

    // This will scan the input for you! Uncomment pieces once you implement
    // the functions for that part
    while (1)
    {
        int res = scanf(" p%d", &part_num);

        if (res != 1)
        {
            break;
        }
        else if (part_num == 1)
        {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_debug(n1);
        }
        else if (part_num == 2)
        {
            scanf("%f", &f1);
            n1 = float_to_nfloat(f1);
            nfloat_debug(n1);
        }
        else if (part_num == 3)
        {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_print(n1);
        }
        else
        {
            scanf("%s ", s1);

            if (s1[0] == 'd')
            {
                scanf("%f", &f1);
                n1 = float_to_nfloat(f1);
                n1 = nfloat_double(n1);
            }
            else
            {
                scanf("%f %f", &f1, &f2);
                n1 = float_to_nfloat(f1);
                n2 = float_to_nfloat(f2);
                n1 = nfloat_add(n1, n2);
            }

            nfloat_print(n1);
        }
    }
}

void nfloat_debug(NewFloat f)
{
    for (int i = 31; i >= 0; i--)
    {
        if ((i == 30) | (i == 25))
        {
            printf(" ");
        }
        printf("%d", (f >> i) & 1);
    }
    printf("\n");
}

NewFloat bits_string_to_nfloat(const char *bin_str)
{
    // Convert binary string to NewFloat
    NewFloat result = 0;
    for (int i = 0; i < 32; i++)
    {
        result <<= 1;
        result |= (bin_str[i] - '0');
    }

    return result;
}

NewFloat float_to_nfloat(float f)
{
    NewFloat result;
    
    memcpy(&result, &f, sizeof(NewFloat));
    
    // Extract sign bit
    uint32_t sign = (result >> 31) & 0x1;

    // Extract exponent bits
    uint32_t exponent = (result >> 23) & 0xFF;

    // Extract mantissa bits
    uint32_t fraction = result & 0x7FFFFF;

    // Adjust the exponent for the new data type
    int exp_diff = exponent - 127;
    exponent = exp_diff + 15 ; // Bias of 15 for the new 5-bit exponent

    // Exclude the leading 1 if it exists
    if ((exponent + 127 - 15) == 0) {
        //printBits(exponent);
        unsigned int mask = 1 << 4;  // 1 followed by 4 zeros
    
        // Check if the 4th bit is 1
        if (exponent & mask) {
            // If it is 1, mask it to 0
            exponent &= ~mask;
        }
    }
    
    

    // Construct the NewFloat
    result = (sign << 31) | (exponent << 26) | (fraction << 3);
    //printBits(result);
    return result;
}

void printBits(uint64_t value) {
    for (int i = 63; i >= 0; --i) {
        printf("%lu", (value >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

void nfloat_print(NewFloat f)
{
    // Extract sign bit
    uint64_t sign = (f >> 31) & 0x1;
    printBits(sign);
    printBits(0x1);
    // Extract exponent bits
    uint64_t exponent = (f >> 26) & 0x1F;
    printBits(exponent);
    printBits(0x1F);
    // Extract mantissa bits
    uint64_t fraction = f & 0x3FFFFFF;
    printBits(fraction);
    printBits(0x2FFFFFF);

    // Construct the double representation
    uint64_t double_rep = 0;
    double_rep |= (uint64_t)sign << 63;               // Sign bit
    //printBits(double_rep);

    // Adjust the exponent bias
    uint64_t actual_exponent = exponent - 15;

    if (actual_exponent == -15) {
        actual_exponent = -511;
    }

    double_rep |= (uint64_t)(actual_exponent + 1023) << 52; // Exponent
    //printBits(double_rep);

    // Convert the 26-bit mantissa to a 52-bit mantissa by shifting left
    uint64_t mantissa = (uint64_t)fraction << 26;
    double_rep |= mantissa;
    //printBits(double_rep);

    // Print the result with 7 digits after the decimal point
    // Type cast to double and print
    double double_value;
    memcpy(&double_value, &double_rep, sizeof(double));
    printf("%.7f\n", double_value);
}

NewFloat nfloat_double(NewFloat f)
{
    // Extract sign, exponent, and fraction from the NewFloat number
    uint32_t sign = (f >> 31) & 0x1;
    uint32_t exponent = (f >> 26) & 0x1F;
    uint32_t fraction = f & 0x3FFFFFF;

    // Double the fraction
    fraction = fraction << 1;

    // Check for overflow in the fraction
    if (fraction > 0x3FFFFFF) {
        // Shift right and increment exponent
        fraction = fraction >> 1;
        exponent += 1;

        // Check for exponent overflow
        if (exponent > 0x1F) {
            // Overflow, set to the maximum exponent
            exponent = 0x1F;
            fraction = 0;
        }
    }

    // Combine the sign, exponent, and fraction to get the result
    NewFloat result = (sign << 31) | (exponent << 26) | fraction;
    return result;
}

NewFloat nfloat_add(NewFloat a, NewFloat b) {
    // Extract sign, exponent, and mantissa
    uint32_t sign_a = (a >> 31) & 0x1;
    uint32_t sign_b = (b >> 31) & 0x1;
    uint32_t exponent_a = (a >> 26) & 0x1F;
    uint32_t exponent_b = (b >> 26) & 0x1F;
    uint32_t mantissa_a = a & 0x3FFFFFF;
    uint32_t mantissa_b = b & 0x3FFFFFF;

    // If exponent is not 0, add implicit bit to mantissa at the 27th spot
    if (exponent_a != 0) {
        mantissa_a |= 0x4000000;
    }
    if (exponent_b != 0) {
        mantissa_b |= 0x4000000;
    }

    // Adjust exponents
    while (exponent_a != exponent_b) {
        if (exponent_a > exponent_b) {
            mantissa_b >>= 1;
            exponent_b++;
        } else {
            mantissa_a >>= 1;
            exponent_a++;
        }
    }

    // Perform addition or subtraction based on sign
    uint32_t result_mantissa;
    if (sign_a == sign_b) {
        result_mantissa = mantissa_a + mantissa_b;
    } else {
        // Corrected subtraction
        result_mantissa = (mantissa_a > mantissa_b) ? (mantissa_a - mantissa_b) : (mantissa_b - mantissa_a);

        // Set the sign of the result based on the larger mantissa
        if (mantissa_a < mantissa_b) {
            sign_a = sign_b;
        }
    }

    // Check for and handle overflow
    if (result_mantissa & 0x4000000) {
        result_mantissa >>= 1;
        exponent_a++;
    }

    // Normalize result
    while (!(result_mantissa & 0x4000000)) {
        result_mantissa <<= 1;
        exponent_a--;
    }

    // Trim out the 27th bit
    result_mantissa &= 0x3FFFFFF;

    // Put sign, exponent, and result back together
    NewFloat result = (sign_a << 31) | (exponent_a << 26) | result_mantissa;
    return result;
}




