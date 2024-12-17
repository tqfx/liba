#define MAIN(x) linalg##x
#include "test.h"
#include "a/linalg.h"

static void test_mul(void)
{
    a_uint i;
    a_float z[3 * 3];
    a_float x[3 * 3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_float y[3 * 3] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    debug("X\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_FLOAT_PRI "g%c", x[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    debug("Y\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_FLOAT_PRI "g%c", y[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_linalg_mulmm(z, x, y, 3, 3, 3);

    debug("XY\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_FLOAT_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_linalg_mulTm(z, x, y, 3, 3, 3);

    debug("X'Y\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_FLOAT_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_linalg_mulmT(z, x, y, 3, 3, 3);

    debug("XY'\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_FLOAT_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");

    a_linalg_mulTT(z, x, y, 3, 3, 3);

    debug("X'Y'\t={");
    for (i = 0; i < 9; ++i)
    {
        debug("%" A_FLOAT_PRI "g%c", z[i], i < 8 ? ',' : '}');
    }
    debug("\n");
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    main_init(argc, argv, 1);
    test_mul();
    return 0;
}
