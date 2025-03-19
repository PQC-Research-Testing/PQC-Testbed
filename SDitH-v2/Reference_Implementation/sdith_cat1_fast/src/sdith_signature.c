#include <string.h>

#include "ggm.h"
#include "math.h"
#include "vole_private.h"

const uint8_t HASH_BAVC_PREFIX = 1;
const uint8_t HASH_AUX_PREFIX = 2;
const uint8_t HASH_LINES_PREFIX = 3;
const uint8_t HASH_PIOP_PREFIX = 4;
const uint64_t PROOFOW_CTR_REVEALED_BYTES = 4;  // we reveal this num of bytes of proofow ctr in the signature

uint64_t compute_rsd_codim(uint64_t rsd_n, uint64_t rsd_w) {
  // target density is 1/100
  static const double LOG2_INV_TARGET_DENSITY = 6.64385618977;  // log2(100.);
  const uint64_t rsd_nsw = rsd_n / rsd_w;                       // exact division
  // smallest codim where density drops below TARGET_DENSITY
  const uint64_t rsd_min_codim = ceil(rsd_w * log2(rsd_nsw) + LOG2_INV_TARGET_DENSITY);
  // smallest multiple of 8 above that bound
  return ((rsd_min_codim + 7) & UINT64_C(-8));
}

void compute_extended_parameters(extended_parameters_t* res, const signature_parameters* sig_params) {
  // compute extended parameters
  res->lambda = sig_params->lambda;
  res->kappa = sig_params->kappa;
  res->tau = sig_params->tau;
  res->target_topen = sig_params->target_topen;
  res->rsd_n = sig_params->rsd_n;
  res->rsd_w = sig_params->rsd_w;
  res->mux_depth = sig_params->mux_depth;
  memcpy(res->mux_arities, sig_params->mux_arities, sizeof(uint64_t) * 8);
  res->rsd_npw = sig_params->rsd_n / sig_params->rsd_w;  // exact division
  res->rsd_codim = compute_rsd_codim(res->rsd_n, res->rsd_w);
  res->proofow_w = sig_params->proofow_w;
  res->delta0_bits = res->kappa * res->tau + sig_params->proofow_w;
  res->delta0_dwords = (res->delta0_bits + 63) >> 6;
  res->delta0_bytess = (res->delta0_bits + 7) >> 3;
  res->delta0_capacity = res->delta0_dwords << 3;
  memset(&res->vole_params, 0, sizeof(vole_parameters));
  vole_parameters_init(&res->vole_params, res->lambda, res->tau, res->kappa);
  uint64_t mux_inputs = 0;
  uint64_t chall_unitary_powers = 0;
  {
    for (uint64_t i = 0; i < res->mux_depth; ++i) {
      mux_inputs += res->mux_arities[i] - 1;
      if (res->mux_arities[i] > 2) chall_unitary_powers += 32;
    }
  }
  CREQUIRE(chall_unitary_powers <= res->lambda, "Params error: too many non-binary arities");
  res->mux_inputs = mux_inputs;
  res->chall_unitary_powers = chall_unitary_powers;
  res->degree = res->mux_depth > 2 ? res->mux_depth : 2;
  res->num_inputs_pairs = mux_inputs * res->rsd_w;
  res->num_cchk_pairs = vole_consistency_check_matrix_nrows(&res->vole_params);
  CREQUIRE((res->num_cchk_pairs & 7) == 0, "non mult of 8 cchk is not supported");
  res->num_cz_pairs = res->lambda * (res->degree - 1);
  res->real_L = res->num_inputs_pairs + res->num_cchk_pairs + res->num_cz_pairs;
  res->L = (res->real_L + 7) & UINT64_C(-8);  // L must be an exact mult of 8
  res->Lbyte = res->L >> 3;
  res->lambda_bytes = res->lambda >> 3;
  res->cchk_matrix_nrows = vole_consistency_check_matrix_nrows(&res->vole_params);
  res->cchk_matrix_ncols = vole_consistency_check_matrix_ncols(&res->vole_params, res->L);
  res->rsd_codim_bytes = (res->rsd_codim + 7) >> 3;
  res->rsd_codim_limbs = (res->rsd_codim + res->lambda - 1) / res->lambda;
}

EXPORT uint64_t sdith_signature_bytes(const signature_parameters* sig_params) {
  extended_parameters_t par;
  compute_extended_parameters(&par, sig_params);

  uint64_t sig_bytes = 0;
  sig_bytes += par.lambda_bytes;                     // global_salt
  sig_bytes += par.target_topen * par.lambda_bytes;  // sibbling path;
  sig_bytes += par.tau * 2 * par.lambda_bytes;       // ggm_hidden_leaf_cmt
  sig_bytes += par.Lbyte * (par.tau - 1);            // corr_u
  sig_bytes += par.num_cchk_pairs >> 3;              // cchk_u
  sig_bytes += (par.num_inputs_pairs + 7) >> 3;      // circuit_in_pub
  sig_bytes += par.degree * par.lambda_bytes;        // circuit_cz_pub
  sig_bytes += 2 * par.lambda_bytes;                 // hash_piop
  sig_bytes += 4;                                    // proofow_ctr_reveal
  return sig_bytes;
}

