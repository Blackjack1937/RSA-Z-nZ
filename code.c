#include <stdio.h>
#include <stdint.h>

typedef uint64_t Element;

/*---------------------------------------------------------
  gcd(a, b)
  Computes the greatest common divisor using Euclid's algorithm.
---------------------------------------------------------*/
Element gcd(Element a, Element b) {
    while (b != 0) {
        Element temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/*---------------------------------------------------------
  extended_gcd(a, b, x, y)
  Extended Euclidean Algorithm.
  Finds integers x, y such that a*x + b*y = gcd(a, b).
  Returns gcd(a, b).
---------------------------------------------------------*/
Element extended_gcd(Element a, Element b, int64_t *x, int64_t *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int64_t x1, y1;
    Element g = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

/*---------------------------------------------------------
  modular_inverse(a, m)
  Returns x such that (a * x) mod m = 1, if it exists.
  Uses extended Euclid to solve a*x + m*y = 1.
---------------------------------------------------------*/
Element modular_inverse(Element a, Element m) {
    int64_t x, y;
    Element g = extended_gcd(a, m, &x, &y);
    if (g != 1) {
        // No inverse if gcd(a, m) != 1
        return 0;
    }

    // x might be negative, so take it mod m
    int64_t res = x % (int64_t)m;
    if (res < 0) {
        res += m;
    }
    return (Element)res;
}

/*---------------------------------------------------------
  add(x, y, n)
  Addition modulo n
---------------------------------------------------------*/
Element add(Element x, Element y, Element n) {
    return (x + y) % n;
}

/*---------------------------------------------------------
  mul(x, y, n)
  Multiplication modulo n
---------------------------------------------------------*/
Element mul(Element x, Element y, Element n) {
    return (x * y) % n;
}

/*---------------------------------------------------------
  neg(x, n)
  Negation modulo n
---------------------------------------------------------*/
Element neg(Element x, Element n) {
    return (n - x) % n;
}

/*---------------------------------------------------------
  isInvertible(x, n)
  Checks if x is invertible mod n (gcd(x, n) == 1)
---------------------------------------------------------*/
int isInvertible(Element x, Element n) {
    return (gcd(x, n) == 1);
}

/*---------------------------------------------------------
  invert(x, n)
  Returns the inverse of x mod n, or 0 if not invertible
---------------------------------------------------------*/
Element invert(Element x, Element n) {
    if (!isInvertible(x, n)) {
        return 0; // No inverse exists
    }
    return modular_inverse(x, n);
}

/*---------------------------------------------------------
  modexp(x, k, n)
  Computes x^k mod n using exponentiation by squaring
---------------------------------------------------------*/
Element modexp(Element x, uint64_t k, Element n) {
    Element result = 1;
    x = x % n; // Reduce x modulo n initially

    while (k > 0) {
        if (k & 1) { // if k is odd
            result = (result * x) % n;
        }
        k >>= 1;        // divide k by 2
        x = (x * x) % n;
    }
    return result;
}

/*---------------------------------------------------------
  rsa_keygen(p, q, n, e, d)
  Generates an RSA keypair (n, e, d) from primes p and q
---------------------------------------------------------*/
void rsa_keygen(Element p, Element q, Element *n, Element *e, Element *d) {
    *n = p * q;                 // Modulus
    Element phi = (p - 1) * (q - 1);

    *e = 65537;                 // A common public exponent
    *d = invert(*e, phi);       // d = e^{-1} mod phi(n)
}

/*---------------------------------------------------------
  rsa_encrypt(m, e, n)
  Encrypts message m to ciphertext = m^e mod n
---------------------------------------------------------*/
Element rsa_encrypt(Element m, Element e, Element n) {
    return modexp(m, e, n);
}

/*---------------------------------------------------------
  rsa_decrypt(c, d, n)
  Decrypts ciphertext c to message = c^d mod n
---------------------------------------------------------*/
Element rsa_decrypt(Element c, Element d, Element n) {
    return modexp(c, d, n);
}

/*---------------------------------------------------------
  main()
  Minimal testing of (a)–(d) with small examples
---------------------------------------------------------*/
int main() {
    printf("======== Testing Modular Arithmetic, Part (b) ========\n");
    Element n = 31;
    Element x = 10, y = 25;

    printf("n = %lu, x = %lu, y = %lu\n", (unsigned long)n,
           (unsigned long)x, (unsigned long)y);

    Element sum = add(x, y, n);
    Element prod = mul(x, y, n);
    Element negx = neg(x, n);
    Element invx = invert(x, n);

    printf("x + y mod n = %lu\n", (unsigned long)sum);
    printf("x * y mod n = %lu\n", (unsigned long)prod);
    printf("-x mod n    = %lu\n", (unsigned long)negx);

    if (invx == 0) {
        printf("x = %lu is not invertible mod %lu\n", (unsigned long)x, (unsigned long)n);
    } else {
        printf("Inverse of x mod n = %lu\n", (unsigned long)invx);
    }

    printf("\n======== Testing Modular Exponentiation, Part (c) ========\n");
    Element base = 7;
    uint64_t exponent = 13;
    Element modexp_result = modexp(base, exponent, n);
    printf("%lu^%lu mod %lu = %lu\n", (unsigned long)base, (unsigned long)exponent,
           (unsigned long)n, (unsigned long)modexp_result);

    printf("\n======== Testing RSA, Part (d) ========\n");
    // For demonstration only - these are small primes, not secure!
    Element p = 11, q = 13;
    Element N, e, d;
    rsa_keygen(p, q, &N, &e, &d);

    printf("Generated RSA keys:\n");
    printf("  n = %lu\n", (unsigned long)N);
    printf("  e = %lu (public exponent)\n", (unsigned long)e);
    printf("  d = %lu (private exponent)\n", (unsigned long)d);

    Element message = 42;
    Element ciphertext = rsa_encrypt(message, e, N);
    Element decrypted  = rsa_decrypt(ciphertext, d, N);

    printf("Message      : %lu\n", (unsigned long)message);
    printf("Ciphertext   : %lu\n", (unsigned long)ciphertext);
    printf("Decrypted    : %lu\n", (unsigned long)decrypted);

    if (decrypted == message) {
        printf("RSA Decryption successful!\n");
    } else {
        printf("RSA Decryption failed.\n");
    }

    return 0;
}
