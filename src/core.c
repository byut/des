#include <des/core.h>
#include <des/core/sboxes.h>
#include <des/core/tables.h>

#include <string.h>

static inline void f(uint64_t *out, const uint64_t *in, const uint64_t *keys,
                     const uint8_t *R, size_t n) {
    uint64_t s_in[48];
    memset(out, 0, 32 * sizeof(uint64_t));
    for (size_t i = 0; i < 48; ++i)
        s_in[i] = in[R[DES_E[i]]] ^ keys[DES_K[n][i]];
    s1(s_in[0], s_in[1], s_in[2], s_in[3], s_in[4], s_in[5], &out[DES_P[0]],
       &out[DES_P[1]], &out[DES_P[2]], &out[DES_P[3]]);
    s2(s_in[6], s_in[7], s_in[8], s_in[9], s_in[10], s_in[11], &out[DES_P[4]],
       &out[DES_P[5]], &out[DES_P[6]], &out[DES_P[7]]);
    s3(s_in[12], s_in[13], s_in[14], s_in[15], s_in[16], s_in[17],
       &out[DES_P[8]], &out[DES_P[9]], &out[DES_P[10]], &out[DES_P[11]]);
    s4(s_in[18], s_in[19], s_in[20], s_in[21], s_in[22], s_in[23],
       &out[DES_P[12]], &out[DES_P[13]], &out[DES_P[14]], &out[DES_P[15]]);
    s5(s_in[24], s_in[25], s_in[26], s_in[27], s_in[28], s_in[29],
       &out[DES_P[16]], &out[DES_P[17]], &out[DES_P[18]], &out[DES_P[19]]);
    s6(s_in[30], s_in[31], s_in[32], s_in[33], s_in[34], s_in[35],
       &out[DES_P[20]], &out[DES_P[21]], &out[DES_P[22]], &out[DES_P[23]]);
    s7(s_in[36], s_in[37], s_in[38], s_in[39], s_in[40], s_in[41],
       &out[DES_P[24]], &out[DES_P[25]], &out[DES_P[26]], &out[DES_P[27]]);
    s8(s_in[42], s_in[43], s_in[44], s_in[45], s_in[46], s_in[47],
       &out[DES_P[28]], &out[DES_P[29]], &out[DES_P[30]], &out[DES_P[31]]);
}

void DES_e(uint64_t *out, const uint64_t *in, const uint64_t *keys) {
    uint64_t buf[64], s_out[32];
    const uint8_t *L = DES_IP_L, *R = DES_IP_R, *temp = NULL;
    f(s_out, in, keys, R, 0);
    for (size_t i = 0; i < 32; ++i)
        buf[L[i]] = in[L[i]] ^ s_out[i];
    f(s_out, buf, keys, L, 1);
    for (size_t i = 0; i < 32; ++i)
        buf[R[i]] = in[R[i]] ^ s_out[i];
    for (size_t n = 2; n < 16; ++n) {
        f(s_out, buf, keys, R, n);
        for (size_t i = 0; i < 32; ++i)
            buf[L[i]] ^= s_out[i];
        temp = L, L = R, R = temp;
    }
    for (size_t i = 0; i < 64; ++i)
        out[i] = buf[DES_IIP[i]];
}

void DES_d(uint64_t *out, const uint64_t *in, const uint64_t *keys) {
    uint64_t buf[64], s_out[32];
    const uint8_t *L = DES_IP_L, *R = DES_IP_R, *temp = NULL;
    f(s_out, in, keys, R, 15);
    for (size_t i = 0; i < 32; ++i)
        buf[L[i]] = in[L[i]] ^ s_out[i];
    f(s_out, buf, keys, L, 14);
    for (size_t i = 0; i < 32; ++i)
        buf[R[i]] = in[R[i]] ^ s_out[i];
    for (size_t n = 2; n < 16; ++n) {
        f(s_out, buf, keys, R, 15 - n);
        for (size_t i = 0; i < 32; ++i)
            buf[L[i]] ^= s_out[i];
        temp = L, L = R, R = temp;
    }
    for (size_t i = 0; i < 64; ++i)
        out[i] = buf[DES_IIP[i]];
}
