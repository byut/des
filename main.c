#include <des/core.h>
#include <des/core/common.h>

#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define FPRINTM_N     8

static const char *out_filename = "out.log";
static FILE       *out          = NULL;

static clock_t start, end;
static clock_t current, total;

static uint64_t buffer[DES_DSIZE] = {0};
static uint64_t data[DES_DSIZE]   = {0};
static uint64_t keys[DES_DSIZE]   = {0};
static uint64_t cipher[DES_DSIZE] = {0};

static void fprintm(FILE *stream, const uint64_t *matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) {
        fprintf(stream, "0x%016" PRIx64 " ", matrix[i]);
        if ((i + 1) % m == 0) fprintf(stream, "\n");
    }
}

int main(int argc, char *argv[]) {
    UNUSED(argc), UNUSED(argv);

    out = fopen(out_filename, "w");
    if (!out) {
        fprintf(stderr, "-- Failed opening the log file\n");
        return 1;
    } else
        fprintf(stdout, "-- Log file created/opened successfully (%s)\n",
                out_filename);

    srand(time(0));

    fprintf(stdout, "-- Generating data        ... ");

    start = clock();

    for (size_t i = 0; i < DES_DSIZE; ++i) {
        buffer[i] = RANDU64();
    }

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Data:\n");
    fprintm(out, buffer, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "-- Transposing data       ... ");

    start = clock();

    DES_transpose(data, buffer);

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Data (transposed):\n");
    fprintm(out, data, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "-- Generating random keys ... ");

    start = clock();

    for (size_t i = 0; i < DES_DSIZE; ++i) {
        buffer[i] = RANDU64();
    }

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Keys:\n");
    fprintm(out, buffer, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "-- Transposing keys       ... ");

    start = clock();

    DES_transpose(keys, buffer);

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Keys (transposed):\n");
    fprintm(out, keys, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "-- Encrypting data        ... ");

    start = clock();

    DES_e(cipher, data, keys);

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Cipher:\n");
    fprintm(out, cipher, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "-- Transposing cipher     ... ");

    start = clock();

    DES_transpose(buffer, cipher);

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Cipher (transposed):\n");
    fprintm(out, buffer, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "-- Decrypting cipher      ... ");

    start = clock();

    DES_d(data, cipher, keys);

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Data (decrypted):\n");
    fprintm(out, data, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "-- Transposing data       ... ");

    start = clock();

    DES_transpose(buffer, data);

    end     = clock();
    current = end - start;
    total += current;

    fprintf(stdout, "%fms\n", ((double)current / CLOCKS_PER_MS));

    fprintf(out, "Data (decrypted + transposed):\n");
    fprintm(out, buffer, DES_DSIZE, FPRINTM_N);
    fprintf(out, "\n");

    fprintf(stdout, "\n");
    fprintf(stdout, "-- Done in %fms\n", ((double)total / CLOCKS_PER_MS));

    return 0;
}
