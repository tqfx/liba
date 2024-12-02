#define MAIN(x) hash##x
#include "test.h"
#include "a/hash.h"

static void test_hash_bkdr(int argc, char *argv[])
{
    int idx;
    for (idx = 1; idx < argc; ++idx)
    {
        debug("case 0x%08" A_PRI32 "X: // %s\n    break;\n", a_hash_bkdr(argv[idx], 0), argv[idx]);
    }
}

static void test_hash_sdbm(int argc, char *argv[])
{
    int idx;
    for (idx = 1; idx < argc; ++idx)
    {
        debug("case 0x%08" A_PRI32 "X: // %s\n    break;\n", a_hash_sdbm(argv[idx], 0), argv[idx]);
    }
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    if (argc < 2)
    {
        test_hash_bkdr(argc, argv);
        test_hash_sdbm(argc, argv);
        return 0;
    }
    switch (a_hash_bkdr(argv[1], 0))
    {
    case 0x0E0928A2: /* hash */
    case 0x0D3DEDB7: /* bkdr */
        test_hash_bkdr(argc - 1, argv + 1);
        break;
    case 0x0F833EB8: /* sdbm */
        test_hash_sdbm(argc - 1, argv + 1);
        break;
    default:
        debug("hash\n");
        debug("bkdr\n");
        debug("sdbm\n");
    }
    return 0;
}
