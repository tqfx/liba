#define MAIN(x) random##x
#include "test.h"
#include "a/random.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_random_lcg48 ctx = A_RANDOM_LCG48_INIT;
    a_random_lcg48_init(&ctx, 0);
    a_random_lcg48_seed(&ctx, A_NULL);
    for (int i = 0; i < 10; ++i)
    {
        debug("%i: %" A_PRI32 "i\n", i, a_random_lcg48i(&ctx, A_NULL));
    }
    for (int i = 0; i < 10; ++i)
    {
        debug("%i: %" A_PRI32 "u\n", i, a_random_lcg48u(&ctx, A_NULL));
    }
    for (int i = 0; i < 10; ++i)
    {
        debug("%i: %g\n", i, a_random_lcg48f(&ctx, A_NULL));
    }
    (void)argc;
    (void)argv;
    return 0;
}
