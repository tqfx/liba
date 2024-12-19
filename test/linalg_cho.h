
#define MAIN(x) linalg_cho##x
#include "test.h"
#include "a/linalg.h"

static void show(a_float const *p, a_size m, a_size n)
{
    a_size i, ii;
    for (i = 0; i < m; ++i)
    {
        debug("\t");
        for (ii = 0; ii < n; ++ii)
        {
            a_float const x = *p++;
            if (ii) { debug(","); }
            debug("%+.6" A_FLOAT_PRI "f", x);
        }
        debug("\n");
    }
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
#define N 3
    int i, ii;
    a_float b[N];
    a_float m[N * N];
    a_float a[N * N] = {4, 12, -16, 12, 37, -43, -16, -43, 98};
    main_init(argc, argv, 1);
    debug("A=\n");
    show(a, N, N);
    if (a_linalg_cho(a, N) == 0)
    {
        a_linalg_cho_get_L(a, N, m);
        debug("L=\n");
        show(m, N, N);
        a_linalg_cho_inv(a, N, b, m);
        debug("INV=\n");
        show(m, N, N);
        for (i = 0; i < N; ++i)
        {
            a_float *x = m + a_size_c(i) * N;
            for (ii = 0; ii < N; ++ii)
            {
                x[ii] = 0;
            }
            x[i] = 1;
            a_linalg_cho_solve(a, N, x);
        }
        a_linalg_T1(m, N);
        debug("I=\n");
        show(m, N, N);
        a_linalg_T2(a, m, N, N);
        debug("T=\n");
        show(a, N, N);
        if (a_linalg_cho(m, N) == 0)
        {
            a_linalg_cho_get_L(m, N, a);
            debug("L=\n");
            show(a, N, N);
            a_linalg_cho_inv(m, N, b, a);
            debug("INV=\n");
            show(a, N, N);
        }
    }
    return 0;
}
