
#ifndef SIG_PERK_GF_POLY_ARITHMETIC_H
#define SIG_PERK_GF_POLY_ARITHMETIC_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "gf_arithmetic.h"

#if PERK_SECURITY_BYTES == 16
#define GF2_Q_POLY_MODULUS   {0, 3, 12};  // X^12 + X^3 + 1
#define KARAT_MUL_STACK_SIZE 44
#elif PERK_SECURITY_BYTES == 24
#define GF2_Q_POLY_MODULUS   {0, 7, 18};  // X^18 + X^7 + 1
#define KARAT_MUL_STACK_SIZE 76
#elif PERK_SECURITY_BYTES == 32
#define GF2_Q_POLY_MODULUS   {0, 1, 11, 17, 24};  // X^24 + X^17 + X^11+ X + 1
#define KARAT_MUL_STACK_SIZE 92
#else
#error "Invalid PERK_SECURITY_BYTES defined"
#endif

typedef gf2_q_elt gf2_q_poly[PERK_TOWER_FIELD_EXT];
typedef gf2_q_elt gf2_q_poly_ur[2 * PERK_TOWER_FIELD_EXT /*- 1*/];  // 1 more element for the use as temporary buffer

static inline void gf2_q_poly_kar_fold(gf2_q_poly res, const gf2_q_poly src, int32_t half_size, int32_t remaining) {
    int32_t i = 0;
    for (i = 0; i < remaining; ++i) {
        sig_perk_gf2_q_add(&res[i], src[i], src[i + half_size]);
    }

    for (; i < half_size; i++) {
        res[i] = src[i];
    }
}

static inline void gf2_q_poly_kar_mul_1_by_1(gf2_q_elt o[], const gf2_q_elt a[], const gf2_q_elt b[]) {
    sig_perk_gf2_q_mul(&o[0], a[0], b[0]);
}

static inline void gf2_q_poly_kar_mul_2_by_2(gf2_q_elt o[], const gf2_q_elt a[], const gf2_q_elt b[]) {
    // Hardcoded Karatsuba mul of two degree 1 polynomials
    // (a0 + a1 X) * (b0 + b1 X) = a0 * b0 + a1 * b1 X^2 +
    // ((a0 + a1) * (b0 + b1) - a0 * b0 - a1 * b1) X
    gf2_q_elt ea2, eb2, ed;
    sig_perk_gf2_q_mul(&o[0], a[0], b[0]);
    sig_perk_gf2_q_mul(&o[2], a[1], b[1]);
    sig_perk_gf2_q_add(&ea2, a[0], a[1]);
    sig_perk_gf2_q_add(&eb2, b[0], b[1]);
    sig_perk_gf2_q_mul(&ed, ea2, eb2);
    sig_perk_gf2_q_add(&o[1], o[0], o[2]);
    sig_perk_gf2_q_add(&o[1], o[1], ed);
}

static inline void gf2_q_poly_kar_mul(gf2_q_elt o[], const gf2_q_elt a[], const gf2_q_elt b[], int32_t size) {
    if (size == 1) {
        gf2_q_poly_kar_mul_1_by_1(o, a, b);
        return;
    }

    if (size == 2) {
        gf2_q_poly_kar_mul_2_by_2(o, a, b);
        return;
    }

    gf2_q_poly a2 = {0};
    gf2_q_poly b2 = {0};

    const int32_t ha_size = (size + 1) / 2;
    const int32_t remaining = size - ha_size;

    // Compute a2 = a0 + a1 and b2 = b0 + b1

    gf2_q_poly_kar_fold(a2, a, ha_size, remaining);
    gf2_q_poly_kar_fold(b2, b, ha_size, remaining);

    // Computation of d = a2*b2

    gf2_q_poly d = {0};
    gf2_q_poly_kar_mul(d, a2, b2, ha_size);

    // Computation of c0 = a0*b0 in the low part of o
    gf2_q_poly_kar_mul(o, a, b, ha_size);

    // Computation of c2 = a1*b1 in the high part of o (we ensure o has enough space)
    gf2_q_poly_kar_mul(o + 2 * ha_size, a + ha_size, b + ha_size, remaining);

    // Computation of c1 = d + c2 + c0
    for (int32_t i = 0; i < 2 * (remaining - 1) + 1; ++i) {
        sig_perk_gf2_q_add(&d[i], d[i], (o + 2 * ha_size)[i]);
    }

    for (int32_t i = 0; i < 2 * (ha_size - 1) + 1; ++i) {
        sig_perk_gf2_q_add(&d[i], d[i], o[i]);
    }

    // Add c1 to o
    for (int32_t i = 0; i <= 2 * (ha_size - 1) + 1; i++) {
        sig_perk_gf2_q_add(&o[i + ha_size], o[i + ha_size], d[i]);
    }
}

