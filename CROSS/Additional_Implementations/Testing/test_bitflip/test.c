#include "api.h"
#include "csprng_hash.h"
#include "rng.h"
#include "test_helpers.h"

#define NUM_TESTS 1

int main() {

    unsigned char       *m, *sm, *m1, *tampered_sm;
    unsigned char       *sig;
    unsigned long long  siglen;
    unsigned long long  mlen;
    unsigned long long  smlen;
    unsigned long long  mlen1;
    
    unsigned char       pk[CRYPTO_PUBLICKEYBYTES] = {1};
    unsigned char       sk[CRYPTO_SECRETKEYBYTES] = {1};

    unsigned char       entropy_input[48] = {0};

    mlen = 50;

    m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
    m1 = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
    sm = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
    sig = (unsigned char *)calloc(CRYPTO_BYTES, sizeof(unsigned char));
    tampered_sm = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));

    setbuf(stdout, NULL);

    simple_randombytes(m, mlen); 

    simple_randombytes(entropy_input, 48);
    csprng_initialize(&platform_csprng_state, entropy_input, 48, 0);

    for(int i=0; i<NUM_TESTS; i++) {

        // print_progress(i, NUM_TESTS);

        simple_randombytes(m, mlen);

        if ( crypto_sign_keypair(pk, sk) != 0) {
            printf("\n\n **** KEYPAIR ERROR ****\n\n");
            exit(-1);
        }
        if ( crypto_sign(sm, &smlen, m, mlen, sk) != 0) {
            printf("\n\n **** SIGN ERROR ****\n\n");
            exit(-1);
        }
        if ( crypto_sign_open(m1, &mlen1, sm, smlen, pk) != 0) {
            printf("\n\n **** VERIFY ERROR ****\n\n");
            exit(-1);
        }

        // For every bit of the signature, flip it and check if the verification fails
        for(long long bit_index=0; bit_index<(smlen*8); bit_index++){
            print_progress(bit_index, smlen*8);
            memcpy(tampered_sm, sm, smlen);
            flip_bit(tampered_sm, smlen, bit_index);
            if ( crypto_sign_open(m1, &mlen1, tampered_sm, smlen, pk) == 0) {
                // printf("#");
                // printf("%02x", sm[bit_index/8]);
                printf("\n\n **** TAMPER ERROR: flipping bit %lld produces a valid signature ****\n\n", bit_index);
                exit(-1);
            }
            // else{
            //     printf(".");
            //     // printf("%02x", sm[bit_index/8]);
            // }
            // tampered_sm[bit_index]--;
        }
        printf("\n");

    }

    // avoid -Wunused-variable warning
    (void)siglen;
    (void)mlen;
    (void)smlen;
    (void)mlen1;

    free(m);
    free(m1);
    free(sm);
    free(sig);
    free(tampered_sm);

}
