#define MAIN_(x) A_CAST_2(x, _main)
#include "test.h"

static int test(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    return 0;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s", A_FUNC);
    debug(" ok");
    putchar('\n');
    test(argc, argv);
    return 0;
}
