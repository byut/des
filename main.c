#include <des/core.h>
#include <des/core/common.h>

#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FPRINTM_N 8

static uint64_t buffer[DES_DSIZE] = {0};
static uint64_t data[DES_DSIZE] = {0};
static uint64_t keys[DES_DSIZE] = {0};
static uint64_t cipher[DES_DSIZE] = {0};

static void fprintm(FILE *stream, const uint64_t *matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) {
        fprintf(stream, "0x%016" PRIx64 " ", matrix[i]);
        if ((i + 1) % m == 0)
            fprintf(stream, "\n");
    }
}

int main(int argc, char *argv[]) {
    UNUSED(argc), UNUSED(argv);
    srand(time(0));

    for (size_t i = 0; i < DES_DSIZE; ++i)
        buffer[i] = RANDU64();

    fprintf(stdout, "Data:\n");
    fprintm(stdout, buffer, DES_DSIZE, FPRINTM_N);
    fprintf(stdout, "\n");

    DES_transpose(data, buffer);

    for (size_t i = 0; i < DES_DSIZE; ++i)
        buffer[i] = RANDU64();

    fprintf(stdout, "Keys:\n");
    fprintm(stdout, buffer, DES_DSIZE, FPRINTM_N);
    fprintf(stdout, "\n");

    DES_transpose(keys, buffer);

    DES_e(cipher, data, keys);

    DES_transpose(buffer, cipher);
    fprintf(stdout, "Cipher:\n");
    fprintm(stdout, buffer, DES_DSIZE, FPRINTM_N);
    fprintf(stdout, "\n");

    for (size_t i = 0; i < DES_DSIZE; ++i)
        data[i] = 0;
    DES_d(data, cipher, keys);

    DES_transpose(buffer, data);
    fprintf(stdout, "Data (decrypted):\n");
    fprintm(stdout, buffer, DES_DSIZE, FPRINTM_N);

    return 0;
}
