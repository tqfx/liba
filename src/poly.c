#include "a/poly.h"

a_float *a_poly_swap(a_float *const a, a_size const n)
{
    for (a_float m[1], *l = a, *r = a + n; l < --r; ++l)
    {
        *m = *l;
        *l = *r;
        *r = *m;
    }
    return a;
}

a_float a_poly_eval(a_float const *a, a_size const n, a_float const x)
{
    a_float y = 0;
    for (a_float const *p = --a + n; p > a; --p) { y = y * x + *p; }
    return y;
}

a_float *a_poly_evaln(a_float const *a, a_size const n, a_float const *ptr, a_size num, a_float *out)
{
    a_float x; /* when ptr == out, cache it */
    for (a_float const *p = --a + n; num; ++ptr, ++out, --num)
    {
        x = *ptr;
        *out = 0;
        for (a_float const *q = p; q > a; --q) { *out = *out * x + *q; }
    }
    return out;
}

a_float a_poly_evar(a_float const *a, a_size const n, a_float const x)
{
    a_float y = 0;
    for (a_float const *q = a + n; a < q; ++a) { y = y * x + *a; }
    return y;
}

a_float *a_poly_evarn(a_float const *const a, a_size const n, a_float const *ptr, a_size num, a_float *out)
{
    a_float x; /* when ptr == out, cache it */
    for (a_float const *q = a + n; num; ++ptr, ++out, --num)
    {
        x = *ptr;
        *out = 0;
        for (a_float const *p = a; p < q; ++p) { *out = *out * x + *p; }
    }
    return out;
}
