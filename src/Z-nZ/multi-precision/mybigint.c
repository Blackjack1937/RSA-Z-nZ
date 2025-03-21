#include "mybigint.h"
#include <string.h>

// static void ensure_capacity(mpint_t *x, size_t needed) {
//     if (x->size < needed) {
//         x->data = realloc(x->data, needed * sizeof(uint32_t));
//         memset(x->data + x->size, 0, (needed - x->size) * sizeof(uint32_t));
//         x->size = needed;
//     }
// }

static void normalize(mpint_t *x) {
    while (x->size > 1 && x->data[x->size - 1] == 0) {
        x->size--;
    }
    if (x->size == 0) {
        x->size = 1;
    }
}

void mpint_init(mpint_t *x) {
    x->size = 1;
    x->data = calloc(1, sizeof(uint32_t));
    x->data[0] = 0;
}

void mpint_free(mpint_t *x) {
    free(x->data);
    x->data = NULL;
    x->size = 0;
}

void mpint_from_uint64(mpint_t *x, uint64_t val) {
    mpint_free(x);
    x->size = (val > 0xFFFFFFFFULL) ? 2 : 1;
    x->data = calloc(x->size, sizeof(uint32_t));
    x->data[0] = (uint32_t)(val & 0xFFFFFFFFULL);
    if (x->size > 1) {
        x->data[1] = (uint32_t)((val >> 32) & 0xFFFFFFFFULL);
    }
    normalize(x);
}

void mpint_print(const mpint_t *x) {
    printf("0x"); // print in hex
    for (size_t i = x->size; i > 0; i--) {
        printf("%08X", x->data[i - 1]);
    }
}



void mpint_copy(mpint_t *dst, const mpint_t *src) {
    mpint_free(dst);
    dst->size = src->size;
    dst->data = calloc(dst->size, sizeof(uint32_t));
    memcpy(dst->data, src->data, dst->size * sizeof(uint32_t));
}

int mpint_cmp(const mpint_t *a, const mpint_t *b) {
    //  compare sizes
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;
    for (size_t i = a->size; i > 0; i--) {
        uint32_t aa = a->data[i-1];
        uint32_t bb = b->data[i-1];
        if (aa > bb) return 1;
        if (aa < bb) return -1;
    }
    return 0;
}

void mpint_add(mpint_t *r, const mpint_t *a, const mpint_t *b) {
    //ensure capacity for the bigger & possible carry
    size_t max_size = (a->size > b->size ? a->size : b->size) + 1;
    mpint_free(r);
    r->data = calloc(max_size, sizeof(uint32_t));
    r->size = max_size;
    uint64_t carry = 0;
    for (size_t i = 0; i < max_size; i++) {
        uint64_t av = (i < a->size) ? a->data[i] : 0ULL;
        uint64_t bv = (i < b->size) ? b->data[i] : 0ULL;
        uint64_t sum = av + bv + carry;
        r->data[i] = (uint32_t)(sum & 0xFFFFFFFFULL);
        carry = sum >> 32;
    }
    normalize(r);
}

void mpint_sub(mpint_t *r, const mpint_t *a, const mpint_t *b) {
    mpint_free(r); //assume a >= b
    r->size = a->size;
    r->data = calloc(r->size, sizeof(uint32_t));
    uint64_t borrow = 0;
    for (size_t i = 0; i < r->size; i++) {
        uint64_t av = (i < a->size) ? a->data[i] : 0ULL;
        uint64_t bv = (i < b->size) ? b->data[i] : 0ULL;
        uint64_t diff = av - bv - borrow;
        r->data[i] = (uint32_t)(diff & 0xFFFFFFFFULL);
        borrow = (diff >> 32) & 1ULL; // if diff < 0, borrow=1
    }


    normalize(r);
}



// overflow here too ? 
void mpint_mul(mpint_t *r, const mpint_t *a, const mpint_t *b) {
    mpint_free(r);
    r->size = a->size + b->size;
    r->data = calloc(r->size, sizeof(uint32_t));

    for (size_t i = 0; i < a->size; i++) {
        uint64_t carry = 0ULL;
        for (size_t j = 0; j < b->size || carry; j++) {
            uint64_t cur = r->data[i+j] + (uint64_t)a->data[i] * 
                           (j < b->size ? b->data[j] : 0ULL) + carry;
            r->data[i+j] = (uint32_t)(cur & 0xFFFFFFFFULL);
            carry = cur >> 32;
        }
    }
    normalize(r);
}

void mpint_divmod(mpint_t *quot, mpint_t *rem, const mpint_t *num, const mpint_t *den){
    mpint_init(quot);
    mpint_copy(rem, num);

                                    //iff rem < den => quotient=0, remainder=num
    if (mpint_cmp(rem, den) < 0) {
        return;
    }

    mpint_t one, tempDen;
    mpint_init(&one);
    mpint_init(&tempDen);
    mpint_from_uint64(&one, 1ULL);
//loop
    while (mpint_cmp(rem, den) >= 0) {
        mpint_copy(&tempDen, den);

        mpint_t multiple;
        mpint_init(&multiple);
        mpint_copy(&multiple, &one);

        while (1) {
        mpint_t temp2;
        mpint_init(&temp2);
        mpint_add(&temp2, &tempDen, &tempDen);

        if (mpint_cmp(&temp2, rem) > 0) {
            mpint_free(&temp2);
            break;
        }

        mpint_free(&tempDen);
        mpint_init(&tempDen);
        mpint_copy(&tempDen, &temp2);
        mpint_free(&temp2);

        mpint_t mul2;
        mpint_init(&mul2);
        mpint_add(&mul2, &multiple, &multiple);

        mpint_free(&multiple);
        mpint_init(&multiple);
        mpint_copy(&multiple, &mul2);
        mpint_free(&mul2);
        }
        mpint_t newRem; // subtract tempden from rem
        mpint_init(&newRem);
        mpint_sub(&newRem, rem, &tempDen);
        mpint_free(rem);
        mpint_init(rem);
        mpint_copy(rem, &newRem);
        mpint_free(&newRem);
        
        
        mpint_t newQuot;
        mpint_init(&newQuot);
        mpint_add(&newQuot, quot, &multiple);

        mpint_free(quot);
        mpint_init(quot);
        mpint_copy(quot, &newQuot);
        mpint_free(&newQuot);
        mpint_free(&multiple);
        mpint_free(&tempDen);
    }

    mpint_free(&one);
}


void mpint_mod(mpint_t *r, const mpint_t *x, const mpint_t *m) {
    mpint_t q, tmp;
    mpint_init(&q);
    mpint_init(&tmp);

    mpint_divmod(&q, &tmp, x, m);
    mpint_copy(r, &tmp);

    mpint_free(&q);
    mpint_free(&tmp);
}


