#include "rsa.h"

// already have gcd, invert, modexp from znz files

void rsa_keygen(Element p, Element q, Element *n, Element *e, Element *d) {
    *n = p * q; 
    Element phi = (p - 1) * (q - 1);
    *e = 65537;  
    *d = invert(*e, phi);
}

Element rsa_encrypt(Element m, Element e, Element n) {
    return modexp(m, e, n);
}

Element rsa_decrypt(Element c, Element d, Element n) {
    return modexp(c, d, n);
}
