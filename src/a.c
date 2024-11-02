#define LIBA_A_C
#include "a/a.h"
#include <string.h>
#include <stdlib.h>
#if defined(A_HAVE_MIMALLOC_H)
#include <mimalloc-override.h>
#endif /* A_HAVE_MIMALLOC_H */

void *a_copy(void *__restrict dst, void const *__restrict src, a_size siz)
{
    return memcpy(dst, src, siz);
}

void *a_move(void *dst, void const *src, a_size siz)
{
    return memmove(dst, src, siz);
}

void *a_fill(void *ptr, a_size siz, int val)
{
    return memset(ptr, val, siz);
}

void *a_zero(void *ptr, a_size siz)
{
    return memset(ptr, 0, siz);
}

void a_swap(void *lhs_, void *rhs_, a_size siz)
{
    a_byte byte;
    a_byte *lhs = (a_byte *)lhs_;
    a_byte *rhs = (a_byte *)rhs_;
    for (; siz; --siz, ++lhs, ++rhs)
    {
        byte = *lhs;
        *lhs = *rhs;
        *rhs = byte;
    }
}

A_ALLOC((*a_alloc), addr, size) = a_alloc_;
A_ALLOC(a_alloc_, addr, size)
{
    if (size)
    {
        if (addr)
        {
            return realloc(addr, size);
        }
        return malloc(size);
    }
    free(addr);
    return A_NULL;
}
