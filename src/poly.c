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
