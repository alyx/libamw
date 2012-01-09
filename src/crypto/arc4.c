#include "amw.h"

static inline void switch_bytes(unsigned char *a, unsigned char *b)
{
    unsigned char temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void amw_arc4_init(struct amw_arc4_state *state, 
        const char *key, size_t keylen)
{
    int i;
    unsigned char j;

    for (i = 0; i < 256; i++)
        state->state[i] = (unsigned char)i;
    state->index[0] = 0;
    state->index[1] = 0;

    for (i = j = 0; i < 256; i++)
    {
        j = (j + key[i % keylen] + state->state[i]) % 256;
        switch_bytes(&state->state[i], &state->state[j]);
    }
}

void amw_arc4_crypt(struct amw_arc4_state *state, const unsigned char *in,
        unsigned char *out, size_t buflen)
{
    int i;
    unsigned char j;

    for (i = 0; i < (int)buflen; i++)
    {
        state->index[0]++;
        state->index[1] += state->state[state->index[0]];

        switch_bytes(&state->state[state->index[0]],
                &state->state[state->index[1]]);

        j = state->state[state->index[0]] + state->state[state->index[1]];
        out[i] = in[i] ^ state->state[j];
    }
}
