#include <des/core/utils.h>
#include <string.h>

void DES_transpose(uint64_t *out, const uint64_t *in) {
    memset(out, 0, 64 * sizeof(uint64_t));
    for (size_t i = 0; i < 64; ++i)
        for (size_t j = 0; j < 64; ++j)
            out[i] |= ((in[j] << i) & 0x8000000000000000) >> j;
}
