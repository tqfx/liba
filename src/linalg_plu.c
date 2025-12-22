#include "a/linalg.h"
#include "a/math.h"

int a_real_plu(a_uint n, a_real *A, a_uint *p, int *sign)
{
    a_uint i;
    *sign = 1;
    for (i = 0; i < n; ++i) { p[i] = i; }
    for (i = 0; i < n; ++i)
    {
        a_real *const Ai = A + (a_size)n * i;
        a_uint max_i = i, r, c;
        a_real max_x = Ai[i];
        a_real abs_x = a_real_abs(max_x);
        for (r = i + 1; r < n; ++r)
        {
            a_real const max_r = A[(a_size)n * r + i];
            a_real const abs_r = a_real_abs(max_r);
            if (abs_r > abs_x)
            {
                abs_x = abs_r;
                max_x = max_r;
                max_i = r;
            }
        }
        if (abs_x < A_REAL_MIN) { return A_FAILURE; }
        if (max_i != i)
        {
            a_uint u = p[i];
            p[i] = p[max_i];
            p[max_i] = u;
            *sign = -*sign;
            a_real_swap(n, Ai, A + (a_size)n * max_i);
        }
        for (r = i + 1; r < n; ++r)
        {
            a_real *const Ar = A + (a_size)n * r;
            a_real const x = Ar[i] / max_x;
            for (c = i + 1; c < n; ++c)
            {
                Ar[c] -= Ai[c] * x;
            }
            Ar[i] = x;
        }
    }
    return A_SUCCESS;
}

void a_real_plu_P(a_uint n, a_uint const *__restrict p, a_real *__restrict P)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        a_uint const i = p[r];
        for (c = 0; c < n; ++c)
        {
            *P++ = (c == i);
        }
    }
}

void a_real_plu_P_(a_uint n, a_uint const *__restrict p, a_real *__restrict P)
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

void a_real_plu_L(a_uint n, a_real const *__restrict A, a_real *__restrict L)
{
    a_real_triL1(n, A, L);
}

void a_real_plu_U(a_uint n, a_real const *__restrict A, a_real *__restrict U)
{
    a_real_triU(n, A, U);
}

void a_real_plu_apply(a_uint n, a_uint const *__restrict p, a_real const *__restrict b, a_real *__restrict Pb)
{
    a_uint i;
    for (i = 0; i < n; ++i) { Pb[i] = b[p[i]]; }
}

void a_real_plu_lower(a_uint n, a_real const *L, a_real *y)
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

void a_real_plu_lower_(a_uint n, a_real const *L, a_real *y)
{
    a_uint r, c; /* Ly = Pb */
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

void a_real_plu_upper(a_uint n, a_real const *U, a_real *x)
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

void a_real_plu_upper_(a_uint n, a_real const *U, a_real *x)
{
    a_uint r, c; /* Ux = y */
    for (r = n; r;)
    {
        a_real const *const Ur = U + (a_size)n * --r;
        a_real *const xr = x + (a_size)n * r;
        for (c = r + 1; c < n; ++c)
        {
            *xr -= Ur[c] * x[(a_size)n * c];
        }
        *xr /= Ur[r];
    }
}

void a_real_plu_solve(a_uint n, a_real const *A, a_uint const *p, a_real const *b, a_real *x)
{
    a_real_plu_apply(n, p, b, x);
    a_real_plu_lower(n, A, x);
    a_real_plu_upper(n, A, x);
}

void a_real_plu_inv(a_uint n, a_real const *A, a_uint const *p, a_real *b, a_real *oI)
{
    a_uint r, c;
    a_real_plu_P(n, p, oI);
    for (c = 0; c < n; ++c, ++oI)
    {
        for (r = 0; r < n; ++r)
        {
            b[r] = oI[(a_size)n * r];
        }
        a_real_plu_lower(n, A, b);
        a_real_plu_upper(n, A, b);
        for (r = 0; r < n; ++r)
        {
            oI[(a_size)n * r] = b[r];
        }
    }
}

void a_real_plu_inv_(a_uint n, a_real const *A, a_uint const *p, a_real *oI)
{
    a_uint i;
    a_real_plu_P(n, p, oI);
    for (i = 0; i < n; ++i, ++oI)
    {
        a_real_plu_lower_(n, A, oI);
        a_real_plu_upper_(n, A, oI);
    }
}

a_real a_real_plu_det(a_uint n, a_real const *A, int sign)
{
    a_uint i;
    a_real r = (a_real)sign;
    for (i = 0; i < n; ++i)
    {
        r *= A[i];
        A += n;
    }
    return r;
}

a_real a_real_plu_lndet(a_uint n, a_real const *A)
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

int a_real_plu_sgndet(a_uint n, a_real const *A, int sign)
{
    a_uint i;
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
