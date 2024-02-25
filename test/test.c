#define MAIN_(x) A_CAST_2(x, _test)
#include "test.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s", A_FUNC);
    debug(" ok");
    printf("\n");
    (void)argv;
    (void)argc;
    return 0;
}
