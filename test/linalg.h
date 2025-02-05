#define MAIN(x) linalg##x
#include "test.h"
#include "a/linalg.h"
#include "a/math.h"

static void test_mul(void)
{
    a_uint i;
    a_real z[3 * 3];
    a_real x[3 * 3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_real y[3 * 3] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    debug("X\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_REAL_PRI "g%c", x[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    debug("Y\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_REAL_PRI "g%c", y[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_real_mulmm(3, 3, 3, x, y, z);

    debug("XY\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_REAL_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_real_mulTm(3, 3, 3, x, y, z);

    debug("X'Y\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_REAL_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_real_mulmT(3, 3, 3, x, y, z);

    debug("XY'\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_REAL_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_real_mulTT(3, 3, 3, x, y, z);

    debug("X'Y'\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_REAL_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    debug("X.Y\t=%" A_REAL_PRI "g\n", a_real_dot(9, x, y));
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    main_init(argc, argv, 1);
    test_mul();
    return 0;
}
