#include "a/poly.h"

a_real_t *a_poly_inv(a_real_t *const a, a_size_t const n)
{
    for (a_real_t *l = a, *r = a + n - 1, *m = a + (n >> 1); l < m; ++l, --r)
    {
        a_swap(l, r, sizeof(a_real_t));
    }
    return a;
}

a_real_t a_poly_eval(a_real_t const *a, a_size_t const n, a_real_t const x)
{
    a_real_t y = 0;
    for (a_real_t const *p = --a + n; p > a; --p)
    {
        y = y * x + *p;
    }
    return y;
}

a_real_t *a_poly_evaln(a_real_t const *a, a_size_t const n, a_real_t const *ptr, a_size_t num, a_real_t *out)
{
    a_real_t x; /* when ptr == out, cache it */
    for (a_real_t const *p = --a + n; num--; ++ptr, ++out)
    {
        x = *ptr;
        *out = 0;
        for (a_real_t const *q = p; q > a; --q)
        {
            *out = *out * x + *q;
        }
    }
    return out;
}

a_real_t a_poly_evar(a_real_t const *a, a_size_t const n, a_real_t const x)
{
    a_real_t y = 0;
    for (a_real_t const *q = a + n; a < q; ++a)
    {
        y = y * x + *a;
    }
    return y;
}

a_real_t *a_poly_evarn(a_real_t const *const a, a_size_t const n, a_real_t const *ptr, a_size_t num, a_real_t *out)
{
    a_real_t x; /* when ptr == out, cache it */
    for (a_real_t const *q = a + n; num--; ++ptr, ++out)
    {
        x = *ptr;
        *out = 0;
        for (a_real_t const *p = a; p < q; ++p)
        {
            *out = *out * x + *p;
        }
    }
    return out;
}
