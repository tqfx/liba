#define MAIN(x) regress_linear##x
#include "test.h"
#include "a/regress_linear.h"
#include "a/math.h"
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

typedef struct config
{
    a_float delta;
    a_float lrmax;
    a_float lrmin;
    a_size lrtim;
    a_size epoch;
    a_size batch;
} config;

static void main_1(int m, a_float a, a_float b, a_size n, config const *cfg)
{
    a_float *x = a_new(a_float, A_NULL, n);
    a_float *y = a_new(a_float, A_NULL, n);
    a_float *e = a_new(a_float, A_NULL, n);
    long x_n = a_cast_s(long, n) * 10;
    long y_n = a_cast_s(long, n) * 2;

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
        a_float lrcur = 0;
        a_float const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_float const lrper = A_FLOAT_PI / a_float_c(cfg->lrtim);
        a_regress_linear_err1(&ctx, n, x, y, e);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < cfg->epoch; ++i)
        {
            a_float alpha = cfg->lrmin + lramp * (a_float_cos(lrcur) + 1);
            a_regress_linear_sgd1(&ctx, n, x, y, alpha);
            a_regress_linear_err1(&ctx, n, x, y, e);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < cfg->delta)
            {
                break;
            }
            lrcur += lrper;
            r = s;
        }
        break;
    }
    case 'b':
    {
        a_float lrcur = 0;
        a_float const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_float const lrper = A_FLOAT_PI / a_float_c(cfg->lrtim);
        a_regress_linear_err1(&ctx, n, x, y, e);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < cfg->epoch; ++i)
        {
            a_float alpha = cfg->lrmin + lramp * (a_float_cos(lrcur) + 1);
            a_regress_linear_bgd1(&ctx, n, x, e, alpha);
            a_regress_linear_err1(&ctx, n, x, y, e);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < cfg->delta)
            {
                break;
            }
            lrcur += lrper;
            r = s;
        }
        break;
    }
    case 'm':
        a_regress_linear_mgd1(&ctx, n, x, y, e, cfg->delta, cfg->lrmax, cfg->lrmin, cfg->lrtim, cfg->epoch, cfg->batch);
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

static void main_2(int m, a_float a, a_float b, a_float c, a_size n, config const *cfg)
{
    a_float *x = a_new(a_float, A_NULL, n * 2);
    a_float *y = a_new(a_float, A_NULL, n);
    a_float *e = a_new(a_float, A_NULL, n);
    long x_n = a_cast_s(long, n) * 10;
    long y_n = a_cast_s(long, n) * 2;

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
        a_float lrcur = 0;
        a_float const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_float const lrper = A_FLOAT_PI / a_float_c(cfg->lrtim);
        a_regress_linear_err1(&ctx, n, x, y, e);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < cfg->epoch; ++i)
        {
            a_float alpha = cfg->lrmin + lramp * (a_float_cos(lrcur) + 1);
            a_regress_linear_sgd1(&ctx, n, x, y, alpha);
            a_regress_linear_err1(&ctx, n, x, y, e);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < cfg->delta)
            {
                break;
            }
            lrcur += lrper;
            r = s;
        }
        break;
    }
    case 'b':
    {
        a_float lrcur = 0;
        a_float const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_float const lrper = A_FLOAT_PI / a_float_c(cfg->lrtim);
        a_regress_linear_err1(&ctx, n, x, y, e);
        a_float r = a_float_sum2(e, n);
        for (a_size i = 0; i < cfg->epoch; ++i)
        {
            a_float alpha = cfg->lrmin + lramp * (a_float_cos(lrcur) + 1);
            a_regress_linear_bgd1(&ctx, n, x, e, alpha);
            a_regress_linear_err1(&ctx, n, x, y, e);
            a_float s = a_float_sum2(e, n);
            if (A_ABS_(r, s) < cfg->delta)
            {
                break;
            }
            lrcur += lrper;
            r = s;
        }
        break;
    }
    case 'm':
        a_regress_linear_mgd1(&ctx, n, x, y, e, cfg->delta, cfg->lrmax, cfg->lrmin, cfg->lrtim, cfg->epoch, cfg->batch);
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

    a_float a = A_FLOAT_C(0.7);
    a_float b = A_FLOAT_C(1.4);
    a_float c = 12;
    a_size n = 100;
    char m = 'm';
    int d = 1;

    config cfg;
    cfg.delta = 1;
    cfg.lrmax = A_FLOAT_C(5e-7);
    cfg.lrmin = A_FLOAT_C(5e-9);
    cfg.lrtim = 100;
    cfg.epoch = 1000;
    cfg.batch = 16;

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

    char *endptr;
    if (d == 1)
    {
        if (argc > 2) { a = strtonum(argv[2], &endptr); }
        if (argc > 3) { c = strtonum(argv[3], &endptr); }
        if (argc > 4) { n = strtoul(argv[4], &endptr, 0); }
        main_1(m, a, c, n, &cfg);
    }
    if (d == 2)
    {
        if (argc > 2) { a = strtonum(argv[2], &endptr); }
        if (argc > 3) { b = strtonum(argv[3], &endptr); }
        if (argc > 4) { c = strtonum(argv[4], &endptr); }
        if (argc > 5) { n = strtoul(argv[5], &endptr, 0); }
        main_2(m, a, b, c, n, &cfg);
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_regress_linear>::value);
#endif /* __cplusplus */

    return 0;
}
