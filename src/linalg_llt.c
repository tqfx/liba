#include "a/linalg.h"
#include "a/math.h"

int a_real_llt(a_uint n, a_real *A)
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
        if (Ar[r] < A_REAL_MIN) { return A_FAILURE; }
        Ar[r] = a_real_sqrt(Ar[r]);
    }
    return A_SUCCESS;
}

void a_real_llt_L(a_uint n, a_real const *__restrict A, a_real *__restrict L)
{
    a_real_triL(n, A, L);
}

void a_real_llt_lower(a_uint n, a_real const *L, a_real *y)
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

void a_real_llt_lower_(a_uint n, a_real const *L, a_real *y)
{
    a_uint r, c; /* Ly = b */
    for (r = 0; r < n; ++r)
    {
        a_real const *const Lr = L + (a_size)n * r;
        a_real *const yr = y + (a_size)n * r;
        for (c = 0; c < r; ++c)
        {
            *yr -= Lr[c] * y[(a_size)n * c];
        }
        *yr /= Lr[r];
    }
}

void a_real_llt_upper(a_uint n, a_real const *L, a_real *x)
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

void a_real_llt_upper_(a_uint n, a_real const *L, a_real *x)
{
    a_uint r, c; /* L^T x = y */
    for (c = n; c;)
    {
        a_real const *Lc = L + ((a_size)n + 1) * --c;
        a_real const Lcc = *Lc;
        a_real *const xc = x + (a_size)n * c;
        for (r = c + 1; r < n; ++r)
        {
            Lc += n;
            *xc -= *Lc * x[(a_size)n * r];
        }
        *xc /= Lcc;
    }
}

void a_real_llt_solve(a_uint n, a_real const *A, a_real *x)
{
    a_real_llt_lower(n, A, x);
    a_real_llt_upper(n, A, x);
}

void a_real_llt_inv(a_uint n, a_real const *A, a_real *b, a_real *I)
{
    a_uint i, r, c;
    for (i = 0; i < n; ++i, ++I)
    {
        for (r = 0; r < n; ++r) { b[r] = 0; }
        b[i] = 1;
        for (r = i; r < n; ++r) /* Ly = b */
        {
            a_real const *const Ar = A + (a_size)n * r;
            for (c = i; c < r; ++c)
            {
                b[r] -= Ar[c] * b[c];
            }
            b[r] /= Ar[r];
        }
        a_real_llt_upper(n, A, b);
        for (r = 0; r < n; ++r)
        {
            I[(a_size)n * r] = b[r];
        }
    }
}

void a_real_llt_inv_(a_uint n, a_real const *A, a_real *I)
{
    a_uint i, r, c;
    for (i = 0; i < n; ++i, ++I)
    {
        for (r = 0; r < n; ++r)
        {
            I[(a_size)n * r] = (r == i);
        }
        for (r = i; r < n; ++r) /* Ly = b */
        {
            a_real const *const Ar = A + (a_size)n * r;
            a_real *const yr = I + (a_size)n * r;
            for (c = i; c < r; ++c)
            {
                *yr -= Ar[c] * I[(a_size)n * c];
            }
            *yr /= Ar[r];
        }
        a_real_llt_upper_(n, A, I);
    }
}

a_real a_real_llt_det(a_uint n, a_real const *A)
{
    a_uint i;
    a_real r = 1;
    for (i = 0; i < n; ++i)
    {
        r *= A[i];
        A += n;
    }
    return r * r;
}

a_real a_real_llt_lndet(a_uint n, a_real const *A)
{
    a_uint i;
    a_real r = 0;
    for (i = 0; i < n; ++i)
    {
        r += a_real_log(A[i]);
        A += n;
    }
    return r * 2;
}
