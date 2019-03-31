#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16

typedef uint8_t block[BLOCK_SIZE];

static const unsigned char PI[256] = {
    0xfc, 0xee, 0xdd, 0x11, 0xcf, 0x6e, 0x31, 0x16, 0xfb, 0xc4, 0xfa, 0xda, 0x23, 0xc5, 0x04, 0x4d,
    0xe9, 0x77, 0xf0, 0xdb, 0x93, 0x2e, 0x99, 0xba, 0x17, 0x36, 0xf1, 0xbb, 0x14, 0xcd, 0x5f, 0xc1,
    0xf9, 0x18, 0x65, 0x5a, 0xe2, 0x5c, 0xef, 0x21, 0x81, 0x1c, 0x3c, 0x42, 0x8b, 0x01, 0x8e, 0x4f,
    0x05, 0x84, 0x02, 0xae, 0xe3, 0x6a, 0x8f, 0xa0, 0x06, 0x0b, 0xed, 0x98, 0x7f, 0xd4, 0xd3, 0x1f,
    0xeb, 0x34, 0x2c, 0x51, 0xea, 0xc8, 0x48, 0xab, 0xf2, 0x2a, 0x68, 0xa2, 0xfd, 0x3a, 0xce, 0xcc,
    0xb5, 0x70, 0x0e, 0x56, 0x08, 0x0c, 0x76, 0x12, 0xbf, 0x72, 0x13, 0x47, 0x9c, 0xb7, 0x5d, 0x87,
    0x15, 0xa1, 0x96, 0x29, 0x10, 0x7b, 0x9a, 0xc7, 0xf3, 0x91, 0x78, 0x6f, 0x9d, 0x9e, 0xb2, 0xb1,
    0x32, 0x75, 0x19, 0x3d, 0xff, 0x35, 0x8a, 0x7e, 0x6d, 0x54, 0xc6, 0x80, 0xc3, 0xbd, 0x0d, 0x57,
    0xdf, 0xf5, 0x24, 0xa9, 0x3e, 0xa8, 0x43, 0xc9, 0xd7, 0x79, 0xd6, 0xf6, 0x7c, 0x22, 0xb9, 0x03,
    0xe0, 0x0f, 0xec, 0xde, 0x7a, 0x94, 0xb0, 0xbc, 0xdc, 0xe8, 0x28, 0x50, 0x4e, 0x33, 0x0a, 0x4a,
    0xa7, 0x97, 0x60, 0x73, 0x1e, 0x00, 0x62, 0x44, 0x1a, 0xb8, 0x38, 0x82, 0x64, 0x9f, 0x26, 0x41,
    0xad, 0x45, 0x46, 0x92, 0x27, 0x5e, 0x55, 0x2f, 0x8c, 0xa3, 0xa5, 0x7d, 0x69, 0xd5, 0x95, 0x3b,
    0x07, 0x58, 0xb3, 0x40, 0x86, 0xac, 0x1d, 0xf7, 0x30, 0x37, 0x6b, 0xe4, 0x88, 0xd9, 0xe7, 0x89,
    0xe1, 0x1b, 0x83, 0x49, 0x4c, 0x3f, 0xf8, 0xfe, 0x8d, 0x53, 0xaa, 0x90, 0xca, 0xd8, 0x85, 0x61,
    0x20, 0x71, 0x67, 0xa4, 0x2d, 0x2b, 0x09, 0x5b, 0xcb, 0x9b, 0x25, 0xd0, 0xbe, 0xe5, 0x6c, 0x52,
    0x59, 0xa6, 0x74, 0xd2, 0xe6, 0xf4, 0xb4, 0xc0, 0xd1, 0x66, 0xaf, 0xc2, 0x39, 0x4b, 0x63, 0xb6
};

static const unsigned char PI_INV[256] = {
    0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91,
    0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18, 0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F,
    0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4, 0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,
    0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9, 0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5,
    0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B, 0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F,
    0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F, 0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,
    0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2, 0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B,
    0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11, 0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C,
    0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F, 0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,
    0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1, 0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD,
    0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0, 0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA,
    0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D, 0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,
    0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67, 0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04,
    0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88, 0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80,
    0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,
    0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7, 0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74
};

