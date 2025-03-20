#include <stdio.h>
#include "rsa.h"

static Element prime_list[] = {
    313486403ULL, 521502889ULL, 804582047ULL, 529940513ULL,
    184789603ULL, 981009509ULL, 618567539ULL, 117004469ULL,
    773296369ULL, 240271079ULL
};



int main() {
    size_t total_primes = sizeof(prime_list)/sizeof(prime_list[0]);
    Element message = 123456789ULL;

    printf("===== Extended RSA Demo with proposed primes =====\n");
 
    

    for (size_t i = 0; i < total_primes; i++) {
        for (size_t j = i + 1; j < total_primes; j++) {
            Element p = prime_list[i];
            Element q = prime_list[j];

          
            Element n, e, d;
            rsa_keygen(p, q, &n, &e, &d);
            Element ciphertext = rsa_encrypt(message, e, n);
            Element decrypted  = rsa_decrypt(ciphertext, d, n);

            //print res
            printf("\n-- Testing p=%llu, q=%llu --\n",
                   (unsigned long long)p, (unsigned long long)q);
            printf("n = %llu, e = %llu, d = %llu\n",
                   (unsigned long long)n,
                   (unsigned long long)e,
                   (unsigned long long)d);
            printf("Message    = %llu\n", (unsigned long long)message);
            printf("Ciphertext = %llu\n", (unsigned long long)ciphertext);
            printf("Decrypted  = %llu\n", (unsigned long long)decrypted);

            if (decrypted == message) {
                printf("RSA Decryption successful.\n");
            } else {
                printf("RSA Decryption mismatch !.\n");
            }
        }
    }
    return 0;
}
