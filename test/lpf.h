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
    rand_seed = (rand_seed * 1103515245 + 12345) % 2147483648;
    return a_cast_s(long, rand_seed);
}

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    main_init(argc, argv, 1);
    a_lpf ctx = A_LPF_INIT(A_LPF_GEN(10, 0.01));
    a_lpf_init(&ctx, a_lpf_gen(10, A_FLOAT_C(0.01)));
    srand_(a_cast_s(unsigned long, time(A_NULL)));
    for (unsigned int i = 0; i < 100; ++i)
    {
        a_float noise = (a_float_c(rand_()) / a_float_c(RAND_MAX_) - A_FLOAT_C(0.5));
        a_float x = A_FLOAT_PI / 25 * a_float_c(i);
        a_float x0 = a_float_sin(x);
        a_float x1 = x0 + A_FLOAT_C(0.2) * noise;
        a_float x2 = a_lpf_iter(&ctx, x1);
        debug(A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f\n"), x, x0, x1, x2);
    }
    a_lpf_zero(&ctx);
#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_ASSERT_BUILD(std::is_pod<a_lpf>::value);
#endif /* __cplusplus */
    return 0;
}
