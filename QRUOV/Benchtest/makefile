
.PHONY: ryde1f-bench
qruov_config.h: ../src/avx2/qruov_config_h_gen.c
	${CC} @qruov_config.txt -DQRUOV_PLATFORM=${PLATFORM} -DQRUOV_CONFIG_H_GEN ${CFLAGS} ${LDFLAGS} ../src/avx2/qruov_config_h_gen.c
	./a.out > qruov_config.h
	rm a.out
api.h: ../src/avx2/api_h_gen.c
	${CC} -DAPI_H_GEN ${CFLAGS} ${LDFLAGS} ../src/avx2/api_h_gen.c
	./a.out > api.h
	rm a.out
ryde1f-bench: benchtest.c ../src/avx2/qruov.c ../src/avx2/rng.c ../src/avx2/sign.c ../src/avx2/api.h ../src/avx2/rng.h
	gcc -o test benchtest.c ../src/avx2/qruov.c ../src/avx2/rng.c ../src/avx2/sign.c ../src/avx2/rng.h


