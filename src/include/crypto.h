#ifndef __AMW_CRYPTO_H
#define __AMW_CRYPTO_H

struct amw_arc4_state
{
    unsigned char state[256];
    unsigned char index[1];
};

void amw_arc4_init(struct amw_arc4_state *state, 
        const char *key, size_t keylen);

void amw_arc4_crypt(struct amw_arc4_state *state, const unsigned char *in,
        unsigned char *out, size_t buflen);

#endif