EXPORT uint64_t sdith_signature_tmp_bytes(const signature_parameters* sig_params) {
  extended_parameters_t par;
  compute_extended_parameters(&par, sig_params);

  COMP_SPACE_INIT();
  COMP_SPACE_MAP_ALIGNED(hash_t*, hash_com, 32, 2 * par.lambda_bytes);  // commitment of the ggm tree
  COMP_SPACE_MAP_ALIGNED(hash_t*, hash_aux, 32,
                         2 * par.lambda_bytes);  // (round1) ggm_cmt_hash + corr_terms :=> cchk matrix
  // (round3) hash_aux + cchk_u + cchk_v + inputs_mask :=> chall
  COMP_SPACE_MAP_ALIGNED(hash_t*, hash_lines, 32, 2 * par.lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(seed_t*, root_seed, 32, par.lambda_bytes);
  COMP_SPACE_MAP(full_ggm_tree*, ggm_tree, bytes_of_full_ggm_tree(par.lambda, par.tau, par.kappa));
  COMP_SPACE_MAP(uint8_t*, u, par.Lbyte* par.tau);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, v, 32, par.Lbyte* par.lambda);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, v2, 32, par.Lbyte* par.lambda);  // copy needed during transposition
  COMP_SPACE_MAP_ALIGNED(uint8_t*, rvp_f_cz, 32, par.lambda_bytes* par.degree * 2);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, res_f, 32, par.lambda_bytes*(par.degree + 1));
  COMP_SPACE_MAP_ALIGNED(uint8_t*, mux_f, 32, par.lambda_bytes*(par.degree + 1));
  COMP_SPACE_MAP_ALIGNED(uint8_t*, inputs_f, 32, par.lambda_bytes * 2 * par.num_inputs_pairs);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, chall_unitary, 32, par.lambda_bytes* par.rsd_w);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, chall_a, 32, par.lambda_bytes* par.rsd_codim_limbs);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, chall_a_H, 32, par.lambda_bytes* par.rsd_n);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, chall_a_y, 32, par.lambda_bytes);
  COMP_SPACE_MAP(uint8_t*, cchk_matrix, par.cchk_matrix_nrows* par.cchk_matrix_ncols >> 3);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, cchk_res_v, 32, par.lambda_bytes* par.cchk_matrix_nrows);
  COMP_SPACE_MAP(uint8_t*, delta0, par.delta0_capacity);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, delta1, 32, par.lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(uint32_t*, hidden_leaves_idx, 4, par.tau * sizeof(uint32_t));
  COMP_SPACE_MAP_CALL(
      prover_cst_mux_circuit_ct_ref_tmp_bytes(&par.vole_params, par.mux_depth, par.mux_arities, par.rsd_npw));
  COMP_SPACE_MAP_CALL(estimate_topen_tmp_bytes(par.tau, par.kappa));
  COMP_SPACE_MAP_CALL(rsd_public_key_times_challenge_tmp_bytes(&par.vole_params, par.rsd_w, par.rsd_n, par.rsd_codim));
  COMP_SPACE_RETURN();
}

EXPORT uint64_t sdith_signature_entropy_bytes(const signature_parameters* sig_params) {
  const uint64_t lambda = sig_params->lambda;
  const uint64_t lambda_bytes = lambda >> 3;
  return 2 * lambda_bytes;
}

EXPORT uint64_t sdith_secret_key_bytes(const signature_parameters* sig_params) {
  const uint64_t lambda = sig_params->lambda;
  const uint64_t lambda_bytes = lambda >> 3;
  const uint64_t mux_depth = sig_params->mux_depth;
  const uint64_t* mux_arities = sig_params->mux_arities;
  const uint64_t rsd_w = sig_params->rsd_w;
  const uint64_t rsd_codim = compute_rsd_codim(sig_params->rsd_n, sig_params->rsd_w);
  const uint64_t rsd_codim_bytes = (rsd_codim + 7) >> 3;
  uint64_t mux_inputs = 0;
  for (uint64_t i = 0; i < mux_depth; ++i) {
    mux_inputs += mux_arities[i] - 1;
  }
  const uint64_t skey_encoded_solution_bytes = (rsd_w * mux_inputs + 7) >> 3;
  return 2 * lambda_bytes + skey_encoded_solution_bytes + rsd_codim_bytes;
}

EXPORT uint64_t sdith_public_key_bytes(const signature_parameters* sig_params) {
  const uint64_t lambda = sig_params->lambda;
  const uint64_t lambda_bytes = lambda >> 3;
  const uint64_t rsd_codim = compute_rsd_codim(sig_params->rsd_n, sig_params->rsd_w);
  ;
  const uint64_t rsd_codim_bytes = (rsd_codim + 7) >> 3;
  return lambda_bytes + rsd_codim_bytes;
}
EXPORT uint64_t sdith_keygen_tmp_bytes(const signature_parameters* sig_params) {
  const uint64_t lambda = sig_params->lambda;
  const uint64_t lambda_bytes = lambda >> 3;
  const uint64_t rsd_n = sig_params->rsd_n;
  const uint64_t rsd_w = sig_params->rsd_w;
  const uint64_t rsd_codim = compute_rsd_codim(sig_params->rsd_n, sig_params->rsd_w);
  ;
  const uint64_t rsd_codim_limbs = (rsd_codim + lambda - 1) / lambda;

  COMP_SPACE_INIT();
  COMP_SPACE_MAP_ALIGNED(uint32_t*, skey_solution, 4, rsd_w * sizeof(uint32_t));
  COMP_SPACE_MAP_ALIGNED(uint8_t*, pkey_full_H, 32, (rsd_n - rsd_codim) * rsd_codim_limbs * lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, pkey_full_y, 32, rsd_codim_limbs* lambda_bytes);
  COMP_SPACE_RETURN();
}

EXPORT uint64_t sdith_keygen_entropy_bytes(const signature_parameters* sig_params) {
  const uint64_t lambda = sig_params->lambda;
  const uint64_t lambda_bytes = lambda >> 3;
  return 2 * lambda_bytes;
}

#define MAP_FIELD(POOL_NAME, FIELD_NAME, VAR_BYTES) \
  FIELD_NAME = (typeof(FIELD_NAME))POOL_NAME;       \
  POOL_NAME += (VAR_BYTES)

/** secret key mapping */
typedef struct skey_mapping_t {
  uint8_t* skey_seed;
  uint8_t* pkey_seed;
  uint8_t* skey_encoded_solution;
  uint8_t* pkey_y;
} skey_mapping_t;

