#include "a/linalg.h"
#include "a/math.h"

int a_linalg_cho(a_real *A, a_uint n)
{
    a_uint r, c, i;
    for (r = 0; r < n; ++r)
    {
        a_real *const Ar = A + (a_size)n * r;
        for (c = 0; c < r; ++c)
        {
            a_real *const Ac = A + (a_size)n * c;
            for (i = 0; i < c; ++i)
            {
                Ar[c] -= Ar[i] * Ac[i];
            }
            Ar[c] /= Ac[c];
        }
        for (i = 0; i < r; ++i)
        {
            Ar[r] -= Ar[i] * Ar[i];
        }
        if (Ar[r] < A_REAL_MIN) { return ~0; }
        Ar[r] = a_real_sqrt(Ar[r]);
    }
    return 0;
}

void a_linalg_cho_get_L(a_real const *A, a_uint n, a_real *L)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c <= r; ++c)
        {
            *L++ = A[c];
        }
        for (; c < n; ++c)
        {
            *L++ = 0;
        }
        A += n;
    }
}

void a_linalg_cho_lower(a_real const *L, a_uint n, a_real *y)
{
    a_uint r, c; /* Ly = b */
    for (r = 0; r < n; ++r)
    {
        a_real const *const Lr = L + (a_size)n * r;
        for (c = 0; c < r; ++c)
        {
            y[r] -= Lr[c] * y[c];
        }
        y[r] /= Lr[r];
    }
}

void a_linalg_cho_upper(a_real const *L, a_uint n, a_real *x)
{
    a_uint r, c; /* L^T x = y */
    for (c = n; c;)
    {
        a_real const *Lc = L + ((a_size)n + 1) * --c;
        a_real const Lcc = *Lc;
        for (r = c + 1; r < n; ++r)
        {
            Lc += n;
            x[c] -= *Lc * x[r];
        }
        x[c] /= Lcc;
    }
}

void a_linalg_cho_solve(a_real const *A, a_uint n, a_real *x)
{
    a_linalg_cho_lower(A, n, x);
    a_linalg_cho_upper(A, n, x);
}

void a_linalg_cho_inv(a_real const *A, a_uint n, a_real *b, a_real *I)
{
    a_uint r, c, i;
    for (c = 0; c < n; ++c)
    {
        a_real *x = I + c;
        for (r = 0; r < n; ++r) { b[r] = 0; }
        b[c] = 1;
        for (r = c; r < n; ++r)
        {
            a_real const *const Ar = A + (a_size)n * r;
            for (i = c; i < r; ++i)
            {
                b[r] -= Ar[i] * b[i];
            }
            b[r] /= Ar[r];
        }
        a_linalg_cho_upper(A, n, b);
        for (r = 0; r < n; ++r)
        {
            *x = b[r];
            x += n;
        }
    }
}
