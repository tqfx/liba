#include "a/linalg.h"
#include "a/math.h"

int a_linalg_cho(a_float *A, a_uint n)
{
    a_uint r, c, i;
    for (r = 0; r < n; ++r)
    {
        a_float *const Ar = A + (a_size)n * r;
        for (c = 0; c < r; ++c)
        {
            a_float *const Ac = A + (a_size)n * c;
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
        if (Ar[r] < A_FLOAT_MIN) { return ~0; }
        Ar[r] = a_float_sqrt(Ar[r]);
    }
    return 0;
}

void a_linalg_cho_get_L(a_float const *A, a_uint n, a_float *L)
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

void a_linalg_cho_lower(a_float const *L, a_uint n, a_float *y)
{
    a_uint r, c; /* Ly = b */
    for (r = 0; r < n; ++r)
    {
        a_float const *const Lr = L + (a_size)n * r;
        for (c = 0; c < r; ++c)
        {
            y[r] -= Lr[c] * y[c];
        }
        y[r] /= Lr[r];
    }
}

void a_linalg_cho_upper(a_float const *L, a_uint n, a_float *x)
{
    a_uint r, c; /* L^T x = y */
    for (c = n; c;)
    {
        a_float const *Lc = L + ((a_size)n + 1) * --c;
        a_float const Lcc = *Lc;
        for (r = c + 1; r < n; ++r)
        {
            Lc += n;
            x[c] -= *Lc * x[r];
        }
        x[c] /= Lcc;
    }
}

void a_linalg_cho_solve(a_float const *A, a_uint n, a_float *x)
{
    a_linalg_cho_lower(A, n, x);
    a_linalg_cho_upper(A, n, x);
}

void a_linalg_cho_inv(a_float const *A, a_uint n, a_float *b, a_float *I)
{
    a_uint r, c, i;
    for (c = 0; c < n; ++c)
    {
        a_float *x = I + c;
        for (r = 0; r < n; ++r) { b[r] = 0; }
        b[c] = 1;
        for (r = c; r < n; ++r)
        {
            a_float const *const Ar = A + (a_size)n * r;
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
