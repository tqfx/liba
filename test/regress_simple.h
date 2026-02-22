#define MAIN(x) regress_simple##x
#include "test.h"
#include "a/regress_simple.h"
#include "a/rand.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    char *endptr;
    int x_n, y_n;
    a_real *x, *y;
    a_size i, n = 100;
    a_real a = A_REAL_C(0.7);
    a_real b = 12;
    a_rand_lcg48 lcg = A_RAND_LCG48_INIT;
    a_regress_simple ctx = A_REGRESS_SIMPLE_0();

    if (argc > 2) { a = a_str2num(argv[2], &endptr); }
    if (argc > 3) { b = a_str2num(argv[3], &endptr); }
    if (argc > 4) { n = strtoul(argv[4], &endptr, 0); }

    x = a_new(a_real, A_NULL, n);
    y = a_new(a_real, A_NULL, n);
    x_n = a_cast_s(int, n * 10);
    y_n = a_cast_s(int, n * 2);

    main_init(argc, argv, 1);
    for (i = 0; i < n; ++i)
    {
        x[i] = a_cast_s(a_real, a_rand_lcg48f(&lcg) * x_n);
        y[i] = a * x[i] + b + a_cast_s(a_real, a_rand_lcg48f(&lcg) * y_n) - a_cast_s(a_real, n);
    }

    a_regress_simple_init(&ctx, 0, 0);
    a_regress_simple_ols(&ctx, n, x, y);

    for (i = 0; i < n; ++i)
    {
        a_real u = a_cast_s(a_real, i * 10);
        a_real v = a_regress_simple_eval(&ctx, u);
        debug("%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f\n", u, v, x[i], y[i]);
    }

    a_regress_simple_zero(&ctx);

    a_die(x);
    a_die(y);

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_regress_simple>::value);
#endif /* __cplusplus */

    return 0;
}
