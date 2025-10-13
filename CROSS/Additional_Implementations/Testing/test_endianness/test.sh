#!/bin/bash

# ./Additional_Implementations/Testing/test_endianness/test.sh

set -e
# set -x

TESTING_DIR="./Additional_Implementations/Testing"
DOCKER_NUKE="$TEST_DIR/helpers/docker_nuke.sh"

TEST_DIR="$TESTING_DIR/test_endianness"
DOCKERFILE="$TEST_DIR/Dockerfile"
BUILD_DIR="$TEST_DIR/build"

# Clean up Docker containers on exit
trap "echo '>> Test interrupted. Stopping Docker containers.'; $DOCKER_NUKE ;exit 1" SIGINT

# Create the build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
echo '*' > "$BUILD_DIR/.gitignore"

# Check that Docker is installed
if ! [ -x "$(command -v docker)" ]; then
    echo ">> ERROR: Docker package not found, please install it" >&2
    exit 1
fi
if ! docker buildx ls --no-trunc | grep -q s390x; then
    echo ">> ERROR: platform s390x is not available in Docker, please install it" >&2
    exit 1
fi

# Generate KAT on a big-endian architecture
echo ">> Generating KAT on a big-endian architecture"
docker buildx build -f "$DOCKERFILE" --quiet --platform=linux/s390x -t endiannesstest . > /dev/null
docker run -m 4g --rm endiannesstest > "$BUILD_DIR/big_endian.txt"

# Generate KAT on a little-endian architecture
echo ">> Generating KAT on a little-endian architecture"
docker build -f "$DOCKERFILE" --quiet -t endiannesstest . > /dev/null
docker run -m 4g --rm endiannesstest > "$BUILD_DIR/little_endian.txt"

# Get the hashes
hash_be=$(tail -n 1 $BUILD_DIR/big_endian.txt)
hash_le=$(tail -n 1 $BUILD_DIR/little_endian.txt)

# Check that the hashes match
echo ">> Comparing the hashes"
if [[ "$hash_be" == *"sha_512_sum_KATs"* ]] && [[ "$hash_le" == *"sha_512_sum_KATs"* ]]; then
    if [[ "$hash_be" == "$hash_le" ]]; then
        echo ">> OK: big-endian and little-endian hashes match"
    else
        echo ">> ERROR: hashes don't match"
        echo ">> Big-endian hash: $hash_be"
        echo ">> Little-endian hash: $hash_le"
        exit 1
    fi
else
    echo ">> ERROR: KAT hash not found"
    echo ">> Big-endian hash: $hash_be"
    echo ">> Little-endian hash: $hash_le"
    exit 1
fi
