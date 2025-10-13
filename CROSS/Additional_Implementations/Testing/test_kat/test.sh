#!/bin/bash

# ./Additional_Implementations/Testing/test_kat/test.sh

set -e
# set -x

TESTING_DIR="./Additional_Implementations/Testing"

TEST_DIR="$TESTING_DIR/test_kat"
BUILD_DIR="$TEST_DIR/build"

# Create the build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
echo '*' > "$BUILD_DIR/.gitignore"

################################################################################
generate_kat() {
    local kat_file="../$BUILD_DIR/test_sha_512_sum_KATs"
    # Build CROSS
    cd Additional_Implementations/KAT_Generation/
    rm -rf build 
    mkdir build
    cd build 
    echo "*" > .gitignore
    cmake ../ "$@"
    make -j$(nproc)
    cd ..
    rm -rf ../../KAT/PQC*
    # Generate KAT
    ./gen_all_kat.sh
    cd ../../KAT
    sha512sum * > $kat_file
    cat $kat_file
    echo ">> KAT generated"
    # Single hash for all KAT
    sha256sum $kat_file
    rm $kat_file
    cd ..
    # Clean up
    rm -rf KAT/PQC*
}
################################################################################

# Generate KAT for Reference Implementation
echo ">> Generating KAT for Reference Implementation"
generate_kat "-DREFERENCE=1" > "$BUILD_DIR/reference_kat.txt"

# Generate KAT for Optimized Implementation
echo ">> Generating KAT for Optimized Implementation"
generate_kat "-DREFERENCE=0" >  "$BUILD_DIR/optimized_kat.txt"

# Generate KAT for Optimized Implementation without AVX2 (fallback)
echo ">> Generating KAT for Optimized Implementation without AVX2"
generate_kat "-DREFERENCE=0" "-DTEST_FLAGS=-march=nocona -Wno-pedantic" >  "$BUILD_DIR/fallback_kat.txt"

# Get the hashes
kat_ref=$(tail -n 1 $BUILD_DIR/reference_kat.txt)
kat_opt=$(tail -n 1 $BUILD_DIR/optimized_kat.txt)
kat_fal=$(tail -n 1 $BUILD_DIR/fallback_kat.txt)

# Check that the hashes match
echo ">> Comparing the hashes"
if [[ "$kat_ref" == *"test_sha_512_sum_KATs"* ]] && [[ "$kat_opt" == *"test_sha_512_sum_KATs"* ]] && [[ "$kat_fal" == *"test_sha_512_sum_KATs"* ]]; then
    if [[ "$kat_ref" == "$kat_opt" ]] && [[ "$kat_ref" == "$kat_fal" ]]; then
        echo ">> OK: hashes match"
    else
        echo ">> ERROR: hashes don't match"
        echo ">> Reference Implementation hash: $kat_ref"
        echo ">> Optimized Implementation hash: $kat_opt"
        echo ">> Fallback  Implementation hash: $kat_fal"
        exit 1
    fi
else
    echo ">> ERROR: KAT hash not found"
    echo ">> Reference Implementation hash: $kat_ref"
    echo ">> Optimized Implementation hash: $kat_opt"
    echo ">> Fallback  Implementation hash: $kat_fal"
    exit 1
fi
