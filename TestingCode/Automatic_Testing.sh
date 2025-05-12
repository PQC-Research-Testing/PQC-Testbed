#!/bin/bash

#Algorithms to re-run
cd ../QRUOV/Optimized_Implementation/
make clean
cd ../../TestingCode
cd ../QRUOV/Optimized_Implementation/
make
cd ../../TestingCode

make -f QRUOV1q7L10Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q7L10Vmake clean
mv qruov1q7L10v740m100portable64a Data


make -f QRUOV1q7L10Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q7L10Vsmake clean
mv qruov1q7L10v740m100portable64s Data

make -f QRUOV1q127L3Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q127L3Vmake clean
mv qruov1q127L3v156m54portable64a Data

make -f QRUOV1q31L3Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q31L3Vsmake clean
mv qruov1q31L3v165m60portable64s Data

make -f QRUOV1q31L3Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q31L3Vmake clean
mv qruov1q31L3v165m60portable64a Data

make -f QRUOV1q127L3Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q127L3Vsmake clean
mv qruov1q127L3v156m54portable64s Data

make -f QRUOV1q31L10Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q31L10Vsmake clean
mv qruov1q31L10v600m70portable64s Data

make -f QRUOV1q31L10Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q31L10Vmake clean
mv qruov1q31L10v600m70portable64a Data

make -f QRUOV3q31L10Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q31L10Vsmake clean
mv qruov3q31L10v890m100portable64s Data

make -f QRUOV3q31L10Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q31L10Vmake clean
mv qruov3q31L10v890m100portable64a Data

make -f QRUOV5q31L10Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q31L10Vsmake clean
mv qruov5q31L10v1120m120portable64s Data

make -f QRUOV3q31L3Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q31L3Vmake clean
mv qruov3q31L3v246m87portable64a Data

make -f QRUOV3q31L3Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q31L3Vsmake clean
mv qruov3q31L3v246m87portable64s Data

make -f QRUOV3q127L3Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q127L3Vmake clean
mv qruov3q127L3v228m78portable64a Data

make -f QRUOV3q127L3Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q127L3Vsmake clean
mv qruov3q127L3v228m78portable64s Data

make -f QRUOV3q7L10Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q7L10Vmake clean
mv qruov3q7L10v1100m140portable64a Data

make -f QRUOV3q7L10Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV3q7L10Vsmake clean
mv qruov3q7L10v1100m140portable64s Data

make -f QRUOV5q7L10Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q7L10Vmake clean
mv qruov5q7L10v1490m190portable64a Data

make -f QRUOV5q7L10Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q7L10Vsmake clean
mv qruov5q7L10v1490m190portable64s Data

make -f QRUOV5q31L3Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q31L3Vsmake clean
mv qruov5q31L3v324m114portable64s Data

make -f QRUOV5q31L3Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q31L3Vmake clean
mv qruov5q31L3v324m114portable64a Data

make -f QRUOV5q31L10Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q31L10Vmake clean
mv qruov5q31L10v1120m120portable64a Data

make -f QRUOV5q127L3Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q127L3Vmake clean
mv qruov5q127L3v306m105portable64a Data

make -f QRUOV5q127L3Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV5q127L3Vsmake clean
mv qruov5q127L3v306m105portable64s Data

cd ../QRUOV/Optimized_Implementation/
make clean
cd ../../TestingCode
