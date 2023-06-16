#include "a/crc.h"

void a_crc8l_init(a_u8_t table[A_CRC_SIZ], a_u8_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u8_t value = (a_u8_t)i;
        for (unsigned int j = 8; j; --j)
        {
            if (value & 1)
            {
                value >>= 1;
                value ^= poly;
            }
            else
            {
                value >>= 1;
            }
        }
        table[i] = value;
    }
}

void a_crc16l_init(a_u16_t table[A_CRC_SIZ], a_u16_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u16_t value = (a_u16_t)i;
        for (unsigned int j = 8; j; --j)
        {
            if (value & 1)
            {
                value >>= 1;
                value ^= poly;
            }
            else
            {
                value >>= 1;
            }
        }
        table[i] = value;
    }
}

void a_crc32l_init(a_u32_t table[A_CRC_SIZ], a_u32_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u32_t value = i;
        for (unsigned int j = 8; j; --j)
        {
            if (value & 1)
            {
                value >>= 1;
                value ^= poly;
            }
            else
            {
                value >>= 1;
            }
        }
        table[i] = value;
    }
}

void a_crc64l_init(a_u64_t table[A_CRC_SIZ], a_u64_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u64_t value = i;
        for (unsigned int j = 8; j; --j)
        {
            if (value & 1)
            {
                value >>= 1;
                value ^= poly;
            }
            else
            {
                value >>= 1;
            }
        }
        table[i] = value;
    }
}

void a_crc8h_init(a_u8_t table[A_CRC_SIZ], a_u8_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        unsigned int value = i;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U8_C(0x80) & value)
            {
                value <<= 1;
                value ^= poly;
            }
            else
            {
                value <<= 1;
            }
        }
        table[i] = (a_u8_t)value;
    }
}

void a_crc16h_init(a_u16_t table[A_CRC_SIZ], a_u16_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        unsigned int value = i << 8;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U16_C(0x8000) & value)
            {
                value <<= 1;
                value ^= poly;
            }
            else
            {
                value <<= 1;
            }
        }
        table[i] = (a_u16_t)value;
    }
}

void a_crc32h_init(a_u32_t table[A_CRC_SIZ], a_u32_t const poly)
{
    for (a_u32_t i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u32_t value = i << 24;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U32_C(0x80000000) & value)
            {
                value <<= 1;
                value ^= poly;
            }
            else
            {
                value <<= 1;
            }
        }
        table[i] = value;
    }
}

void a_crc64h_init(a_u64_t table[A_CRC_SIZ], a_u64_t const poly)
{
    for (a_u64_t i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u64_t value = i << 56;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U64_C(0x8000000000000000) & value)
            {
                value <<= 1;
                value ^= poly;
            }
            else
            {
                value <<= 1;
            }
        }
        table[i] = value;
    }
}

a_u8_t a_crc8(a_u8_t const table[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u8_t value)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        value = table[value ^ *p++];
    }
    return value;
}

a_u16_t a_crc16l(a_u16_t const table[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u16_t value)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        value = (a_u16_t)((value >> 8) ^ table[(value ^ *p++) & 0xFF]);
    }
    return value;
}

a_u32_t a_crc32l(a_u32_t const table[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u32_t value)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        value = (value >> 8) ^ table[(value ^ *p++) & 0xFF];
    }
    return value;
}

a_u64_t a_crc64l(a_u64_t const table[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u64_t value)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        value = (value >> 8) ^ table[(value ^ *p++) & 0xFF];
    }
    return value;
}

a_u16_t a_crc16h(a_u16_t const table[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u16_t value)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        value = (a_u16_t)((value << 8) ^ table[((value >> 8) ^ *p++) & 0xFF]);
    }
    return value;
}

a_u32_t a_crc32h(a_u32_t const table[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u32_t value)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        value = (value << 8) ^ table[((value >> 24) ^ *p++) & 0xFF];
    }
    return value;
}

a_u64_t a_crc64h(a_u64_t const table[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u64_t value)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        value = (value << 8) ^ table[((value >> 56) ^ *p++) & 0xFF];
    }
    return value;
}
