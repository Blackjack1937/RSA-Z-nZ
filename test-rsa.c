#include <stdio.h>
#include "rsa.h"

int main() {
    
    Element p = 313486403ULL;
    Element q = 521502889ULL;


    Element n, e, d;
    rsa_keygen(p, q, &n, &e, &d);
    printf("===== RSA Demo with Large Primes =====\n");
    printf("p = %llu, q = %llu\n", 
           (unsigned long long)p, (unsigned long long)q);
    printf("n = %llu\n", (unsigned long long)n);
    printf("e = %llu, d = %llu\n", 
           (unsigned long long)e, (unsigned long long)d);

    Element message = 123456789ULL;
    Element ciphertext = rsa_encrypt(message, e, n);
    Element decrypted  = rsa_decrypt(ciphertext, d, n);

    printf("\nOriginal message : %llu\n", (unsigned long long)message);
    printf("Ciphertext       : %llu\n", (unsigned long long)ciphertext);
    printf("Decrypted        : %llu\n", (unsigned long long)decrypted);

    if (decrypted == message) {
        printf("RSA Decryption successful.\n");
    } else {
        printf("RSA Decryption mismatch!\n");
    }
    return 0;
}
