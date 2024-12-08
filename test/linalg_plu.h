#define MAIN(x) linalg_plu##x
#include "test.h"
#include "a/linalg.h"

static void show(a_float const *p, a_size n)
{
    a_size i, ii;
    for (i = 0; i < n; ++i)
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
    int sign;
    a_uint p[N];
    a_float b[N];
    a_float m[N * N];
    a_float a[N * N] = {4, 3, 6, 8, 7, 5, 2, 1, 9};
    main_init(argc, argv, 1);
    debug("A=\n");
    show(a, N);
    if (a_linalg_plu(a, N, p, &sign) == 0)
    {
        debug("SGN=%i\n", a_linalg_plu_sgndet(a, N, sign));
        debug("LN=%" A_FLOAT_PRI "g\n", a_linalg_plu_lndet(a, N));
        debug("D=%" A_FLOAT_PRI "g\n", a_linalg_plu_det(a, N, sign));
        a_linalg_plu_get_P(p, N, m);
        debug("P=\n");
        show(m, N);
        debug("LU=\n");
        show(a, N);
        a_linalg_plu_get_L(a, N, m);
        debug("L=\n");
        show(m, N);
        a_linalg_plu_get_U(a, N, m);
        debug("U=\n");
        show(m, N);
        a_linalg_plu_inv(a, N, p, b, m);
        debug("INV=\n");
        show(m, N);
        if (a_linalg_plu(m, N, p, &sign) == 0)
        {
            debug("SGN=%i\n", a_linalg_plu_sgndet(m, N, sign));
            debug("LN=%" A_FLOAT_PRI "g\n", a_linalg_plu_lndet(m, N));
            debug("D=%" A_FLOAT_PRI "g\n", a_linalg_plu_det(m, N, sign));
            a_linalg_plu_get_P(p, N, a);
            debug("P=\n");
            show(a, N);
            debug("LU=\n");
            show(m, N);
            a_linalg_plu_inv(m, N, p, b, a);
            debug("INV=\n");
            show(a, N);
        }
    }
    return 0;
}
