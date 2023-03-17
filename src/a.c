#define LIBA_A_C
#include "a/a.h"

a_vptr_t a_copy(a_vptr_t const A_RESTRICT _dst, a_cptr_t const A_RESTRICT _src, a_size_t siz)
{
    a_byte_t const *src = A_BYTE_P(_src);
    a_byte_t *dst = a_byte_p(_dst);
    while (siz--)
    {
        *dst++ = *src++;
    }
    return _dst;
}

a_vptr_t a_move(a_vptr_t const _dst, a_cptr_t const _src, a_size_t siz)
{
    a_byte_t const *src = A_BYTE_P(_src);
    a_byte_t *dst = a_byte_p(_dst);
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

a_vptr_t a_fill(a_vptr_t const _ptr, a_size_t siz, a_int_t const val)
{
    for (a_byte_t *ptr = a_byte_p(_ptr); siz--; ++ptr)
    {
        *ptr = a_byte_c(val);
    }
    return _ptr;
}

a_vptr_t a_zero(a_vptr_t const ptr, a_size_t const siz)
{
    return a_fill(ptr, siz, 0);
}

a_void_t a_swap(a_vptr_t const _lhs, a_vptr_t const _rhs, a_size_t siz)
{
    for (a_byte_t *lhs = a_byte_p(_lhs), *rhs = a_byte_p(_rhs); siz--; ++lhs, ++rhs)
    {
        *lhs ^= *rhs;
        *rhs ^= *lhs;
        *lhs ^= *rhs;
    }
}

a_umax_t a_hash_bkdr(a_cptr_t const _str, a_umax_t val)
{
    if (_str)
    {
        for (a_u8_t const *str = A_U8_P(_str); *str; ++str)
        {
            val = val * 131 + *str;
        }
    }
    return val;
}

a_umax_t a_hash_bkdrn(a_cptr_t const _ptr, a_size_t siz, a_umax_t val)
{
    if (_ptr && siz)
    {
        for (a_u8_t const *ptr = A_U8_P(_ptr); siz--; ++ptr)
        {
            val = val * 131 + *ptr;
        }
    }
    return val;
}