skey_mapping_t map_secret_key(const extended_parameters_t* par, const void* skey) {
  const uint64_t skey_encoded_solution_bytes = (par->rsd_w * par->mux_inputs + 7) >> 3;
  skey_mapping_t res;
  uint8_t* secret_key = (uint8_t*)skey;
  MAP_FIELD(secret_key, res.skey_seed, par->lambda_bytes);
  MAP_FIELD(secret_key, res.pkey_seed, par->lambda_bytes);
  MAP_FIELD(secret_key, res.skey_encoded_solution, skey_encoded_solution_bytes);  // unary encoded
  MAP_FIELD(secret_key, res.pkey_y, par->rsd_codim_bytes);
  return res;
}

/** public key mapping */
typedef struct pkey_mapping_t {
  uint8_t* pkey_seed;
  uint8_t* pkey_y;
} pkey_mapping_t;

pkey_mapping_t map_public_key(const extended_parameters_t* par, const void* pkey) {
  pkey_mapping_t res;
  uint8_t* public_key = (uint8_t*)pkey;
  MAP_FIELD(public_key, res.pkey_seed, par->lambda_bytes);
  MAP_FIELD(public_key, res.pkey_y, par->rsd_codim_bytes);
  return res;
}

/** signature mapping */
typedef struct signature_mapping_t {
  uint8_t* global_salt;
  uint8_t* ggm_sibling_path;
  uint8_t* ggm_hidden_leaf_cmt;
  uint8_t* corr_u;
  uint8_t* cchk_u;
  uint8_t* circuit_in_pub;
  uint8_t* circuit_cz_pub;
  uint8_t* hash_piop;
  uint8_t* proofow_ctr_reveal;
} signature_mapping_t;

signature_mapping_t map_signature(const extended_parameters_t* par, const void* sign) {
  signature_mapping_t res;
  uint8_t* sign_fields = (uint8_t*)sign;
  MAP_FIELD(sign_fields, res.global_salt, par->lambda_bytes);
  MAP_FIELD(sign_fields, res.ggm_sibling_path, par->target_topen * par->lambda_bytes);
  MAP_FIELD(sign_fields, res.ggm_hidden_leaf_cmt, par->tau * 2 * par->lambda_bytes);
  MAP_FIELD(sign_fields, res.corr_u, par->Lbyte * (par->tau - 1));
  MAP_FIELD(sign_fields, res.cchk_u, par->num_cchk_pairs >> 3);
  MAP_FIELD(sign_fields, res.circuit_in_pub, (par->num_inputs_pairs + 7) >> 3);
  MAP_FIELD(sign_fields, res.circuit_cz_pub, par->degree * par->lambda_bytes);
  MAP_FIELD(sign_fields, res.hash_piop, 2 * par->lambda_bytes);
  MAP_FIELD(sign_fields, res.proofow_ctr_reveal, PROOFOW_CTR_REVEALED_BYTES);
  return res;
}

EXPORT void sdith_keygen(const signature_parameters* sig_params,  //
                         void* skey,                              // out: secret key
                         void* pkey,                              // out: public key
                         const void* entropy,                     // in: entropy
                         uint8_t* tmp_space) {
  extended_parameters_t par;
  compute_extended_parameters(&par, sig_params);
  const uint64_t skey_encoded_solution_bytes = (par.rsd_w * par.mux_inputs + 7) >> 3;

  // local variables
  TMP_SPACE_MAP_ALIGNED(uint32_t*, skey_solution, 4, par.rsd_w * sizeof(uint32_t));
  TMP_SPACE_MAP_ALIGNED(uint8_t*, pkey_full_H, 32,
                        (par.rsd_n - par.rsd_codim) * par.rsd_codim_limbs * par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, pkey_full_y, 32, par.rsd_codim_limbs* par.lambda_bytes);

  // secret key
  skey_mapping_t sk = map_secret_key(&par, skey);

  // public key
  pkey_mapping_t pk = map_public_key(&par, pkey);

  // copy the entropy
  memcpy(pk.pkey_seed, entropy, par.lambda_bytes);
  memcpy(sk.skey_seed, (uint8_t*)entropy + par.lambda_bytes, par.lambda_bytes);
  memcpy(sk.pkey_seed, pk.pkey_seed, par.lambda_bytes);

  rsd_generate_random_instance_expanded_ref(par.rsd_w, par.rsd_n, par.rsd_codim,                  //
                                            par.lambda, &par.vole_params.prg,                     //
                                            pkey_full_H, par.rsd_codim_limbs * par.lambda_bytes,  //
                                            pkey_full_y, par.rsd_codim_limbs * par.lambda_bytes,  //
                                            skey_solution,                                        //
                                            sk.skey_seed, pk.pkey_seed);                          //
  rsd_encode_solution_ref(                                                                        //
      par.rsd_w, par.rsd_n, par.rsd_codim,                                                        //
      par.mux_depth, par.mux_arities,                                                             //
      sk.skey_encoded_solution, skey_encoded_solution_bytes,                                      //
      skey_solution);

  memcpy(pk.pkey_y, pkey_full_y, par.rsd_codim_bytes);
  memcpy(sk.pkey_y, pkey_full_y, par.rsd_codim_bytes);
}

