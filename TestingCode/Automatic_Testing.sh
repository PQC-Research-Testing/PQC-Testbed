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