static const unsigned char C[32][BLOCK_SIZE] = {
    { 0x01, 0x94, 0x84, 0xdd, 0x10, 0xbd, 0x27, 0x5d, 0xb8, 0x7a, 0x48, 0x6c, 0x72, 0x76, 0xa2, 0x6e },
    { 0x02, 0xeb, 0xcb, 0x79, 0x20, 0xb9, 0x4e, 0xba, 0xb3, 0xf4, 0x90, 0xd8, 0xe4, 0xec, 0x87, 0xdc },
    { 0x03, 0x7f, 0x4f, 0xa4, 0x30, 0x04, 0x69, 0xe7, 0x0b, 0x8e, 0xd8, 0xb4, 0x96, 0x9a, 0x25, 0xb2 },
    { 0x04, 0x15, 0x55, 0xf2, 0x40, 0xb1, 0x9c, 0xb7, 0xa5, 0x2b, 0xe3, 0x73, 0x0b, 0x1b, 0xcd, 0x7b },
    { 0x05, 0x81, 0xd1, 0x2f, 0x50, 0x0c, 0xbb, 0xea, 0x1d, 0x51, 0xab, 0x1f, 0x79, 0x6d, 0x6f, 0x15 },
    { 0x06, 0xfe, 0x9e, 0x8b, 0x60, 0x08, 0xd2, 0x0d, 0x16, 0xdf, 0x73, 0xab, 0xef, 0xf7, 0x4a, 0xa7 },
    { 0x07, 0x6a, 0x1a, 0x56, 0x70, 0xb5, 0xf5, 0x50, 0xae, 0xa5, 0x3b, 0xc7, 0x9d, 0x81, 0xe8, 0xc9 },
    { 0x08, 0x2a, 0xaa, 0x27, 0x80, 0xa1, 0xfb, 0xad, 0x89, 0x56, 0x05, 0xe6, 0x16, 0x36, 0x59, 0xf6 },
    { 0x09, 0xbe, 0x2e, 0xfa, 0x90, 0x1c, 0xdc, 0xf0, 0x31, 0x2c, 0x4d, 0x8a, 0x64, 0x40, 0xfb, 0x98 },
    { 0x0a, 0xc1, 0x61, 0x5e, 0xa0, 0x18, 0xb5, 0x17, 0x3a, 0xa2, 0x95, 0x3e, 0xf2, 0xda, 0xde, 0x2a },
    { 0x0b, 0x55, 0xe5, 0x83, 0xb0, 0xa5, 0x92, 0x4a, 0x82, 0xd8, 0xdd, 0x52, 0x80, 0xac, 0x7c, 0x44 },
    { 0x0c, 0x3f, 0xff, 0xd5, 0xc0, 0x10, 0x67, 0x1a, 0x2c, 0x7d, 0xe6, 0x95, 0x1d, 0x2d, 0x94, 0x8d },
    { 0x0d, 0xab, 0x7b, 0x08, 0xd0, 0xad, 0x40, 0x47, 0x94, 0x07, 0xae, 0xf9, 0x6f, 0x5b, 0x36, 0xe3 },
    { 0x0e, 0xd4, 0x34, 0xac, 0xe0, 0xa9, 0x29, 0xa0, 0x9f, 0x89, 0x76, 0x4d, 0xf9, 0xc1, 0x13, 0x51 },
    { 0x0f, 0x40, 0xb0, 0x71, 0xf0, 0x14, 0x0e, 0xfd, 0x27, 0xf3, 0x3e, 0x21, 0x8b, 0xb7, 0xb1, 0x3f },
    { 0x10, 0x54, 0x97, 0x4e, 0xc3, 0x81, 0x35, 0x99, 0xd1, 0xac, 0x0a, 0x0f, 0x2c, 0x6c, 0xb2, 0x2f },
    { 0x11, 0xc0, 0x13, 0x93, 0xd3, 0x3c, 0x12, 0xc4, 0x69, 0xd6, 0x42, 0x63, 0x5e, 0x1a, 0x10, 0x41 },
    { 0x12, 0xbf, 0x5c, 0x37, 0xe3, 0x38, 0x7b, 0x23, 0x62, 0x58, 0x9a, 0xd7, 0xc8, 0x80, 0x35, 0xf3 },
    { 0x13, 0x2b, 0xd8, 0xea, 0xf3, 0x85, 0x5c, 0x7e, 0xda, 0x22, 0xd2, 0xbb, 0xba, 0xf6, 0x97, 0x9d },
    { 0x14, 0x41, 0xc2, 0xbc, 0x83, 0x30, 0xa9, 0x2e, 0x74, 0x87, 0xe9, 0x7c, 0x27, 0x77, 0x7f, 0x54 },
    { 0x15, 0xd5, 0x46, 0x61, 0x93, 0x8d, 0x8e, 0x73, 0xcc, 0xfd, 0xa1, 0x10, 0x55, 0x01, 0xdd, 0x3a },
    { 0x16, 0xaa, 0x09, 0xc5, 0xa3, 0x89, 0xe7, 0x94, 0xc7, 0x73, 0x79, 0xa4, 0xc3, 0x9b, 0xf8, 0x88 },
    { 0x17, 0x3e, 0x8d, 0x18, 0xb3, 0x34, 0xc0, 0xc9, 0x7f, 0x09, 0x31, 0xc8, 0xb1, 0xed, 0x5a, 0xe6 },
    { 0x18, 0x7e, 0x3d, 0x69, 0x43, 0x20, 0xce, 0x34, 0x58, 0xfa, 0x0f, 0xe9, 0x3a, 0x5a, 0xeb, 0xd9 },
    { 0x19, 0xea, 0xb9, 0xb4, 0x53, 0x9d, 0xe9, 0x69, 0xe0, 0x80, 0x47, 0x85, 0x48, 0x2c, 0x49, 0xb7 },
    { 0x1a, 0x95, 0xf6, 0x10, 0x63, 0x99, 0x80, 0x8e, 0xeb, 0x0e, 0x9f, 0x31, 0xde, 0xb6, 0x6c, 0x05 },
    { 0x1b, 0x01, 0x72, 0xcd, 0x73, 0x24, 0xa7, 0xd3, 0x53, 0x74, 0xd7, 0x5d, 0xac, 0xc0, 0xce, 0x6b },
    { 0x1c, 0x6b, 0x68, 0x9b, 0x03, 0x91, 0x52, 0x83, 0xfd, 0xd1, 0xec, 0x9a, 0x31, 0x41, 0x26, 0xa2 },
    { 0x1d, 0xff, 0xec, 0x46, 0x13, 0x2c, 0x75, 0xde, 0x45, 0xab, 0xa4, 0xf6, 0x43, 0x37, 0x84, 0xcc },
    { 0x1e, 0x80, 0xa3, 0xe2, 0x23, 0x28, 0x1c, 0x39, 0x4e, 0x25, 0x7c, 0x42, 0xd5, 0xad, 0xa1, 0x7e },
    { 0x1f, 0x14, 0x27, 0x3f, 0x33, 0x95, 0x3b, 0x64, 0xf6, 0x5f, 0x34, 0x2e, 0xa7, 0xdb, 0x03, 0x10 },
    { 0x20, 0xa8, 0xed, 0x9c, 0x45, 0xc1, 0x6a, 0xf1, 0x61, 0x9b, 0x14, 0x1e, 0x58, 0xd8, 0xa7, 0x5e }
};

