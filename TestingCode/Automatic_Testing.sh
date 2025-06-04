#!/bin/bash

#Algorithms to re-run
cd ..
cd SNOVA/Optimized_Implementation
make
cd ../..
cd TestingCode
make -f SNOVA_24_4_SSKmake 
make -f SNOVA_24_4_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA_24_4_SSKmake clean
mv SNOVA_24_5_4_SSK Data

make -f SNOVA24_4_SHAKE_ESKmake 
make -f SNOVA24_4_SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_4_SHAKE_ESKmake clean
mv SNOVA_24_5_4_SHAKE_ESK Data

make -f SNOVA24_4_SHAKE_SSKmake 
make -f SNOVA24_4_SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_4_SHAKE_SSKmake clean
mv SNOVA_24_5_4_SHAKE_SSK Data

make -f SNOVA24_4ESKmake 
make -f SNOVA24_4ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_4ESKmake clean
mv SNOVA_24_5_4_ESK Data

make -f SNOVA24_5ESKmake 
make -f SNOVA24_5ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_5ESKmake clean
mv SNOVA_24_5_5_ESK Data

make -f SNOVA24_5SHAKE_ESK
make -f SNOVA24_5SHAKE_ESK bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_5SHAKE_ESK clean
mv SNOVA_24_5_5_SHAKE_ESK Data

make -f SNOVA24_5SHAKE_SSKmake
make -f SNOVA24_5SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_5SHAKE_SSKmake clean
mv SNOVA_24_5_5_SHAKE_SSK Data

make -f SNOVA24_5SSKmake
make -f SNOVA24_5SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_5SSKmake clean
mv SNOVA_24_5_5_SSK Data

make -f SNOVA24_5ESKmake
make -f SNOVA24_5ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA24_5ESKmake clean
mv SNOVA_24_5_5_ESK Data

make -f SNOVA25_3ESKmake
make -f SNOVA25_3ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA25_3ESKmake clean
mv SNOVA_25_8_3_ESK Data

make -f SNOVA25_3SHAKE_ESKmake
make -f SNOVA25_3SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA25_3SHAKE_ESKmake clean
mv SNOVA_25_8_3_SHAKE_ESK Data

make -f SNOVA25_3SHAKE_SSKmake
make -f SNOVA25_3SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA25_3SHAKE_SSKmake clean
mv SNOVA_25_8_3_SHAKE_SSK Data

make -f SNOVA25_3SSKmake
make -f SNOVA25_3SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA25_3SSKmake clean
mv SNOVA_25_8_3_SSK Data

make -f SNOVA29_5ESKmake
make -f SNOVA29_5ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA29_5ESKmake clean
mv SNOVA_29_6_5_ESK Data

make -f SNOVA29_5SHAKE_ESKmake
make -f SNOVA29_5SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA29_5SHAKE_ESKmake clean
mv SNOVA_29_6_5_SHAKE_ESK Data

make -f SNOVA29_5SHAKE_SSKmake
make -f SNOVA29_5SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA29_5SHAKE_SSKmake clean
mv SNOVA_29_6_5_SHAKE_SSK Data

make -f SNOVA29_5SSKmake
make -f SNOVA29_5SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA29_5SSKmake clean
mv SNOVA_29_6_5_SSK Data

make -f SNOVA37_2ESKmake
make -f SNOVA37_2ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_2ESKmake clean
mv SNOVA_37_17_2_ESK Data

make -f SNOVA37_2SHAKE_ESKmake
make -f SNOVA37_2SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_2SHAKE_ESKmake clean
mv SNOVA_37_17_2_SHAKE_ESK Data

make -f SNOVA37_2SHAKE_SSKmake
make -f SNOVA37_2SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_2SHAKE_SSKmake clean
mv SNOVA_37_17_2_SHAKE_SSK Data

make -f SNOVA37_2SSKmake
make -f SNOVA37_2SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_2SSKmake clean
mv SNOVA_37_17_2_SSK Data

make -f SNOVA37_4ESKmake
make -f SNOVA37_4ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_4ESKmake clean
mv SNOVA_37_8_4_ESK Data

