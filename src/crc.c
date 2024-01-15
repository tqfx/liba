#include "a/crc.h"

void a_crc8le_init(a_u8 table[A_CRC_SIZ], a_u8 poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u8 value = (a_u8)i;
        for (unsigned int j = 8; j; --j)
        {
            unsigned int is1 = (unsigned int)(value & 1);
            value >>= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = value;
    }
}

void a_crc16le_init(a_u16 table[A_CRC_SIZ], a_u16 poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u16 value = (a_u16)i;
        for (unsigned int j = 8; j; --j)
        {
            unsigned int is1 = (unsigned int)(value & 1);
            value >>= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = value;
    }
}

void a_crc32le_init(a_u32 table[A_CRC_SIZ], a_u32 poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u32 value = i;
        for (unsigned int j = 8; j; --j)
        {
            unsigned int is1 = (unsigned int)(value & 1);
            value >>= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = value;
    }
}

void a_crc64le_init(a_u64 table[A_CRC_SIZ], a_u64 poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u64 value = i;
        for (unsigned int j = 8; j; --j)
        {
            unsigned int is1 = (unsigned int)(value & 1);
            value >>= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = value;
    }
}

void a_crc8be_init(a_u8 table[A_CRC_SIZ], a_u8 poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        unsigned int value = i;
        for (unsigned int j = 8; j; --j)
        {
            unsigned int is1 = A_U8_C(0x80) & value;
            value <<= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = (a_u8)value;
    }
}

void a_crc16be_init(a_u16 table[A_CRC_SIZ], a_u16 poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        unsigned int value = i << 8;
        for (unsigned int j = 8; j; --j)
        {
            unsigned int is1 = A_U16_C(0x8000) & value;
            value <<= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = (a_u16)value;
    }
}

void a_crc32be_init(a_u32 table[A_CRC_SIZ], a_u32 poly)
{
    for (a_u32 i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u32 value = i << 24;
        for (unsigned int j = 8; j; --j)
        {
            a_u32 is1 = A_U32_C(0x80000000) & value;
            value <<= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = value;
    }
}

void a_crc64be_init(a_u64 table[A_CRC_SIZ], a_u64 poly)
{
    for (a_u64 i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u64 value = i << 56;
        for (unsigned int j = 8; j; --j)
        {
            a_u64 is1 = A_U64_C(0x8000000000000000) & value;
            value <<= 1;
            if (is1) { value ^= poly; }
        }
        table[i] = value;
    }
}

a_u8 a_crc8(a_u8 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u8 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = table[value ^ *p++]; }
    return value;
}

a_u16 a_crc16le(a_u16 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u16 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (a_u16)((value >> 8) ^ table[(value ^ *p++) & 0xFF]); }
    return value;
}

a_u32 a_crc32le(a_u32 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u32 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value >> 8) ^ table[(value ^ *p++) & 0xFF]; }
    return value;
}

a_u64 a_crc64le(a_u64 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u64 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value >> 8) ^ table[(value ^ *p++) & 0xFF]; }
    return value;
}

a_u16 a_crc16be(a_u16 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u16 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (a_u16)((value << 8) ^ table[((value >> 8) ^ *p++) & 0xFF]); }
    return value;
}

a_u32 a_crc32be(a_u32 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u32 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value << 8) ^ table[((value >> 24) ^ *p++) & 0xFF]; }
    return value;
}

a_u64 a_crc64be(a_u64 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u64 value)
{
    a_byte const *p = (a_byte const *)pdata;
    a_byte const *q = (a_byte const *)pdata + nbyte;
    while (p != q) { value = (value << 8) ^ table[((value >> 56) ^ *p++) & 0xFF]; }
    return value;
}
