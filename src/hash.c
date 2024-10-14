#include "a/hash.h"

a_u32 a_hash_bkdr(void const *str_, a_u32 val)
{
    a_byte const *str = (a_byte const *)str_;
    if (str)
    {
        for (; *str; ++str)
        {
            val = val * 131 + *str;
        }
    }
    return val;
}

a_u32 a_hash_bkdr_(void const *ptr_, a_size siz, a_u32 val)
{
    a_byte const *ptr = (a_byte const *)ptr_;
    for (; siz; --siz, ++ptr)
    {
        val = val * 131 + *ptr;
    }
    return val;
}

a_u32 a_hash_sdbm(void const *str_, a_u32 val)
{
    a_byte const *str = (a_byte const *)str_;
    if (str)
    {
        for (; *str; ++str)
        {
            val = val * 65599 + *str;
        }
    }
    return val;
}

a_u32 a_hash_sdbm_(void const *ptr_, a_size siz, a_u32 val)
{
    a_byte const *ptr = (a_byte const *)ptr_;
    for (; siz; --siz, ++ptr)
    {
        val = val * 65599 + *ptr;
    }
    return val;
}
