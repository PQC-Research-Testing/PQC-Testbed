#ifndef MATRIX_FF_ARITH_H
#define MATRIX_FF_ARITH_H

#include "ff.h"

#define mirath_matrix_ff_bytes_per_column(n_rows) (((n_rows) >> 3) + ((n_rows % 8) == 0 ? 0 : 1))
#define mirath_matrix_ff_bytes_size(n_rows, n_cols) ((mirath_matrix_ff_bytes_per_column(n_rows)) * (n_cols))

#define MIRATH_VAR_FF_AUX_BYTES (mirath_matrix_ff_bytes_size(MIRATH_PARAM_M, MIRATH_PARAM_R) + mirath_matrix_ff_bytes_size(MIRATH_PARAM_R, MIRATH_PARAM_N - MIRATH_PARAM_R))
#define MIRATH_VAR_FF_S_BYTES (mirath_matrix_ff_bytes_size(MIRATH_PARAM_M, MIRATH_PARAM_R))
#define MIRATH_VAR_FF_C_BYTES (mirath_matrix_ff_bytes_size(MIRATH_PARAM_R, MIRATH_PARAM_N - MIRATH_PARAM_R))
#define MIRATH_VAR_FF_H_BYTES (mirath_matrix_ff_bytes_size(MIRATH_PARAM_M * MIRATH_PARAM_N - MIRATH_PARAM_K, MIRATH_PARAM_K))
#define MIRATH_VAR_FF_Y_BYTES (mirath_matrix_ff_bytes_size(MIRATH_PARAM_M * MIRATH_PARAM_N - MIRATH_PARAM_K, 1))
#define MIRATH_VAR_FF_T_BYTES (mirath_matrix_ff_bytes_size(MIRATH_PARAM_M, MIRATH_PARAM_N - MIRATH_PARAM_R))
#define MIRATH_VAR_FF_E_BYTES (mirath_matrix_ff_bytes_size(MIRATH_PARAM_M * MIRATH_PARAM_N, 1))

#define OFF_E_A ((8 * MIRATH_VAR_FF_Y_BYTES) - (MIRATH_PARAM_M * MIRATH_PARAM_N - MIRATH_PARAM_K))
#define OFF_E_B ((8 * mirath_matrix_ff_bytes_size(MIRATH_PARAM_K, 1)) - MIRATH_PARAM_K)

static inline void mirath_matrix_set_to_ff(ff_t *matrix, const uint32_t n_rows, const uint32_t n_cols) {
    if (n_rows & 0x7) {
        const uint32_t matrix_height =  mirath_matrix_ff_bytes_per_column(n_rows);
        const uint32_t matrix_height_x = matrix_height -  1;

        ff_t mask = 0xff >> (8 - (n_rows % 8));

        for (uint32_t i = 0; i < n_cols; i++) {
            matrix[i * matrix_height + matrix_height_x ] &= mask;
        }
    }
}

static inline ff_t mirath_matrix_ff_get_entry(const ff_t *matrix, const uint32_t n_rows, const uint32_t i, const uint32_t j) {
    const uint32_t nbytes_col = mirath_matrix_ff_bytes_per_column(n_rows);
    const uint32_t idx_line = i / 8;
    const uint32_t bit_line = i % 8;

    return (matrix[nbytes_col * j + idx_line] >> bit_line) & 0x01;
}

static inline void mirath_matrix_ff_set_entry(ff_t *matrix, const uint32_t n_rows, const uint32_t i, const uint32_t j, const ff_t scalar) {
    const uint32_t nbytes_col = mirath_matrix_ff_bytes_per_column(n_rows);
    const uint32_t idx_line = i / 8;
    const uint32_t bit_line = i % 8;

    const uint8_t mask = 0xff ^ (1 << bit_line);

    matrix[nbytes_col * j + idx_line] = (matrix[nbytes_col * j + idx_line] & mask) ^ (scalar << bit_line);
}

/// matrix1 = matrix2 + matrix3
static inline void mirath_matrix_ff_add_arith(ff_t *matrix1, const ff_t *matrix2, const ff_t *matrix3,
		const uint32_t n_rows, const uint32_t n_cols) {
    const uint32_t n_bytes = mirath_matrix_ff_bytes_size(n_rows, n_cols);

    for (uint32_t i = 0; i < n_bytes; i++) {
        matrix1[i] = matrix2[i] ^ matrix3[i];
    }
}

/// matrix1 += scalar *matrix2
static inline void mirath_matrix_ff_add_multiple_arith(ff_t *matrix1, ff_t scalar, const ff_t *matrix2,
    const uint32_t n_rows, const uint32_t n_cols) {
    const uint32_t n_bytes = mirath_matrix_ff_bytes_size(n_rows, n_cols);

    for (uint32_t i = 0; i < n_bytes; i++) {
        matrix1[i] ^= ((-scalar) & matrix2[i]);
    }
}

/// result = matrix1 * matrix2
// matrix1 of size n_rows1 * n_cols1
// matrix2 of size n_cols1 * n_cols2
// result  of size n_rows1 * n_cols2
static inline void mirath_matrix_ff_product_arith(ff_t *result, const ff_t *matrix1, const ff_t *matrix2,
    const uint32_t n_rows1, const uint32_t n_cols1, const uint32_t n_cols2) {

    uint32_t i, j, k;
    ff_t entry_i_k, entry_k_j, entry_i_j;

    for (i = 0; i < n_rows1; i++) {
        for (j = 0; j < n_cols2; j++) {
            entry_i_j = 0;

            for (k = 0; k < n_cols1; k++) {
                entry_i_k = mirath_matrix_ff_get_entry(matrix1, n_rows1, i, k);
                entry_k_j = mirath_matrix_ff_get_entry(matrix2, n_cols1, k, j);
                entry_i_j ^= mirath_ff_product(entry_i_k, entry_k_j);
            }

            mirath_matrix_ff_set_entry(result, n_rows1, i, j, entry_i_j);
        }
    }
}

#endif
