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
    a_float *e = a_new(a_float, A_NULL, n);
    a_float *y = a_new(a_float, A_NULL, n);
    a_float *x = a_new(a_float, A_NULL, n);
    long y_n = a_cast_s(long, n) * 2;
    long x_n = a_cast_s(long, n) * 10;

    for (a_size i = 0; i < n; ++i)
    {
        x[i] = a_cast_s(a_float, rand_() % x_n);
        y[i] = a * x[i] + b + a_cast_s(a_float, rand_() % y_n) - a_cast_s(a_float, n);
    }

    a_float coef[] = {1};

    a_regress_linear ctx;
    a_regress_linear_init(&ctx, coef, 1, 1);
    a_regress_linear_zero(&ctx);

    switch (m)
    {
    default:
    case 's':
    {
        a_regress_linear_err1(&ctx, e, y, x, n);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < 100; ++i)
        {
            a_regress_linear_bgd1(&ctx, e, x, n, alpha);
            a_regress_linear_err1(&ctx, e, y, x, n);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < threshold)
            {
                break;
            }
            r = s;
        }
        break;
    }
    case 'b':
    {
        a_regress_linear_err1(&ctx, e, y, x, n);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < 100; ++i)
        {
            a_regress_linear_sgd1(&ctx, y, x, n, alpha);
            a_regress_linear_err1(&ctx, e, y, x, n);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < threshold)
            {
                break;
            }
            r = s;
        }
        break;
    }
    case 'm':
        a_regress_linear_mgd1(&ctx, e, y, x, n, alpha, threshold, 100, 16);
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        a_float u = a_cast_s(a_float, i * 10);
        a_float v = a_regress_linear_eval(&ctx, &u);
        debug(A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,")
                  A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f\n"),
              u, v, x[i], y[i], e[i]);
    }

    a_regress_linear_zero(&ctx);

    a_die(x);
    a_die(y);
    a_die(e);
}

static void main_2(int m, a_float a, a_float b, a_float c, a_size n, a_float alpha, a_float threshold)
{
    a_float *e = a_new(a_float, A_NULL, n);
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

    a_float coef[2] = {1, 1};

    a_regress_linear ctx;
    a_regress_linear_init(&ctx, coef, 2, 1);
    a_regress_linear_zero(&ctx);

    switch (m)
    {
    default:
    case 's':
    {
        a_regress_linear_err1(&ctx, e, y, x, n);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < 100; ++i)
        {
            a_regress_linear_bgd1(&ctx, e, x, n, alpha);
            a_regress_linear_err1(&ctx, e, y, x, n);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < threshold)
            {
                break;
            }
            r = s;
        }
        break;
    }
    case 'b':
    {
        a_regress_linear_err1(&ctx, e, y, x, n);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < 100; ++i)
        {
            a_regress_linear_sgd1(&ctx, y, x, n, alpha);
            a_regress_linear_err1(&ctx, e, y, x, n);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < threshold)
            {
                break;
            }
            r = s;
        }
        break;
    }
    case 'm':
        a_regress_linear_mgd1(&ctx, e, y, x, n, alpha, threshold, 100, 16);
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        a_float u[2];
        u[0] = a_cast_s(a_float, i * 10);
        for (unsigned int j = 0; j < n; ++j)
        {
            u[1] = a_cast_s(a_float, j * 10);
            a_float v = a_regress_linear_eval(&ctx, u);
            debug(A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f"), u[0], u[1], v);
            debug("%c", i ? '\n' : ',');
            if (i == 0)
            {
                debug(A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f,")
                          A_FLOAT_PRI("+.1", "f,") A_FLOAT_PRI("+.1", "f\n"),
                      x[j * 2 + 0], x[j * 2 + 1], y[j], e[j]);
            }
        }
        debug("\n");
    }

    a_regress_linear_zero(&ctx);

    a_die(x);
    a_die(y);
    a_die(e);
}

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    srand_(a_cast_s(a_ulong, time(A_NULL)));
    main_init(argc, argv, 1);

    a_float threshold = A_FLOAT_C(1.0);
    a_float alpha = A_FLOAT_C(5e-8);
    a_float a = A_FLOAT_C(0.7);
    a_float b = A_FLOAT_C(1.4);
    a_float c = 12;
    a_size n = 100;
    char m = 'm';
    int d = 1;

    if (argc > 1)
    {
        char const *s = strstr(argv[1], "regress_linear_");
        if (s) { sscanf(s, "regress_linear_%i%c", &d, &m); } // NOLINT
        else
        {
            debug("regress_linear_1bgd.csv\n");
            debug("regress_linear_1sgd.csv\n");
            debug("regress_linear_1mgd.csv\n");
            debug("regress_linear_2bgd.csv\n");
            debug("regress_linear_2sgd.csv\n");
            debug("regress_linear_2mgd.csv\n");
            return 0;
        }
    }

    if (m == 's') { alpha = A_FLOAT_C(2e-8); }

    char *endptr;
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
