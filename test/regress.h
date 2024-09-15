
#define MAIN(x) regress##x
#include "test.h"
#include "a/regress.h"

static void test_odm(int argc, char *argv[])
{
    a_size const n = a_cast_s(a_size, argc);
    a_float *p = a_new(a_float, A_NULL, n);
    for (a_size i = 0; i < n; ++i)
    {
        char *endptr;
        p[i] = strtonum(argv[i], &endptr);
    }

    a_float *odm = a_new(a_float, A_NULL, n);
    debug("{");
    for (a_size i = 0; i < n; ++i)
    {
        debug("%c" A_FLOAT_PRI("", "g"), i ? ',' : 0, p[i]);
    }
    debug("}:" A_FLOAT_PRI("", "g\n{"), a_regress_odm(odm, p, n));
    for (a_size i = 0; i < n; ++i)
    {
        debug("%c" A_FLOAT_PRI("", "g"), i ? ',' : 0, odm[i]);
    }
    debug("}\n");

    a_die(odm);
    a_die(p);
}

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    if (argc < 2)
    {
        test_odm(argc - 1, argv + 1);
        return 0;
    }

    switch (a_hash_bkdr(argv[1], 0))
    {
    case 0x001D4480: // odm
        test_odm(argc - 2, argv + 2);
        break;
    default:
        debug("odm\n");
    }

    return 0;
}
