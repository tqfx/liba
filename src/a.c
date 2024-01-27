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

void a_swap(void *_lhs, void *_rhs, a_size siz)
{
    a_byte *lhs = (a_byte *)_lhs;
    a_byte *rhs = (a_byte *)_rhs;
    for (a_byte buf; siz; --siz, ++lhs, ++rhs)
    {
        buf = *lhs;
        *lhs = *rhs;
        *rhs = buf;
    }
}

a_u32 a_hash_bkdr(void const *_str, a_u32 val)
{
    a_byte const *str = (a_byte const *)_str;
    if (str)
    {
        for (; *str; ++str)
        {
            val = val * 131 + *str;
        }
    }
    return val;
}

a_u32 a_hash_bkdr_(void const *_ptr, a_size siz, a_u32 val)
{
    a_byte const *ptr = (a_byte const *)_ptr;
    if (ptr && siz)
    {
        for (; siz; --siz, ++ptr)
        {
            val = val * 131 + *ptr;
        }
    }
    return val;
}

a_u32 a_hash_sdbm(void const *_str, a_u32 val)
{
    a_byte const *str = (a_byte const *)_str;
    if (str)
    {
        for (; *str; ++str)
        {
            val = val * 65599 + *str;
        }
    }
    return val;
}

a_u32 a_hash_sdbm_(void const *_ptr, a_size siz, a_u32 val)
{
    a_byte const *ptr = (a_byte const *)_ptr;
    if (ptr && siz)
    {
        for (; siz; --siz, ++ptr)
        {
            val = val * 65599 + *ptr;
        }
    }
    return val;
}

void a_float_push(a_float *array_p, a_size array_n,
                  a_float const *cache_p, a_size cache_n)
{
    a_size const n = A_MIN(cache_n, array_n);
    for (a_size i = array_n, j = array_n - n; j;)
    {
        array_p[--i] = array_p[--j];
    }
    for (a_size i = 0; i != n; ++i)
    {
        array_p[i] = cache_p[i];
    }
}

void a_float_roll(a_float *array_p, a_size array_n,
                  a_float *shift_p, a_size shift_n)
{
    a_size const shift = shift_n % array_n;
    a_size const start = array_n - shift;
    for (a_size i = 0, j = start; i != shift; ++i, ++j)
    {
        shift_p[i] = array_p[j];
    }
    for (a_size i = array_n, j = start; j;)
    {
        array_p[--i] = array_p[--j];
    }
    for (a_size i = 0; i != shift; ++i)
    {
        array_p[i] = shift_p[i];
    }
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
