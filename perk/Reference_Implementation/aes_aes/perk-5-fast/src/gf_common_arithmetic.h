#ifndef SIG_PERK_GF_Q_ARITHMETIC_H
#define SIG_PERK_GF_Q_ARITHMETIC_H

#include <stddef.h>
#include <stdint.h>
#include "parameters.h"

// GF(2^11)
#if (PERK_PARAM_Q != 11)
#error implementation is only for GF(2^11)
#endif

typedef uint16_t gf2_q_elt;
#define GF2_Q_ELT_UINT8_SIZE 2

#define GF2_Q_FIELD_MUL_ORDER ((1 << PERK_PARAM_Q) - 1)
#define GF2_Q_FIELD_POLY      0X805  // Irreducible polynomial

void sig_perk_gf2_q_add(gf2_q_elt *c, gf2_q_elt a, gf2_q_elt b);
void sig_perk_gf2_q_mul(gf2_q_elt *c, gf2_q_elt a, gf2_q_elt b);
uint16_t sig_perk_gf2_q_square(uint16_t a);
void sig_perk_gf2_q_inverse(gf2_q_elt *b, gf2_q_elt a);

extern const uint16_t gf2_11_expTab[];
extern const uint16_t gf2_11_logTab[];

// GF(2^8)
// GF(2^8) with X^8 + X^4 + X^3 + X + 1
#define GF2_8_FIELD_POLY 0x11B

#define GF2_8_FIELD_M  8
#define GF2_8_ELT_SIZE 1

#define GF2_8_ELT_UINT8_SIZE    1
#define GF2_8_ELT_UR_UINT8_SIZE 2

typedef uint8_t gf2_8_elt;
typedef uint32_t gf2_8_elt_ur;

uint16_t gf2_8_mod(uint16_t i);
void sig_perk_gf2_8_mul(gf2_8_elt *c, gf2_8_elt a, gf2_8_elt b);
void sig_perk_gf2_8_add(gf2_8_elt *o, const gf2_8_elt e1, const gf2_8_elt e2);

extern const uint16_t gf2_8_expTab[];
extern const uint16_t gf2_8_logTab[];

// GF2_9
// GF(2^9) with X^9 + X + 1
#define GF2_9_FIELD_POLY 0x203

#define GF2_9_FIELD_M  9
#define GF2_9_ELT_SIZE 1

#define GF2_9_ELT_UINT8_SIZE    2
#define GF2_9_ELT_UR_UINT8_SIZE 2

typedef uint16_t gf2_9_elt;
typedef uint32_t gf2_9_elt_ur;

uint16_t gf2_9_mod(uint32_t i);
void sig_perk_gf2_9_mul(gf2_9_elt *c, gf2_9_elt a, gf2_9_elt b);
void sig_perk_gf2_9_add(gf2_9_elt *o, const gf2_9_elt e1, const gf2_9_elt e2);

extern const uint16_t gf2_9_expTab[];
extern const uint16_t gf2_9_logTab[];

// GF2_12
// GF(2^12) with X^12 + X^3 + 1
#define GF2_12_FIELD_POLY 0x1009

#define GF2_12_FIELD_M  12
#define GF2_12_ELT_SIZE 1

#define GF2_12_ELT_UINT8_SIZE    2
#define GF2_12_ELT_UR_UINT8_SIZE 3

typedef uint16_t gf2_12_elt;
typedef uint32_t gf2_12_elt_ur;

uint16_t gf2_12_mod(uint32_t i);
void sig_perk_gf2_12_mul(gf2_12_elt *c, gf2_12_elt a, gf2_12_elt b);
void sig_perk_gf2_12_add(gf2_12_elt *o, const gf2_12_elt e1, const gf2_12_elt e2);

extern const uint16_t gf2_12_expTab[];
extern const uint16_t gf2_12_logTab[];

// GF2_13
// GF(2^13) with X^13 + X^4 + X^3 + X + 1
#define GF2_13_FIELD_POLY 0x201b

#define GF2_13_FIELD_M  13
#define GF2_12_ELT_SIZE 1

#define GF2_13_ELT_UINT8_SIZE    2
#define GF2_13_ELT_UR_UINT8_SIZE 3

typedef uint16_t gf2_13_elt;
typedef uint32_t gf2_13_elt_ur;

uint16_t gf2_13_mod(uint32_t i);
void sig_perk_gf2_13_mul(gf2_13_elt *c, gf2_13_elt a, gf2_13_elt b);
void sig_perk_gf2_13_add(gf2_13_elt *o, const gf2_13_elt e1, const gf2_13_elt e2);

extern const uint16_t gf2_13_expTab[];
extern const uint16_t gf2_13_logTab[];

// GF2^64
// X^64 + X^4 + X^3 + X^1 + 1

#define GF2_64_FIELD_M 64

#define GF2_64_ELT_SIZE      1
#define GF2_64_ELT_DATA_SIZE 1

#define GF2_64_ELT_UR_SIZE      2
#define GF2_64_ELT_UR_DATA_SIZE 2

#define GF2_64_ELT_UINT8_SIZE    8
#define GF2_64_ELT_UR_UINT8_SIZE 16

typedef int64_t gf2_64_elt_int;
typedef uint64_t gf2_64_elt_uint;
typedef uint64_t gf2_64_elt[GF2_64_ELT_SIZE];
typedef uint64_t gf2_64_elt_ur[GF2_64_ELT_UR_SIZE];
typedef uint64_t *gf2_64_elt_ptr;

void sig_perk_gf2_64_add(gf2_64_elt o, const gf2_64_elt e1, const gf2_64_elt e2);
void sig_perk_gf2_64_mul(gf2_64_elt o, gf2_64_elt e1, gf2_64_elt e2);
void sig_perk_gf2_64_reduce(gf2_64_elt o, const gf2_64_elt_ur e);
uint8_t sig_perk_gf2_64_elt_get_coefficient(const gf2_64_elt e, uint32_t index);
void sig_perk_gf2_64_elt_print(const gf2_64_elt e);
void sig_perk_gf2_64_elt_ur_print(const gf2_64_elt_ur e);
void sig_perk_gf2_64_from_bytes(gf2_64_elt e, uint8_t bytes_array[GF2_64_ELT_UINT8_SIZE]);

static inline gf2_q_elt sig_perk_gf2_q_reduce(uint64_t x) {
    for (size_t i = 0; i < 2; ++i) {
        uint64_t mod = x >> PERK_PARAM_Q;
        x &= (1 << PERK_PARAM_Q) - 1;
        x ^= mod;
        mod <<= 2;
        x ^= mod;
    }
    return (gf2_q_elt)x;
}

#endif  // SIG_PERK_GF_Q_ARITHMETIC_H
