#include "ghgost_test.h"
#include "ghgost_core.c"
#include <time.h>

#define SIZE 64 * 1024 * 10 // 10MB

static const unsigned char KEY_1[BLOCK_SIZE] = {
    0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88
};

static const unsigned char KEY_2[BLOCK_SIZE] = {
    0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe
};

static const unsigned char PLAIN_TEXT[BLOCK_SIZE] = {
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11
};
static const unsigned char CIPHER_TEXT[BLOCK_SIZE] = {
    0xcd, 0xed, 0xd4, 0xb9, 0x42, 0x8d, 0x46, 0x5a, 0x30, 0x24, 0xbc, 0xbe, 0x90, 0x9d, 0x67, 0x7f
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
    GHGOST_KEY iter_key;
    char key1[BLOCK_SIZE];
    char key2[BLOCK_SIZE];
    memcpy(key1, &USER_KEY[0], BLOCK_SIZE * sizeof(*USER_KEY));
    memcpy(key2, &USER_KEY[BLOCK_SIZE], BLOCK_SIZE * sizeof(*USER_KEY));
    ghgost_expand_keys(key1, key2, iter_key);
    
    // assertion
    ghgost_block_t cipher;
    ghgost_encrypt(PLAIN_TEXT, cipher, iter_key);

    print_block(cipher);
    printf("\n");

    if (eq(cipher, CIPHER_TEXT)) {
        printf("PASSED!\n");
    } else {
        printf("FAILED!\n");
        return 1;
    }

    ghgost_block_t plain;
    ghgost_decrypt(cipher, plain, iter_key);

    print_block(plain);
    printf("\n");

    if (eq(plain, PLAIN_TEXT)) {
        printf("PASSED!\n");
    } else {
        printf("FAILED!\n");
        return 1;
    }
    
    clock_t start, end;
    int t = SIZE;
    start = clock();
    while(t--) {
        ghgost_block_t cipher;
        ghgost_encrypt(PLAIN_TEXT, cipher, iter_key);

        // ghgost_block_t plain;
        // ghgost_decrypt(cipher, plain, iter_key);
    }
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    double speed = ((double) SIZE * 16) / cpu_time_used / 1048576;
    printf("time used = %.3fs\n", cpu_time_used);
    printf("approx. speed = %.3fMBps\n", speed);
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