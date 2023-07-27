#include "a/host/a.h"

void *(*a_alloc)(void *, a_size_t) = a_alloc_;

void *a_alloc_(void *const addr, a_size_t const size)
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
