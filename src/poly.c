#define LIBA_POLY_C
#include "a/poly.h"

void a_poly_swap_(a_float *a, a_float *b)
{
    for (; a < --b; ++a)
    {
        a_float _c;
        _c = *a;
        *a = *b;
        *b = _c;
    }
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
