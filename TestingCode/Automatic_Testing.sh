#!/bin/bash

#Algorithms to re-run
make -f Dilithium2AESmake bench-dilithium
for ((i=0; i<2; i++))
do
    ./bench-dilithium
done
sudo mv Dilithium2-AES Data
make -f Dilithium2AESmake clean

: '
make -f Dilithium2AESmake bench-dilithium
for ((i=0; i<2; i++))
do
    ./bench-dilithium
done
sudo mv Dilithium2-AES Data
make -f Dilithium2AESmake clean

make -f Dilithium3AESmake bench-dilithium
for ((i=0; i<2; i++))
do
    ./bench-dilithium
done
sudo mv Dilithium3-AES Data
make -f Dilithium3AESmake clean

make -f Dilithium5AESmake bench-dilithium
for ((i=0; i<2; i++))
do
    ./bench-dilithium
done
sudo mv Dilithium5-AES Data
make -f Dilithium5AESmake clean

make -f Dilithium2make bench-dilithium
for ((i=0; i<2; i++))
do
    ./bench-dilithium
done
sudo mv Dilithium2 Data
make -f Dilithium2make clean

make -f Dilithium3make bench-dilithium
for ((i=0; i<2; i++))
do
    ./bench-dilithium
done
sudo mv Dilithium3 Data
make -f Dilithium3make clean

make -f Dilithium5make bench-dilithium
for ((i=0; i<2; i++))
do
    ./bench-dilithium
done
sudo mv Dilithium5 Data
make -f Dilithium5make clean



'