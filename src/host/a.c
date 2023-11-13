#include "a/host/a.h"

A_ALLOC((*a_alloc), , ) = a_alloc_;
A_ALLOC(a_alloc_, const addr, const size)
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
