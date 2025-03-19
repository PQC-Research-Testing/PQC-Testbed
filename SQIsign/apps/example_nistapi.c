// SPDX-License-Identifier: Apache-2.0

/**
 * An example to demonstrate how to use SQIsign with the NIST API.
 */
#include <inttypes.h>
#include <mem.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <api.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>
#include <rng.h>
#include <bench_test_arguments.h>
#if defined(TARGET_BIG_ENDIAN)
#include <tutil.h>
#endif

size_t getPeakRSS(){
    struct rusage rusage;
    getrusage(RUSAGE_SELF, &rusage );
    return (size_t)(rusage.ru_maxrss * 1024L);
}

static __inline__ unsigned long GetCC(void)
{
  unsigned a, d; 
  asm volatile("rdtsc" : "=a" (a), "=d" (d)); 
  return ((unsigned long)a) | (((unsigned long)d) << 32); 
}

static uint32_t rand_u32()
{
    unsigned char buf[4];
    if (randombytes(buf, sizeof(buf)))
        abort();
    return ((uint32_t) buf[3] << 24)
         | ((uint32_t) buf[2] << 16)
         | ((uint32_t) buf[1] <<  8)
         | ((uint32_t) buf[0] <<  0);
}

/**
 * Example for SQIsign variant:
 * - crypto_sign_keypair
 * - crypto_sign
 * - crypto_sign_open
 *
 * @return int return code
 */
static int
example_sqisign(void)
{
    unsigned long long msglen = rand_u32() % 100;
    unsigned long long smlen = CRYPTO_BYTES + msglen;

    unsigned char *sk = calloc(CRYPTO_SECRETKEYBYTES, 1);
    unsigned char *pk = calloc(CRYPTO_PUBLICKEYBYTES, 1);

    unsigned char *sm = calloc(smlen, 1);
    int res = 0;
    unsigned char temp;
    unsigned char msg[msglen], msg2[msglen];
    unsigned long before, after;
    unsigned long rss_peak;

    printf("Example with %s\n", CRYPTO_ALGNAME);
    before = GetCC();
    res = crypto_sign_keypair(pk, sk);
    after = GetCC();
    printf("Cycles: %lu\n",(after-before)/1000000);
    printf("crypto_sign_keypair -> ");
    if (res) {
        printf("FAIL\n");
        goto err;
    }else {
        printf("OK\n");
    }
    // choose a random message
    for (size_t i = 0; i < msglen; ++i){
        //temp = rand_u32();   
        temp = 1;
        msg[i] = temp;
        msg2[i] = temp;
    }

    before = GetCC();
    res = crypto_sign(sm, &smlen, msg, msglen, sk);
    after = GetCC();

    printf("Cycles: %lu\n",(after-before)/1000000);
    printf("crypto_sign -> ");
    if (res) {
        printf("FAIL\n");
        goto err;
    } else {
        printf("OK\n");
    }

    before = GetCC();
    res = crypto_sign_open(msg2, &msglen, sm, smlen, pk);
    after = GetCC();

    printf("Cycles: %lu\n",(after-before)/1000000);
    printf("crypto_sign_open (with correct signature) -> ");
    if (res || msglen != sizeof(msg) || memcmp(msg, msg2, msglen)) {
        printf("FAIL\n"); // signature was not accepted!?
        goto err;
    } else {
        printf("OK\n");
    }
    rss_peak = getPeakRSS();
    printf("Peak RSS Usage: %ld KB\n",rss_peak/1000);

err:
    sqisign_secure_free(sk, CRYPTO_SECRETKEYBYTES);
    free(pk);
    free(sm);

    return res;
}

int
main(int argc, char *argv[])
{
    uint32_t seed[12] = { 0 };
    int help = 0;
    int seed_set = 0;

    for (int i = 1; i < argc; i++) {
        if (!help && strcmp(argv[i], "--help") == 0) {
            help = 1;
            continue;
        }

        if (!seed_set && !parse_seed(argv[i], seed)) {
            seed_set = 1;
            continue;
        }
    }

    if (help) {
        printf("Usage: %s [--seed=<seed>]\n", argv[0]);
        printf("Where <seed> is the random seed to be used; if not present, a random seed is "
               "generated\n");
        return 1;
    }

    if (!seed_set) {
        randombytes_select((unsigned char *)seed, sizeof(seed));
    }

    print_seed(seed);

#if defined(TARGET_BIG_ENDIAN)
    for (int i = 0; i < 12; i++) {
        seed[i] = BSWAP32(seed[i]);
    }
#endif

    randombytes_init((unsigned char *)seed, NULL, 256);

    return example_sqisign();
}