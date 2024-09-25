#define MAIN(x) regress_simple##x
#include "test.h"
#include "a/regress_simple.h"
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
    srand_(a_cast_s(a_ulong, time(A_NULL)));
    main_init(argc, argv, 1);

    a_float a = A_FLOAT_C(0.7);
    a_float b = 12;
    a_size n = 100;
    char *endptr;

    if (argc > 2) { a = strtonum(argv[2], &endptr); }
    if (argc > 3) { b = strtonum(argv[3], &endptr); }
    if (argc > 4) { n = strtoul(argv[4], &endptr, 0); }

    a_float *x = a_new(a_float, A_NULL, n);
    a_float *y = a_new(a_float, A_NULL, n);
    long x_n = a_cast_s(long, n) * 10;
    long y_n = a_cast_s(long, n) * 2;

    for (a_size i = 0; i < n; ++i)
    {
        x[i] = a_cast_s(a_float, rand_() % x_n);
        y[i] = a * x[i] + b + a_cast_s(a_float, rand_() % y_n) - a_cast_s(a_float, n);
    }

    a_regress_simple ctx;
    a_regress_simple_init(&ctx, 0, 0);
    a_regress_simple_ols(&ctx, n, x, y);

    for (unsigned int i = 0; i < n; ++i)
    {
        a_float u = a_cast_s(a_float, i * 10);
        a_float v = a_regress_simple_eval(&ctx, u);
        debug(A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,")
                  A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f\n"),
              u, v, x[i], y[i]);
    }

    a_regress_simple_zero(&ctx);

    a_die(x);
    a_die(y);

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_regress_simple>::value);
#endif /* __cplusplus */

    return 0;
}
