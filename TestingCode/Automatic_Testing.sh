cd ..
cd SQIsign/
mkdir build
cd build
cmake -DSQISIGN_BUILD_TYPE=opt -DCMAKE_BUILD_TYPE=Release ..

cd apps
make benchmark_lvl1
for ((i=0; i<2; i++))
do
    ./benchmark_lvl1
done
make clean
cd ../../..
cd TestingCode/
sudo mv ../SQIsign/build/apps/SQIsign_lvl1 Data