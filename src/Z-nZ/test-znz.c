#include <stdio.h>
#include "znz.h"

int main() {
    Element n = 31;
    Element x = 10, y = 25;

    printf("======== Testing Z/nZ Functions ========\n");
    printf("n = %llu, x = %llu, y = %llu\n",
           (unsigned long long)n, (unsigned long long)x, (unsigned long long)y);

    Element sum = add(x, y, n);
   /*  Element product = mul(x, y, n);  */
    Element product = mul_mod64(x, y, n);  // replaced mul with mul_mod64
    Element negx = neg(x, n);

    printf("(x + y) mod n = %llu\n", (unsigned long long)sum);
    printf("(x * y) mod n = %llu\n", (unsigned long long)product);
    printf("-x mod n      = %llu\n", (unsigned long long)negx);

    if (isInvertible(x, n)) {
        Element invx = invert(x, n);
        printf("Inverse of x  = %llu\n", (unsigned long long)invx);
    } else {
        printf("x not invertible mod n\n");
    }

    Element base = 7;
    uint64_t exponent = 13;
    Element modexp_result = modexp(base, exponent, n);
    printf("ModExp: %llu^%llu mod %llu = %llu\n",
           (unsigned long long)base, (unsigned long long)exponent,
           (unsigned long long)n, (unsigned long long)modexp_result);

    return 0;
}