EXPORT void sdith_sign(const signature_parameters* sig_params,       //
                       void* signature,                              // out: signature
                       const void* message, uint64_t message_bytes,  // in: message
                       const void* skey,                             // secret key
                       const void* entropy,                          // in: entropy
                       uint8_t* tmp_space) {
  extended_parameters_t par;
  compute_extended_parameters(&par, sig_params);

  // secret key
  const skey_mapping_t sk = map_secret_key(&par, skey);

  // signature fields
  const signature_mapping_t sign = map_signature(&par, signature);

  // local variables
  TMP_SPACE_MAP_ALIGNED(hash_t*, hash_com, 32, 2 * par.lambda_bytes);  // commitment of the ggm tree
  TMP_SPACE_MAP_ALIGNED(hash_t*, hash_aux, 32,
                        2 * par.lambda_bytes);  // (round1) ggm_cmt_hash + corr_terms :=> cchk matrix
  // (round3) hash_aux + cchk_u + cchk_v + inputs_mask :=> chall
  TMP_SPACE_MAP_ALIGNED(hash_t*, hash_lines, 32, 2 * par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(seed_t*, root_seed, 32, par.lambda_bytes);
  TMP_SPACE_MAP(full_ggm_tree*, ggm_tree, bytes_of_full_ggm_tree(par.lambda, par.tau, par.kappa));
  TMP_SPACE_MAP(uint8_t*, u, par.Lbyte* par.tau);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, v, 32, par.Lbyte* par.lambda);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, v2, 32, par.Lbyte* par.lambda);  // copy needed during transposition
  TMP_SPACE_MAP_ALIGNED(uint8_t*, rvp_f_cz, 32, par.lambda_bytes* par.degree * 2);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, res_f, 32, par.lambda_bytes*(par.degree + 1));
  TMP_SPACE_MAP_ALIGNED(uint8_t*, mux_f, 32, par.lambda_bytes*(par.degree + 1));
  TMP_SPACE_MAP_ALIGNED(uint8_t*, inputs_f, 32, par.lambda_bytes * 2 * par.num_inputs_pairs);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, chall_unitary, 32, par.lambda_bytes* par.rsd_w);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, chall_a, 32, par.lambda_bytes* par.rsd_codim_limbs);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, chall_a_H, 32, par.lambda_bytes* par.rsd_n);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, chall_a_y, 32, par.lambda_bytes);
  TMP_SPACE_MAP(uint8_t*, cchk_matrix, par.cchk_matrix_nrows* par.cchk_matrix_ncols >> 3);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, cchk_res_v, 32, par.lambda_bytes* par.cchk_matrix_nrows);
  TMP_SPACE_MAP(uint8_t*, delta0, par.delta0_capacity);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, delta1, 32, par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(uint32_t*, hidden_leaves_idx, 4, par.tau * sizeof(uint32_t));
  TMP_SPACE_MAP_CALL(
      prover_cst_mux_circuit_ct_ref_tmp_bytes(&par.vole_params, par.mux_depth, par.mux_arities, par.rsd_npw));
  TMP_SPACE_MAP_CALL(estimate_topen_tmp_bytes(par.tau, par.kappa));
  TMP_SPACE_MAP_CALL(rsd_public_key_times_challenge_tmp_bytes(&par.vole_params, par.rsd_w, par.rsd_n, par.rsd_codim));

  // draw a random root seed and global salt (entropy)
  memcpy(sign.global_salt, entropy, par.lambda_bytes);
  memcpy(root_seed, ((uint8_t*)entropy) + par.lambda_bytes, par.lambda_bytes);

  // --------------------------------------
  // Phase 0: generation of the Vole pairs
  // --------------------------------------

  // initialize the tree structure
  full_ggm_tree_init(                                                   //
      ggm_tree,                                                         //
      par.lambda, par.tau, par.kappa,                                   //
      par.vole_params.ggm_seed_rng_lr, par.vole_params.ggm_commit_rng,  // crypto functions
      sign.global_salt, root_seed);

  // generate vole pairs
  xof_ctx prover_hash_bavc_ctx;
  par.vole_params.xof.xof_init_and_seed(&prover_hash_bavc_ctx, &HASH_BAVC_PREFIX, 1);
  prover_generate_midsize_grey_vole_from_seeds_ct_ref(  //
      &par.vole_params, par.L, &prover_hash_bavc_ctx, u, v, ggm_tree);
  par.vole_params.xof.xof_finalize_and_output(&prover_hash_bavc_ctx, hash_com, 2 * par.lambda_bytes);

  // transpose vole
  memset(v + par.kappa * par.tau * par.Lbyte, 0, (par.lambda - par.kappa * par.tau) * par.Lbyte);
  prover_midsize_to_fullsize_std_vole_ct_ref(&par.vole_params, par.L, u, sign.corr_u, v2, u, v);

  xof_ctx hash_aux_ctx;  // round 1 hash: incl salt, hash_com(ggm), aux(corr_terms) :=> cchk matrix
  par.vole_params.xof.xof_init_and_seed(&hash_aux_ctx, &HASH_AUX_PREFIX, 1);
  par.vole_params.xof.xof_seed(&hash_aux_ctx, hash_com, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&hash_aux_ctx, sign.corr_u, (par.tau - 1) * par.Lbyte);
  par.vole_params.xof.xof_finalize_and_output(&hash_aux_ctx, hash_aux, 2 * par.lambda_bytes);

  uint8_t* const rvp_u_cchk = u;
  uint8_t* const rvp_v_cchk = v2;
  uint8_t* const rvp_u_cz = rvp_u_cchk + (par.num_cchk_pairs >> 3);
  uint8_t* const rvp_v_cz = rvp_v_cchk + (par.num_cchk_pairs * par.lambda_bytes);
  uint8_t* const rvp_u_in = rvp_u_cz + (par.num_cz_pairs >> 3);
  uint8_t* const rvp_v_in = rvp_v_cz + (par.num_cz_pairs * par.lambda_bytes);

  // vole consistency check
  both_vole_consistency_check_matrix(&par.vole_params, par.L, cchk_matrix, hash_aux, 2 * par.lambda_bytes);
  prover_vole_consistency_check(&par.vole_params, par.L, sign.cchk_u, cchk_res_v, u, v2, cchk_matrix);

  // --------------------------------------
  // Phase 1: Build and Commit Witness/Masking polynomials
  // --------------------------------------

  // f2 to flambda
  prover_f2_to_flambda_deg1_std_vole_ct_ref(&par.vole_params, par.degree, rvp_f_cz, rvp_u_cz, rvp_v_cz);
  // deg1 to degd [in place]
  prover_flambda_deg1_to_degd_vole_ref(&par.vole_params, par.degree - 1, rvp_f_cz, rvp_f_cz);
  // std to cst: deg d [in place]
  prover_flambda_degd_std_to_cst_vole_ct_ref(&par.vole_params, par.degree - 1, rvp_f_cz, rvp_f_cz);
  // std to cst: deg 1 [in place]
  prover_f2_std_to_cst_vole_ct_ref(&par.vole_params, par.num_inputs_pairs, rvp_u_in, rvp_v_in, rvp_u_in, rvp_v_in);

  // ----- circuit evaluation ------
  //  inputs + commit to it
  prover_cst_vole_packed_secret_input_ct_ref(  //
      &par.vole_params,                        //
      par.num_inputs_pairs,                    //
      sign.circuit_in_pub,                     // publications -> signature
      inputs_f,                                // output vole
      sk.skey_encoded_solution,                // input secret key bits
      rvp_u_in, rvp_v_in);                     // rvp

  xof_ctx hash_lines_ctx;  // round1 + cchk_u + cchk_v + inputs_mask :=> chall
  par.vole_params.xof.xof_init_and_seed(&hash_lines_ctx, &HASH_LINES_PREFIX, 1);
  par.vole_params.xof.xof_seed(&hash_lines_ctx, hash_aux, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&hash_lines_ctx, sign.cchk_u, (par.num_cchk_pairs + 7) >> 3);
  par.vole_params.xof.xof_seed(&hash_lines_ctx, cchk_res_v, par.cchk_matrix_nrows * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&hash_lines_ctx, sign.circuit_in_pub, (par.num_inputs_pairs + 7) >> 3);
  par.vole_params.xof.xof_finalize_and_output(&hash_lines_ctx, hash_lines, 2 * par.lambda_bytes);

  // --------------------------------------
  // Phase 3: PIOP protocol (prover side)
  // --------------------------------------

  //  generate the batching challenge points
  xof_ctx chall_rng;
  par.vole_params.xof.xof_init_and_seed(&chall_rng, hash_lines, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_finalize_and_output(&chall_rng, chall_a, par.lambda_bytes * par.rsd_codim_limbs);
  par.vole_params.xof.xof_output(&chall_rng, chall_unitary, par.lambda_bytes * par.rsd_w);

  rsd_public_key_times_challenge_ref(                         //
      &par.vole_params, par.rsd_w, par.rsd_n, par.rsd_codim,  //
      chall_a_H, chall_a_y,                                   //
      chall_a, sk.pkey_seed,                                  //
      sk.pkey_y, tmp_space);                                  //

  //  evaluate the mux trees
  memset(res_f, 0, (par.degree + 1) * par.lambda_bytes);
  par.vole_params.flambda_set(res_f, chall_a_y);
  for (uint64_t i = 0; i < par.rsd_w; i++) {
    prover_cst_mux_circuit_ct_ref(                             //
        &par.vole_params,                                      //
        par.mux_depth, par.mux_arities, par.rsd_npw,           // circuit parameters
        mux_f,                                                 // mux output
        inputs_f + 2 * par.lambda_bytes * par.mux_inputs * i,  // secret input bits (bin, deg 1)
        chall_a_H + par.lambda_bytes * par.rsd_npw * i,        // challenge points (mul by H)
        chall_unitary + par.lambda_bytes * i,                  // check_unitary challenge (depth coeffs)
        tmp_space);
    prover_cst_vole_xor_gate_ct_ref(  //
        &par.vole_params,             //
        res_f,                        // result
        res_f, par.degree,            // lhs
        mux_f, par.degree);           // rhs
  }
#ifdef PARANOIA_CHECK
  {
    // manual verification that res_f is zero
    for (uint64_t i = 0; i < par.lambda_bytes; i++) {
      CREQUIRE(res_f[i] == 0, "bug! res_f cst term is not zero!");
    }
  }
#endif  // PARANOIA_CHECK
  //  checkzero
  prover_cst_vole_check_zero_gate_ct_ref(  //
      &par.vole_params,                    //
      par.degree,                          //
      sign.circuit_cz_pub,                 // publication -> signature
      res_f,                               //
      rvp_f_cz);                           // rvp
  // generate h3

  xof_ctx hash_piop_ctx;  // round3 + check_zero + message :=> delta
  par.vole_params.xof.xof_init_and_seed(&hash_piop_ctx, &HASH_PIOP_PREFIX, 1);
  par.vole_params.xof.xof_seed(&hash_piop_ctx, sk.pkey_seed, par.lambda_bytes);
  par.vole_params.xof.xof_seed(&hash_piop_ctx, hash_lines, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&hash_piop_ctx, sign.circuit_cz_pub, par.degree * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&hash_piop_ctx, message, message_bytes);
  par.vole_params.xof.xof_finalize_and_output(&hash_piop_ctx, sign.hash_piop, 2 * par.lambda_bytes);

  // --------------------------------------
  // Phase 3: Open one random evaluation
  // --------------------------------------

  // ----- open delta ------
  // generate delta0 != 0 s.t. topen is good (POW)
  uint64_t topen = 1e9;
  memset(delta0, 0, par.delta0_capacity);
  uint64_t num_trials = 0;
  for (;; ++num_trials) {
    par.vole_params.proofow_rng(delta0, par.delta0_bytess, sign.hash_piop, num_trials);
    uint64_t vgrind = extract_kappabit_uint(par.proofow_w, par.tau * par.kappa, delta0);
    if (vgrind) continue;
    if (bitvec_is_zero_nonct(delta0, par.tau * par.kappa)) continue;
    hidden_leaves_indexes2(par.kappa, par.tau, hidden_leaves_idx, delta0);
    topen = estimate_topen(par.tau, par.kappa, par.target_topen, hidden_leaves_idx, tmp_space);
    if (topen <= par.target_topen) break;
  }
  memcpy(sign.proofow_ctr_reveal, &num_trials, PROOFOW_CTR_REVEALED_BYTES);

  // generate delta1
  delta1_from_delta0_ref(&par.vole_params, delta1, delta0);

  // generate ggm_opening_data
  full_ggm_tree_open_sibling_path(  //
      ggm_tree,                     //
      sign.ggm_sibling_path,        // -> signature
      sign.ggm_hidden_leaf_cmt,     // -> signature
      hidden_leaves_idx);
  // zero-out the unused ggm path
  uint8_t* ggm_sibling_path_zero_start = (uint8_t*)sign.ggm_sibling_path + topen * par.lambda_bytes;
  memset(ggm_sibling_path_zero_start, 0, (par.target_topen - topen) * par.lambda_bytes);
}

