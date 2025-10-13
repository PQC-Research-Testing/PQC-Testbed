#ifndef SIG_PERK_CONFIG_H
#define SIG_PERK_CONFIG_H

#define PERK_CONFIG_ALGNAME         "perk-5-fast"
#define PERK_CONFIG_SECURITY_BYTES  32
#define PERK_CONFIG_TOWER_FIELD_EXT 24
#define PERK_CONFIG_PARAM_N         118
#define PERK_CONFIG_PARAM_M         59
#define PERK_CONFIG_PARAM_TAU1      26
#define PERK_CONFIG_PARAM_KAPPA1    8
#define PERK_CONFIG_PARAM_TAU2      6
#define PERK_CONFIG_PARAM_KAPPA2    7
#define PERK_CONFIG_PARAM_MU1       9
#define PERK_CONFIG_PARAM_MU2       8
#define PERK_CONFIG_PARAM_TAU_PRIME 8
#define PERK_CONFIG_SHARE_DEGREE    4
#define PERK_CONFIG_PARAM_C         7
#define PERK_CONFIG_PARAM_W         8
#define PERK_CONFIG_PARAM_T_OPEN    220

#define PERK_USE_AVX2 1

#define xkcp4x                1
#define xkcp1x                2
#define FINAL_COMMITMENT_MODE xkcp4x

#define xkcp 1
#define aes  2
#define PRG_LEAF_COMMIT_IMPL xkcp
#define PRG_EXPAND_SEED_IMPL xkcp

#define PERK_CONFIG_PARAM_SEC_LEVEL 5
#endif  // SIG_PERK_CONFIG_H
