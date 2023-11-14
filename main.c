#include <des/core.h>
#include <des/core/utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNUSED(x) (void)(x)

static uint64_t *randu64arr() {
    uint64_t *arr = (uint64_t *)malloc(64 * sizeof(uint64_t));
    for (size_t i = 0; i < 64; ++i)
        for (size_t j = 0; j < 64; ++j)
            arr[i] = arr[i] * 2 + rand() % 2;
    return arr;
}

static void printT(const uint64_t *matrix_T, size_t coln) {
    for (size_t i = 0; i < 64; ++i) {
        printf("0x");
        uint8_t byte = 0;
        for (size_t j = 0, size = 0; j < 64; ++j) {
            byte |= ((((matrix_T[j] << i) & 0x8000000000000000) >> j) != 0)
                    << (7 - size++);
            if (size % 8 == 0) {
                printf("%02x", byte);
                size = 0, byte = 0;
            }
        }
        printf((i + 1) % coln == 0 || i == 63 ? "\n" : " ");
    }
}

int main(int argc, char *argv[]) {
    UNUSED(argc), UNUSED(argv);

    srand(time(0));

    uint64_t *in = randu64arr(), in_T[64];
    DES_transpose(in_T, in), free(in), in = NULL;
    printf("Input:\n"), fflush(stdout);
    printT(in_T, 5);
    printf("\n");

    uint64_t *keys = randu64arr(), keys_T[64];
    DES_transpose(keys_T, keys), free(keys), keys = NULL;
    printf("Keys:\n");
    printT(keys_T, 5);
    printf("\n");

    uint64_t cipher_T[64];
    DES_e(cipher_T, in_T, keys_T);
    printf("Ciphertext:\n");
    printT(cipher_T, 5);
    printf("\n");

    uint64_t plain_T[64];
    DES_d(plain_T, cipher_T, keys_T);
    printf("Plaintext:\n");
    printT(plain_T, 5);

    return 0;
}
