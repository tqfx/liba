#define MAIN_(x) A_CAST_2(x, _lpf)
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

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    test_init(argc, argv, 1);
    a_lpf_s ctx = A_LPF_INIT(A_LPF_GEN(10, 0.01));
    a_lpf_init(&ctx, a_lpf_gen(10, A_FLOAT_C(0.01)));
    srand_(a_cast_s(unsigned long, time(A_NULL)));
    for (unsigned int i = 0; i < 100; ++i)
    {
        a_float_t x = A_FLOAT_PI / 10 * a_float_c(i);
        a_float_t noise = (a_float_c(rand_()) / RAND_MAX_ - A_FLOAT_C(0.5));
        a_float_t x1 = a_float_sin(x) + A_FLOAT_C(0.2) * noise;
        a_float_t x2 = a_lpf_iter(&ctx, x1);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), x, x1, x2);
    }
    a_lpf_zero(&ctx);
    return 0;
}
