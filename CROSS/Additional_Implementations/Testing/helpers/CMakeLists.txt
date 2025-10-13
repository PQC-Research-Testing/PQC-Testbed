cmake_minimum_required(VERSION 3.7)

project(CROSS C)
set(CMAKE_C_STANDARD 11)

################################################################################
############################### TEST PARAMETERS ################################
################################################################################

set(CC ${CMAKE_C_COMPILER})

set(STANDALONE_KECCAK 1)
set(SKIP_ASSERT "-DSKIP_ASSERT=1")

message(">> Variant: CROSS " ${CROSS_PROBLEM} " " ${CROSS_CATEGORY} " " ${CROSS_TARGET} " " (${CROSS_IMPLEMENTATION}))
message(">> Options: " STANDALONE_KECCAK=${STANDALONE_KECCAK} " " ${SKIP_ASSERT})
message(">> Compile: " ${CC} " " ${CMAKE_C_FLAGS})

if(CROSS_IMPLEMENTATION STREQUAL "reference")
    set(REFERENCE 1)
endif()

if(CROSS_TARGET STREQUAL "balanced")
    set(CROSS_TARGET "BALANCED")
endif()

if(CROSS_TARGET STREQUAL "small")
    set(CROSS_TARGET "SIG_SIZE")
endif()

if(CROSS_TARGET STREQUAL "fast")
    set(CROSS_TARGET "SPEED")
    set(OMIT_SEED_TREE "-DNO_TREES=1")
else()
    set(OMIT_SEED_TREE "")
endif()

################################################################################
############################## COMPILATION UNITS ###############################
################################################################################


set(REFERENCE_CODE_DIR ../../../../Reference_Implementation)
set(OPTIMIZED_CODE_DIR ../../../../Optimized_Implementation)
set(TEST_DIR ../../../Testing)

if(REFERENCE EQUAL 1)
set(BASE_DIR ${REFERENCE_CODE_DIR})
set(SPEC_HEADERS
        ${BASE_DIR}/include/sha3.h
        ${BASE_DIR}/include/csprng_hash.h
        ${BASE_DIR}/include/restr_arith.h
        ${BASE_DIR}/include/fp_arith.h )
set(SPEC_SOURCES
        ${BASE_DIR}/lib/merkle.c
        ${BASE_DIR}/lib/seedtree.c
        ${BASE_DIR}/lib/CROSS.c
)
else()
set(BASE_DIR ${OPTIMIZED_CODE_DIR})
set(SPEC_HEADERS
        ${BASE_DIR}/include/align.h
        ${BASE_DIR}/include/fips202x4.h
        ${BASE_DIR}/include/KeccakP-1600-times4-SnP.h
        ${BASE_DIR}/include/SIMD256-config.h
        ${BASE_DIR}/include/sha3.h
        ${BASE_DIR}/include/csprng_hash.h
        ${BASE_DIR}/include/architecture_detect.h
        ${BASE_DIR}/include/restr_arith.h
        ${BASE_DIR}/include/fp_arith.h )
set(SPEC_SOURCES
        ${BASE_DIR}/lib/fips202x4.c
        ${BASE_DIR}/lib/KeccakP-1600-times4-SIMD256.c
        ${BASE_DIR}/lib/merkle.c
        ${BASE_DIR}/lib/seedtree.c
        ${BASE_DIR}/lib/CROSS.c
)
endif()

set(COMMON_DIR ${REFERENCE_CODE_DIR})
set(HEADERS
    ${SPEC_HEADERS}
    ${COMMON_DIR}/include/api.h
    ${COMMON_DIR}/include/CROSS.h
    ${COMMON_DIR}/include/pack_unpack.h
    ${COMMON_DIR}/include/fips202.h
    ${COMMON_DIR}/include/keccakf1600.h
    ${COMMON_DIR}/include/parameters.h
    ${COMMON_DIR}/include/seedtree.h
    ${COMMON_DIR}/include/merkle_tree.h
    ${TEST_DIR}/helpers/test_helpers.h
)

if(STANDALONE_KECCAK)
  set(KECCAK_EXTERNAL_LIB "")
  set(KECCAK_EXTERNAL_ENABLE "")
  list(APPEND FALLBACK_SOURCES ${COMMON_DIR}/lib/keccakf1600.c)
  list(APPEND FALLBACK_SOURCES ${COMMON_DIR}/lib/fips202.c)
else()
  set(KECCAK_EXTERNAL_LIB keccak)
  set(KECCAK_EXTERNAL_ENABLE "-DSHA_3_LIBKECCAK")
endif()

set(SOURCES
    ${SPEC_SOURCES}
    ${FALLBACK_SOURCES}
    ${COMMON_DIR}/lib/csprng_hash.c
    ${COMMON_DIR}/lib/pack_unpack.c
    ${COMMON_DIR}/lib/keccakf1600.c
    ${COMMON_DIR}/lib/fips202.c
    ${COMMON_DIR}/lib/sign.c
)

################################################################################
################################ OUTPUT BINARY #################################
################################################################################

set(TARGET_BINARY_NAME test.o)
add_executable(${TARGET_BINARY_NAME} ${HEADERS} ${SOURCES} ../test.c)
target_include_directories(${TARGET_BINARY_NAME} PRIVATE
                        ${BASE_DIR}/include
                        ${COMMON_DIR}/include
                        ${TEST_DIR}/helpers
                        ../include)
target_link_libraries(${TARGET_BINARY_NAME} m ssl crypto ${KECCAK_EXTERNAL_LIB})
set_target_properties(${TARGET_BINARY_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./bin)
set_property(TARGET ${TARGET_BINARY_NAME} APPEND PROPERTY
    COMPILE_FLAGS "${OMIT_SEED_TREE} ${SKIP_ASSERT} -DCATEGORY_${CROSS_CATEGORY}=1 -D${CROSS_TARGET}=1 -D${CROSS_PROBLEM}=1 ${KECCAK_EXTERNAL_ENABLE} ")