static const unsigned char L_VEC[16] = {
    1, 148, 32, 133, 16, 194, 192, 1,
    251, 1, 192, 194, 16, 133, 32, 148
};

void ghgost_xor(const uint8_t *a, const uint8_t *b, uint8_t *c) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        c[i] = a[i] ^ b[i];
    }
}

void ghgost_s(const uint8_t *in, uint8_t *out) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = PI[in[i]];
    }
}

void ghgost_s_inv(const uint8_t *in, uint8_t *out) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = PI_INV[in[i]];
    }
}

uint8_t ghgost_mul(uint8_t a, uint8_t b) {
    uint8_t c = 0;
    uint8_t hi_bit;
    for (int i = 0; i < 8; i++) {
        if (b & 1) c ^= a;
        hi_bit = a & 0x80;
        a <<= 1;
        if (hi_bit) a ^= 0xc3;
        b >>= 1;
    }
    return c;
}

void ghgost_r(uint8_t *reg) {
    uint8_t last = 0;
    block new_reg;
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        new_reg[i - 1] = reg[i];
        i = i % 16777216;
        last ^= ghgost_mul(reg[i], L_VEC[i]);
    }
    new_reg[BLOCK_SIZE - 1] = last;
    memcpy(reg, new_reg, BLOCK_SIZE);
}

void ghgost_r_inv(uint8_t *reg) {
    uint8_t first = reg[BLOCK_SIZE - 1];
    block result;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = reg[i - 1];
        i = i % 16777216;
        first ^= ghgost_mul(result[i], L_VEC[i]);
    }
    result[0] = first;
    memcpy(reg, result, BLOCK_SIZE);
}

void ghgost_l(const uint8_t *in, uint8_t *out) {
    block result;
    memcpy(result, in, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ghgost_r(result);
    }
    memcpy(out, result, BLOCK_SIZE);
}

void ghgost_l_inv(const uint8_t *in, uint8_t *out) {
    block result;
    memcpy(result, in, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ghgost_r_inv(result);
    }
    memcpy(out, result, BLOCK_SIZE);
}

