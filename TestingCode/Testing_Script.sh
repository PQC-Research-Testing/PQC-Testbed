#!/bin/bash
cd ..
##SQIsign Testing Section
cd SQIsign/
mkdir -p build
cd build
cmake -DSQISIGN_BUILD_TYPE=ref ..
make
make test