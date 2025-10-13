#!/bin/bash

#UPDATED ALGORITHMS:
#HAWK
#MQOM
#FALCON
#SPHINCS+
#CROSS
#perk
#SQIsign
#MIRATH
#LESS
#Dilithium
#Algorithms to re-run
cd ../ryde/Optimized_Implementation/ryde5s
rm -rf build
cmake -DCMAKE_BUILD_TYPE=Release -DOPT_IMPL=avx -B build
cmake --build build
cd build/bench
for ((i=0; i<1; i++))
do
    ./bench-ryde-5s
done
sudo mv RYDE-5S ../../../../../TestingCode/Data
cd ../..
rm -r build
cd ../../../TestingCode