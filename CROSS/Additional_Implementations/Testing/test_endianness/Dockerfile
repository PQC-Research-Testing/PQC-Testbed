# Build and run:
# docker build -t cross-test-endianness -f ./Additional_Implementations/Testing/test_endianness/Dockerfile .
# docker run --rm cross-test-endianness

FROM ubuntu:latest

ENV DEBIAN_FRONTEND noninteractive

# Get all packages
RUN apt update
RUN apt install -y git cmake libssl-dev

# Copy CROSS source code inside the container
WORKDIR /testdir
COPY . /testdir

STOPSIGNAL SIGTERM

ENTRYPOINT \
    # Build CROSS
    cd /testdir/Additional_Implementations/KAT_Generation && \
    rm -rf build && \
    mkdir build && \ 
    cd build  && \ 
    cmake ../ -DCMAKE_RULE_MESSAGES=OFF && \ 
    make -s -j$(nproc) && \ 
    cd .. && \ 
    rm -rf ../../KAT/* && \ 
    # Generate KAT
    ./gen_all_kat.sh && \
    cd ../../KAT && \ 
    sha512sum * > sha_512_sum_KATs && \ 
    cat sha_512_sum_KATs && \ 
    # Single hash for all KAT
    sha256sum sha_512_sum_KATs