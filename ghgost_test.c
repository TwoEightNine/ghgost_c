#include "ghgost_test.h"
#include "ghgost_core.c"

static const unsigned char KEY_1[BLOCK_SIZE] = {
    0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88
};

static const unsigned char KEY_2[BLOCK_SIZE] = {
    0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe
};

static const unsigned char PLAIN_TEXT[BLOCK_SIZE] = {
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11
};

int main(int argc, const char *argv[]) {
    ghgost_block_t iter_key[10];

    ghgost_expand_keys(KEY_1, KEY_2, iter_key);
    printf("\nIterkeys:\n");
    for (int i = 0; i < 10; i++) {
        print_block(iter_key[i]);
        printf("\n");
    }

    ghgost_block_t cipher;
    ghgost_encrypt(PLAIN_TEXT, cipher, iter_key);
    printf("\nCiphertext:\n");
    print_block(cipher);
    printf("\n");

    printf("\nIterkeys:\n");
    for (int i = 0; i < 10; i++) {
        print_block(iter_key[i]);
        printf("\n");
    }

    ghgost_block_t plain;
    ghgost_decrypt(cipher, plain, iter_key);
    printf("\nPlaintext:\n");
    print_block(plain);
    printf("\n");

    printf("Passed: %d\n", eq(plain, PLAIN_TEXT));


    return 0;
}