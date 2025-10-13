
#ifndef SIG_PERK_GF2_ARITHMETIC_AVX2_H
#define SIG_PERK_GF2_ARITHMETIC_AVX2_H

#include <emmintrin.h>
#include <immintrin.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <wmmintrin.h>

// GF(2^256) with X^256 + X^10 + X^5 + X^2 + 1

#define GF2_LAMBDA_FIELD_M 256

#define GF2_LAMBDA_ELT_SIZE          4
#define GF2_LAMBDA_ELT_UR_SIZE       8
#define GF2_LAMBDA_ELT_UINT8_SIZE    32
#define GF2_LAMBDA_ELT_UR_UINT8_SIZE 64

typedef int64_t gf2_lambda_elt_int;
typedef uint64_t gf2_lambda_elt_uint;
typedef uint64_t gf2_lambda_elt[GF2_LAMBDA_ELT_SIZE] __attribute__((aligned(16)));
typedef uint64_t gf2_lambda_elt_ur[GF2_LAMBDA_ELT_UR_SIZE] __attribute__((aligned(16)));
typedef uint64_t* gf2_lambda_elt_ptr;

static inline void sig_perk_gf2_lambda_elt_ur_set(gf2_lambda_elt_ur o, const gf2_lambda_elt_ur e) {
    for (size_t i = 0; i < GF2_LAMBDA_ELT_UR_SIZE; i++) {
        o[i] = e[i];
    }
}

static inline void sig_perk_gf2_lambda_elt_set(gf2_lambda_elt o, const gf2_lambda_elt_ur e) {
    for (size_t i = 0; i < GF2_LAMBDA_ELT_SIZE; i++) {
        o[i] = e[i];
    }
}

static inline void sig_perk_gf2_lambda_add(gf2_lambda_elt o, const gf2_lambda_elt e1, const gf2_lambda_elt e2) {
    o[0] = e1[0] ^ e2[0];
    o[1] = e1[1] ^ e2[1];
    o[2] = e1[2] ^ e2[2];
    o[3] = e1[3] ^ e2[3];
}

static inline void sig_perk_gf2_lambda_reduce(gf2_lambda_elt o, gf2_lambda_elt_ur e) {
    gf2_lambda_elt_ur e2;
    sig_perk_gf2_lambda_elt_ur_set(e2, e);

    e2[4] ^= (e2[7] >> 54) ^ (e2[7] >> 59) ^ (e2[7] >> 62);

    e2[3] ^= (e2[7] << 10) ^ (e2[7] << 5) ^ (e2[7] << 2) ^ (e2[7] << 0) ^ (e2[6] >> 54) ^ (e2[6] >> 59) ^ (e2[6] >> 62);

    e2[2] ^= (e2[6] << 10) ^ (e2[6] << 5) ^ (e2[6] << 2) ^ (e2[6] << 0) ^ (e2[5] >> 54) ^ (e2[5] >> 59) ^ (e2[5] >> 62);

    e2[1] ^= (e2[5] << 10) ^ (e2[5] << 5) ^ (e2[5] << 2) ^ (e2[5] << 0);

    uint64_t tmp = (e2[4] >> 0);
    e2[0] ^= (tmp << 10) ^ (tmp << 5) ^ (tmp << 2) ^ (tmp << 0);
    e2[1] ^= (tmp >> 54) ^ (tmp >> 59) ^ (tmp >> 62);

    sig_perk_gf2_lambda_elt_set(o, e2);
}

static inline void sig_perk_gf2_lambda_ur_mul(gf2_lambda_elt_ur o, gf2_lambda_elt e1, gf2_lambda_elt e2) {
    __m128i a = _mm_load_si128((__m128i*)e1);
    __m128i b = _mm_load_si128((__m128i*)e2);
    __m128i c = _mm_load_si128((__m128i*)(e1 + 2));
    __m128i d = _mm_load_si128((__m128i*)(e2 + 2));

    __m128i a0_b0 = _mm_clmulepi64_si128(a, b, 0x00);

    __m128i a0_b1 = _mm_clmulepi64_si128(a, b, 0x10);
    __m128i a1_b0 = _mm_clmulepi64_si128(a, b, 0x01);

    __m128i a0_b2 = _mm_clmulepi64_si128(a, d, 0x00);
    __m128i a1_b1 = _mm_clmulepi64_si128(a, b, 0x11);
    __m128i a2_b0 = _mm_clmulepi64_si128(c, b, 0x00);

    __m128i a0_b3 = _mm_clmulepi64_si128(a, d, 0x10);
    __m128i a1_b2 = _mm_clmulepi64_si128(a, d, 0x01);
    __m128i a2_b1 = _mm_clmulepi64_si128(c, b, 0x10);
    __m128i a3_b0 = _mm_clmulepi64_si128(c, b, 0x01);

    __m128i a1_b3 = _mm_clmulepi64_si128(a, d, 0x11);
    __m128i a2_b2 = _mm_clmulepi64_si128(c, d, 0x00);
    __m128i a3_b1 = _mm_clmulepi64_si128(c, b, 0x11);

    __m128i a2_b3 = _mm_clmulepi64_si128(c, d, 0x10);
    __m128i a3_b2 = _mm_clmulepi64_si128(c, d, 0x01);

    __m128i a3_b3 = _mm_clmulepi64_si128(c, d, 0x11);

    __m128i c1 = _mm_xor_si128(a0_b1, a1_b0);
    __m128i c2 = _mm_xor_si128(a0_b2, _mm_xor_si128(a1_b1, a2_b0));
    __m128i c3 = _mm_xor_si128(a0_b3, _mm_xor_si128(a1_b2, _mm_xor_si128(a2_b1, a3_b0)));
    __m128i c4 = _mm_xor_si128(a1_b3, _mm_xor_si128(a2_b2, a3_b1));
    __m128i c5 = _mm_xor_si128(a2_b3, a3_b2);

    o[0] = _mm_extract_epi64(a0_b0, 0);
    o[1] = _mm_extract_epi64(a0_b0, 1) ^ _mm_extract_epi64(c1, 0);
    o[2] = _mm_extract_epi64(c1, 1) ^ _mm_extract_epi64(c2, 0);
    o[3] = _mm_extract_epi64(c2, 1) ^ _mm_extract_epi64(c3, 0);
    o[4] = _mm_extract_epi64(c3, 1) ^ _mm_extract_epi64(c4, 0);
    o[5] = _mm_extract_epi64(c4, 1) ^ _mm_extract_epi64(c5, 0);
    o[6] = _mm_extract_epi64(c5, 1) ^ _mm_extract_epi64(a3_b3, 0);
    o[7] = _mm_extract_epi64(a3_b3, 1);
}

static inline void sig_perk_gf2_lambda_mul(gf2_lambda_elt o, gf2_lambda_elt e1, gf2_lambda_elt e2) {
    gf2_lambda_elt_ur tmp;
    sig_perk_gf2_lambda_ur_mul(tmp, e1, e2);
    sig_perk_gf2_lambda_reduce(o, tmp);
}

#endif  // SIG_PERK_GF2_ARITHMETIC_H
