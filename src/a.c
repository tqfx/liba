#define LIBA_A_C
#include "a/a.h"
#include <string.h>

void *a_copy(void *const A_RESTRICT dst, void const *const A_RESTRICT src, a_size const siz) { return memcpy(dst, src, siz); }

void *a_move(void *const dst, void const *const src, a_size const siz) { return memmove(dst, src, siz); }

void *a_fill(void *const ptr, a_size siz, int const val) { return memset(ptr, val, siz); }

void *a_zero(void *const ptr, a_size const siz) { return memset(ptr, 0, siz); }

void a_swap(void *const _lhs, void *const _rhs, a_size siz)
{
    a_byte tmp[1];
    for (a_byte *lhs = (a_byte *)_lhs,
                *rhs = (a_byte *)_rhs;
         siz; ++lhs, ++rhs, --siz)
    {
        *tmp = *lhs;
        *lhs = *rhs;
        *rhs = *tmp;
    }
}

a_umax a_hash_bkdr(void const *const _str, a_umax val)
{
    if (_str)
    {
        for (a_byte const *str = (a_byte const *)_str; *str; ++str)
        {
            val = val * 131 + *str;
        }
    }
    return val;
}

a_umax a_hash_bkdrn(void const *const _ptr, a_size siz, a_umax val)
{
    if (_ptr && siz)
    {
        for (a_byte const *ptr = (a_byte const *)_ptr; siz; ++ptr, --siz)
        {
            val = val * 131 + *ptr;
        }
    }
    return val;
}

void a_float_save(a_float *const array_p, a_size const array_n,
                  a_float const *const cache_p, a_size const cache_n)
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

void a_float_roll(a_float *const array_p, a_size const array_n,
                  a_float *const shift_p, a_size const shift_n)
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

A_ALLOC((*a_alloc), , ) = a_alloc_;
A_ALLOC(a_alloc_, const addr, const size)
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