EXPORT uint64_t sdith_verify_tmp_bytes(const signature_parameters* sig_params) {
  extended_parameters_t par;
  compute_extended_parameters(&par, sig_params);

  COMP_SPACE_INIT();
  COMP_SPACE_MAP_ALIGNED(hash_t*, verif_hash_aux, 32,
                         2 * par.lambda_bytes);  // ggm_cmt_hash + corr_terms :=> cchk matrix
  COMP_SPACE_MAP_ALIGNED(hash_t*, verif_hash_lines, 32,
                         2 * par.lambda_bytes);  // round1 + cchk_u + cchk_v + inputs_mask :=> chall
  COMP_SPACE_MAP_ALIGNED(hash_t*, verif_hash_piop, 32,
                         2 * par.lambda_bytes);  // round3 + check_zero + message :=> delta
  COMP_SPACE_MAP_ALIGNED(uint32_t*, verif_hidden_leaves_idx, 4, par.tau * sizeof(uint32_t));
  COMP_SPACE_MAP(uint8_t*, verif_delta0, par.delta0_capacity);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_delta1, 32, par.lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_delta2, 32, par.lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_delta2_dm1, 32, par.lambda_bytes);
  COMP_SPACE_MAP(ggm_multi_sibling_tree*, sib_tree, bytes_of_ggm_multi_sibling_tree(par.lambda, par.tau, par.kappa));
  COMP_SPACE_MAP(uint8_t*, verif_corr, par.Lbyte* par.tau);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, q, 32, par.Lbyte* par.lambda);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, q2, 32, par.Lbyte* par.lambda);  // copy needed during transposition
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_hash_com, 32,
                         2 * par.lambda_bytes);  // ggm commitment hash (verify against the signature)
  COMP_SPACE_MAP(uint8_t*, verif_cchk_matrix, par.Lbyte* par.num_cchk_pairs);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_cchk_res_v, 32, par.lambda_bytes* par.num_cchk_pairs);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, inputs_q, 32, par.lambda_bytes* par.num_inputs_pairs);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_unitary, 32, par.lambda_bytes* par.rsd_w);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_a, 32, par.lambda_bytes* par.rsd_codim_limbs);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_a_H, 32, par.lambda_bytes* par.rsd_n);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_a_y, 32, par.lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, mux_q, 32, par.lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, res_q, 32, par.lambda_bytes);
  COMP_SPACE_MAP_ALIGNED(uint8_t*, cz_res, 32, par.lambda_bytes);
  COMP_SPACE_MAP_CALL(estimate_topen_tmp_bytes(par.tau, par.kappa));
  COMP_SPACE_MAP_CALL(
      verifier_cst_mux_circuit_ref_tmp_bytes(&par.vole_params, par.mux_depth, par.mux_arities, par.rsd_npw));
  COMP_SPACE_MAP_CALL(rsd_public_key_times_challenge_tmp_bytes(&par.vole_params, par.rsd_w, par.rsd_n, par.rsd_codim));
  COMP_SPACE_RETURN();
}

