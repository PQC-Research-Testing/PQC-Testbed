
#include "gf_common_arithmetic.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GF(2^11)
uint16_t gf2_q_mod(uint16_t i);
uint16_t gf2_q_exp(uint16_t i);
uint16_t gf2_q_log(uint16_t elt);
uint16_t gf2_q_reduce(uint64_t x);
void gf_generate_lut(uint16_t *exp, uint16_t *log, unsigned int m);

void sig_perk_gf2_q_add(gf2_q_elt *c, gf2_q_elt a, gf2_q_elt b) {
    *c = a ^ b;
}

void gf_generate_lut(uint16_t *exp, uint16_t *log, unsigned int m) {
    uint16_t elt = 1;
    uint16_t alpha = 2;
    uint16_t gf_poly = GF2_Q_FIELD_POLY;

    for (int32_t i = 0; i < (1 << m) - 1; ++i) {
        exp[i] = elt;
        log[elt] = i;

        elt *= alpha;
        if (elt >= 1 << m)
            elt ^= gf_poly;
    }

    exp[(1 << m) - 1] = 1;
    exp[1 << m] = 2;
    exp[(1 << m) + 1] = 4;
    log[0] = 1 << m;  // by convention
}

void sig_perk_gf2_q_mul(gf2_q_elt *c, gf2_q_elt a, gf2_q_elt b) {
    // mask = 0xffff if neither a nor b is zero. Otherwise mask is 0.
    int16_t mask = ((gf2_11_logTab[a] | gf2_11_logTab[b]) >> PERK_PARAM_Q) - 1;
    *c = mask & gf2_11_expTab[gf2_q_mod(gf2_11_logTab[a] + gf2_11_logTab[b])];
}

uint16_t gf2_q_mod(uint16_t i) {
    uint16_t tmp = i - ((1 << PERK_PARAM_Q) - 1);
    // mask = 0xffff if (i < GF_MUL_ORDER)
    int16_t mask = -(tmp >> 15);

    return tmp + (mask & ((1 << PERK_PARAM_Q) - 1));
}

uint16_t sig_perk_gf2_q_square(uint16_t a) {
    uint32_t b = a;
    uint32_t s = b & 1;
    for (size_t i = 1; i < PERK_PARAM_Q; ++i) {
        b <<= 1;
        s ^= b & (1 << 2 * i);
    }

    return sig_perk_gf2_q_reduce(s);
}

void sig_perk_gf2_q_inverse(gf2_q_elt *b, gf2_q_elt a) {
    size_t pow = (1 << PERK_PARAM_Q) - 2;
    uint16_t inv = 1;

    do {
        if (pow & 1)
            sig_perk_gf2_q_mul(&inv, inv, a);
        a = sig_perk_gf2_q_square(a);
        pow >>= 1;
    } while (pow);

    *b = inv;
}

// GF(2^8)

uint16_t gf2_8_mod(uint16_t i) {
    uint16_t tmp = i - ((1 << GF2_8_FIELD_M) - 1);
    int16_t mask = -(tmp >> 15);

    return tmp + (mask & ((1 << GF2_8_FIELD_M) - 1));
}

void sig_perk_gf2_8_mul(gf2_8_elt *c, gf2_8_elt a, gf2_8_elt b) {
    // mask = 0xffff if neither a nor b is zero. Otherwise mask is 0.
    int16_t mask = ((gf2_8_logTab[a] | gf2_8_logTab[b]) >> GF2_8_FIELD_M) - 1;
    *c = mask & gf2_8_expTab[gf2_8_mod(gf2_8_logTab[a] + gf2_8_logTab[b])];
}

void sig_perk_gf2_8_add(gf2_8_elt *o, const gf2_8_elt e1, const gf2_8_elt e2) {
    *o = e1 ^ e2;
}

// GF(2^9)

uint16_t gf2_9_mod(uint32_t i) {
    uint32_t tmp = i - ((1 << GF2_9_FIELD_M) - 1);
    int32_t mask = -(tmp >> 31);

    return tmp + (mask & ((1 << GF2_9_FIELD_M) - 1));
}

void sig_perk_gf2_9_mul(gf2_9_elt *c, gf2_9_elt a, gf2_9_elt b) {
    // mask = 0xffff if neither a nor b is zero. Otherwise mask is 0.
    int16_t mask = ((gf2_9_logTab[a] | gf2_9_logTab[b]) >> GF2_9_FIELD_M) - 1;
    *c = mask & gf2_9_expTab[gf2_9_mod(gf2_9_logTab[a] + gf2_9_logTab[b])];
}

void sig_perk_gf2_9_add(gf2_9_elt *o, const gf2_9_elt e1, const gf2_9_elt e2) {
    *o = e1 ^ e2;
}

// GF(2^12)

uint16_t gf2_12_mod(uint32_t i) {
    uint32_t tmp = i - ((1 << GF2_12_FIELD_M) - 1);
    int32_t mask = -(tmp >> 31);

    return tmp + (mask & ((1 << GF2_12_FIELD_M) - 1));
}

