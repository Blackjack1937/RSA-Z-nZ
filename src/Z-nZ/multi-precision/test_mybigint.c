#include <stdio.h>
#include "mybigint.h"

int main() {
    mpint_t a, b, n;
    mpint_init(&a);
    mpint_init(&b);
    mpint_init(&n);

    // Example: a=10, b=25, n=31
    mpint_from_uint64(&a, 10ULL);
    mpint_from_uint64(&b, 25ULL);
    mpint_from_uint64(&n, 31ULL);

    printf("===== Minimal Big-Int Demo =====\n");
    printf("a = "); mpint_print(&a); printf("\n");
    printf("b = "); mpint_print(&b); printf("\n");
    printf("n = "); mpint_print(&n); printf("\n\n");

    // a+b mod n
    mpint_t sum, tmp;
    mpint_init(&sum);
    mpint_init(&tmp);
    mpint_add(&tmp, &a, &b);    // tmp = a + b
    mpint_mod(&sum, &tmp, &n);  // sum = (a+b) mod n
    mpint_free(&tmp);

    printf("(a+b) mod n = "); mpint_print(&sum); printf("\n");
    mpint_free(&sum);

    // a*b mod n
    mpint_t product;
    mpint_init(&product);
    mpint_mul(&product, &a, &b);  // product = a * b
    mpint_t product_mod; mpint_init(&product_mod);
    mpint_mod(&product_mod, &product, &n);
    printf("(a*b) mod n = "); mpint_print(&product_mod); printf("\n");
    mpint_free(&product);
    mpint_free(&product_mod);

    // Cleanup
    mpint_free(&a);
    mpint_free(&b);
    mpint_free(&n);

    return 0;
}
