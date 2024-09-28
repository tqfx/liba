#define LIBA_A_C
#include "a/a.h"
#include <string.h>
#include <stdlib.h>
#if defined(A_HAVE_MIMALLOC_H)
#include <mimalloc-override.h>
#endif /* A_HAVE_MIMALLOC_H */

void *a_copy(void *__restrict dst, void const *__restrict src, a_size siz) { return memcpy(dst, src, siz); }

void *a_move(void *dst, void const *src, a_size siz) { return memmove(dst, src, siz); }

void *a_fill(void *ptr, a_size siz, int val) { return memset(ptr, val, siz); }

void *a_zero(void *ptr, a_size siz) { return memset(ptr, 0, siz); }

void a_swap(void *lhs_, void *rhs_, a_size siz)
{
    a_byte *lhs = (a_byte *)lhs_;
    a_byte *rhs = (a_byte *)rhs_;
    for (a_byte byte; siz; --siz, ++lhs, ++rhs)
    {
        byte = *lhs;
        *lhs = *rhs;
        *rhs = byte;
    }
}

a_u32 a_hash_bkdr(void const *str_, a_u32 val)
{
    a_byte const *str = (a_byte const *)str_;
    if (str)
    {
        for (; *str; ++str)
        {
            val = val * 131 + *str;
        }
    }
    return val;
}

a_u32 a_hash_bkdr_(void const *ptr_, a_size siz, a_u32 val)
{
    a_byte const *ptr = (a_byte const *)ptr_;
    for (; siz; --siz, ++ptr)
    {
        val = val * 131 + *ptr;
    }
    return val;
}

a_u32 a_hash_sdbm(void const *str_, a_u32 val)
{
    a_byte const *str = (a_byte const *)str_;
    if (str)
    {
        for (; *str; ++str)
        {
            val = val * 65599 + *str;
        }
    }
    return val;
}

a_u32 a_hash_sdbm_(void const *ptr_, a_size siz, a_u32 val)
{
    a_byte const *ptr = (a_byte const *)ptr_;
    for (; siz; --siz, ++ptr)
    {
        val = val * 65599 + *ptr;
    }
    return val;
}

void a_float_push_fore(a_float *p, a_size n, a_float x)
{
    if (n--)
    {
        a_move(p + 1, p, sizeof(a_float) * n);
        p[0] = x;
    }
}

void a_float_push_back(a_float *p, a_size n, a_float x)
{
    if (n--)
    {
        a_move(p, p + 1, sizeof(a_float) * n);
        p[n] = x;
    }
}

void a_float_push_fore_(a_float *block_p, a_size block_n,
                        a_float const *cache_p, a_size cache_n)
{
    a_size const n = A_MIN(cache_n, block_n);
    if (n)
    {
        a_size const m = block_n - n;
        cache_p = cache_p + cache_n - n;
        a_move(block_p + n, block_p, sizeof(a_float) * m);
        a_copy(block_p, cache_p, sizeof(a_float) * n);
    }
}

void a_float_push_back_(a_float *block_p, a_size block_n,
                        a_float const *cache_p, a_size cache_n)
{
    a_size const n = A_MIN(cache_n, block_n);
    if (n)
    {
        a_size const m = block_n - n;
        cache_p = cache_p + cache_n - n;
        a_move(block_p, block_p + n, sizeof(a_float) * m);
        a_copy(block_p + m, cache_p, sizeof(a_float) * n);
    }
}

void a_float_roll_fore(a_float *p, a_size n)
{
    if (n--)
    {
        a_float x = p[0];
        a_move(p, p + 1, sizeof(a_float) * n);
        p[n] = x;
    }
}

void a_float_roll_back(a_float *p, a_size n)
{
    if (n--)
    {
        a_float x = p[n];
        a_move(p + 1, p, sizeof(a_float) * n);
        p[0] = x;
    }
}

void a_float_roll_fore_(a_float *block_p, a_size block_n,
                        a_float *shift_p, a_size shift_n)
{
    a_size const shift = shift_n % block_n;
    a_size const start = block_n - shift;
    a_copy(shift_p, block_p, sizeof(a_float) * shift);
    a_move(block_p, block_p + shift, sizeof(a_float) * start);
    a_copy(block_p + start, shift_p, sizeof(a_float) * shift);
}

void a_float_roll_back_(a_float *block_p, a_size block_n,
                        a_float *shift_p, a_size shift_n)
{
    a_size const shift = shift_n % block_n;
    a_size const start = block_n - shift;
    a_copy(shift_p, block_p + start, sizeof(a_float) * shift);
    a_move(block_p + shift, block_p, sizeof(a_float) * start);
    a_copy(block_p, shift_p, sizeof(a_float) * shift);
}

a_float a_float_mean(a_float const *p, a_size n)
{
    a_float res = 0;
    a_float const inv = 1 / (a_float)n;
    for (; n; --n, ++p) { res += *p * inv; }
    return res;
}

a_float a_float_sum(a_float const *p, a_size n)
{
    a_float res = 0;
    for (; n; --n, ++p) { res += *p; }
    return res;
}

a_float a_float_sum1(a_float const *p, a_size n)
{
    a_float res = 0;
    for (; n; --n, ++p) { res += A_ABS(*p); }
    return res;
}

a_float a_float_sum2(a_float const *p, a_size n)
{
    a_float res = 0;
    for (; n; --n, ++p) { res += A_SQ(*p); }
    return res;
}

A_ALLOC((*a_alloc), addr, size) = a_alloc_;
A_ALLOC(a_alloc_, addr, size)
{
    if (size)
    {
        if (addr)
        {
            return realloc(addr, size);
        }
        return malloc(size);
    }
    free(addr);
    return A_NULL;
}
