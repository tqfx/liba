#define LIBA_POLY_C
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

a_float a_poly_eval_(a_float const *a, a_float const *b, a_float x)
{
    a_float y;
    for (y = *--b; b > a;)
    {
        y = y * x + *--b;
    }
    return y;
}

a_float a_poly_evar_(a_float const *a, a_float const *b, a_float x)
{
    a_float y;
    for (y = *a; ++a < b;)
    {
        y = y * x + *a;
    }
    return y;
}

a_float *a_poly_evaln(a_float const *a, a_size n, a_float const *ptr, a_size num, a_float *out)
{
    if (n)
    {
        for (a_float const *b = a + n; num; --num, ++ptr, ++out)
        {
            *out = a_poly_eval_(a, b, *ptr);
        }
    }
    else
    {
        for (; num; --num, ++out) { *out = 0; }
    }
    return out;
}

a_float *a_poly_evarn(a_float const *a, a_size n, a_float const *ptr, a_size num, a_float *out)
{
    if (n)
    {
        for (a_float const *b = a + n; num; --num, ++ptr, ++out)
        {
            *out = a_poly_evar_(a, b, *ptr);
        }
    }
    else
    {
        for (; num; --num, ++out) { *out = 0; }
    }
    return out;
}
