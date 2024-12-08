#include "a/linalg.h"
#include "a/math.h"

int a_linalg_plu(a_float *A, a_uint n, a_uint *p, int *sign)
{
    a_uint r;
    *sign = 1;
    for (r = 0; r < n; ++r) { p[r] = r; }
    for (r = 0; r < n; ++r)
    {
        a_float *const Ar = A + (a_size)n * r;
        a_uint max_r = r, i, ii;
        a_float max_x = Ar[r];
        a_float abs_x = a_float_abs(max_x);
        for (i = r + 1; i < n; ++i)
        {
            a_float const max_i = A[n * i + r];
            a_float const abs_i = a_float_abs(max_i);
            if (abs_i > abs_x)
            {
                abs_x = abs_i;
                max_x = max_i;
                max_r = i;
            }
        }
        if (abs_x < A_FLOAT_MIN) { return ~0; }
        if (max_r != r)
        {
            a_uint u = p[r];
            p[r] = p[max_r];
            p[max_r] = u;
            a_float_swap(Ar, A + (a_size)n * max_r, n);
            *sign = -*sign;
        }
        for (i = r + 1; i < n; ++i)
        {
            a_float *const Ai = A + (a_size)n * i;
            a_float const x = Ai[r] / max_x;
            for (ii = r + 1; ii < n; ++ii)
            {
                Ai[ii] -= Ar[ii] * x;
            }
            Ai[r] = x;
        }
    }
    return 0;
}

void a_linalg_plu_get_P(a_uint const *p, a_uint n, a_float *P)
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

void a_linalg_plu_get_L(a_float const *A, a_uint n, a_float *L)
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

void a_linalg_plu_get_U(a_float const *A, a_uint n, a_float *U)
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

void a_linalg_plu_apply(a_uint const *p, a_uint n, a_float const *b, a_float *Pb)
{
    a_uint i;
    for (i = 0; i < n; ++i) { Pb[i] = b[p[i]]; }
}

void a_linalg_plu_lower(a_float const *L, a_uint n, a_float *y)
{
    a_uint i, ii; /* Ly=Pb */
    for (i = 0; i < n; ++i)
    {
        a_float const *const Li = L + (a_size)n * i;
        for (ii = 0; ii < i; ++ii)
        {
            y[i] -= Li[ii] * y[ii];
        }
    }
}

void a_linalg_plu_upper(a_float const *U, a_uint n, a_float *x)
{
    a_uint i, ii; /* Ux=y */
    for (i = n; i;)
    {
        a_float const *const Ui = U + (a_size)n * --i;
        for (ii = i + 1; ii < n; ++ii)
        {
            x[i] -= Ui[ii] * x[ii];
        }
        x[i] /= Ui[i];
    }
}

void a_linalg_plu_solve(a_float const *A, a_uint n, a_uint const *p, a_float const *b, a_float *x)
{
    a_linalg_plu_apply(p, n, b, x);
    a_linalg_plu_lower(A, n, x);
    a_linalg_plu_upper(A, n, x);
}

void a_linalg_plu_inv(a_float const *A, a_uint n, a_uint const *p, a_float *b, a_float *I)
{
    a_uint r, c;
    a_float *x = I;
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

a_float a_linalg_plu_det(a_float const *A, a_uint n, int sign)
{
    a_uint i;
    a_float res = (a_float)sign;
    for (i = 0; i < n; ++i)
    {
        res *= A[i];
        A += n;
    }
    return res;
}

a_float a_linalg_plu_lndet(a_float const *A, a_uint n)
{
    a_uint i;
    a_float res = 0;
    for (i = 0; i < n; ++i)
    {
        res += a_float_log(a_float_abs(A[i]));
        A += n;
    }
    return res;
}

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

int a_linalg_plu_sgndet(a_float const *A, a_uint n, int sign)
{
    a_uint i;
    int res = sign;
    for (i = 0; i < n; ++i)
    {
        a_float const x = A[i];
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
