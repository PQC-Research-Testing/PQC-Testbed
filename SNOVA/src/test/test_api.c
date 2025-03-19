#include <stdio.h>

#include "../api.h"
#include "../util/util.h"
#include "../nistkat/rng.h"
#include<inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#define msglen 1000

size_t getPeakRSS(){
    struct rusage rusage;
    getrusage(RUSAGE_SELF, &rusage );
    return (size_t)(rusage.ru_maxrss * 1024L);
}

static __inline__ unsigned long GetCC(void)
{
  unsigned a, d; 
  asm ("rdtsc" : "=a" (a), "=d" (d)); 
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
SNOVA_Test(void)
{
    snova_init();
    uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
    uint8_t text[msglen] = {0};
    uint8_t sm[CRYPTO_BYTES + msglen];
    unsigned long long smlen;
    uint8_t entropy_input[48];
    for (int i = 0; i < 48; i++) {
        entropy_input[i] = i;
    }

    randombytes_init(entropy_input, NULL, 256);
    unsigned long long mlan;
    unsigned long before, after;
    unsigned long rss_peak;
    int temp;
    uint8_t msg[msglen];

    printf("Example with %s\n", CRYPTO_ALGNAME);
    before = GetCC();
    crypto_sign_keypair(pk, sk);
    after = GetCC();
    printf("Cycles: %lu\n",(after-before)/1000000);

    // choose a random message
    for (size_t i = 0; i < msglen; ++i){
        temp = rand_u32();   
        temp = 1;
        msg[i] = temp;
    }

    before = GetCC();
    crypto_sign(sm, &smlen, text, msglen, sk);
    after = GetCC();
    printf("Cycles: %lu\n",(after-before)/1000000);

    before = GetCC();
    crypto_sign_open(msg, &mlan, sm, CRYPTO_BYTES + msglen, pk);
    after = GetCC();
    printf("Cycles: %lu\n",(after-before)/1000000);

    rss_peak = getPeakRSS();
    printf("Peak RSS Usage: %ld KB\n",rss_peak/1000);
    return 1;
}

int
main()
{
    return SNOVA_Test();
}

