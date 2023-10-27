#include <core/pc1.h>
#include <core/pc2.h>

#include <des.h>

void DES_key_schedule(uint64_t *out, uint64_t in) {
    uint32_t C = DES_PC1_C(in), D = DES_PC1_D(in);
    C = C << 1 | (C & 0x8000000) >> 27;
    D = D << 1 | (D & 0x8000000) >> 27;
    out[0] = DES_PC2(C, D);
    C = C << 1 | (C & 0x8000000) >> 27;
    D = D << 1 | (D & 0x8000000) >> 27;
    out[1] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[2] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[3] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[4] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[5] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[6] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[7] = DES_PC2(C, D);
    C = C << 1 | (C & 0x8000000) >> 27;
    D = D << 1 | (D & 0x8000000) >> 27;
    out[8] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[9] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[10] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[11] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[12] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[13] = DES_PC2(C, D);
    C = C << 2 | (C & 0xC000000) >> 26;
    D = D << 2 | (D & 0xC000000) >> 26;
    out[14] = DES_PC2(C, D);
    C = C << 1 | (C & 0x8000000) >> 27;
    D = D << 1 | (D & 0x8000000) >> 27;
    out[15] = DES_PC2(C, D);
}
