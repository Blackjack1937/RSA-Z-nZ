#include <stdio.h>
#include "znz.h"

Element gcd(Element a, Element b) {
    while (b != 0) {
        Element temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
static Element extended_gcd(Element a, Element b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    Element g = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

Element modular_inverse(Element a, Element m) {
    long long x, y;
    Element g = extended_gcd(a, m, &x, &y);
    if (g != 1) {
        return 0;
    }
    long long res = x % (long long)m;
    if (res < 0) {
        res += m;
    }
    return (Element)res;
}
Element add(Element x, Element y, Element n) {
    return (x + y) % n;
}
Element neg(Element x, Element n) {
    return (n - x) % n;
}
int isInvertible(Element x, Element n) {
    return (gcd(x, n) == 1);
}

Element invert(Element x, Element n) {
    if (!isInvertible(x, n)) {
        return 0;
    }
    return modular_inverse(x, n);
}


Element mul_mod64(Element x, Element y, Element n) {  //  changed mul to avoid overflow, needs testing
    __uint128_t product = (__uint128_t)x * (__uint128_t)y;
    return (Element)(product % n);
}

Element modexp(Element x, uint64_t k, Element n) {
    Element result = 1;
    x %= n; // reduce once initially

    while (k > 0) {
        if (k & 1) {  // if k is odd
            result = mul_mod64(result, x, n);
        }
        k >>= 1;
        x = mul_mod64(x, x, n);
    }
    return result;
}
