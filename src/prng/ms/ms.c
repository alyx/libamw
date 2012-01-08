/* libms - A half-arsed middle-square algorithm implementation in C
 * Copyright (c) 2011 Alyx <alyx@malkier.net>
 * Released under the NCSA Open Source License
 */

#include "amw.h"

static uint32_t square;

void amw_prng_ms_init(uint32_t seed)
{
    square = seed;
}

uint16_t amw_prng_ms_get(void)
{
    register uint16_t i;

    i = (square >>8) & 0xffff;
    square = i*i;

    return i;
}

