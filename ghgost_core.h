#ifndef GHGOST_CORE_H
# define GHGOST_CORE_H

# include <stdint.h>
# include <stdio.h>
# include <string.h>

# define BLOCK_SIZE 16

typedef uint8_t ghgost_block_t[BLOCK_SIZE];

typedef ghgost_block_t GHGOST_KEY[10];

static const unsigned char PI[256];

static const unsigned char PI_INV[256];

static const unsigned char C[32][BLOCK_SIZE];

// static const unsigned char L_VEC[16];

void ghgost_xor(const ghgost_block_t a, const ghgost_block_t b, ghgost_block_t c);

void ghgost_s(const ghgost_block_t in, ghgost_block_t out);

void ghgost_s_inv(const ghgost_block_t in, ghgost_block_t out);

// void ghgost_r(ghgost_block_t reg);

// void ghgost_r_inv(ghgost_block_t reg);

void ghgost_l(ghgost_block_t out);

void ghgost_l_inv(ghgost_block_t out);

void ghgost_f(
    const ghgost_block_t in_key_1,
    const ghgost_block_t in_key_2,
    ghgost_block_t out_key_1,
    ghgost_block_t out_key_2,
    ghgost_block_t iter_const
);

void ghgost_expand_keys(
    const ghgost_block_t key_1, 
    const ghgost_block_t key_2, 
    GHGOST_KEY iter_keys
);

void ghgost_encrypt(
    const ghgost_block_t in, 
    ghgost_block_t out,
    const GHGOST_KEY iter_key
);

void ghgost_decrypt(
    const ghgost_block_t in, 
    ghgost_block_t out,
    const GHGOST_KEY iter_key
);

void print_block(ghgost_block_t b);

int eq(ghgost_block_t a, ghgost_block_t b);

void gener_iter_consts();

#endif /* GHGOST_CORE_H */