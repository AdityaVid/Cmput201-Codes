#include "ex6q1.h"

#define LEN 200000000
uint32_t MEMO[LEN];

// This function should be pure recursion - no dynamic programming allowed
uint32_t exp_mod_1(uint32_t base, uint32_t exp, uint32_t modulo) {
    EXP_MOD_1_CALL_COUNT++;
    if (exp == 1) { // base case
        return base;
    }
    else if (exp % 2 == 0) {
        uint32_t cases = exp / 2; // divide cases if even
        uint32_t mod_result = (exp_mod_1(base, cases, modulo) % modulo) * ((exp_mod_1(base, cases, modulo) % modulo)) % modulo;
        return mod_result;
    }
    else {
        uint32_t cases = exp - (exp / 2); // divide cases if odd
        uint32_t mod_result = (exp_mod_1(base, exp/2, modulo) % modulo) * ((exp_mod_1(base, cases, modulo) % modulo)) % modulo;
        return mod_result;
    }
        
    
}


uint32_t exp_mod_2(uint32_t base, uint32_t exp, uint32_t modulo) {
    EXP_MOD_2_CALL_COUNT++;
    
    // Check if the result is already memoized
    if (MEMO[exp] != 0) {
        return MEMO[exp];
    }
    
    // Base cases
    if (exp == 0) {
        return 1;
    }
    if (exp == 1) {
        return base % modulo;
    }
    
    // Split the exponent into two parts
    uint32_t exp1 = exp / 2;
    uint32_t exp2 = exp - exp1;
    
    // Recursive calls for the two parts
    uint32_t result1 = exp_mod_2(base, exp1, modulo);
    uint32_t result2 = exp_mod_2(base, exp2, modulo);
    
    // Combine the results using modular arithmetic
    uint32_t result = (result1 * result2) % modulo;
    
    // Memoize the result
    MEMO[exp] = result;
    
    return result;
}




int main(void) {
    uint32_t base, exp, modulo;

    if (scanf("%d %d %d", &base, &exp, &modulo) != 3) {
        return 1;
    }

    uint32_t mod_1 = exp_mod_1(base, exp, modulo);
    uint32_t mod_2 = exp_mod_2(base, exp, modulo);

    fprintf(stdout, "exp_mod_1 calls: %d\n", EXP_MOD_1_CALL_COUNT);
    fprintf(stdout, "exp_mod_2 calls: %d\n", EXP_MOD_2_CALL_COUNT);
    fprintf(stdout, "%d == %d\n", mod_1, mod_2);
	return 0;
}
