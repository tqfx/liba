#include "a/linalg.h"
#include "a/math.h"

int a_real_ldl(a_uint n, a_real *A)
{
    a_uint c, r, i;
    for (c = 0; c < n; ++c)
    {
        a_real *const Ac = A + (a_size)n * c;
        for (i = 0; i < c; ++i)
        {
            Ac[c] -= Ac[i] * Ac[i] * A[(a_size)n * i + i];
        }
        if (a_real_abs(Ac[c]) < A_REAL_MIN) { return ~0; }
        for (r = c + 1; r < n; ++r)
        {
            a_real *const Ar = A + (a_size)n * r;
            for (i = 0; i < c; ++i)
            {
                Ar[c] -= Ar[i] * Ac[i] * A[(a_size)n * i + i];
            }
            Ar[c] /= Ac[c];
        }
    }
    return 0;
}

void a_real_ldl_L(a_uint n, a_real const *__restrict A, a_real *__restrict L)
{
    a_real_triL1(n, A, L);
}

void a_real_ldl_D(a_uint n, a_real const *__restrict A, a_real *__restrict d)
{
    a_real_diag1(n, A, d);
}

void a_real_ldl_lower(a_uint n, a_real const *L, a_real *y)
{
    a_uint r, c; /* Ly = b */
    for (r = 0; r < n; ++r)
    {
        a_real const *const Lr = L + (a_size)n * r;
        for (c = 0; c < r; ++c)
        {
            y[r] -= Lr[c] * y[c];
        }
    }
}

void a_real_ldl_lower_(a_uint n, a_real const *L, a_real *y)
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
    }
}

void a_real_ldl_upper(a_uint n, a_real const *L, a_real *x)
{
    a_uint r, c; /* D L^T x = y */
    for (c = n; c;)
    {
        a_real const *Lc = L + ((a_size)n + 1) * --c;
        x[c] /= *Lc;
        for (r = c + 1; r < n; ++r)
        {
            Lc += n;
            x[c] -= *Lc * x[r];
        }
    }
}

void a_real_ldl_upper_(a_uint n, a_real const *L, a_real *x)
{
    a_uint r, c; /* D L^T x = y */
    for (c = n; c;)
    {
        a_real const *Lc = L + ((a_size)n + 1) * --c;
        a_real *const xc = x + (a_size)n * c;
        *xc /= *Lc;
        for (r = c + 1; r < n; ++r)
        {
            Lc += n;
            *xc -= *Lc * x[(a_size)n * r];
        }
    }
}

void a_real_ldl_solve(a_uint n, a_real const *A, a_real *x)
{
    a_real_ldl_lower(n, A, x);
    a_real_ldl_upper(n, A, x);
}

void a_real_ldl_inv(a_uint n, a_real const *A, a_real *b, a_real *I)
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
        }
        a_real_ldl_upper(n, A, b);
        for (r = 0; r < n; ++r)
        {
            I[(a_size)n * r] = b[r];
        }
    }
}

void a_real_ldl_inv_(a_uint n, a_real const *A, a_real *I)
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
        }
        a_real_ldl_upper_(n, A, I);
    }
}

a_real a_real_ldl_det(a_uint n, a_real const *A)
{
    a_uint i;
    a_real r = 1;
    for (i = 0; i < n; ++i)
    {
        r *= A[i];
        A += n;
    }
    return r;
}

a_real a_real_ldl_lndet(a_uint n, a_real const *A)
{
    a_uint i;
    a_real r = 0;
    for (i = 0; i < n; ++i)
    {
        r += a_real_log(a_real_abs(A[i]));
        A += n;
    }
    return r;
}

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

int a_real_ldl_sgndet(a_uint n, a_real const *A)
{
    a_uint i;
    int sign = 1;
    for (i = 0; i < n; ++i)
    {
        a_real const x = A[i];
        if (x < 0) { sign = -sign; }
        else if (x == 0)
        {
            sign = 0;
            break;
        }
        A += n;
    }
    return sign;
}
