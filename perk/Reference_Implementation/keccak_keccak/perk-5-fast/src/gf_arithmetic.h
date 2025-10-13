
#ifndef SIG_PERK_GF2_ARITHMETIC_AVX2_H
#define SIG_PERK_GF2_ARITHMETIC_AVX2_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include "gf_common_arithmetic.h"

// GF(2^256) with X^256 + X^10 + X^5 + X^2 + 1

#define GF2_LAMBDA_FIELD_Q 2
#define GF2_LAMBDA_FIELD_M 256

#define GF2_LAMBDA_ELT_SIZE      4
#define GF2_LAMBDA_ELT_DATA_SIZE 4

#define GF2_LAMBDA_ELT_UR_SIZE 8

#define GF2_LAMBDA_ELT_UINT8_SIZE    32
#define GF2_LAMBDA_ELT_UR_UINT8_SIZE 64

typedef int64_t gf2_lambda_elt_int;
typedef uint64_t gf2_lambda_elt_uint;
typedef uint64_t gf2_lambda_elt[GF2_LAMBDA_ELT_SIZE];
typedef uint64_t gf2_lambda_elt_ur[GF2_LAMBDA_ELT_UR_SIZE];
typedef uint64_t* gf2_lambda_elt_ptr;

void sig_perk_gf2_lambda_add(gf2_lambda_elt o, const gf2_lambda_elt e1, const gf2_lambda_elt e2);
void sig_perk_gf2_lambda_mul(gf2_lambda_elt o, gf2_lambda_elt e1, gf2_lambda_elt e2);
void sig_perk_gf2_lambda_reduce(gf2_lambda_elt o, gf2_lambda_elt_ur e);
void sig_perk_gf2_lambda_set(gf2_lambda_elt o, const gf2_lambda_elt e);
uint8_t sig_perk_gf2_lambda_elt_get_coefficient(const gf2_lambda_elt e, uint32_t index);
void sig_perk_gf2_lambda_elt_print(const gf2_lambda_elt e);
void sig_perk_gf2_lambda_elt_ur_print(const gf2_lambda_elt_ur e);
void sig_perk_gf2_lambda_from_bytes(gf2_lambda_elt e, uint8_t bytes_array[GF2_LAMBDA_ELT_UINT8_SIZE]);
void sig_perk_gf2_lambda_to_bytes(uint8_t bytes_array[GF2_LAMBDA_ELT_UINT8_SIZE], gf2_lambda_elt e);
void sig_perk_gf2_lambda_from_gf2_64(gf2_lambda_elt o, const gf2_64_elt e);

#endif  // SIG_PERK_GF2_ARITHMETIC_H
