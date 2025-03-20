#ifndef ZNZ_H
#define ZNZ_H
#include <stdint.h>

typedef uint64_t Element;

Element add(Element x, Element y, Element n);
// Element mul(Element x, Element y, Element n);
Element neg(Element x, Element n);

Element mul_mod64(Element x, Element y, Element n);


int isInvertible(Element x, Element n);
Element invert(Element x, Element n);

Element gcd(Element a, Element b);
Element modular_inverse(Element a, Element m);
Element modexp(Element x, uint64_t k, Element n);

#endif
