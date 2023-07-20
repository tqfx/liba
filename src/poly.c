#include "a/poly.h"

a_float_t *a_poly_swap(a_float_t *const a, a_size_t const n)
{
    for (a_float_t t[1], *l = a, *r = a + n - 1, *m = a + (n >> 1); l < m; ++l, --r)
    {
        *t = *l;
        *l = *r;
        *r = *t;
    }
    return a;
}

a_float_t a_poly_eval(a_float_t const *a, a_size_t const n, a_float_t const x)
{
    a_float_t y = 0;
    for (a_float_t const *p = --a + n; p > a; --p)
    {
        y = y * x + *p;
    }
    return y;
}

a_float_t *a_poly_evaln(a_float_t const *a, a_size_t const n, a_float_t const *ptr, a_size_t num, a_float_t *out)
{
    a_float_t x; /* when ptr == out, cache it */
    for (a_float_t const *p = --a + n; num--; ++ptr, ++out)
    {
        x = *ptr;
        *out = 0;
        for (a_float_t const *q = p; q > a; --q)
        {
            *out = *out * x + *q;
        }
    }
    return out;
}

a_float_t a_poly_evar(a_float_t const *a, a_size_t const n, a_float_t const x)
{
    a_float_t y = 0;
    for (a_float_t const *q = a + n; a < q; ++a)
    {
        y = y * x + *a;
    }
    return y;
}

a_float_t *a_poly_evarn(a_float_t const *const a, a_size_t const n, a_float_t const *ptr, a_size_t num, a_float_t *out)
{
    a_float_t x; /* when ptr == out, cache it */
    for (a_float_t const *q = a + n; num--; ++ptr, ++out)
    {
        x = *ptr;
        *out = 0;
        for (a_float_t const *p = a; p < q; ++p)
        {
            *out = *out * x + *p;
        }
    }
    return out;
}
