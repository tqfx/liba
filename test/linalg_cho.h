
#define MAIN(x) linalg_cho##x
#include "test.h"
#include "a/linalg.h"

static void show(a_real const *p, a_size m, a_size n)
{
    a_size r, c;
    for (r = 0; r < m; ++r)
    {
        debug("\t");
        for (c = 0; c < n; ++c)
        {
            a_real const x = *p++;
            if (c) { debug(","); }
            debug("%+.6" A_REAL_PRI "f", x);
        }
        debug("\n");
    }
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
#define N 3
    int r, c;
    a_real b[N];
    a_real m[N * N];
    a_real a[N * N] = {4, 12, -16, 12, 37, -43, -16, -43, 98};
    main_init(argc, argv, 1);
    debug("A=\n");
    show(a, N, N);
    if (a_linalg_cho(N, a) == 0)
    {
        a_linalg_cho_get_L(N, a, m);
        debug("L=\n");
        show(m, N, N);
        a_linalg_cho_inv(N, a, b, m);
        debug("INV=\n");
        show(m, N, N);
        for (r = 0; r < N; ++r)
        {
            a_real *x = m + a_size_c(r) * N;
            for (c = 0; c < N; ++c)
            {
                x[c] = 0;
            }
            x[r] = 1;
            a_linalg_cho_solve(N, a, x);
        }
        a_linalg_T1(N, m);
        debug("I=\n");
        show(m, N, N);
        a_linalg_T2(N, N, m, a);
        debug("T=\n");
        show(a, N, N);
        if (a_linalg_cho(N, m) == 0)
        {
            a_linalg_cho_get_L(N, m, a);
            debug("L=\n");
            show(a, N, N);
            a_linalg_cho_inv(N, m, b, a);
            debug("INV=\n");
            show(a, N, N);
        }
    }
    return 0;
}
