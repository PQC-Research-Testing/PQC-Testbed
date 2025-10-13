#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <openssl/sha.h>

static inline void simple_randombytes(unsigned char *x, unsigned long long xlen) {
    for (unsigned long long i = 0; i < xlen; i++) {
        x[i] = (unsigned char) (rand() % 256);
    }
}

static inline void flip_bit(unsigned char *a, unsigned long long alen, unsigned long long pos) {
    unsigned long long byte_index = pos / 8;
    unsigned long long bit_index = pos % 8;
    if (byte_index >= alen) {
        fprintf(stderr, "flip_bit error: position out of bounds.\n");
        return;
    }
    a[byte_index] ^= (1 << bit_index);
}

static inline void print_array_short(const char *name, unsigned char *array, unsigned long long len) {
    printf("%s: ", name);
    for (size_t i = 0; i < len; i++) {
        if(i < 3) printf("%02x", array[i]);
        else if(i == len/2) printf(" ... ");
        else if(i > (len-4)) printf("%02x", array[i]);
    }
    printf("\n");
}

static inline void print_array_full(const char *name, unsigned char *array, unsigned long long len) {
    printf("%s: ", name);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", array[i]);
    }
    printf("\n");
}

static inline void print_sha256(unsigned char *a, unsigned long long alen) {
    printf("\n");
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(a, alen, hash);
    printf("SHA-256: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

static inline void print_progress(long long test, long long num_tests) {
    test++;
    int total_dots = 100;
    int dots_to_print = (test * total_dots) / num_tests;
    if (dots_to_print > total_dots) {
        dots_to_print = total_dots;
    }
    printf("[");
    for (int i = 0; i < total_dots; i++) {
        if (i < dots_to_print) {
            printf(".");
        } else {
            printf(" ");
        }
    }
    if(test == num_tests) printf("] %lld/%lld\n", test, num_tests);
    else printf("] %lld/%lld\r", test, num_tests);
    fflush(stdout);
}

#define CROSS_RUNTIME_INFO_HEADER "problem,cateogry,target,length-secret-key,length-public-key,length-signature,length-seed,lambda,P,Z,G,N,K,M,T,W"

static inline void print_cross_runtime_info(int extended) {
    //
    #ifdef RSDP
    printf("RSDP");
    #endif
    #ifdef RSDPG
    printf("RSDPG");
    #endif
    //
    printf(",");
    //
    #ifdef CATEGORY_1
    printf("1");
    #endif
    #ifdef CATEGORY_3
    printf("3");
    #endif
    #ifdef CATEGORY_5
    printf("5");
    #endif
    //
    printf(",");
    //
    #ifdef BALANCED
    printf("balanced");
    #endif
    #ifdef SPEED
    printf("fast");
    #endif
    #ifdef SIG_SIZE
    printf("small");
    #endif
    if(extended) {
        printf(",");
        printf("%ld,", CRYPTO_SECRETKEYBYTES);
        printf("%ld,", CRYPTO_PUBLICKEYBYTES);
        printf("%ld,", CRYPTO_BYTES);
        printf("%d,", CRYPTO_RANDOMBYTES);
        printf("%d,", SEC_MARGIN_LAMBDA);
        printf("%d,", P);
        printf("%d,", Z);
        printf("%d,", RESTR_G_GEN);
        printf("%d,", N);
        printf("%d,", K);
        #ifdef RSDPG
        printf("%d", M);
        #endif
        printf(",");
        printf("%d,", T);
        printf("%d", W);
    }

    // #ifdef REFERENCE
    // printf("- REFERENCE ");
    // #else
    // printf("- OPTIMIZED ");
    // #endif
    //
}