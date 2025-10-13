
#include "gf_arithmetic.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void sig_perk_gf2_lambda_ur_mul(gf2_lambda_elt_ur o, const gf2_lambda_elt e1, const gf2_lambda_elt e2);
void sig_perk_gf2_lambda_ur_elt_set(gf2_lambda_elt_ur o, const gf2_lambda_elt_ur e);
void sig_perk_gf2_lambda_elt_set(gf2_lambda_elt o, const gf2_lambda_elt e);
void sig_perk_gf2_lambda_elt_ur_set_zero(gf2_lambda_elt_ur o);
void sig_perk_gf2_lambda_elt_ur_set(gf2_lambda_elt_ur o, const gf2_lambda_elt_ur e);

void sig_perk_gf2_lambda_elt_ur_set_zero(gf2_lambda_elt_ur o) {
    for (uint8_t i = 0; i < GF2_LAMBDA_ELT_UR_SIZE; i++) {
        o[i] = 0;
    }
}

void sig_perk_gf2_lambda_elt_ur_set(gf2_lambda_elt_ur o, const gf2_lambda_elt_ur e) {
    for (size_t i = 0; i < GF2_LAMBDA_ELT_UR_SIZE; i++) {
        o[i] = e[i];
    }
}

void sig_perk_gf2_lambda_elt_set(gf2_lambda_elt o, const gf2_lambda_elt e) {
    for (size_t i = 0; i < GF2_LAMBDA_ELT_SIZE; i++) {
        o[i] = e[i];
    }
}

void sig_perk_gf2_lambda_add(gf2_lambda_elt o, const gf2_lambda_elt e1, const gf2_lambda_elt e2) {
    o[0] = e1[0] ^ e2[0];
    o[1] = e1[1] ^ e2[1];
    o[2] = e1[2] ^ e2[2];
}

void sig_perk_gf2_lambda_mul(gf2_lambda_elt o, gf2_lambda_elt e1, gf2_lambda_elt e2) {
    gf2_lambda_elt_ur tmp;
    sig_perk_gf2_lambda_ur_mul(tmp, e1, e2);
    sig_perk_gf2_lambda_reduce(o, tmp);
}

void sig_perk_gf2_lambda_ur_mul(gf2_lambda_elt_ur o, const gf2_lambda_elt e1, const gf2_lambda_elt e2) {
    uint64_t shifts[64][GF2_LAMBDA_ELT_SIZE + 1];
    sig_perk_gf2_lambda_elt_set(shifts[0], e2);
    shifts[0][GF2_LAMBDA_ELT_SIZE] = 0;

    for (uint8_t shift = 1; shift < 64; shift++) {
        shifts[shift][0] = shifts[shift - 1][0] << 1;
        for (uint8_t i = 1; i < GF2_LAMBDA_ELT_SIZE + 1; i++) {
            shifts[shift][i] = (shifts[shift - 1][i] << 1) | (shifts[shift - 1][i - 1] >> 63);
        }
    }

    sig_perk_gf2_lambda_elt_ur_set_zero(o);
    for (uint8_t i = 0; i < GF2_LAMBDA_FIELD_M; i++) {
        uint8_t shift = i % 64;
        uint8_t offset = i / 64;
        uint64_t multiplier = (e1[offset] >> shift) & 0x1;
        for (uint8_t j = 0; j < GF2_LAMBDA_ELT_SIZE + 1; j++) {
            o[j + offset] ^= multiplier * shifts[shift][j];
        }
    }
}

void sig_perk_gf2_lambda_reduce(gf2_lambda_elt o, gf2_lambda_elt_ur e) {
    gf2_lambda_elt_ur e2;
    sig_perk_gf2_lambda_elt_ur_set(e2, e);

    e2[3] ^= (e2[5] >> 57) ^ (e2[5] >> 62) ^ (e2[5] >> 63);

    e2[2] ^= (e2[5] << 7) ^ (e2[5] << 2) ^ (e2[5] << 1) ^ (e2[5] << 0) ^ (e2[4] >> 57) ^ (e2[4] >> 62) ^ (e2[4] >> 63);

    e2[1] ^= (e2[4] << 7) ^ (e2[4] << 2) ^ (e2[4] << 1) ^ (e2[4] << 0);

    uint64_t tmp = (e2[3] >> 0);
    e2[0] ^= (tmp << 7) ^ (tmp << 2) ^ (tmp << 1) ^ (tmp << 0);
    e2[1] ^= (tmp >> 57) ^ (tmp >> 62) ^ (tmp >> 63);

    sig_perk_gf2_lambda_elt_set(o, e2);

    // o[3] &= 0x0;
}

void sig_perk_gf2_lambda_set(gf2_lambda_elt o, const gf2_lambda_elt e) {
    for (size_t i = 0; i < GF2_LAMBDA_ELT_SIZE; i++) {
        o[i] = e[i];
    }
}

uint8_t sig_perk_gf2_lambda_elt_get_coefficient(const gf2_lambda_elt e, uint32_t index) {
    uint64_t w = 0;

    for (uint8_t i = 0; i < GF2_LAMBDA_ELT_DATA_SIZE; i++) {
        w |= -((i ^ (index >> 6)) == 0) & e[i];
    }

    return (w >> (index & 63)) & 1;
}

void sig_perk_gf2_lambda_elt_print(const gf2_lambda_elt e) {
    printf("[");
    printf(" %16" PRIx64 " %16" PRIx64 " %16" PRIx64, e[0], e[1], e[2]);
    printf(" ]");
}

void sig_perk_gf2_lambda_from_bytes(gf2_lambda_elt e, uint8_t bytes_array[GF2_LAMBDA_ELT_UINT8_SIZE]) {
    memcpy(e, bytes_array, sizeof(uint64_t) * GF2_LAMBDA_ELT_SIZE);
}

void sig_perk_gf2_lambda_to_bytes(uint8_t bytes_array[GF2_LAMBDA_ELT_UINT8_SIZE], gf2_lambda_elt e) {
    memcpy(bytes_array, e, GF2_LAMBDA_ELT_UINT8_SIZE);
}

void sig_perk_gf2_lambda_from_gf2_64(gf2_lambda_elt o, const gf2_64_elt e) {
    memcpy(o, e, sizeof(gf2_64_elt));
}
