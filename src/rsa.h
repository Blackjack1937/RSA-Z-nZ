#ifndef RSA_H
#define RSA_H
#include <stdint.h>
#include "znz.h"  

void rsa_keygen(Element p, Element q, Element *n, Element *e, Element *d);

Element rsa_encrypt(Element m, Element e, Element n);
Element rsa_decrypt(Element c, Element d, Element n);

#endif
