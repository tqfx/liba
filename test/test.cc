#define MAIN(x) test##x
#include "test.h"

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s", A_FUNC);
    debug(" ok");
    printf("\n");
    (void)argv;
    (void)argc;
    return 0;
}
