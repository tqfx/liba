#include "a/host/a.h"

static a_alloc_f a_alloc_ptr = a_alloc_;
a_alloc_f a_alloc_reg(a_alloc_f const alloc)
{
    a_alloc_f ptr = a_alloc_ptr;
    if (alloc)
    {
        a_alloc_ptr = alloc;
    }
    return ptr;
}

void *a_alloc(void *const addr, a_size_t const size)
{
    return a_alloc_ptr(addr, size);
}

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
