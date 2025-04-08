#include "a/utf.h"

unsigned int a_utf_encode(a_u32 val, void *buf)
{
    a_u32 mask = 0;
    unsigned int offset = 0;
    a_u32 x = val & A_U32_C(0x7FFFFFFF);
    if (x < A_U32_C(0x0010000))
    {
        if (x < A_U32_C(0x0000800))
        {
            if (x < A_U32_C(0x0000080))
            {
                offset = x > 0; /* U+0000001 ~ U+0000007F */
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
    if (buf)
    {
        a_byte *const str = (a_byte *)buf;
        switch (offset)
        {
        case 6:
            str[5] = (a_byte)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 5:
            str[4] = (a_byte)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 4:
            str[3] = (a_byte)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 3:
            str[2] = (a_byte)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 2:
            str[1] = (a_byte)(0x80 | (x & 0x3F));
            x >>= 6;
            A_FALLTHROUGH;
        case 1:
            str[0] = (a_byte)(mask | x);
            A_FALLTHROUGH;
        default:
            break;
        }
    }
    return offset;
}

unsigned int a_utf_decode(void const *ptr, a_size num, a_u32 *val)
{
    a_u32 code = 0;
    a_byte const *str = (a_byte const *)ptr;
    unsigned int chr, offset = 0;
    if (num) { chr = *str; }
    else { return 0; }
    if (chr < 0x80)
    {
        if (!chr) { return 0; }
        code = chr;
    }
    else
    {
        a_byte const *const nul = str + num;
        for (; chr & 0x40; chr <<= 1)
        {
            unsigned int const c = ++str < nul ? *str : 0;
            if ((c & 0xC0) != 0x80) { return 0; }
            code = (code << 6) | (c & 0x3F);
        }
        offset = (unsigned int)(str - (a_byte const *)ptr);
        code |= (a_u32)(chr & 0x7F) << (offset * 5);
    }
    if (val) { *val = code; }
    return offset + 1;
}

a_size a_utf_length(void const *ptr, a_size num, a_size *stop)
{
    a_size length = 0;
    char const *str = (char const *)ptr;
    unsigned int offset = a_utf_decode(str, num, A_NULL);
    for (; offset; offset = a_utf_decode(str, num, A_NULL))
    {
        str += offset;
        num -= offset;
        ++length;
    }
    if (stop) { *stop = (a_size)(str - (char const *)ptr); }
    return length;
}
