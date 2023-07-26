#include "a/host/a.h"

a_alloc_f a_alloc = a_alloc_;

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
