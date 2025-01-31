#define LIBA_POLY_C
#include "a/poly.h"

void a_poly_swap_(a_real *a, a_real *b)
{
    for (; a < --b; ++a)
    {
        a_real _c;
        _c = *a;
        *a = *b;
        *b = _c;
    }
}

a_real a_poly_eval_(a_real const *a, a_real const *b, a_real x)
{
    a_real y;
    for (y = *--b; b > a;)
    {
        y = y * x + *--b;
    }
    return y;
}

a_real a_poly_evar_(a_real const *a, a_real const *b, a_real x)
{
    a_real y;
    for (y = *a; ++a < b;)
    {
        y = y * x + *a;
    }
    return y;
}
