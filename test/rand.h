#define MAIN(x) rand##x
#include "test.h"
#include "a/rand.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
#if defined(__cplusplus)
    {
        a::rand_lcg48 ctx = A_RAND_LCG48_INIT;
        ctx.init(a_cast_r(a_iptr, &ctx));
        ctx.seed();
        ctx.i();
        ctx.u();
        ctx.f();
    }
#endif /* __cplusplus */
    a_size i, ii;
    a_real v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_rand_lcg48 ctx = A_RAND_LCG48_INIT;
    a_rand_lcg48_init(&ctx, a_cast_r(a_iptr, &ctx));
    a_rand_lcg48_seed(&ctx, A_NULL);
    for (i = 0; i < 4; ++i)
    {
        for (ii = 0; ii < 4; ++ii)
        {
            if (ii) { debug("\t"); }
            debug("%-8" A_PRI32 "i", a_rand_lcg48i(&ctx));
        }
        debug("\n");
    }
    for (i = 0; i < 4; ++i)
    {
        for (ii = 0; ii < 4; ++ii)
        {
            if (ii) { debug("\t"); }
            debug("%-8" A_PRI32 "u", a_rand_lcg48u(&ctx));
        }
        debug("\n");
    }
    for (i = 0; i < 4; ++i)
    {
        for (ii = 0; ii < 4; ++ii)
        {
            if (ii) { debug("\t"); }
            debug("%-8" A_REAL_PRI "g", a_rand_lcg48f(&ctx));
        }
        debug("\n");
    }
    a_rand_lcg48_shuf(&ctx, v, A_LEN(v), sizeof(*v));
    for (i = 0; i < A_LEN(v); ++i)
    {
        if (i) { debug(" "); }
        debug("%g", v[i]);
    }
    debug("\n");
    (void)argc;
    (void)argv;
    return 0;
}
