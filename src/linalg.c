#include "a/linalg.h"

void a_real_T1(a_uint n, a_real *A)
{
    a_uint r, c;
    a_real value;
    for (r = 0; r < n; ++r)
    {
        a_real *const Ar = A + (a_size)n * r;
        for (c = r + 1; c < n; ++c)
        {
            a_real *const Ac = A + (a_size)n * c;
            value = Ac[r];
            Ac[r] = Ar[c];
            Ar[c] = value;
        }
    }
}

void a_real_T2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict T)
{
    a_uint r, c;
    for (c = 0; c < n; ++c)
    {
        a_size const mc = (a_size)m * c;
        for (r = 0; r < m; ++r)
        {
            a_size const nr = (a_size)n * r;
            T[mc + r] = A[nr + c];
        }
    }
}

void a_real_eye1(a_uint n, a_real *E)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c < r; ++c)
        {
            *E++ = 0;
        }
        *E++ = 1;
        while (++c < n)
        {
            *E++ = 0;
        }
    }
}

void a_real_eye2(a_uint m, a_uint n, a_real *E)
{
    a_uint r, c;
    a_uint const M = A_MIN(m, n);
    for (r = 0; r < M; ++r)
    {
        for (c = 0; c < r; ++c)
        {
            *E++ = 0;
        }
        *E++ = 1;
        while (++c < n)
        {
            *E++ = 0;
        }
    }
    for (r = n; r < m; ++r)
    {
        for (c = 0; c < n; ++c)
        {
            *E++ = 0;
        }
    }
}

void a_real_tri1(a_uint n, a_real *L)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c <= r; ++c)
        {
            *L++ = 1;
        }
        for (; c < n; ++c)
        {
            *L++ = 0;
        }
    }
}

void a_real_tri2(a_uint m, a_uint n, a_real *L)
{
    a_uint r, c;
    a_uint const M = A_MIN(m, n);
    for (r = 0; r < M; ++r)
    {
        for (c = 0; c <= r; ++c)
        {
            *L++ = 1;
        }
        for (; c < n; ++c)
        {
            *L++ = 0;
        }
    }
    for (r = n; r < m; ++r)
    {
        for (c = 0; c < n; ++c)
        {
            *L++ = 1;
        }
    }
}

void a_real_diag(a_uint n, a_real const *__restrict a, a_real *__restrict A)
{
    a_uint r, c;
    a_size const N = (a_size)n + 1;
    for (r = 0; r < n; ++r) { A[N * r] = a[r]; }
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c < r; ++c)
        {
            A[c] = 0;
        }
        while (++c < n)
        {
            A[c] = 0;
        }
        A += n;
    }
}

void a_real_diag1(a_uint n, a_real const *__restrict A, a_real *__restrict a)
{
    a_uint i;
    a_size const N = (a_size)n + 1;
    for (i = 0; i < n; ++i) { a[i] = A[N * i]; }
}

void a_real_diag2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict a)
{
    a_uint i;
    a_uint const M = A_MIN(m, n);
    a_size const N = (a_size)n + 1;
    for (i = 0; i < M; ++i) { a[i] = A[N * i]; }
}

void a_real_triL(a_uint n, a_real const *__restrict A, a_real *__restrict L)
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

void a_real_triL1(a_uint n, a_real const *__restrict A, a_real *__restrict L)
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

void a_real_triL2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict L)
{
    a_uint r, c;
    a_uint const M = A_MIN(m, n);
    for (r = 0; r < M; ++r)
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
    for (r = n; r < m; ++r)
    {
        for (c = 0; c < n; ++c)
        {
            *L++ = *A++;
        }
    }
}

void a_real_triU(a_uint n, a_real const *__restrict A, a_real *__restrict U)
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

void a_real_triU1(a_uint n, a_real const *__restrict A, a_real *__restrict U)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        for (c = 0; c < r; ++c)
        {
            *U++ = 0;
        }
        *U++ = 1;
        while (++c < n)
        {
            *U++ = A[c];
        }
        A += n;
    }
}

void a_real_triU2(a_uint m, a_uint n, a_real const *__restrict A, a_real *__restrict U)
{
    a_uint r, c;
    a_uint const M = A_MIN(m, n);
    for (r = 0; r < M; ++r)
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
    for (r = n; r < m; ++r)
    {
        for (c = 0; c < n; ++c)
        {
            *U++ = 0;
        }
    }
}

void a_real_mulmm(a_uint row, a_uint c_r, a_uint col, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z)
{
    a_real const *x, *x_, *y, *y_;
    a_real *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (x = X; row--; Z = z)
    {
        x_ = x + c_r;
        for (y = Y; x < x_; ++x)
        {
            y_ = y + col;
            for (z = Z; y < y_; ++y)
            {
                *z++ += *x * *y;
            }
        }
    }
}

void a_real_mulTm(a_uint c_r, a_uint row, a_uint col, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z)
{
    a_real const *x, *x_, *y, *y_;
    a_real *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (x = X; c_r--; Y = y_)
    {
        x_ = x + row;
        y_ = Y + col;
        for (z = Z; x < x_; ++x)
        {
            for (y = Y; y < y_; ++y)
            {
                *z++ += *x * *y;
            }
        }
    }
}

void a_real_mulmT(a_uint row, a_uint col, a_uint c_r, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z)
{
    a_real const *x, *x_, *y, *y_ = Y + (a_size)col * c_r;
    a_real *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (z = Z; row--; X = x_)
    {
        x_ = X + c_r;
        for (y = Y; y < y_; ++z)
        {
            for (x = X; x < x_; ++x)
            {
                *z += *x * *y++;
            }
        }
    }
}

void a_real_mulTT(a_uint row, a_uint c_r, a_uint col, a_real const *__restrict X, a_real const *__restrict Y, a_real *__restrict Z)
{
    a_uint const n = c_r;
    a_real const *x, *x_, *y, *y_ = Y + (a_size)col * c_r;
    a_real *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (x = X; c_r--; ++Y)
    {
        x_ = x + row;
        for (z = Z; x < x_; ++x)
        {
            for (y = Y; y < y_; y += n)
            {
                *z++ += *x * *y;
            }
        }
    }
}
