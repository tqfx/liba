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

#include "a/math.h"

void a_poly_xTx(a_uint m, a_real const *x, a_uint n, a_real *A)
{
    a_uint r, c, i;
    for (r = 0; r < n; ++r)
    {
        a_real *const Ar = A + (a_size)n * r;
        for (c = 0; c <= r; ++c)
        {
            a_real *const Ac = A + (a_size)n * c;
            a_real const d = (a_real)(r + c);
            a_real val = 0;
            for (i = 0; i < m; ++i)
            {
                val += a_real_pow(x[i], d);
            }
            Ac[r] = Ar[c] = val;
        }
    }
}

void a_poly_xTy(a_uint m, a_real const *x, a_real const *y, a_uint n, a_real *b)
{
    a_uint d, i;
    for (d = 0; d < n; ++d)
    {
        a_real val = 0;
        for (i = 0; i < m; ++i)
        {
            val += a_real_pow(x[i], (a_real)d) * y[i];
        }
        b[d] = val;
    }
}
