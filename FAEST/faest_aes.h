/*
 *  SPDX-License-Identifier: MIT
 */

#ifndef FAEST_FAEST_AES_H
#define FAEST_FAEST_AES_H

#include <stdint.h>

#include "instances.h"
#include "aes.h"

FAEST_BEGIN_C_DECL

void aes_prove(uint8_t* a0_tilde, uint8_t* a1_tilde, uint8_t* a2_tilde, const uint8_t* w,
               const uint8_t* u, uint8_t** V, const uint8_t* owf_in, const uint8_t* owf_out,
               const uint8_t* chall_2, const faest_paramset_t* params);

void aes_verify(uint8_t* a0_tilde, const uint8_t* d, uint8_t** Q, const uint8_t* chall_2,
                const uint8_t* chall_3, const uint8_t* a1_tilde, const uint8_t* a2_tilde,
                const uint8_t* owf_in, const uint8_t* owf_out, const faest_paramset_t* params);

void aes_128_prover(uint8_t* a0_tilde, uint8_t* a1_tilde, uint8_t* a2_tilde, const uint8_t* w,
                    const uint8_t* u, uint8_t** V, const uint8_t* owf_in, const uint8_t* owf_out,
                    const uint8_t* chall_2, const faest_paramset_t* params);

void aes_192_prover(uint8_t* a0_tilde, uint8_t* a1_tilde, uint8_t* a2_tilde, const uint8_t* w,
                    const uint8_t* u, uint8_t** V, const uint8_t* owf_in, const uint8_t* owf_out,
                    const uint8_t* chall_2, const faest_paramset_t* params);

void aes_256_prover(uint8_t* a0_tilde, uint8_t* a1_tilde, uint8_t* a2_tilde, const uint8_t* w,
                    const uint8_t* u, uint8_t** V, const uint8_t* owf_in, const uint8_t* owf_out,
                    const uint8_t* chall_2, const faest_paramset_t* params);

void aes_128_verifier(uint8_t* a0_tilde, const uint8_t* d, uint8_t** Q, const uint8_t* owf_in,
                      const uint8_t* owf_out, const uint8_t* chall_2, const uint8_t* chall_3,
                      const uint8_t* a1_tilde, const uint8_t* a2_tilde,
                      const faest_paramset_t* params);

void aes_192_verifier(uint8_t* a0_tilde, const uint8_t* d, uint8_t** Q, const uint8_t* owf_in,
                      const uint8_t* owf_out, const uint8_t* chall_2, const uint8_t* chall_3,
                      const uint8_t* a1_tilde, const uint8_t* a2_tilde,
                      const faest_paramset_t* params);

void aes_256_verifier(uint8_t* a0_tilde, const uint8_t* d, uint8_t** Q, const uint8_t* owf_in,
                      const uint8_t* owf_out, const uint8_t* chall_2, const uint8_t* chall_3,
                      const uint8_t* a1_tilde, const uint8_t* a2_tilde,
                      const faest_paramset_t* params);

FAEST_END_C_DECL

#endif
