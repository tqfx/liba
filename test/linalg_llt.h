
#define MAIN(x) linalg_llt##x
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
    if (a_real_llt(N, a) == 0)
    {
        debug("LN=%" A_REAL_PRI "g\n", a_real_llt_lndet(N, a));
        debug("D=%" A_REAL_PRI "g\n", a_real_llt_det(N, a));
        a_real_llt_L(N, a, m);
        debug("L=\n");
        show(m, N, N);
        a_real_llt_inv(N, a, b, m);
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
            a_real_llt_solve(N, a, x);
        }
        a_real_T1(N, m);
        debug("I=\n");
        show(m, N, N);
        a_real_T2(N, N, m, a);
        debug("T=\n");
        show(a, N, N);
        if (a_real_llt(N, m) == 0)
        {
            debug("LN=%" A_REAL_PRI "g\n", a_real_llt_lndet(N, m));
            debug("D=%" A_REAL_PRI "g\n", a_real_llt_det(N, m));
            a_real_llt_L(N, m, a);
            debug("L=\n");
            show(a, N, N);
            a_real_llt_inv(N, m, b, a);
            debug("INV=\n");
            show(a, N, N);
        }
    }
    return 0;
}