static inline void gf2_q_poly_mulmod(gf2_q_poly o, const gf2_q_poly a, const gf2_q_poly b) {
    // Step 1 - Carry-less multiplication
    gf2_q_poly_ur tmp_ur = {0};
    gf2_q_poly_kar_mul(tmp_ur, a, b, PERK_TOWER_FIELD_EXT);

    // Step 2 - Modular reduction modulo GF2_Q_POLY_MODULUS
    const gf2_q_elt modulus[] = GF2_Q_POLY_MODULUS;
    const size_t modulus_nb_coefs = sizeof(modulus) / sizeof(modulus[0]);
    int16_t max_deg = 2 * PERK_TOWER_FIELD_EXT - 1;
    for (int16_t i = max_deg - PERK_TOWER_FIELD_EXT; i > 0; --i) {
        for (size_t j = 0; j < modulus_nb_coefs - 1; ++j) {
            sig_perk_gf2_q_add(&tmp_ur[i + modulus[j] - 1], tmp_ur[i + modulus[j] - 1],
                               tmp_ur[i + (PERK_TOWER_FIELD_EXT - 1)]);
        }
        tmp_ur[i + (PERK_TOWER_FIELD_EXT - 1)] = 0;
    }
    memcpy(o, tmp_ur, sizeof(gf2_q_elt) * PERK_TOWER_FIELD_EXT);
}

static inline void gf2_q_poly_scal_mul(gf2_q_poly c, const gf2_q_poly a, const gf2_q_elt b) {
    for (size_t i = 0; i < PERK_TOWER_FIELD_EXT; ++i) {
        sig_perk_gf2_q_mul(&c[i], a[i], b);
    }
}

static inline void gf2_q_poly_add(gf2_q_poly c, const gf2_q_poly a, const gf2_q_poly b) {
    for (uint8_t i = 0; i < PERK_TOWER_FIELD_EXT; ++i) {
        c[i] = a[i] ^ b[i];
    }
}

static inline void gf2_q_poly_copy(gf2_q_poly b, const gf2_q_poly a) {
    for (uint8_t i = 0; i < PERK_TOWER_FIELD_EXT; ++i) {
        b[i] = a[i];
    }
}

static inline uint8_t gf2_q_poly_is_zero(const gf2_q_poly a) {
    for (uint8_t i = 0; i < PERK_TOWER_FIELD_EXT; ++i) {
        if (a[i] != 0) {
            return 1;
        }
    }
    return 0;
}

static inline void gf2_q_poly_expo(gf2_q_poly b, const gf2_q_poly a, uint8_t d) {
    if (d == 0) {
        b[0] = 1;
        for (unsigned i = 1; i < PERK_TOWER_FIELD_EXT; ++i) {
            b[i] = 0;
        }
    } else {
        gf2_q_poly tmp = {0};
        gf2_q_poly_copy(tmp, a);
        gf2_q_poly_copy(b, a);
        for (uint8_t i = 1; i < d; ++i) {
            gf2_q_poly_mulmod(b, b, tmp);
        }
    }
}

static inline void sig_perk_print_tower_field_element(gf2_q_poly a) {
    for (int i = 0; i < PERK_TOWER_FIELD_EXT; ++i) {
        printf("%03" PRIx16 " ", a[i]);
    }
}

static inline uint8_t gf2_q_poly_cmp(const gf2_q_poly b, const gf2_q_poly a) {
    for (uint8_t i = 0; i < PERK_TOWER_FIELD_EXT; ++i) {
        if (a[i] != b[i]) {
            return 1;
        }
    }
    return 0;
}

#endif  // SIG_PERK_GF_POLY_ARITHMETIC_H
