#include "a/crc.h"

void a_crc8m_init(a_u8 table[0x100], a_u8 poly)
{
    for (unsigned int c = 0; c != 0x100; ++c)
    {
        unsigned int value = c;
        for (unsigned int b = 8; b; --b)
        {
            unsigned int sig = A_U8_C(0x80) & value;
            value <<= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = (a_u8)value;
    }
}
void a_crc8l_init(a_u8 table[0x100], a_u8 poly)
{
    poly = a_u8_rev(poly);
    for (unsigned int c = 0; c != 0x100; ++c)
    {
        unsigned int value = c;
        for (unsigned int b = 8; b; --b)
        {
            unsigned int sig = value & 1;
            value >>= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = (a_u8)value;
    }
}
a_u8 a_crc8(a_u8 const table[0x100], void const *pdata, a_size nbyte, a_u8 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = table[value ^ *p++]; }
    return value;
}

void a_crc16m_init(a_u16 table[0x100], a_u16 poly)
{
    for (unsigned int c = 0; c != 0x100; ++c)
    {
        unsigned int value = c << 8;
        for (unsigned int b = 8; b; --b)
        {
            unsigned int sig = A_U16_C(0x8000) & value;
            value <<= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = (a_u16)value;
    }
}
void a_crc16l_init(a_u16 table[0x100], a_u16 poly)
{
    poly = a_u16_rev(poly);
    for (unsigned int c = 0; c != 0x100; ++c)
    {
        unsigned int value = c;
        for (unsigned int b = 8; b; --b)
        {
            unsigned int sig = value & 1;
            value >>= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = (a_u16)value;
    }
}
a_u16 a_crc16m(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (a_u16)((value << 8) ^ table[((value >> 8) ^ *p++) & 0xFF]); }
    return value;
}
a_u16 a_crc16l(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (a_u16)((value >> 8) ^ table[(value ^ *p++) & 0xFF]); }
    return value;
}

void a_crc32m_init(a_u32 table[0x100], a_u32 poly)
{
    for (a_u32 c = 0; c != 0x100; ++c)
    {
        a_u32 value = c << 24;
        for (unsigned int b = 8; b; --b)
        {
            a_u32 sig = A_U32_C(0x80000000) & value;
            value <<= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = value;
    }
}
void a_crc32l_init(a_u32 table[0x100], a_u32 poly)
{
    poly = a_u32_rev(poly);
    for (unsigned int c = 0; c != 0x100; ++c)
    {
        a_u32 value = c;
        for (unsigned int b = 8; b; --b)
        {
            a_u32 sig = value & 1;
            value >>= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = value;
    }
}
a_u32 a_crc32m(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value << 8) ^ table[((value >> 24) ^ *p++) & 0xFF]; }
    return value;
}
a_u32 a_crc32l(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value >> 8) ^ table[(value ^ *p++) & 0xFF]; }
    return value;
}

void a_crc64m_init(a_u64 table[0x100], a_u64 poly)
{
    for (a_u64 c = 0; c != 0x100; ++c)
    {
        a_u64 value = c << 56;
        for (unsigned int b = 8; b; --b)
        {
            a_u64 sig = A_U64_C(0x8000000000000000) & value;
            value <<= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = value;
    }
}
void a_crc64l_init(a_u64 table[0x100], a_u64 poly)
{
    poly = a_u64_rev(poly);
    for (unsigned int c = 0; c != 0x100; ++c)
    {
        a_u64 value = c;
        for (unsigned int b = 8; b; --b)
        {
            a_u64 sig = value & 1;
            value >>= 1;
            if (sig) { value ^= poly; }
        }
        table[c] = value;
    }
}
a_u64 a_crc64m(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value << 8) ^ table[((value >> 56) ^ *p++) & 0xFF]; }
    return value;
}
a_u64 a_crc64l(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value >> 8) ^ table[(value ^ *p++) & 0xFF]; }
    return value;
}
