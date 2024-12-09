#include "a/linalg.h"

void a_linalg_T1(a_float *A, a_uint n)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        a_float *Ar = A + (a_size)n * r;
        for (c = r + 1; c < n; ++c)
        {
            a_float *Ac = A + (a_size)n * c;
            a_float *const lhs = Ar + c;
            a_float *const rhs = Ac + r;
            a_float swap;
            swap = *lhs;
            *lhs = *rhs;
            *rhs = swap;
        }
    }
}

void a_linalg_T2(a_float const *__restrict A, a_uint m, a_uint n, a_float *__restrict T)
{
    a_uint r, c;
    for (r = 0; r < m; ++r)
    {
        a_float *Tr = T + r;
        for (c = 0; c < n; ++c)
        {
            *Tr = *A++;
            Tr += m;
        }
    }
}
