#define MAIN(x) lpf##x
#include "test.h"
#include "a/lpf.h"
#include <time.h>

#define RAND_MAX_ 2147483647
static unsigned long rand_seed = 1;
static void srand_(unsigned long seed)
{
    rand_seed = seed;
}
static long rand_(void)
{
    rand_seed = (rand_seed * 1103515245UL + 12345) % 2147483648UL;
    return a_cast_s(long, rand_seed);
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    unsigned int i;
    a_lpf ctx = A_LPF_1(A_LPF_GEN(10, 0.01));
    main_init(argc, argv, 1);
    a_lpf_init(&ctx, a_lpf_gen(10, A_REAL_C(0.01)));
    srand_(a_cast_s(unsigned long, time(A_NULL)));
    for (i = 0; i < 100; ++i)
    {
        a_real noise = (a_real_c(rand_()) / a_real_c(RAND_MAX_) - A_REAL_C(0.5));
        a_real x = A_REAL_PI / 25 * a_real_c(i);
        a_real x0 = a_real_sin(x);
        a_real x1 = x0 + A_REAL_C(0.2) * noise;
        a_real x2 = a_lpf_iter(&ctx, x1);
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n", x, x0, x1, x2);
    }
    a_lpf_zero(&ctx);
#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_lpf>::value);
#endif /* __cplusplus */
    return 0;
}
