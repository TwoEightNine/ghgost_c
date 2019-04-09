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

static const unsigned char USER_KEY[2 * BLOCK_SIZE] = {
    0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
    0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe
};

void set_key(const char *key1, const char *key2, GHGOST_KEY *key) {
    GHGOST_KEY ghgost_key;
    for (int i = 0; i < 10; i++) {
        print_block(ghgost_key[i]);
        printf("\n");
    }

    ghgost_expand_keys(key1, key2, ghgost_key);
    printf("After\n");
    for (int i = 0; i < 10; i++) {
        print_block(ghgost_key[i]);
        printf("\n");
    }
    memcpy(key, &ghgost_key, 10 * 16);
}

int main(int argc, const char *argv[]) {
    long t = 1000;
    while(t) {
        GHGOST_KEY iter_key;

        char key1[BLOCK_SIZE];
        char key2[BLOCK_SIZE];
        memcpy(key1, &USER_KEY[0], BLOCK_SIZE * sizeof(*USER_KEY));
        memcpy(key2, &USER_KEY[BLOCK_SIZE], BLOCK_SIZE * sizeof(*USER_KEY));

        // printf("Userkey:\n");
        // print_block(key1);
        // print_block(key2);
        // printf("\n\nPlaintext:\n");
        // print_block(PLAIN_TEXT);
        ghgost_expand_keys(key1, key2, iter_key);
        // printf("\n\nIterkeys:\n");
        // for (int i = 0; i < 10; i++) {
            // print_block(iter_key[i]);
            // printf("\n");
        // }

        ghgost_block_t cipher;
        ghgost_encrypt(PLAIN_TEXT, cipher, iter_key);
        // printf("\nCiphertext:\n");
        // print_block(cipher);
        // printf("\n");

        // printf("\nIterkeys:\n");
        // for (int i = 0; i < 10; i++) {
            // print_block(iter_key[i]);
            // printf("\n");
        // }

        ghgost_block_t plain;
        ghgost_decrypt(cipher, plain, iter_key);
        // printf("\nPlaintext:\n");
        // print_block(plain);
        // printf("\n");

        // printf("Passed: %d\n", eq(plain, PLAIN_TEXT));
        t--;
    }
    // GHGOST_KEY key;
    // set_key(KEY_1, KEY_2, key);
    // printf("Finally\n");
    // for (int i = 0; i < 10; i++) {
    //     print_block(key[i]);
    //     printf("\n");
    // }

    return 0;
}

/*
Plaintext:
1122334455667700ffeeddccbbaa9988

Iterkeys:
8899aabbccddeeff0011223344556677
fedcba98765432100123456789abcdef
db31485315694343228d6aef8cc78c44
3d4553d8e9cfec6815ebadc40a9ffd04
57646468c44a5e28d3e59246f429f1ac
bd079435165c6432b532e82834da581b
51e640757e8745de705727265a0098b1
5a7925017b9fdd3ed72a91a22286f984
bb44e25378c73123a5f32f73cdb6e517
72e9dd7416bcf45b755dbaa88e4a4043

Ciphertext:
7f679d90bebc24305a468d42b9d4edcd

Iterkeys:
8899aabbccddeeff0011223344556677
fedcba98765432100123456789abcdef
db31485315694343228d6aef8cc78c44
3d4553d8e9cfec6815ebadc40a9ffd04
57646468c44a5e28d3e59246f429f1ac
bd079435165c6432b532e82834da581b
51e640757e8745de705727265a0098b1
5a7925017b9fdd3ed72a91a22286f984
bb44e25378c73123a5f32f73cdb6e517
72e9dd7416bcf45b755dbaa88e4a4043

Plaintext:
1122334455667700ffeeddccbbaa9988
Passed: 1


*/