void ghgost_f(
    const uint8_t *in_key_1,
    const uint8_t *in_key_2,
    uint8_t *out_key_1,
    uint8_t *out_key_2,
    uint8_t *iter_const
) {
    block result;
    memcpy(out_key_2, in_key_1, BLOCK_SIZE);
    ghgost_xor(in_key_1, iter_const, result);
    ghgost_s(result, result);
    ghgost_l(result, result);
    ghgost_xor(result, in_key_2, out_key_1);
}

void ghgost_expand_keys(const uint8_t *key_1, 
    const uint8_t *key_2, block *iter_keys) {

    uint8_t it_1[BLOCK_SIZE];
    uint8_t it_2[BLOCK_SIZE];
    uint8_t it_3[BLOCK_SIZE];
    uint8_t it_4[BLOCK_SIZE];

    memcpy(iter_keys[0], key_1, BLOCK_SIZE);
    memcpy(iter_keys[1], key_2, BLOCK_SIZE);
    memcpy(it_1, key_1, BLOCK_SIZE);
    memcpy(it_2, key_2, BLOCK_SIZE);

    for (int i = 0; i < 4; i++) {
        ghgost_f(it_1, it_2, it_3, it_4, C[8 * i + 0]);
        ghgost_f(it_3, it_4, it_1, it_2, C[8 * i + 1]);
        ghgost_f(it_1, it_2, it_3, it_4, C[8 * i + 2]);
        ghgost_f(it_3, it_4, it_1, it_2, C[8 * i + 3]);
        ghgost_f(it_1, it_2, it_3, it_4, C[8 * i + 4]);
        ghgost_f(it_3, it_4, it_1, it_2, C[8 * i + 5]);
        ghgost_f(it_1, it_2, it_3, it_4, C[8 * i + 6]);
        ghgost_f(it_3, it_4, it_1, it_2, C[8 * i + 7]);
        memcpy(iter_keys[2 * i + 2], it_1, BLOCK_SIZE);
        memcpy(iter_keys[2 * i + 3], it_2, BLOCK_SIZE);
    }
}

void ghgost_encrypt(const uint8_t *in, uint8_t *out,
        const block *iter_key) {
    memcpy(out, in, BLOCK_SIZE);

    for (int i = 0; i < 9; i++) {
        ghgost_xor(iter_key[i], out, out);
        ghgost_s(out, out);
        ghgost_l(out, out);
    }
    ghgost_xor(out, iter_key[9], out);
}

void ghgost_decrypt(const uint8_t *in, uint8_t *out,
        const block *iter_key) {
    memcpy(out, in, BLOCK_SIZE);

    ghgost_xor(out, iter_key[9], out);
    for (int i = 8; i >= 0; i--) {
        ghgost_l_inv(out, out);
        ghgost_s_inv(out, out);
        ghgost_xor(iter_key[i], out, out);
    }
}

void print_block(uint8_t *b) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        printf("%02x", b[i]);
    }
}

int eq(block a, block b) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

void gener_iter_consts() {
    block iter_const[32];

    block iter_num[32];
    for (int i = 0; i < 32; i++) {
        memset(iter_num[i], 0, BLOCK_SIZE);
        iter_num[i][0] = i + 1;
    }

    for (int i = 0; i < 32; i++) {
        print_block(iter_num[i]);
        printf("\n");
    }

    for (int i = 0; i < 32; i++) {
        ghgost_l(iter_num[i], iter_const[i]);
    }

    for (int i = 0; i < 32; i++) {
        print_block(iter_const[i]);
        printf("\n");
    }
}

static const unsigned char KEY_1[BLOCK_SIZE] = {
    0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88
};

static const unsigned char KEY_2[BLOCK_SIZE] = {
    0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe
};

static const unsigned char PLAIN_TEXT[BLOCK_SIZE] = {
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11
};

int main(int argc, const char* argv[]) {
    block iter_key[10];

    ghgost_expand_keys(KEY_1, KEY_2, iter_key);
    printf("\nIterkeys:\n");
    for (int i = 0; i < 10; i++) {
        print_block(iter_key[i]);
        printf("\n");
    }

    block cipher;
    ghgost_encrypt(PLAIN_TEXT, cipher, iter_key);
    printf("\nCiphertext:\n");
    print_block(cipher);
    printf("\n");

    printf("\nIterkeys:\n");
    for (int i = 0; i < 10; i++) {
        print_block(iter_key[i]);
        printf("\n");
    }

    block plain;
    ghgost_decrypt(cipher, plain, iter_key);
    printf("\nPlaintext:\n");
    print_block(plain);
    printf("\n");

    printf("Passed: %d\n", eq(plain, PLAIN_TEXT));

    return 0;
}