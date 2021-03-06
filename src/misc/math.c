/*!
 @file math.c
 @brief Calculate math library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/math.h"

#include <assert.h>
#include <stdarg.h>

float a_sqrt_inv(float x)
{
    union
    {
        float x;
        uint32_t u;
    } u[1] = {{x}};
    if (x > 0)
    {
        float xh = 0.5F * x;
        u->u = 0x5F3759DF - (u->u >> 1);
        u->x *= (1.5F - (xh * u->x * u->x));
        u->x *= (1.5F - (xh * u->x * u->x));
    }
    else if (x < 0)
    {
        u->u = 0xFFC00000;
    }
    else
    {
        u->u = 0x7F800000;
    }
    return u->x;
}

#undef A_SQRT_UINT
#define A_SQRT_UINT(bit, func, type, mask)         \
    type func(type x)                              \
    {                                              \
        type y = 0;                                \
        for (unsigned int i = 0; i != bit; i += 2) \
        {                                          \
            type k = mask >> i;                    \
            if (k + y <= x)                        \
            {                                      \
                x -= k + y;                        \
                y = (y >> 1) | k;                  \
            }                                      \
            else                                   \
            {                                      \
                y >>= 1;                           \
            }                                      \
        }                                          \
        return y;                                  \
    }
A_SQRT_UINT(32, a_sqrt_u32, uint32_t, UINT32_C(0x40000000))
A_SQRT_UINT(64, a_sqrt_u64, uint64_t, UINT64_C(0x4000000000000000))
#undef A_SQRT_UINT

void a_normalizef(float *dat, size_t num)
{
    assert(!num || dat);

    float norm = 0;
    float *q = dat + num;

    for (float *p = dat; p != q; ++p)
    {
        norm += A_SQ(*p);
    }

    norm = a_sqrt_inv(norm);

    for (float *p = dat; p != q; ++p)
    {
        *p *= norm;
    }
}

void a_normalizevf(unsigned int num, ...)
{
    va_list ap;
    float norm = 0;

    va_start(ap, num);
    for (unsigned int n = num; n; --n)
    {
        float *p = va_arg(ap, float *);
        norm += A_SQ(*p);
    }
    va_end(ap);

    norm = a_sqrt_inv(norm);

    va_start(ap, num);
    for (unsigned int n = num; n; --n)
    {
        float *p = va_arg(ap, float *);
        *p *= norm;
    }
    va_end(ap);
}

#undef A_RESTRICT_LOOP
#define A_RESTRICT_LOOP(func, type)       \
    type func(type x, type min, type max) \
    {                                     \
        type siz = max - min;             \
        if (x > max)                      \
        {                                 \
            do                            \
            {                             \
                x -= siz;                 \
            } while (x > max);            \
        }                                 \
        else if (x < min)                 \
        {                                 \
            do                            \
            {                             \
                x += siz;                 \
            } while (x < min);            \
        }                                 \
        return x;                         \
    }
A_RESTRICT_LOOP(a_restrict_loop, double)
A_RESTRICT_LOOP(a_restrict_loopf, float)
#undef A_RESTRICT_LOOP
