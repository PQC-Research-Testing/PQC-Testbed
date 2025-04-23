This repository contains code for the measuring the performance of the fourteen algorithms and their variants submitted to NIST's Post-Quantum Cryptography: Additional Digital Signature Schemes Round 2. Each of the algorithms and their variants are tested using a near-identical benchmarking executable. The executable measures the following metrics:
    -Runtime
    -CPU Cycles
    -Peak Resident Set Size usage (RAM)

Benchmarking can be done automatically using the 'FinishedScript.sh' bash file. The script will execute every algorithm and their variants one-thousand times, storing the results of each run in a .CVS file for each variant in a 'Data' directory. 

Requirements for Code:
    -build-essentials
    -OpenSSL (Version 3.0 or later)
    -CMake (Version 3.13 or later)
    -Make (Version 4.4 or later)
    -GMP (Version 6.0.0 or later)
    -GCC (or any C11-compatiable compiler)

