#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <api.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>
#include <rng.h>
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

int
main()
{
    unsigned char seed[48] = {0};
    randombytes_init(seed, NULL, 256);
    unsigned long long msglen = 100;
    unsigned long long smlen = CRYPTO_BYTES + msglen;

    unsigned char *sk = calloc(CRYPTO_SECRETKEYBYTES, 1);
    unsigned char *pk = calloc(CRYPTO_PUBLICKEYBYTES, 1);
    struct timeval st, et;
    unsigned long timeElapsed;
    unsigned char *sm = calloc(smlen, 1);
    int res = 0;
    unsigned char temp;
    unsigned char msg[msglen], msg2[msglen];
    unsigned long before, after;
    unsigned long rss_peak;

    printf("Bench with %s\n", CRYPTO_ALGNAME);
    gettimeofday(&st, NULL);
    before = GetCC();
    res = crypto_sign_keypair(pk, sk);
    after = GetCC();
    gettimeofday(&et, NULL);
    timeElapsed = ((et.tv_sec - st.tv_sec)*1000000) + (et.tv_usec - st.tv_usec);
    printf("Cycles: %.2f Megacycles\n",(double)(after-before)/1000000);
    printf("Time elapsed: %lu microseconds\n", timeElapsed);
    // choose a random message
    for (size_t i = 0; i < msglen; i++){
        temp = rand_u32(); //consider making message non-random later.
        msg[i] = temp;
    }

    gettimeofday(&st, NULL);
    before = GetCC();
    res = crypto_sign(sm, &smlen, msg, msglen, sk);
    after = GetCC();
    gettimeofday(&et, NULL);
    timeElapsed = ((et.tv_sec - st.tv_sec)*1000000) + (et.tv_usec - st.tv_usec);
    printf("Cycles: %.2f Megacycles\n",(double)(after-before)/1000000);
    printf("Time elapsed: %lu microseconds\n", timeElapsed);

    gettimeofday(&st, NULL);
    before = GetCC();
    res = crypto_sign_open(msg2, &msglen, sm, smlen, pk);
    after = GetCC();
    gettimeofday(&et, NULL);
    timeElapsed = ((et.tv_sec - st.tv_sec)*1000000) + (et.tv_usec - st.tv_usec);
    printf("Cycles: %.2f Megacycles\n",(double)(after-before)/1000000);
    printf("Time elapsed: %lu microseconds\n", timeElapsed);

    rss_peak = getPeakRSS();
    printf("Peak RSS Usage: %ld KB\n",rss_peak/1000);

    return res;
}
