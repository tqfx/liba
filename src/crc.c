#include "a/crc.h"

void a_crc8l_init(a_u8_t ctx[A_CRC_SIZ], a_u8_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u8_t val = (a_u8_t)i;
        for (unsigned int j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

void a_crc16l_init(a_u16_t ctx[A_CRC_SIZ], a_u16_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u16_t val = (a_u16_t)i;
        for (unsigned int j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

void a_crc32l_init(a_u32_t ctx[A_CRC_SIZ], a_u32_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u32_t val = i;
        for (unsigned int j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

void a_crc64l_init(a_u64_t ctx[A_CRC_SIZ], a_u64_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u64_t val = i;
        for (unsigned int j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

void a_crc8h_init(a_u8_t ctx[A_CRC_SIZ], a_u8_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        unsigned int val = i;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U8_C(0x80) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = (a_u8_t)val;
    }
}

void a_crc16h_init(a_u16_t ctx[A_CRC_SIZ], a_u16_t const poly)
{
    for (unsigned int i = 0; i != A_CRC_SIZ; ++i)
    {
        unsigned int val = i << 8;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U16_C(0x8000) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = (a_u16_t)val;
    }
}

void a_crc32h_init(a_u32_t ctx[A_CRC_SIZ], a_u32_t const poly)
{
    for (a_u32_t i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u32_t val = i << 24;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U32_C(0x80000000) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = val;
    }
}

void a_crc64h_init(a_u64_t ctx[A_CRC_SIZ], a_u64_t const poly)
{
    for (a_u64_t i = 0; i != A_CRC_SIZ; ++i)
    {
        a_u64_t val = i << 56;
        for (unsigned int j = 8; j; --j)
        {
            if (A_U64_C(0x8000000000000000) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = val;
    }
}

a_u8_t a_crc8(a_u8_t const ctx[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u8_t val)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        val = ctx[val ^ *p++];
    }
    return val;
}

a_u16_t a_crc16l(a_u16_t const ctx[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u16_t val)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        val = (a_u16_t)((val >> 8) ^ ctx[(val ^ *p++) & 0xFF]);
    }
    return val;
}

a_u32_t a_crc32l(a_u32_t const ctx[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u32_t val)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        val = (val >> 8) ^ ctx[(val ^ *p++) & 0xFF];
    }
    return val;
}

a_u64_t a_crc64l(a_u64_t const ctx[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u64_t val)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        val = (val >> 8) ^ ctx[(val ^ *p++) & 0xFF];
    }
    return val;
}

a_u16_t a_crc16h(a_u16_t const ctx[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u16_t val)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        val = (a_u16_t)((val << 8) ^ ctx[((val >> 8) ^ *p++) & 0xFF]);
    }
    return val;
}

a_u32_t a_crc32h(a_u32_t const ctx[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u32_t val)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        val = (val << 8) ^ ctx[((val >> 24) ^ *p++) & 0xFF];
    }
    return val;
}

a_u64_t a_crc64h(a_u64_t const ctx[A_CRC_SIZ], void const *const pdata, a_size_t const nbyte, a_u64_t val)
{
    a_byte_t const *p = (a_byte_t const *)pdata;
    a_byte_t const *q = (a_byte_t const *)pdata + nbyte;
    while (p != q)
    {
        val = (val << 8) ^ ctx[((val >> 56) ^ *p++) & 0xFF];
    }
    return val;
}
