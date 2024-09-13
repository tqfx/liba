#define MAIN(x) regress_linear##x
#include "test.h"
#include "a/regress_linear.h"
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

static void main_1(int m, a_float a, a_float b, a_size n, a_float alpha, a_float threshold)
{
    a_float *z = a_new(a_float, A_NULL, n);
    a_float *y = a_new(a_float, A_NULL, n);
    a_float *x = a_new(a_float, A_NULL, n);
    long y_n = a_cast_s(long, n) * 2;
    long x_n = a_cast_s(long, n) * 10;

    for (a_size i = 0; i < n; ++i)
    {
        x[i] = a_cast_s(a_float, rand_() % x_n);
        y[i] = a * x[i] + b + a_cast_s(a_float, rand_() % y_n) - a_cast_s(a_float, n);
    }

    a_float coef = 1, u, v;

    a_regress_linear ctx;
    a_regress_linear_init(&ctx, &coef, 1, 1);
    a_regress_linear_zero(&ctx);

    if (m == 's')
    {
        a_float r = a_regress_linear_sdg1(&ctx, alpha, y, x, n, z);
        for (;;)
        {
            a_float s = a_regress_linear_sdg1(&ctx, alpha, y, x, n, z);
            if (s <= r && r - s < threshold) { break; }
            if (r <= s && s - r < threshold) { break; }
            r = s;
        }
    }
    else
    {
        a_float r = a_regress_linear_bdg1(&ctx, alpha, y, x, n, z);
        for (;;)
        {
            a_float s = a_regress_linear_bdg1(&ctx, alpha, y, x, n, z);
            if (s <= r && r - s < threshold) { break; }
            if (r <= s && s - r < threshold) { break; }
            r = s;
        }
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        u = a_cast_s(a_float, i * 10);
        v = a_regress_linear_eval(&ctx, &u);
        debug(A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,")
                  A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f\n"),
              u, v, x[i], y[i], z[i]);
    }

    a_regress_linear_zero(&ctx);

    a_die(x);
    a_die(y);
    a_die(z);
}

static void main_2(int m, a_float a, a_float b, a_float c, a_size n, a_float alpha, a_float threshold)
{
    a_float *z = a_new(a_float, A_NULL, n);
    a_float *y = a_new(a_float, A_NULL, n);
    a_float *x = a_new(a_float, A_NULL, n * 2);
    long y_n = a_cast_s(long, n) * 2;
    long x_n = a_cast_s(long, n) * 10;

    for (a_size i = 0; i < n; ++i)
    {
        x[i * 2 + 0] = a_cast_s(a_float, rand_() % x_n);
        x[i * 2 + 1] = a_cast_s(a_float, rand_() % x_n);
        y[i] = a * x[i * 2 + 0] + b * x[i * 2 + 1] + c +
               a_cast_s(a_float, rand_() % y_n) - a_cast_s(a_float, n);
    }

    a_float coef[2] = {1, 1}, u[2], v;

    a_regress_linear ctx;
    a_regress_linear_init(&ctx, coef, 2, 1);
    a_regress_linear_zero(&ctx);

    if (m == 's')
    {
        a_float r = a_regress_linear_sdg1(&ctx, alpha, y, x, n, z);
        for (;;)
        {
            a_float s = a_regress_linear_sdg1(&ctx, alpha, y, x, n, z);
            if (s <= r && r - s < threshold) { break; }
            if (r <= s && s - r < threshold) { break; }
            r = s;
        }
    }
    else
    {
        a_float r = a_regress_linear_bdg1(&ctx, alpha, y, x, n, z);
        for (;;)
        {
            a_float s = a_regress_linear_bdg1(&ctx, alpha, y, x, n, z);
            if (s <= r && r - s < threshold) { break; }
            if (r <= s && s - r < threshold) { break; }
            r = s;
        }
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        u[0] = a_cast_s(a_float, i * 10);
        for (unsigned int j = 0; j < n; ++j)
        {
            u[1] = a_cast_s(a_float, j * 10);
            v = a_regress_linear_eval(&ctx, u);
            debug(A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f"), u[0], u[1], v);
            debug("%c", i ? '\n' : ',');
            if (i == 0)
            {
                debug(A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,")
                          A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f\n"),
                      x[j * 2 + 0], x[j * 2 + 1], y[j], z[j]);
            }
        }
        debug("\n");
    }

    a_regress_linear_zero(&ctx);

    a_die(x);
    a_die(y);
    a_die(z);
}

#include <string.h>
int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    srand_(a_cast_s(a_ulong, time(A_NULL)));
    main_init(argc, argv, 1);

    a_float threshold = A_FLOAT_C(0.1);
    a_float alpha = A_FLOAT_C(1e-8);
    a_float a = A_FLOAT_C(0.7);
    a_float b = A_FLOAT_C(1.4);
    a_float c = 12;
    a_size n = 100;
    char *endptr;
    char m = 'b';
    int d = 1;

    if (argc > 1)
    {
        char const *s = strstr(argv[1], "regress_linear_");
        if (s) { sscanf(s, "regress_linear_%i%c", &d, &m); } // NOLINT
    }

    if (d == 1)
    {
        if (argc > 2) { a = strtonum(argv[2], &endptr); }
        if (argc > 3) { c = strtonum(argv[3], &endptr); }
        if (argc > 4) { n = strtoul(argv[4], &endptr, 0); }
        if (argc > 5) { alpha = strtonum(argv[5], &endptr); }
        if (argc > 6) { threshold = strtonum(argv[6], &endptr); }
        main_1(m, a, c, n, alpha, threshold);
    }
    if (d == 2)
    {
        if (argc > 2) { a = strtonum(argv[2], &endptr); }
        if (argc > 3) { b = strtonum(argv[3], &endptr); }
        if (argc > 4) { c = strtonum(argv[4], &endptr); }
        if (argc > 5) { n = strtoul(argv[5], &endptr, 0); }
        if (argc > 6) { alpha = strtonum(argv[6], &endptr); }
        if (argc > 7) { threshold = strtonum(argv[7], &endptr); }
        main_2(m, a, b, c, n, alpha, threshold);
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_regress_linear>::value);
#endif /* __cplusplus */

    return 0;
}
