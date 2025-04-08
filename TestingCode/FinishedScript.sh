#This script contains working commands only, note that the ability to use
#sudo permissions is needed to ensure that files can be moved to the 
#Data directory for easy access.
mkdir Data
#HAWK Implementation Benchmarking
make -f HAWK512make bench-hawk
for ((i=0; i<1000; i++))
do
    ./bench-hawk
done
mv Hawk-512 Data
make -f HAWK512make clean

make -f HAWK1024make bench-hawk
for ((i=0; i<1000; i++))
do
    ./bench-hawk
done
mv Hawk-1024 Data
make -f HAWK1024make clean

#FAEST Implementation
make -f FAEST128fmake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_128f Data
make -f FAEST128fmake clean

make -f FAEST128smake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_128s Data
make -f FAEST128smake clean

make -f FAEST192fmake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_192f Data
make -f FAEST192fmake clean

make -f FAEST192smake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_192s Data
make -f FAEST192smake clean

make -f FAEST256fmake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_256f Data
make -f FAEST256fmake clean

make -f FAEST256smake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_256s Data
make -f FAEST256smake clean

make -f FAESTem128fmake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_em_128f Data
make -f FAEST128fmake clean

make -f FAESTem128smake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_em_128s Data
make -f FAEST128smake clean

make -f FAESTem192fmake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_em_192f Data
make -f FAEST192fmake clean

make -f FAESTem192smake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_em_192s Data
make -f FAEST192smake clean

make -f FAESTem256fmake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_em_256f Data
make -f FAESTem256fmake clean

make -f FAESTem256smake
for ((i=0; i<1000; i++))
do
    ./bench_faest
done
mv faest_em_256s Data
make -f FAESTem256smake clean

#MIRATH Implementation

