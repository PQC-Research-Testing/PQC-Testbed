#include "api.h"
#include "csprng_hash.h"
#include "rng.h"
#include "test_helpers.h"

#define NUM_TESTS 1

int main() {

    for(int i=0; i<NUM_TESTS; i++) {

        printf(">> %s\n", CROSS_RUNTIME_INFO_HEADER);
        
        printf("<< ");
        print_cross_runtime_info(1);
        printf("\n");

    }

}

/*
echo ">> problem,cateogry,target,length-secret-key,length-public-key,length-signature,length-seed,lambda,P,Z,G,N,K,M,T,W"
python3 test.py test=test_parameters implementation=reference 2>/dev/null | grep "<<"
*/