#define VERIFY_OR_FAIL(condition, error_message) \
  if (!(condition)) {                            \
    return 0;                                    \
  }
#define VERIFY_SUCCESS() return 1

EXPORT uint8_t sdith_verify(const signature_parameters* sig_params,       //
                            const void* signature,                        // out: signature
                            const void* message, uint64_t message_bytes,  // in: message
                            const void* pkey,                             // secret key
                            uint8_t* tmp_space) {
  extended_parameters_t par;
  compute_extended_parameters(&par, sig_params);

  // public key
  const pkey_mapping_t pk = map_public_key(&par, pkey);

  // signature fields
  const signature_mapping_t sign = map_signature(&par, signature);

  // local variables
  TMP_SPACE_MAP_ALIGNED(hash_t*, verif_hash_aux, 32,
                        2 * par.lambda_bytes);  // ggm_cmt_hash + corr_terms :=> cchk matrix
  TMP_SPACE_MAP_ALIGNED(hash_t*, verif_hash_lines, 32,
                        2 * par.lambda_bytes);  // round1 + cchk_u + cchk_v + inputs_mask :=> chall
  TMP_SPACE_MAP_ALIGNED(hash_t*, verif_hash_piop, 32, 2 * par.lambda_bytes);  // round3 + check_zero + message :=> delta
  TMP_SPACE_MAP_ALIGNED(uint32_t*, verif_hidden_leaves_idx, 4, par.tau * sizeof(uint32_t));
  TMP_SPACE_MAP(uint8_t*, verif_delta0, par.delta0_capacity);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_delta1, 32, par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_delta2, 32, par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_delta2_dm1, 32, par.lambda_bytes);
  TMP_SPACE_MAP(ggm_multi_sibling_tree*, sib_tree, bytes_of_ggm_multi_sibling_tree(par.lambda, par.tau, par.kappa));
  TMP_SPACE_MAP(uint8_t*, verif_corr, par.Lbyte* par.tau);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, q, 32, par.Lbyte* par.lambda);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, q2, 32, par.Lbyte* par.lambda);  // copy needed during transposition
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_hash_com, 32,
                        2 * par.lambda_bytes);  // ggm commitment hash (verify against the signature)
  TMP_SPACE_MAP(uint8_t*, verif_cchk_matrix, par.Lbyte* par.num_cchk_pairs);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_cchk_res_v, 32, par.lambda_bytes* par.num_cchk_pairs);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, inputs_q, 32, par.lambda_bytes* par.num_inputs_pairs);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_unitary, 32, par.lambda_bytes* par.rsd_w);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_a, 32, par.lambda_bytes* par.rsd_codim_limbs);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_a_H, 32, par.lambda_bytes* par.rsd_n);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, verif_chall_a_y, 32, par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, mux_q, 32, par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, res_q, 32, par.lambda_bytes);
  TMP_SPACE_MAP_ALIGNED(uint8_t*, cz_res, 32, par.lambda_bytes);
  TMP_SPACE_MAP_CALL(estimate_topen_tmp_bytes(par.tau, par.kappa));
  TMP_SPACE_MAP_CALL(
      verifier_cst_mux_circuit_ref_tmp_bytes(&par.vole_params, par.mux_depth, par.mux_arities, par.rsd_npw));
  TMP_SPACE_MAP_CALL(rsd_public_key_times_challenge_tmp_bytes(&par.vole_params, par.rsd_w, par.rsd_n, par.rsd_codim))

  // verifier side
  uint64_t leftover_bits = par.num_inputs_pairs & 7;
  if (leftover_bits) {
    uint64_t mask = ((1 << (8 - leftover_bits)) - 1) << leftover_bits;
    uint64_t idx = ((par.num_inputs_pairs + 7) >> 3) - 1;
    VERIFY_OR_FAIL((sign.circuit_in_pub[idx] & mask) == 0, "in_publications does not have trailing zeros");
  }

  // --------------------------------------
  // Phase 1: Recompute and check the evaluation
  // --------------------------------------

  // ----- open delta ------
  // generate delta0 != 0 s.t. topen is good (POW)
  uint64_t topen = 1e9;
  uint64_t proof_of_work_counter = 0;
  memset(verif_delta0, 0, par.delta0_capacity);
  memcpy(&proof_of_work_counter, sign.proofow_ctr_reveal, PROOFOW_CTR_REVEALED_BYTES);  // load the golden counter
  par.vole_params.proofow_rng(verif_delta0, par.delta0_bytess, sign.hash_piop, proof_of_work_counter);
  uint64_t vgrind = extract_kappabit_uint(par.proofow_w, par.tau * par.kappa, verif_delta0);
  VERIFY_OR_FAIL(vgrind == 0, "invalid proof of work: vgrind");
  VERIFY_OR_FAIL(!bitvec_is_zero_nonct(verif_delta0, par.tau * par.kappa), "invalid proof of work: zero");
  hidden_leaves_indexes2(par.kappa, par.tau, verif_hidden_leaves_idx, verif_delta0);
  topen = estimate_topen(par.tau, par.kappa, par.target_topen, verif_hidden_leaves_idx, tmp_space);
  VERIFY_OR_FAIL(topen <= par.target_topen, "invalid proof of work: topen");

  // check that the sibling path has trailing zeroes (if needed)
  {
    uint64_t zero_values = par.target_topen - topen;
    uint8_t* ggm_sibling_path_zero_start = (uint8_t*)sign.ggm_sibling_path + topen * par.lambda_bytes;
    VERIFY_OR_FAIL(bitvec_is_zero_nonct(ggm_sibling_path_zero_start, zero_values * par.lambda_bytes),
                   "sibling path cleanliness");
  }
  // generate delta1 and delta2
  delta1_from_delta0_ref(&par.vole_params, verif_delta1, verif_delta0);
  delta2_from_delta1_ref(&par.vole_params, verif_delta2, verif_delta1);

  // From Vole perspective, the evaluation point is Delta1 (Delta0 is blockwise, the Grey code of Delta1)
  // Vole protocol reconstructs pairs evaluated in Delta1.

  // initialize the sibling tree structure
  ggm_multi_sibling_tree_init(                                          //
      sib_tree,                                                         //
      par.lambda, par.tau, par.kappa,                                   //
      par.vole_params.ggm_seed_rng_lr, par.vole_params.ggm_commit_rng,  // crypto functions
      sign.global_salt,                                                 //
      verif_hidden_leaves_idx, sign.ggm_sibling_path, sign.ggm_hidden_leaf_cmt);

  // generate vole pairs
  xof_ctx verifier_hash_bavc_ctx;
  par.vole_params.xof.xof_init_and_seed(&verifier_hash_bavc_ctx, &HASH_BAVC_PREFIX, 1);
  memset(verif_corr, 0, par.Lbyte);
  memcpy(verif_corr + par.Lbyte, sign.corr_u, (par.tau - 1) * par.Lbyte);
  verifier_open_midsize_grey_vole_from_seeds_ref(  //
      &par.vole_params, par.L, &verifier_hash_bavc_ctx, q, verif_corr, sib_tree, verif_delta1);
  par.vole_params.xof.xof_finalize_and_output(&verifier_hash_bavc_ctx, verif_hash_com, 2 * par.lambda_bytes);

  // then we reconvert these vole pairs into PIOP material.
  // From PIOP perspective, the verifier gets the evaluation in Delta2 (qhich is the inverse of Delta1)

  // ----- vole preprocessing ------
  // transpose vole
  memset(q + par.kappa * par.tau * par.Lbyte, 0, (par.lambda - par.kappa * par.tau) * par.Lbyte);
  verifier_midsize_to_fullsize_std_vole_ref(&par.vole_params, par.L, q2, q);

  uint8_t* const rvp_q_cchk = q2;
  uint8_t* const rvp_q_cz = rvp_q_cchk + (par.num_cchk_pairs * par.lambda_bytes);
  uint8_t* const rvp_q_in = rvp_q_cz + (par.num_cz_pairs * par.lambda_bytes);

  xof_ctx verif_hash_aux_ctx;  // ggm_cmt_hash + corr_terms :=> cchk matrix
  par.vole_params.xof.xof_init_and_seed(&verif_hash_aux_ctx, &HASH_AUX_PREFIX, 1);
  par.vole_params.xof.xof_seed(&verif_hash_aux_ctx, verif_hash_com, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&verif_hash_aux_ctx, sign.corr_u, (par.tau - 1) * par.Lbyte);
  par.vole_params.xof.xof_finalize_and_output(&verif_hash_aux_ctx, verif_hash_aux, 2 * par.lambda_bytes);

  // vole consistency check
  both_vole_consistency_check_matrix(&par.vole_params, par.L, verif_cchk_matrix, verif_hash_aux, 2 * par.lambda_bytes);
  verifier_vole_consistency_check(&par.vole_params, par.L, verif_cchk_res_v, sign.cchk_u, q2, verif_cchk_matrix,
                                  verif_delta1);

  xof_ctx verif_hash_lines_ctx;  // round1 + cchk_u + cchk_v + inputs_mask :=> chall
  par.vole_params.xof.xof_init_and_seed(&verif_hash_lines_ctx, &HASH_LINES_PREFIX, 1);
  par.vole_params.xof.xof_seed(&verif_hash_lines_ctx, verif_hash_aux, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&verif_hash_lines_ctx, sign.cchk_u, (par.num_cchk_pairs + 7) >> 3);
  par.vole_params.xof.xof_seed(&verif_hash_lines_ctx, verif_cchk_res_v, par.cchk_matrix_nrows * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&verif_hash_lines_ctx, sign.circuit_in_pub, (par.num_inputs_pairs + 7) >> 3);
  par.vole_params.xof.xof_finalize_and_output(&verif_hash_lines_ctx, verif_hash_lines, 2 * par.lambda_bytes);

  // --------------------------------------
  // PIOP Protocol (verifier's side)
  // --------------------------------------
  // At this point, delta2 is the only point that matters: the verifier will check
  // the PIOP circuit evaluated on delta2.

  xof_ctx verif_hash_piop_ctx;  // round3 + check_zero + message :=> delta
  par.vole_params.xof.xof_init_and_seed(&verif_hash_piop_ctx, &HASH_PIOP_PREFIX, 1);
  par.vole_params.xof.xof_seed(&verif_hash_piop_ctx, pk.pkey_seed, par.lambda_bytes);
  par.vole_params.xof.xof_seed(&verif_hash_piop_ctx, verif_hash_lines, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&verif_hash_piop_ctx, sign.circuit_cz_pub, par.degree * par.lambda_bytes);
  par.vole_params.xof.xof_seed(&verif_hash_piop_ctx, message, message_bytes);
  par.vole_params.xof.xof_finalize_and_output(&verif_hash_piop_ctx, verif_hash_piop, 2 * par.lambda_bytes);
  VERIFY_OR_FAIL(memcmp(verif_hash_piop, sign.hash_piop, 2 * par.lambda_bytes) == 0, "invalid hash_piop");

  // f2 to flambda
  verifier_f2_to_flambda_deg1_std_vole_ref(&par.vole_params, par.degree, rvp_q_cz, rvp_q_cz);
  // deg1 to degd [in place]
  verifier_flambda_deg1_to_degd_vole_ref(&par.vole_params, par.degree - 1, rvp_q_cz, rvp_q_cz, verif_delta1);
  // std to cst: deg d [in place]
  flambda_power(&par.vole_params, verif_delta2_dm1, verif_delta2, par.degree - 1);
  verifier_flambda_degd_std_to_cst_vole_ref(&par.vole_params, par.degree - 1, rvp_q_cz, rvp_q_cz, verif_delta2_dm1);
  // std to cst: deg 1 [in place]
  verifier_f2_std_to_cst_vole_ref(&par.vole_params, par.num_inputs_pairs, rvp_q_in, rvp_q_in, verif_delta2);

  // ----- circuit evaluation ------
  //  inputs + commit to it
  verifier_cst_vole_packed_secret_input_ref(  //
      &par.vole_params,                       //
      par.num_inputs_pairs,                   //
      inputs_q,
      sign.circuit_in_pub,  // publications -> signature
      rvp_q_in,
      verif_delta2);  // rvp

  //  reconstruct the batching challenge points
  xof_ctx verif_chall_rng;
  par.vole_params.xof.xof_init_and_seed(&verif_chall_rng, verif_hash_lines, 2 * par.lambda_bytes);
  par.vole_params.xof.xof_finalize_and_output(&verif_chall_rng, verif_chall_a, par.lambda_bytes * par.rsd_codim_limbs);
  // note: the chall unitary are only needed if the mux tree contains one non-binary arity
  par.vole_params.xof.xof_output(&verif_chall_rng, verif_chall_unitary, par.lambda_bytes * par.rsd_w);

  rsd_public_key_times_challenge_ref(&par.vole_params, par.rsd_w, par.rsd_n, par.rsd_codim,  //
                                     verif_chall_a_H, verif_chall_a_y,                       //
                                     verif_chall_a, pk.pkey_seed, pk.pkey_y, tmp_space);
  par.vole_params.flambda_set(res_q, verif_chall_a_y);
  for (uint64_t i = 0; i < par.rsd_w; i++) {
    verifier_cst_mux_circuit_ref(                              //
        &par.vole_params,                                      //
        par.mux_depth, par.mux_arities, par.rsd_npw,           // circuit parameters
        mux_q,                                                 // mux output
        inputs_q + par.lambda_bytes * par.mux_inputs * i,      // secret input bits (bin, deg 1)
        verif_chall_a_H + par.lambda_bytes * par.rsd_npw * i,  // challenge points (mul by H)
        verif_chall_unitary + par.lambda_bytes * i,            // check_unitary challenge (depth coeffs)
        verif_delta2, tmp_space);
    verifier_cst_vole_xor_gate_ref(  //
        &par.vole_params,            //
        res_q,                       // result
        res_q, par.degree,           // lhs
        mux_q, par.degree,           // rhs
        verif_delta2);
  }

  //  checkzero
  uint8_t chk = verifier_cst_vole_check_zero_gate_ref(  //
      &par.vole_params,                                 //
      par.degree,                                       //
      cz_res,
      sign.circuit_cz_pub,  // publication -> signature
      res_q,                //
      rvp_q_cz,             // rvp
      verif_delta2);
  // generate h3
  VERIFY_OR_FAIL(chk == 1, "cz gate returns non zero");

  VERIFY_SUCCESS();
}
