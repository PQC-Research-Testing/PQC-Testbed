

-------------------------------------------------
PERK: a Digital Signature Scheme
-------------------------------------------------


1. SUBMISSION OVERVIEW
----------------------

Six parameters sets denoted respectively perk-1-fast,
perk-1-short, perk-3-fast, perk-3-short, perk-5-fast, and perk-5-short
are provided as explained in the supporting documentation. Each parameter set
folder is organized as follows:

- build/: Files generated during compilation
- doc/: Technical documentation of the scheme
- lib/: Third party libraries used
- src/: Source code of the scheme
- doxygen.conf: Documentation configuration file
- Makefile: Makefile


2. INSTALLATION INSTRUCTIONS
----------------------------

2.1 Requirements

The following software and libraries are required: make, gcc and gmp (version >= 6.2.1).

2.2 Compilation Step

Let X denotes -1-fast, -1-short, -3-fast, -3-short, -5-fast, or -5-short, depending on the parameter set considered. Let Y denotes aes_aes,
aes_keccak or keccak_keccak depending on the symmetric mode considered. PERK can be compiled in three different ways:
- `cd perkX`
- Execute `make perkX-Y` to compile a working example of the scheme. Run `ulimit -s 16000; ./build/bin/perkX-Y` to
  execute all the steps of the scheme and display theirs respective
  performances.
- Execute `make perkX-Y-kat` to compile the NIST KAT generator. Run `ulimit -s 16000; ./build/bin/perkX-Y-PQCgenKAT_sign` to
  generate KAT files.
- Execute `make perkX-Y-verbose` to compile a working example of the scheme in
  verbose mode. Run `ulimit -s 16000; ./build/bin/perkX-Y-verbose` to generate intermediate values.

3. DOCUMENTATION
----------------

3.1 Requirements

The following software are required: doxygen.

3.2 Generation Step

- Run doxygen doxygen.conf to generate the code documentation
- Browse doc/html/index.html to read the documentation


4. IMPLEMENTATION OVERVIEW
-------------------------

The PERK signature scheme is defined in the `api.h` and `parameters.h` files and implemented in `sign.c`.
The internal API of the scheme is defined in `keygen.h`, `signature.h` and `verify.h` (see also `keygen.c`, `signature.c` and `verify.c`).
The data structures used in this implementation are defined in data_structures.h. The arithmetic operations including operations
on polynomials, vectors and matrices are provided in directory `src/ref`. The `voles.c` and voles.h files contains functions related
the VOLE operations. PERK uses permutations, files `permutation.c` and `permutation.h` provide the implementation of functions related
to the generation and operations over random permutations. The aforementioned functions uses the library _djbsort_ to generate 
permutations and to apply them. The _djbsort_ library is provided in the folder `lib/djbsort`. The files `symmetric.c` and `symmetric.h` provides
functions related to symmetric crypto operations such as randomness generation, hashing and commitments generation. The _XKCP_ library is provided in `lib/XKCP` and
is used to perform symmetric operations. As public key, secret key and signature can be manipulated either with their mathematical representations or as bit strings, the files
`parsing.h` and `parsing.c` provide functions to switch between these two representations.