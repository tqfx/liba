/*!
 @file convert.c
 @brief convert library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/convert.h"

#include <assert.h>
#include <ctype.h>

int a_xdigit(int x)
{
    int ret = ~0;
#if 0
    if ('9' >= x && x >= '0')
    {
        /* 0 ~ 9 */
        ret = x - '0';
    }
    else if ('F' >= x && x >= 'A')
    {
        /* A ~ F */
        ret = x - 'A' + 10;
    }
    else if ('f' >= x && x >= 'a')
    {
        /* a ~ f */
        ret = x - 'a' + 10;
    }
#else
    switch (x)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        /* 0 ~ 9 */
        ret = x - '0';
    }
    break;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    {
        /* A ~ F */
        ret = x - 'A' + 10;
    }
    break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    {
        /* a ~ f */
        ret = x - 'a' + 10;
    }
    break;
    default:
        break;
    }
#endif
    return ret;
}

#if __has_warning("-Wdisabled-macro-expansion")
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"
#endif /* __has_warning */

#undef A_TO
#define A_TO(func, to)                                     \
    void *func(const void *pdata, size_t nbyte, void *out) \
    {                                                      \
        assert(!nbyte || pdata);                           \
        const char *p = (const char *)pdata;               \
        if (out || ((void)(out = malloc(nbyte + 1)), out)) \
        {                                                  \
            char *o = (char *)out;                         \
            pdata = (const void *)(p + nbyte);             \
            for (; p != pdata; ++p)                        \
            {                                              \
                *o++ = (char)to(*p);                       \
            }                                              \
            *o = 0;                                        \
        }                                                  \
        return out;                                        \
    }
A_TO(a_lower, tolower)
A_TO(a_upper, toupper)
#undef A_TO

void *a_digest(const void *pdata, size_t nbyte, unsigned int cases, void *out)
{
    static const char hexits[A_DIGEST_ALL][0x10] = {
        /* clang-format off */
        {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
        },
        {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        },
        /* clang-format on */
    };

    assert(!nbyte || pdata);

    const char *hexit = hexits[cases % A_DIGEST_ALL];
    const unsigned char *p = (const unsigned char *)pdata;
    if (out || ((void)(out = malloc((nbyte << 1) + 1)), out))
    {
        char *o = (char *)out;
        pdata = (const void *)(p + nbyte);
        while (p != pdata)
        {
            *o++ = hexit[*p >> 0x4];
            *o++ = hexit[*p & 0x0F];
            ++p;
        }
        *o = 0;
    }

    return out;
}

void *a_digest_lower(const void *pdata, size_t nbyte, void *out)
{
    return a_digest(pdata, nbyte, A_DIGEST_LOWER, out);
}

void *a_digest_upper(const void *pdata, size_t nbyte, void *out)
{
    return a_digest(pdata, nbyte, A_DIGEST_UPPER, out);
}
