#include <des/core.h>
#include <des/core/common.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct benchmark_st {
    double elapsed_time;
    double mbps;
};

static struct benchmark_st benchmark(uint64_t *out, const uint64_t *in,
                                     const uint64_t *keys, size_t size,
                                     size_t rounds) {
    struct benchmark_st b = {0, 0};
    clock_t start_time;
    double elapsed_time;
    for (size_t n = 0, bsize = 2046 * size; n < rounds; ++n) {
        start_time = clock();
        for (size_t i = 0; i < bsize; ++i)
            DES_e(out, in, keys);
        elapsed_time = (double)(clock() - start_time);
        b.mbps += size * CLOCKS_PER_SEC / elapsed_time;
        b.elapsed_time += elapsed_time;
    }
    b.mbps /= rounds;
    return b;
}

static uint64_t *randu64arr() {
    uint64_t *arr = (uint64_t *)malloc(64 * sizeof(uint64_t));
    for (size_t i = 0; i < 64; ++i)
        for (size_t j = 0; j < 64; ++j)
            arr[i] = arr[i] * 2 + rand() % 2;
    return arr;
}

int main(int argc, char *argv[]) {
    UNUSED(argc), UNUSED(argv);

    srand(time(0));

    uint64_t *in = randu64arr(), *keys = randu64arr();
    uint64_t in_T[64], keys_T[64];
    DES_transpose(in_T, in), free(in), in = NULL;
    DES_transpose(keys_T, keys), free(keys), keys = NULL;

    int n = 10;
    struct benchmark_st b;
    double mbps = 0;
    size_t i = 1;
    for (size_t s = 1; s <= 512; ++i, s *= 2) {
        printf("-- Benchmark Test #%zu (%zuM) ... ", i, s), fflush(stdout);
        b = benchmark(in_T, in_T, keys_T, s, n), mbps += b.mbps;
        printf("%f s / %f s / %f MBps\n", b.elapsed_time / CLOCKS_PER_SEC,
               b.elapsed_time / (n * CLOCKS_PER_SEC), b.mbps);
    }

    printf("--\n");
    printf("-- Average Encryption Speed Estimate -> %f MBps\n", mbps / (i - 1));

    return 0;
}