make -f MIRATH1AF bench_mirath
for ((i=0; i<1000; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH1AF
make -f MIRATH1AF clean

make -f MIRATH1AS bench_mirath
for ((i=0; i<1; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH1AS
make -f MIRATH1AS clean

make -f MIRATH1BF bench_mirath
for ((i=0; i<1000; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH1BF
make -f MIRATH1BF clean

make -f MIRATH1BS bench_mirath
for ((i=0; i<1000; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH1BS
make -f MIRATH1BS clean

make -f MIRATH3AF bench_mirath
for ((i=0; i<1000; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH3AF
make -f MIRATH3AF clean

make -f MIRATH3BF bench_mirath
for ((i=0; i<1000; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH3BF
make -f MIRATH3BF clean

make -f MIRATH5AF bench_mirath
for ((i=0; i<1000; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH5AF
make -f MIRATH5AF clean

make -f MIRATH5BF bench_mirath
for ((i=0; i<1000; i++))
do
    ./bench_mirath
done
mv Mirath Data
mv ./Data/Mirath ./Data/MIRATH5BF
make -f MIRATH5BF clean

#MQOM2 Implementations

make -f MQOMC1gf2Fr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf2-fast-r3 Data
make -f MQOMC1gf2Fr3make clean

make -f MQOMC1gf2Fr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf2-fast-r5 Data
make -f MQOMC1gf2Fr5make clean

make -f MQOMC1gf2Sr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf2-short-r3 Data
make -f MQOMC1gf2Sr3make clean

make -f MQOMC1gf2Sr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf2-short-r5 Data
make -f MQOMC1gf2Sr5make clean

make -f MQOMC1gf256Fr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf256-fast-r3 Data
make -f MQOMC1gf256Fr3make clean

make -f MQOMC1gf256Fr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf256-fast-r5 Data
make -f MQOMC1gf256Fr5make clean

make -f MQOMC1gf256Sr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf256-short-r3 Data
make -f MQOMC1gf256Sr3make clean

make -f MQOMC1gf256Sr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L1-gf256-short-r5 Data
make -f MQOMC1gf256Sr5make clean

#MQOM2 Level 3 Variants
make -f MQOMC3gf2Fr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf2-fast-r3 Data
make -f MQOMC3gf2Fr3make clean

make -f MQOMC3gf2Fr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf2-fast-r5 Data
make -f MQOMC3gf2Fr5make clean

make -f MQOMC3gf2Sr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf2-short-r3 Data
make -f MQOMC3gf2Sr3make clean

make -f MQOMC3gf2Sr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf2-short-r5 Data
make -f MQOMC3gf2Sr5make clean

make -f MQOMC3gf256Fr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf256-fast-r3 Data
make -f MQOMC3gf256Fr3make clean

make -f MQOMC3gf256Fr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf256-fast-r5 Data
make -f MQOMC3gf256Fr5make clean

make -f MQOMC3gf256Sr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf256-short-r3 Data
make -f MQOMC3gf256Sr3make clean

make -f MQOMC3gf256Sr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L3-gf256-short-r5 Data
make -f MQOMC3gf256Sr5make clean

#MQOM2 Level 5 Variants
make -f MQOMC5gf2Fr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf2-fast-r3 Data
make -f MQOMC5gf2Fr3make clean

make -f MQOMC5gf2Fr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf2-fast-r5 Data
make -f MQOMC5gf2Fr5make clean

make -f MQOMC5gf2Sr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf2-short-r3 Data
make -f MQOMC5gf2Sr3make clean

make -f MQOMC5gf2Sr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf2-short-r5 Data
make -f MQOMC5gf2Sr5make clean

make -f MQOMC5gf256Fr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf256-fast-r3 Data
make -f MQOMC5gf256Fr3make clean

make -f MQOMC5gf256Fr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf256-fast-r5 Data
make -f MQOMC5gf256Fr5make clean

make -f MQOMC5gf256Sr5make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf256-short-r5 Data
make -f MQOMC5gf256Sr5make clean

make -f MQOMC5gf256Sr3make mqom-bench
for ((i=0; i<1000; i++))
do
    ./mqom-bench
done
mv  MQOM2-L5-gf256-short-r3 Data
make -f MQOMC5gf256Sr3make clean

#PERK Variants
make -f PERK128F3make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-128-fast-3
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-128-fast-3-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-128-fast-3/PERK Data
mv Data/PERK Data/PERK128F3
make -f PERK128F3make clean

make -f PERK128F5make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-128-fast-5
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-128-fast-5-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-128-fast-5/PERK Data
mv Data/PERK Data/PERK128F5
make -f PERK128F5make clean

make -f PERK192F3make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-192-fast-3
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-192-fast-3-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-192-fast-3/PERK Data
mv Data/PERK Data/PERK192F3
make -f PERK192F5make clean

make -f PERK192F5make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-192-fast-5
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-192-fast-5-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-192-fast-5/PERK Data
mv Data/PERK Data/PERK192F5
make -f PERK192F5make clean

make -f PERK256F5make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-256-fast-5
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-256-fast-5-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-256-fast-5/PERK Data
mv Data/PERK Data/PERK256F5
make -f PERK256F5make clean

make -f PERK256F3make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-256-fast-3
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-256-fast-3-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-256-fast-3/PERK Data
mv Data/PERK Data/PERK256F3
make -f PERK256F3make clean

make -f PERK256S3make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-256-short-3
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-256-short-3-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-256-short-3/PERK Data
mv Data/PERK Data/PERK256S3
make -f PERK256S3make clean

make -f PERK256S5make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-256-short-5
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-256-short-5-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-256-short-5/PERK Data
mv Data/PERK Data/PERK256S5
make -f PERK256S5make clean

make -f PERK192S5make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-192-short-5
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-192-short-5-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-192-short-5/PERK Data
mv Data/PERK Data/PERK192S5
make -f PERK192S5make clean

make -f PERK192S3make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-192-short-3
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-192-short-3-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-192-short-3/PERK Data
mv Data/PERK Data/PERK192S3
make -f PERK192S3make clean

make -f PERK128S3make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-128-short-3
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-128-short-3-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-128-short-3/PERK Data
mv Data/PERK Data/PERK128S3
make -f PERK128S3make clean

make -f PERK128S5make perk-bench
cd ..
cd perk/Optimized_Implementation/perk-128-short-5
for ((i=0; i<1000; i++))
do
    ./build/bin/perk-128-short-5-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../perk/Optimized_Implementation/perk-128-short-5/PERK Data
mv Data/PERK Data/PERK128S5
make -f PERK128S5make clean

#QRUOV Variants

make -f QRUOV1q7L10Vmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q7L10Vmake clean
mv qruov1q7L10v740m100avx2a Data

make -f QRUOV1q7L10Vsmake bench_qruov
for ((i=0; i<1000; i++))
do
    ./bench_qruov
done
make -f QRUOV1q7L10Vsmake clean
mv qruov1q7L10v740m100portable64s Data

make -f QRUOV1q127L3Vmake bench_qruov
for ((i=0; i<1; i++))
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

#RYDE Variants
make -f RYDE1Smake ryde1f-bench
cd ..
cd ryde/Optimized_Implementation/ryde1f
for ((i=0; i<1000; i++))
do
    ./bin/ryde1f-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../ryde/Optimized_Implementation/ryde1f/RYDE-1F Data

make -f RYDE1Smake ryde1s-bench
cd ..
cd ryde/Optimized_Implementation/ryde1s
for ((i=0; i<1000; i++))
do
    ./bin/ryde1s-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../ryde/Optimized_Implementation/ryde1s/RYDE-1S Data

make -f RYDE3Fmake ryde3f-bench
cd ..
cd ryde/Optimized_Implementation/ryde3f
for ((i=0; i<1000; i++))
do
    ./bin/ryde3f-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../ryde/Optimized_Implementation/ryde3f/RYDE-3F Data

make -f RYDE3Smake ryde3s-bench
cd ..
cd ryde/Optimized_Implementation/ryde3s
for ((i=0; i<1000; i++))
do
    ./bin/ryde3s-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../ryde/Optimized_Implementation/ryde3s/RYDE-3S Data

make -f RYDE5Fmake ryde5f-bench
cd ..
cd ryde/Optimized_Implementation/ryde5f
for ((i=0; i<1000; i++))
do
    ./bin/ryde5f-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../ryde/Optimized_Implementation/ryde5f/RYDE-5F Data

make -f RYDE5Smake ryde5s-bench
cd ..
cd ryde/Optimized_Implementation/ryde5s
for ((i=0; i<1000; i++))
do
    ./bin/ryde5s-bench
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../ryde/Optimized_Implementation/ryde5s/RYDE-5S Data

#SNOVA variants
cd ..
cd SNOVA
make
cd ..
cd TestingCode


make -f SNOVA_24_4_SSKmake 
make -f SNOVA_24_4_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA_24_4_SSKmake clean
mv SNOVA_24_5_4_SSK Data

make -f SNOVA24_4_SHAKE_ESKmake 
make -f SNOVA24_4_SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_4_SHAKE_ESKmake clean
mv SNOVA_24_5_4_SHAKE_ESK Data

make -f SNOVA24_4_SHAKE_SSKmake 
make -f SNOVA24_4_SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_4_SHAKE_SSKmake clean
mv SNOVA_24_5_4_SHAKE_SSK Data

make -f SNOVA24_4ESKmake 
make -f SNOVA24_4ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_4ESKmake clean
mv SNOVA_24_5_4 Data

make -f SNOVA24_5ESKmake 
make -f SNOVA24_5ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_5ESKmake clean
mv SNOVA_24_5_5_ESK Data

make -f SNOVA24_5SHAKE_ESK
make -f SNOVA24_5SHAKE_ESK bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_5SHAKE_ESK clean
mv SNOVA_24_5_5_SHAKE_ESK Data

make -f SNOVA24_5SHAKE_SSKmake
make -f SNOVA24_5SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_5SHAKE_SSKmake clean
mv SNOVA_24_5_5_SHAKE_SSK Data

make -f SNOVA24_5SSKmake
make -f SNOVA24_5SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_5SSKmake clean
mv SNOVA_24_5_5_SSK Data

make -f SNOVA24_5ESKmake
make -f SNOVA24_5ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA24_5ESKmake clean
mv SNOVA_24_5_5_ESK Data

make -f SNOVA25_3ESKmake
make -f SNOVA25_3ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA25_3ESKmake clean
mv SNOVA_25_8_3_ESK Data

make -f SNOVA25_3SHAKE_ESKmake
make -f SNOVA25_3SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA25_3SHAKE_ESKmake clean
mv SNOVA_25_8_3_SHAKE_ESK Data

make -f SNOVA25_3SHAKE_SSKmake
make -f SNOVA25_3SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA25_3SHAKE_SSKmake clean
mv SNOVA_25_8_3_SHAKE_SSK Data

make -f SNOVA25_3SSKmake
make -f SNOVA25_3SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA25_3SSKmake clean
mv SNOVA_25_8_3_SSK Data

make -f SNOVA29_5ESKmake
make -f SNOVA29_5ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA29_5ESKmake clean
mv SNOVA_29_6_5_ESK Data

make -f SNOVA29_5SHAKE_ESKmake
make -f SNOVA29_5SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA29_5SHAKE_ESKmake clean
mv SNOVA_29_6_5_SHAKE_ESK Data

make -f SNOVA29_5SHAKE_SSKmake
make -f SNOVA29_5SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA29_5SHAKE_SSKmake clean
mv SNOVA_29_6_5_SHAKE_SSK Data

make -f SNOVA29_5SSKmake
make -f SNOVA29_5SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA29_5SSKmake clean
mv SNOVA_29_6_5_SSK Data

make -f SNOVA37_2SHAKE_ESKmake
make -f SNOVA37_2SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA37_2SHAKE_ESKmake clean
mv SNOVA_37_17_2_SHAKE_ESK Data

make -f SNOVA37_2SHAKE_SSKmake
make -f SNOVA37_2SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA37_2SHAKE_SSKmake clean
mv SNOVA_37_17_2_SHAKE_SSK Data

make -f SNOVA37_2SSKmake
make -f SNOVA37_2SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA37_2SSKmake clean
mv SNOVA_37_17_2_SSK Data

make -f SNOVA37_4ESKmake
make -f SNOVA37_4ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA37_4ESKmake clean
mv SNOVA_37_8_4_ESK Data

make -f SNOVA37_4SHAKE_ESKmake
make -f SNOVA37_4SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA37_4SHAKE_ESKmake clean
mv SNOVA_37_8_4_SHAKE_ESK Data

make -f SNOVA37_4SHAKE_SSKmake
make -f SNOVA37_4SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA37_4SHAKE_SSKmake clean
mv SNOVA_37_8_4_SHAKE_SSK Data

make -f SNOVA37_4SSKmake
make -f SNOVA37_4SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA37_4SSKmake clean
mv SNOVA_37_8_4_SSK Data

make -f SNOVA49_3ESKmake
make -f SNOVA49_3ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA49_3ESKmake clean
mv SNOVA_49_11_3_ESK Data

make -f SNOVA49_3SHAKE_ESKmake
make -f SNOVA49_3SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA49_3SHAKE_ESKmake clean
mv SNOVA_49_11_3_SHAKE_ESK Data

make -f SNOVA49_3SHAKE_SSKmake
make -f SNOVA49_3SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA49_3SHAKE_SSKmake clean
mv SNOVA_49_11_3_SHAKE_SSK Data

make -f SNOVA49_3SSKmake
make -f SNOVA49_3SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA49_3SSKmake clean
mv SNOVA_49_11_3_SSK Data

make -f SNOVA56_2ESKmake
make -f SNOVA56_2ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA56_2ESKmake clean
mv SNOVA_56_25_2_ESK Data

make -f SNOVA56_2SHAKE_ESKmake
make -f SNOVA56_2SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA56_2SHAKE_ESKmake clean
mv SNOVA_56_25_2_SHAKE_ESK Data

make -f SNOVA56_2SHAKE_SSKmake
make -f SNOVA56_2SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA56_2SHAKE_SSKmake clean
mv SNOVA_56_25_2_SHAKE_SSK Data

make -f SNOVA56_2SSKmake
make -f SNOVA56_2SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA56_2SSKmake clean
mv SNOVA_56_25_2_SSK Data

make -f SNOVA60_4ESKmake
make -f SNOVA60_4ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA60_4ESKmake clean
mv SNOVA_60_10_4_ESK Data

make -f SNOVA60_4SHAKE_ESKmake
make -f SNOVA60_4SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA60_4SHAKE_ESKmake clean
mv SNOVA_60_10_4_SHAKE_ESK Data

make -f SNOVA60_4SHAKE_SSKmake
make -f SNOVA60_4SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA60_4SHAKE_SSKmake clean
mv SNOVA_60_10_4_SHAKE_SSK Data

make -f SNOVA60_4SSKmake
make -f SNOVA60_4SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA60_4SSKmake clean
mv SNOVA_60_10_4_SSK Data

make -f SNOVA66_3ESKmake
make -f SNOVA66_3ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA66_3ESKmake clean
mv SNOVA_66_15_3_ESK Data

make -f SNOVA66_3SHAKE_ESKmake
make -f SNOVA66_3SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA66_3SHAKE_ESKmake clean
mv SNOVA_66_15_3_SHAKE_ESK Data

make -f SNOVA66_3SHAKE_SSKmake
make -f SNOVA66_3SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA66_3SHAKE_SSKmake clean
mv SNOVA_66_15_3_SHAKE_SSK Data

make -f SNOVA66_3SSKmake
make -f SNOVA66_3SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA66_3SSKmake clean
mv SNOVA_66_15_3_SSK Data

make -f SNOVA75_2ESKmake
make -f SNOVA75_2ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA75_2ESKmake clean
mv SNOVA_75_33_2_ESK Data

make -f SNOVA75_2SHAKE_ESKmake
make -f SNOVA75_2SHAKE_ESKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA75_2SHAKE_ESKmake clean
mv SNOVA_75_33_2_SHAKE_ESK Data

make -f SNOVA75_2SHAKE_SSKmake
make -f SNOVA75_2SHAKE_SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA75_2SHAKE_SSKmake clean
mv SNOVA_75_33_2_SHAKE_SSK Data

make -f SNOVA75_2SSKmake
make -f SNOVA75_2SSKmake bench_snova
for ((i=0; i<1000; i++))
do
    ./bench_snova
done
make -f SNOVA75_2SSKmake clean
mv SNOVA_75_33_2_SSK Data

#UOV Variants

make -f UOVIIImake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIIImake clean
mv 'OV(256,184,72)-classic' Data

make -f UOVIIIPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIIIPKCmake clean
mv 'OV(256,184,72)-pkc' Data

make -f UOVIIISKCPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIIISKCPKCmake clean
mv 'OV(256,184,72)-pkc-skc' Data

make -f UOVIpmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIpmake clean
mv 'OV(256,112,44)-classic' Data

make -f UOVIpPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIpPKCmake clean
mv 'OV(256,112,44)-pkc' Data

make -f UOVIpSKCPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIpSKCPKCmake clean
mv 'OV(256,112,44)-pkc-skc' Data

make -f UOVIsmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIsmake clean
mv 'OV(16,160,64)-classic' Data

make -f UOVIsPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVIsPKCmake clean
mv 'OV(16,160,64)-pkc' Data

make -f UOVlsSKCPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVlsSKCPKCmake clean
mv 'OV(16,160,64)-pkc-skc' Data

make -f UOVVmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVVmake clean
mv 'OV(256,244,96)-classic' Data

make -f UOVVPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVVPKCmake clean
mv 'OV(256,244,96)-pkc' Data

make -f UOVVSKCPKCmake bench_uov
for ((i=0; i<1000; i++))
do
    ./bench_uov
done
make -f UOVVSKCPKCmake clean
mv 'OV(256,244,96)-pkc-skc' Data

#SQIsign Variants
cd ..
cd SQIsign/
mkdir build
cd build
cmake -DSQISIGN_BUILD_TYPE=opt -DCMAKE_BUILD_TYPE=Release ..

cd apps
make benchmark_lvl1
for ((i=0; i<1000; i++))
do
    ./benchmark_lvl1
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../SQIsign/build/apps/SQIsign_lvl1 Data

cd ..
cd SQIsign/build/apps
make benchmark_lvl3
for ((i=0; i<1000; i++))
do
    ./benchmark_lvl3
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../SQIsign/build/apps/SQIsign_lvl3 Data

cd ..
cd SQIsign/build/apps
make benchmark_lvl5
for ((i=0; i<1000; i++))
do
    ./benchmark_lvl5
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../SQIsign/build/apps/SQIsign_lvl5 Data

rm -r ../SQIsign/build

#SDitH-V2 Variants

cd ..
cd SDitH-v2/Optimized_Implementation/sdith_cat1_fast
cmake CMakeLists.txt
cd generator
make bench
for ((i=0; i<1000; i++))
do
    ./bench
done
make clean
cd ../../../..
cd TestingCode/
sudo mv ../SDitH-v2/Optimized_Implementation/sdith_cat1_fast/generator/SDiTH-CAT1-FAST Data

cd ..
cd SDitH-v2/Optimized_Implementation/sdith_cat1_short
cmake CMakeLists.txt
cd generator
make bench
for ((i=0; i<1000; i++))
do
    ./bench
done
make clean
cd ../../../..
cd TestingCode/
sudo mv ../SDitH-v2/Optimized_Implementation/sdith_cat1_short/generator/SDiTH-CAT1-SHORT Data

cd ..
cd SDitH-v2/Optimized_Implementation/sdith_cat3_short
cmake CMakeLists.txt
cd generator
make bench
for ((i=0; i<1000; i++))
do
    ./bench
done
make clean
cd ../../../..
cd TestingCode/
sudo mv ../SDitH-v2/Optimized_Implementation/sdith_cat3_short/generator/SDiTH-CAT3-SHORT Data

cd ..
cd SDitH-v2/Optimized_Implementation/sdith_cat3_fast
cmake CMakeLists.txt
cd generator
make bench
for ((i=0; i<1000; i++))
do
    ./bench
done
make clean
cd ../../../..
cd TestingCode/
sudo mv ../SDitH-v2/Optimized_Implementation/sdith_cat3_fast/generator/SDiTH-CAT3-FAST Data

cd ..
cd SDitH-v2/Optimized_Implementation/sdith_cat5_fast
cmake CMakeLists.txt
cd generator
make bench
for ((i=0; i<1000; i++))
do
    ./bench
done
make clean
cd ../../../..
cd TestingCode/
sudo mv ../SDitH-v2/Optimized_Implementation/sdith_cat5_fast/generator/SDiTH-CAT5-FAST Data

cd ..
cd SDitH-v2/Optimized_Implementation/sdith_cat5_short
cmake CMakeLists.txt
cd generator
make bench
for ((i=0; i<1000; i++))
do
    ./bench
done
make clean
cd ../../../..
cd TestingCode/
sudo mv ../SDitH-v2/Optimized_Implementation/sdith_cat5_short/generator/SDiTH-CAT5-SHORT Data

#MAYO Variants
cd ..
cd MAYO/Optimized_Implementation
cmake CMakeLists.txt
cd generator
make bench_mayo_1
for ((i=0; i<1000; i++))
do
    ./apps/bench_mayo_1
done
make clean
cd ../..
cd TestingCode/
sudo mv ../MAYO/Optimized_Implementation/MAYO-1 Data

cd ..
cd MAYO/Optimized_Implementation
cmake CMakeLists.txt
cd generator
make bench_mayo_2
for ((i=0; i<1000; i++))
do
    ./apps/bench_mayo_2
done
make clean
cd ../..
cd TestingCode/
sudo mv ../MAYO/Optimized_Implementation/MAYO-2 Data

cd ..
cd MAYO/Optimized_Implementation
cmake CMakeLists.txt
cd generator
make bench_mayo_3
for ((i=0; i<1000; i++))
do
    ./apps/bench_mayo_3
done
make clean
cd ../..
cd TestingCode/
sudo mv ../MAYO/Optimized_Implementation/MAYO-3 Data

cd ..
cd MAYO/Optimized_Implementation
cmake CMakeLists.txt
cd generator
make bench_mayo_5
for ((i=0; i<1000; i++))
do
    ./apps/bench_mayo_5
done
make clean
cd ../..
cd TestingCode/
sudo mv ../MAYO/Optimized_Implementation/MAYO-5 Data


#LESS Variants

cd ..
cd LESS/Optimized_Implementation/avx2
cmake CMakeLists.txt
make bench_LESS_252_192
for ((i=0; i<1000; i++))
do
    ./bench_LESS_252_192
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../LESS/Optimized_Implementation/avx2/LESS Data
mv ./Data/LESS ./Data/LESS_252_192

cd ..
cd LESS/Optimized_Implementation/avx2
cmake CMakeLists.txt
make bench_LESS_252_68
for ((i=0; i<1000; i++))
do
    ./bench_LESS_252_68
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../LESS/Optimized_Implementation/avx2/LESS Data
mv ./Data/LESS ./Data/LESS_252_68

cd ..
cd LESS/Optimized_Implementation/avx2
cmake CMakeLists.txt
make bench_LESS_252_45
for ((i=0; i<1000; i++))
do
    ./bench_LESS_252_45
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../LESS/Optimized_Implementation/avx2/LESS Data
mv ./Data/LESS ./Data/LESS_252_45

cd ..
cd LESS/Optimized_Implementation/avx2
cmake CMakeLists.txt
make bench_LESS_400_220
for ((i=0; i<1000; i++))
do
    ./bench_LESS_400_220
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../LESS/Optimized_Implementation/avx2/LESS Data
mv ./Data/LESS ./Data/LESS_400_220

cd ..
cd LESS/Optimized_Implementation/avx2
cmake CMakeLists.txt
make bench_LESS_400_102
for ((i=0; i<1000; i++))
do
    ./bench_LESS_400_102
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../LESS/Optimized_Implementation/avx2/LESS Data
mv ./Data/LESS ./Data/LESS_400_102

cd ..
cd LESS/Optimized_Implementation/avx2
cmake CMakeLists.txt
make bench_LESS_548_345
for ((i=0; i<1000; i++))
do
    ./bench_LESS_548_345
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../LESS/Optimized_Implementation/avx2/LESS Data
mv ./Data/LESS ./Data/LESS_548_345

cd ..
cd LESS/Optimized_Implementation/avx2
cmake CMakeLists.txt
make bench_LESS_548_137
for ((i=0; i<1000; i++))
do
    ./bench_LESS_548_137
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../LESS/Optimized_Implementation/avx2/LESS Data
mv ./Data/LESS ./Data/LESS_548_137

#CROSS Variants

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_1_RSDP_SIG_SIZE
for ((i=0; i<1; i++))
do
    ./bin/bench_CROSS_1_RSDP_SIG_SIZE
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_1_RSDP_SMALL

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_1_RSDP_BALANCED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_1_RSDP_BALANCED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_1_RSDP_BALANCED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_1_RSDP_SPEED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_1_RSDP_SPEED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_1_RSDP_SPEED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_1_RSDPG_SPEED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_1_RSDPG_SPEED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_1_RSDPG_SPEED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_1_RSDPG_BALANCED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_1_RSDPG_BALANCED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_1_RSDPG_BALANCED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_1_RSDPG_SIG_SIZE
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_1_RSDPG_SIG_SIZE
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_1_RSDPG_SMALL

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_3_RSDPG_SIG_SIZE
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_3_RSDPG_SIG_SIZE
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_3_RSDPG_SMALL

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_3_RSDP_SIG_SIZE
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_3_RSDP_SIG_SIZE
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_3_RSDP_SMALL

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_3_RSDP_BALANCED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_3_RSDP_BALANCED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_3_RSDP_BALANCED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_3_RSDPG_BALANCED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_3_RSDPG_BALANCED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_3_RSDPG_BALANCED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_3_RSDPG_SPEED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_3_RSDPG_SPEED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_3_RSDPG_FAST

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_3_RSDP_SPEED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_3_RSDP_SPEED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_3_RSDP_FAST

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_5_RSDP_SPEED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_5_RSDP_SPEED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_5_RSDP_FAST

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_5_RSDPG_SPEED
for ((i=0; i<1; i++))
do
    ./bin/bench_CROSS_5_RSDPG_SPEED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_5_RSDPG_FAST

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_5_RSDPG_BALANCED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_5_RSDPG_BALANCED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_5_RSDPG_BALANCED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_5_RSDP_BALANCED
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_5_RSDP_BALANCED
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_5_RSDP_BALANCED

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_5_RSDP_SIG_SIZE
for ((i=0; i<1; i++))
do
    ./bin/bench_CROSS_5_RSDP_SIG_SIZE
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_5_RSDP_SMALL

cd ..
cd CROSS/Additional_Implementations/Benchmarking
cmake CMakeLists.txt
make bench_CROSS_5_RSDPG_SIG_SIZE
for ((i=0; i<1000; i++))
do
    ./bin/bench_CROSS_5_RSDPG_SIG_SIZE
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../CROSS/Additional_Implementations/Benchmarking/CROSS Data
mv ./Data/CROSS ./Data/CROSS_5_RSDPG_SMALL