make -f SNOVA37_4SHAKE_ESKmake
make -f SNOVA37_4SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_4SHAKE_ESKmake clean
mv SNOVA_37_8_4_SHAKE_ESK Data

make -f SNOVA37_4SHAKE_SSKmake
make -f SNOVA37_4SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_4SHAKE_SSKmake clean
mv SNOVA_37_8_4_SHAKE_SSK Data

make -f SNOVA37_4SSKmake
make -f SNOVA37_4SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA37_4SSKmake clean
mv SNOVA_37_8_4_SSK Data

make -f SNOVA49_3ESKmake
make -f SNOVA49_3ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA49_3ESKmake clean
mv SNOVA_49_11_3_ESK Data

make -f SNOVA49_3SHAKE_ESKmake
make -f SNOVA49_3SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA49_3SHAKE_ESKmake clean
mv SNOVA_49_11_3_SHAKE_ESK Data

make -f SNOVA49_3SHAKE_SSKmake
make -f SNOVA49_3SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA49_3SHAKE_SSKmake clean
mv SNOVA_49_11_3_SHAKE_SSK Data

make -f SNOVA49_3SSKmake
make -f SNOVA49_3SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA49_3SSKmake clean
mv SNOVA_49_11_3_SSK Data

make -f SNOVA56_2ESKmake
make -f SNOVA56_2ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA56_2ESKmake clean
mv SNOVA_56_25_2_ESK Data

make -f SNOVA56_2SHAKE_ESKmake
make -f SNOVA56_2SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA56_2SHAKE_ESKmake clean
mv SNOVA_56_25_2_SHAKE_ESK Data

make -f SNOVA56_2SHAKE_SSKmake
make -f SNOVA56_2SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA56_2SHAKE_SSKmake clean
mv SNOVA_56_25_2_SHAKE_SSK Data

make -f SNOVA56_2SSKmake
make -f SNOVA56_2SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA56_2SSKmake clean
mv SNOVA_56_25_2_SSK Data

make -f SNOVA60_4ESKmake
make -f SNOVA60_4ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA60_4ESKmake clean
mv SNOVA_60_10_4_ESK Data

make -f SNOVA60_4SHAKE_ESKmake
make -f SNOVA60_4SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA60_4SHAKE_ESKmake clean
mv SNOVA_60_10_4_SHAKE_ESK Data

make -f SNOVA60_4SHAKE_SSKmake
make -f SNOVA60_4SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA60_4SHAKE_SSKmake clean
mv SNOVA_60_10_4_SHAKE_SSK Data

make -f SNOVA60_4SSKmake
make -f SNOVA60_4SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA60_4SSKmake clean
mv SNOVA_60_10_4_SSK Data

make -f SNOVA66_3ESKmake
make -f SNOVA66_3ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA66_3ESKmake clean
mv SNOVA_66_15_3_ESK Data

make -f SNOVA66_3SHAKE_ESKmake
make -f SNOVA66_3SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA66_3SHAKE_ESKmake clean
mv SNOVA_66_15_3_SHAKE_ESK Data

make -f SNOVA66_3SHAKE_SSKmake
make -f SNOVA66_3SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA66_3SHAKE_SSKmake clean
mv SNOVA_66_15_3_SHAKE_SSK Data

make -f SNOVA66_3SSKmake
make -f SNOVA66_3SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA66_3SSKmake clean
mv SNOVA_66_15_3_SSK Data

make -f SNOVA75_2ESKmake
make -f SNOVA75_2ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA75_2ESKmake clean
mv SNOVA_75_33_2_ESK Data

make -f SNOVA75_2SHAKE_ESKmake
make -f SNOVA75_2SHAKE_ESKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA75_2SHAKE_ESKmake clean
mv SNOVA_75_33_2_SHAKE_ESK Data

make -f SNOVA75_2SHAKE_SSKmake
make -f SNOVA75_2SHAKE_SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA75_2SHAKE_SSKmake clean
mv SNOVA_75_33_2_SHAKE_SSK Data

make -f SNOVA75_2SSKmake
make -f SNOVA75_2SSKmake bench_snova
for ((i=0; i<1; i++))
do
    ./bench_snova
done
make -f SNOVA75_2SSKmake clean
mv SNOVA_75_33_2_SSK Data
