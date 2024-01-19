#include "a/poly.h"

a_float *a_poly_swap(a_float *a, a_size n)
{
    a_float *l = a, *r = a + n;
    for (a_float x; l < --r; ++l)
    {
        x = *l;
        *l = *r;
        *r = x;
    }
    return a;
}

a_float a_poly_eval(a_float const *a, a_size n, a_float x)
{
    a_float const *p = a + n;
    a_float y = n ? *--p : 0;
    while (p > a)
    {
        y = y * x + *--p;
    }
    return y;
}

a_float *a_poly_evaln(a_float const *a, a_size n, a_float const *ptr, a_size num, a_float *out)
{
    a_float const *q = a + n;
    for (; num; --num, ++ptr, ++out)
    {
        a_float const *p = q;
        a_float const x = *ptr;
        for (*out = n ? *--p : 0; p > a;)
        {
            *out = *out * x + *--p;
        }
    }
    return out;
}

a_float a_poly_evar(a_float const *a, a_size n, a_float x)
{
    a_float const *q = a + n;
    a_float y = n ? *a : 0;
    while (++a < q)
    {
        y = y * x + *a;
    }
    return y;
}

a_float *a_poly_evarn(a_float const *a, a_size n, a_float const *ptr, a_size num, a_float *out)
{
    a_float const *q = a + n;
    for (; num; --num, ++ptr, ++out)
    {
        a_float const *p = a;
        a_float const x = *ptr;
        for (*out = n ? *p : 0; ++p < q;)
        {
            *out = *out * x + *p;
        }
    }
    return out;
}
