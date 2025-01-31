#define MAIN(x) mf##x
#include "test.h"
#include "a/mf.h"
#include <string.h>

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    int i;
    unsigned int e = A_MF_NUL;
    a_real params[6] = {0, 0, 0, 0, 0, 0};
    main_init(argc, argv, 1);
    if (argc > 1)
    {
        if (strstr(argv[1], "gauss2.")) { e = A_MF_GAUSS2; }
        else if (strstr(argv[1], "gauss.")) { e = A_MF_GAUSS; }
        else if (strstr(argv[1], "gbell.")) { e = A_MF_GBELL; }
        else if (strstr(argv[1], "dsig.")) { e = A_MF_DSIG; }
        else if (strstr(argv[1], "psig.")) { e = A_MF_PSIG; }
        else if (strstr(argv[1], "sig.")) { e = A_MF_SIG; }
        else if (strstr(argv[1], "trap.")) { e = A_MF_TRAP; }
        else if (strstr(argv[1], "tri.")) { e = A_MF_TRI; }
        else if (strstr(argv[1], "lins.")) { e = A_MF_LINS; }
        else if (strstr(argv[1], "linz.")) { e = A_MF_LINZ; }
        else if (strstr(argv[1], "s.")) { e = A_MF_S; }
        else if (strstr(argv[1], "z.")) { e = A_MF_Z; }
        else if (strstr(argv[1], "pi.")) { e = A_MF_PI; }
    }
    for (i = 2; i < argc && i < 8; ++i)
    {
        params[i - 2] = strtonum(argv[i], A_NULL);
    }
    if (e != A_MF_NUL)
    {
        a_real delta = (params[1] - params[0]) / A_REAL_C(100.0);
        for (i = 0; i < 100; ++i)
        {
            a_real x = params[0] + delta * a_real_c(i);
            a_real y = a_mf(e, x, params + 2);
            debug("%" A_REAL_PRI "g,%" A_REAL_PRI "g\n", x, y);
        }
    }
    else
    {
        TEST_BUG(a_mf_gauss(0, 1, 0) >= 1);
        TEST_BUG(a_mf_gauss2(0, 1, -1, +1, 1) >= 1);
        TEST_BUG(a_mf_gbell(0, 2, 4, 0) >= 1);
        TEST_BUG(a_mf_sig(0, 2, 0) >= 0.5);
        TEST_BUG(a_mf_dsig(0, 5, -2, +5, +2) > 0.99);
        TEST_BUG(a_mf_psig(0, 5, -2, -5, +2) > 0.99);
        TEST_BUG(a_mf_trap(0, -2, -1, +1, 2) >= 1);
        TEST_BUG(a_mf_tri(0, -1, 0, +1) >= 1);
        TEST_BUG(a_mf_lins(0, -1, 0) >= 1);
        TEST_BUG(a_mf_linz(0, 0, +1) >= 1);
        TEST_BUG(a_mf_s(0, -1, 0) >= 1);
        TEST_BUG(a_mf_z(0, 0, +1) >= 1);
        TEST_BUG(a_mf_pi(0, -2, -1, +1, +2) >= 1);
    }
    return 0;
}
