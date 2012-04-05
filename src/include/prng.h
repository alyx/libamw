#ifndef __AMW_PRNG_H
#define __AMW_PRNG_H

static inline uint16_t amw_prng_ms_get(uint32_t seed)
{
    return (seed >> 8) & 0xffff;
}

#endif /* __AMW_PRNG_H */
