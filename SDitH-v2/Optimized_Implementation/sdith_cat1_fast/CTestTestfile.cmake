# CMake generated Testfile for 
# Source directory: /home/ryane/PQC-Testbed/SDitH-v2/Optimized_Implementation/sdith_cat1_fast
# Build directory: /home/ryane/PQC-Testbed/SDitH-v2/Optimized_Implementation/sdith_cat1_fast
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(bench_sdith "bench_sdith")
set_tests_properties(bench_sdith PROPERTIES  _BACKTRACE_TRIPLES "/home/ryane/PQC-Testbed/SDitH-v2/Optimized_Implementation/sdith_cat1_fast/CMakeLists.txt;126;add_test;/home/ryane/PQC-Testbed/SDitH-v2/Optimized_Implementation/sdith_cat1_fast/CMakeLists.txt;0;")
subdirs("lib/sha3")
subdirs("lib/aes")
subdirs("generator")
