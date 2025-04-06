
#define MAIN(x) regress##x
#include "test.h"
#include "a/regress.h"

static void test_odm(int argc, char *argv[])
{
    a_real *p, *odm;
    a_size i, n = a_cast_s(a_size, argc);

    p = a_new(a_real, A_NULL, n);
    for (i = 0; i < n; ++i)
    {
        char *endptr = argv[i];
        p[i] = a_str2num(argv[i], &endptr);
    }

    odm = a_new(a_real, A_NULL, n);
    debug("{");
    for (i = 0; i < n; ++i)
    {
        debug("%c%" A_REAL_PRI "g", i ? ',' : 0, p[i]);
    }
    debug("}:%" A_REAL_PRI "g\n{", a_regress_odm(n, p, odm));
    for (i = 0; i < n; ++i)
    {
        debug("%c%" A_REAL_PRI "g", i ? ',' : 0, odm[i]);
    }
    debug("}\n");

    a_die(odm);
    a_die(p);
}

#include "a/hash.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    if (argc < 2)
    {
        test_odm(argc - 1, argv + 1);
        return 0;
    }

    switch (a_hash_bkdr(argv[1], 0))
    {
    case 0x001D4480: /* odm */
        test_odm(argc - 2, argv + 2);
        break;
    default:
        debug("odm\n");
    }

    return 0;
}
