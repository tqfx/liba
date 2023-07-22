#define LIBA_A_C
#include "a/a.h"

void *a_copy(void *const A_RESTRICT _dst, void const *const A_RESTRICT _src, a_size_t siz)
{
    a_byte_t const *src = (a_byte_t const *)_src;
    a_byte_t *dst = (a_byte_t *)_dst;
    while (siz--)
    {
        *dst++ = *src++;
    }
    return _dst;
}

void *a_move(void *const _dst, void const *const _src, a_size_t siz)
{
    a_byte_t const *src = (a_byte_t const *)_src;
    a_byte_t *dst = (a_byte_t *)_dst;
    if (dst < src)
    {
        while (siz--)
        {
            *dst++ = *src++;
        }
    }
    else
    {
        src += siz;
        dst += siz;
        while (siz--)
        {
            *--dst = *--src;
        }
    }
    return _dst;
}

void *a_fill(void *const _ptr, a_size_t siz, int const val)
{
    for (a_byte_t *ptr = (a_byte_t *)_ptr; siz--; ++ptr)
    {
        *ptr = (a_byte_t)val;
    }
    return _ptr;
}

void *a_zero(void *const ptr, a_size_t const siz)
{
    return a_fill(ptr, siz, 0);
}

void a_swap(void *const _lhs, void *const _rhs, a_size_t siz)
{
    a_byte_t tmp[1];
    for (a_byte_t *lhs = (a_byte_t *)_lhs,
                  *rhs = (a_byte_t *)_rhs;
         siz--; ++lhs, ++rhs)
    {
        *tmp = *lhs;
        *lhs = *rhs;
        *rhs = *tmp;
    }
}

a_umax_t a_hash_bkdr(void const *const _str, a_umax_t val)
{
    if (_str)
    {
        for (a_byte_t const *str = (a_byte_t const *)_str; *str; ++str)
        {
            val = val * 131 + *str;
        }
    }
    return val;
}

a_umax_t a_hash_bkdrn(void const *const _ptr, a_size_t siz, a_umax_t val)
{
    if (_ptr && siz)
    {
        for (a_byte_t const *ptr = (a_byte_t const *)_ptr; siz--; ++ptr)
        {
            val = val * 131 + *ptr;
        }
    }
    return val;
}

void a_float_save(a_float_t *const array_p, a_size_t const array_n,
                  a_float_t const *const cache_p, a_size_t const cache_n)
{
    a_size_t const n = A_MIN(cache_n, array_n);
    for (a_size_t i = array_n, j = array_n - n; j;)
    {
        array_p[--i] = array_p[--j];
    }
    for (a_size_t i = 0; i != n; ++i)
    {
        array_p[i] = cache_p[i];
    }
}

void a_float_roll(a_float_t *const array_p, a_size_t const array_n,
                  a_float_t *const shift_p, a_size_t const shift_n)
{
    a_size_t const shift = shift_n % array_n;
    a_size_t const start = array_n - shift;
    for (a_size_t i = 0, j = start; i != shift; ++i, ++j)
    {
        shift_p[i] = array_p[j];
    }
    for (a_size_t i = array_n, j = start; j;)
    {
        array_p[--i] = array_p[--j];
    }
    for (a_size_t i = 0; i != shift; ++i)
    {
        array_p[i] = shift_p[i];
    }
}
