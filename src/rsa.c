#include "rsa.h"

void rsa_keygen(Element p, Element q, Element *n, Element *e, Element *d) {
    *n = mul_mod64(p, q, (Element)-1); 
    //mul_mod64 uses mod, we want the full product p*q for n cause p*q < 2^64 is assumed, we can do a direct 64-bit mul
    *n = (Element)p * (Element)q;
    Element phi = (p - 1) * (q - 1);  // phi(n) = (p-1)*(q-1)

    *e = 65537;
    *d = invert(*e, phi); // d = e^{-1} mod phi(n)
}

Element rsa_encrypt(Element m, Element e, Element n) {
    return modexp(m, e, n);
}

Element rsa_decrypt(Element c, Element d, Element n) {
    return modexp(c, d, n);
}
