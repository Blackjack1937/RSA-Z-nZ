#ifndef MYBIGINT_H
#define MYBIGINT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct {
    uint32_t *data;  // array of 32-bit
    size_t size;    
} mpint_t;

void mpint_init(mpint_t *x);
void mpint_free(mpint_t *x);
void mpint_from_uint64(mpint_t *x, uint64_t val);
void mpint_print(const mpint_t *x);


// core ops
void mpint_copy(mpint_t *dst, const mpint_t *src);
int  mpint_cmp(const mpint_t *a, const mpint_t *b);     //   compare a,b
void mpint_add(mpint_t *r, const mpint_t *a, const mpint_t *b);
void mpint_sub(mpint_t *r, const mpint_t *a, const mpint_t *b); //assume a >= b
void mpint_mul(mpint_t *r, const mpint_t *a, const mpint_t *b);
void mpint_divmod(mpint_t *quot, mpint_t *rem, const mpint_t *num, const mpint_t *den); 
void mpint_mod(mpint_t *r, const mpint_t *x, const mpint_t *m);



#endif
