#include "a/utf.h"

unsigned int a_utf_encode(void *const _str, a_u32_t const val)
{
    a_u32_t mask = 0;
    unsigned int offset = 0;
    a_u32_t x = val & A_U32_C(0x7FFFFFFF);
    if (x < A_U32_C(0x0010000))
    {
        if (x < A_U32_C(0x0000800))
        {
            if (x < A_U32_C(0x0000080) && x)
            {
                offset = 1; /* U+0000001 ~ U+0000007F */
            }
            else
            {
                offset = 2; /* U+0000080 ~ U+000007FF */
                mask = 0xC0;
            }
        }
        else
        {
            offset = 3; /* U+0000800 ~ U+0000FFFF */
            mask = 0xE0;
        }
    }
    else
    {
        if (x < A_U32_C(0x0200000))
        {
            offset = 4; /* U+0010000 ~ U+001FFFFF */
            mask = 0xF0;
        }
        else
        {
            if (x < A_U32_C(0x4000000))
            {
                offset = 5; /* U+0200000 ~ U+03FFFFFF */
                mask = 0xF8;
            }
            else
            {
                offset = 6; /* U+4000000 ~ U+7FFFFFFF */
                mask = 0xFC;
            }
        }
    }
    if (_str)
    {
        a_byte_t *const str = (a_byte_t *)_str;
        switch (offset)
        {
        case 6:
            str[5] = (a_byte_t)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 5:
            str[4] = (a_byte_t)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 4:
            str[3] = (a_byte_t)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 3:
            str[2] = (a_byte_t)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 2:
            str[1] = (a_byte_t)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 1:
            str[0] = (a_byte_t)(mask | x);
            A_FALLTHROUGH;
        default:
            break;
        }
    }
    return offset;
}

unsigned int a_utf_decode(void const *const _str, a_u32_t *const val)
{
    a_byte_t const *str = (a_byte_t const *)_str;
    unsigned int offset = 0;
    unsigned int chr = *str;
    a_u32_t res = 0;
    if (chr < 0x80)
    {
        res = chr;
        if (!chr)
        {
            return offset;
        }
    }
    else
    {
        for (; chr & 0x40; chr <<= 1)
        {
            unsigned int c = *(++str);
            if ((c & 0xC0) != 0x80)
            {
                return offset;
            }
            res = (res << 6) | (c & 0x3F);
        }
        offset = (unsigned int)(str - (a_byte_t const *)_str);
        res |= (a_u32_t)(chr & 0x7F) << (offset * 5);
    }
    if (val)
    {
        *val = res;
    }
    return offset + 1;
}

a_size_t a_utf_length(void const *const _str)
{
    a_size_t length = 0;
    char const *str = (char const *)_str;
    for (unsigned int offset; (void)(offset = a_utf_decode(str, A_NULL)), offset; str += offset)
    {
        ++length;
    }
    return length;
}
