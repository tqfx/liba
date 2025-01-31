#include "a/linalg.h"
#include "a/math.h"

int a_linalg_plu(a_real *A, a_uint n, a_uint *p, int *sign)
{
    a_uint r;
    *sign = 1;
    for (r = 0; r < n; ++r) { p[r] = r; }
    for (r = 0; r < n; ++r)
    {
        a_real *const Ar = A + (a_size)n * r;
        a_uint max_r = r, i, c;
        a_real max_x = Ar[r];
        a_real abs_x = a_real_abs(max_x);
        for (i = r + 1; i < n; ++i)
        {
            a_real const max_i = A[(a_size)n * i + r];
            a_real const abs_i = a_real_abs(max_i);
            if (abs_i > abs_x)
            {
                abs_x = abs_i;
                max_x = max_i;
                max_r = i;
            }
        }
        if (abs_x < A_REAL_MIN) { return ~0; }
        if (max_r != r)
        {
            a_uint u = p[r];
            p[r] = p[max_r];
            p[max_r] = u;
            *sign = -*sign;
            a_real_swap(Ar, A + (a_size)n * max_r, n);
        }
        for (i = r + 1; i < n; ++i)
        {
            a_real *const Ai = A + (a_size)n * i;
            a_real const x = Ai[r] / max_x;
            for (c = r + 1; c < n; ++c)
            {
                Ai[c] -= Ar[c] * x;
            }
            Ai[r] = x;
        }
    }
    return 0;
}

void a_linalg_plu_get_P(a_uint const *p, a_uint n, a_real *P)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c < n; ++c)
        {
            *P++ = (p[c] == r);
        }
    }
}

void a_linalg_plu_get_L(a_real const *A, a_uint n, a_real *L)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c < r; ++c)
        {
            *L++ = A[c];
        }
        *L++ = 1;
        while (++c < n)
        {
            *L++ = 0;
        }
        A += n;
    }
}

void a_linalg_plu_get_U(a_real const *A, a_uint n, a_real *U)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c < r; ++c)
        {
            *U++ = 0;
        }
        for (; c < n; ++c)
        {
            *U++ = A[c];
        }
        A += n;
    }
}

void a_linalg_plu_apply(a_uint const *p, a_uint n, a_real const *b, a_real *Pb)
{
    a_uint i;
    for (i = 0; i < n; ++i) { Pb[i] = b[p[i]]; }
}

void a_linalg_plu_lower(a_real const *L, a_uint n, a_real *y)
{
    a_uint r, c; /* Ly = Pb */
    for (r = 0; r < n; ++r)
    {
        a_real const *const Lr = L + (a_size)n * r;
        for (c = 0; c < r; ++c)
        {
            y[r] -= Lr[c] * y[c];
        }
    }
}

void a_linalg_plu_upper(a_real const *U, a_uint n, a_real *x)
{
    a_uint r, c; /* Ux = y */
    for (r = n; r;)
    {
        a_real const *const Ur = U + (a_size)n * --r;
        for (c = r + 1; c < n; ++c)
        {
            x[r] -= Ur[c] * x[c];
        }
        x[r] /= Ur[r];
    }
}

void a_linalg_plu_solve(a_real const *A, a_uint n, a_uint const *p, a_real const *b, a_real *x)
{
    a_linalg_plu_apply(p, n, b, x);
    a_linalg_plu_lower(A, n, x);
    a_linalg_plu_upper(A, n, x);
}

void a_linalg_plu_inv(a_real const *A, a_uint n, a_uint const *p, a_real *b, a_real *I)
{
    a_uint r, c;
    a_real *x = I;
    for (r = 0; r < n; ++r)
    {
        a_uint const u = p[r];
        for (c = 0; c < n; ++c)
        {
            *x++ = (c == u);
        }
    }
    for (c = 0; c < n; ++c)
    {
        x = I + c;
        for (r = 0; r < n; ++r)
        {
            b[r] = *x;
            x += n;
        }
        a_linalg_plu_lower(A, n, b);
        a_linalg_plu_upper(A, n, b);
        x = I + c;
        for (r = 0; r < n; ++r)
        {
            *x = b[r];
            x += n;
        }
    }
}

a_real a_linalg_plu_det(a_real const *A, a_uint n, int sign)
{
    a_uint i;
    a_real res = (a_real)sign;
    for (i = 0; i < n; ++i)
    {
        res *= A[i];
        A += n;
    }
    return res;
}

a_real a_linalg_plu_lndet(a_real const *A, a_uint n)
{
    a_uint i;
    a_real res = 0;
    for (i = 0; i < n; ++i)
    {
        res += a_real_log(a_real_abs(A[i]));
        A += n;
    }
    return res;
}

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

int a_linalg_plu_sgndet(a_real const *A, a_uint n, int sign)
{
    a_uint i;
    int res = sign;
    for (i = 0; i < n; ++i)
    {
        a_real const x = A[i];
        if (x < 0) { res = -res; }
        else if (x == 0)
        {
            res = 0;
            break;
        }
        A += n;
    }
    return res;
}
