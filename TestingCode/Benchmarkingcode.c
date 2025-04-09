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
#include <randombytes.h>
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
    unsigned long long msglen = 1000;
    int size = 11;
    char realmsg[] = "hello world";
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

     //file for storing runtime data
     FILE *file = fopen(CRYPTO_ALGNAME, "a");
     if(file){
         fseek(file, 0, SEEK_END);
         long size = ftell(file);
         if(size==0){
             fprintf(file, "Keygen CC,Keygen Time (Microseconds), Signature CC,Signature Time (Microseconds),Verification CC,Verification Time (Microseconds),PEAK RSS (KB)\n");
         }
     }
     //print statements used to ensure data being gathered. To be removed and replaced with logging in a file.
     //focus on getting everything working first. 
     printf("Bench with %s\n", CRYPTO_ALGNAME);
     gettimeofday(&st, NULL);
     before = GetCC();
     //consider adding mechanism to track elapsed time of GetCC() function to remove it from api function runtime.
     res = crypto_sign_keypair(pk, sk);
     after = GetCC();
     gettimeofday(&et, NULL);
     timeElapsed = ((et.tv_sec - st.tv_sec)*1000000) + (et.tv_usec - st.tv_usec);
     printf("Cycles: %.2f Megacycles\n",(double)(after-before)/1000000);
     printf("Time elapsed: %lu microseconds\n", timeElapsed);
     fprintf(file, "%.2f, %lu, ",(double)(after-before)/1000000, timeElapsed);
     // choose a random message
     for (size_t i = 0; i < msglen; i++){  
        msg[i] = realmsg[i%size];
     }
 
     gettimeofday(&st, NULL);
     before = GetCC();
     res = crypto_sign(sm, &smlen, msg, msglen, sk);
     after = GetCC();
     gettimeofday(&et, NULL);
     timeElapsed = ((et.tv_sec - st.tv_sec)*1000000) + (et.tv_usec - st.tv_usec);
     printf("Cycles: %.2f Megacycles\n",(double)(after-before)/1000000);
     printf("Time elapsed: %lu microseconds\n", timeElapsed);
     fprintf(file, "%.2f, %lu, ",(double)(after-before)/1000000, timeElapsed);
 
     gettimeofday(&st, NULL);
     before = GetCC();
     res = crypto_sign_open(msg2, &msglen, sm, smlen, pk);
     after = GetCC();
     gettimeofday(&et, NULL);
     timeElapsed = ((et.tv_sec - st.tv_sec)*1000000) + (et.tv_usec - st.tv_usec);
     printf("Cycles: %.2f Megacycles\n",(double)(after-before)/1000000);
     printf("Time elapsed: %lu microseconds\n", timeElapsed);
     fprintf(file, "%.2f, %lu, ",(double)(after-before)/1000000, timeElapsed);
 
     rss_peak = getPeakRSS();
     printf("Peak RSS Usage: %ld KB\n",rss_peak/1000);
     fprintf(file, "%ld\n", rss_peak/1000);
     fclose(file);
 
     return res;
 }
 