void sig_perk_gf2_12_mul(gf2_12_elt *c, gf2_12_elt a, gf2_12_elt b) {
    // mask = 0xffff if neither a nor b is zero. Otherwise mask is 0.
    int16_t mask = ((gf2_12_logTab[a] | gf2_12_logTab[b]) >> GF2_12_FIELD_M) - 1;
    *c = mask & gf2_12_expTab[gf2_12_mod(gf2_12_logTab[a] + gf2_12_logTab[b])];
}

void sig_perk_gf2_12_add(gf2_12_elt *o, const gf2_12_elt e1, const gf2_12_elt e2) {
    *o = e1 ^ e2;
}

// GF(2^13)

uint16_t gf2_13_mod(uint32_t i) {
    uint32_t tmp = i - ((1 << GF2_13_FIELD_M) - 1);
    int32_t mask = -(tmp >> 31);

    return tmp + (mask & ((1 << GF2_13_FIELD_M) - 1));
}

void sig_perk_gf2_13_mul(gf2_13_elt *c, gf2_13_elt a, gf2_13_elt b) {
    // mask = 0xffff if neither a nor b is zero. Otherwise mask is 0.
    int16_t mask = ((gf2_13_logTab[a] | gf2_13_logTab[b]) >> GF2_13_FIELD_M) - 1;
    *c = mask & gf2_13_expTab[gf2_13_mod(gf2_13_logTab[a] + gf2_13_logTab[b])];
}

void sig_perk_gf2_13_add(gf2_13_elt *o, const gf2_13_elt e1, const gf2_13_elt e2) {
    *o = e1 ^ e2;
}

// GF2^64

void sig_perk_gf2_64_ur_mul(gf2_64_elt_ur o, const gf2_64_elt e1, const gf2_64_elt e2);
void sig_perk_gf2_64_ur_set(gf2_64_elt_ur o, const gf2_64_elt_ur e);
void sig_perk_gf2_64_set(gf2_64_elt o, const gf2_64_elt e);
void sig_perk_gf2_64_ur_set_zero(gf2_64_elt_ur o);

void sig_perk_gf2_64_add(gf2_64_elt o, const gf2_64_elt e1, const gf2_64_elt e2) {
    o[0] = e1[0] ^ e2[0];
}

void sig_perk_gf2_64_mul(gf2_64_elt o, gf2_64_elt e1, gf2_64_elt e2) {
    gf2_64_elt_ur tmp;
    sig_perk_gf2_64_ur_mul(tmp, e1, e2);
    sig_perk_gf2_64_reduce(o, tmp);
}

void sig_perk_gf2_64_ur_mul(gf2_64_elt_ur o, const gf2_64_elt e1, const gf2_64_elt e2) {
    uint64_t shifts[64][GF2_64_ELT_SIZE + 1];
    sig_perk_gf2_64_set(shifts[0], e2);
    shifts[0][GF2_64_ELT_SIZE] = 0;

    for (uint8_t shift = 1; shift < 64; shift++) {
        shifts[shift][0] = shifts[shift - 1][0] << 1;
        for (uint8_t i = 1; i < GF2_64_ELT_SIZE + 1; i++) {
            shifts[shift][i] = (shifts[shift - 1][i] << 1) | (shifts[shift - 1][i - 1] >> 63);
        }
    }

    sig_perk_gf2_64_ur_set_zero(o);
    for (uint8_t i = 0; i < GF2_64_FIELD_M; i++) {
        uint8_t shift = i % 64;
        uint8_t offset = i / 64;
        uint64_t multiplier = (e1[offset] >> shift) & 0x1;
        for (uint8_t j = 0; j < GF2_64_ELT_SIZE + 1; j++) {
            o[j + offset] ^= multiplier * shifts[shift][j];
        }
    }
}

void sig_perk_gf2_64_reduce(gf2_64_elt o, const gf2_64_elt_ur e) {
    uint64_t tmp = e[1] ^ (e[1] >> 61) ^ (e[1] >> 60);
    o[0] = e[0] ^ tmp ^ (tmp << 1) ^ (tmp << 3) ^ (tmp << 4);
}

void sig_perk_gf2_64_ur_set(gf2_64_elt_ur o, const gf2_64_elt_ur e) {
    for (size_t i = 0; i < GF2_64_ELT_UR_SIZE; i++) {
        o[i] = e[i];
    }
}

void sig_perk_gf2_64_ur_set_zero(gf2_64_elt_ur o) {
    for (size_t i = 0; i < GF2_64_ELT_UR_SIZE; i++) {
        o[i] = 0;
    }
}

void sig_perk_gf2_64_set(gf2_64_elt o, const gf2_64_elt e) {
    for (size_t i = 0; i < GF2_64_ELT_SIZE; i++) {
        o[i] = e[i];
    }
}

uint8_t sig_perk_gf2_64_elt_get_coefficient(const gf2_64_elt e, uint32_t index) {
    uint64_t w = 0;

    for (uint8_t i = 0; i < GF2_64_ELT_DATA_SIZE; i++) {
        w |= -((i ^ (index >> 6)) == 0) & e[i];
    }

    return (w >> (index & 63)) & 1;
}

void sig_perk_gf2_64_from_bytes(gf2_64_elt e, uint8_t bytes_array[GF2_64_ELT_UINT8_SIZE]) {
    memcpy(e, bytes_array, sizeof(uint64_t) * GF2_64_ELT_SIZE);
}
