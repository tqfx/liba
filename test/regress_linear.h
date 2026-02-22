#define MAIN(x) regress_linear##x
#include "test.h"
#include "a/regress_linear.h"
#include "a/rand.h"
#include "a/math.h"
#include <string.h>

typedef struct config
{
    a_real delta;
    a_real lrmax;
    a_real lrmin;
    a_size lrtim;
    a_size epoch;
    a_size batch;
} config;

static void main_1(int m, a_real a, a_real b, a_size n, config const *cfg)
{
    a_real *x = a_new(a_real, A_NULL, n);
    a_real *y = a_new(a_real, A_NULL, n);
    a_real *e = a_new(a_real, A_NULL, n);
    int x_n = a_cast_s(int, n * 10);
    int y_n = a_cast_s(int, n * 2);
    a_real coef[] = {1};
    a_regress_linear ctx = A_REGRESS_LINEAR_0();
    a_rand_lcg48 lcg = A_RAND_LCG48_INIT;
    a_size i;

    for (i = 0; i < n; ++i)
    {
        x[i] = a_cast_s(a_real, a_rand_lcg48f(&lcg) * x_n);
        y[i] = a * x[i] + b + a_cast_s(a_real, a_rand_lcg48f(&lcg) * y_n) - a_cast_s(a_real, y_n >> 1);
    }

    a_regress_linear_init(&ctx, coef, A_LEN(coef), 1);
    a_regress_linear_zero(&ctx);

    switch (m)
    {
    default:
    case 's':
    {
        a_real r, s, lrcur = 0;
        a_real const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_real const lrper = A_REAL_PI / a_real_c(cfg->lrtim);
        a_regress_linear_err(&ctx, n, x, y, e);
        r = a_real_sum2(n, e);
        for (i = 0; i < cfg->epoch; ++i)
        {
            a_real alpha = cfg->lrmin + lramp * (a_real_cos(lrcur) + 1);
            a_regress_linear_sgd(&ctx, n, x, y, alpha);
            a_regress_linear_err(&ctx, n, x, y, e);
            s = a_real_sum2(n, e);
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
        a_real r, s, lrcur = 0;
        a_real const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_real const lrper = A_REAL_PI / a_real_c(cfg->lrtim);
        a_regress_linear_err(&ctx, n, x, y, e);
        r = a_real_sum2(n, e);
        for (i = 0; i < cfg->epoch; ++i)
        {
            a_real alpha = cfg->lrmin + lramp * (a_real_cos(lrcur) + 1);
            a_regress_linear_bgd(&ctx, n, x, e, alpha);
            a_regress_linear_err(&ctx, n, x, y, e);
            s = a_real_sum2(n, e);
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
        a_regress_linear_mgd(&ctx, n, x, y, e, cfg->delta, cfg->lrmax, cfg->lrmin, cfg->lrtim, cfg->epoch, cfg->batch);
    }

    for (i = 0; i < n; ++i)
    {
        a_real u = a_cast_s(a_real, i * 10);
        a_real v = a_regress_linear_eval(&ctx, &u);
        debug("%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f\n",
              u, v, x[i], y[i], e[i]);
    }

    a_regress_linear_zero(&ctx);

    a_die(x);
    a_die(y);
    a_die(e);
}

static void main_2(int m, a_real a, a_real b, a_real c, a_size n, config const *cfg)
{
    a_real *x = a_new(a_real, A_NULL, n * 2);
    a_real *y = a_new(a_real, A_NULL, n);
    a_real *e = a_new(a_real, A_NULL, n);
    int x_n = a_cast_s(int, n * 10);
    int y_n = a_cast_s(int, n * 2);
    a_real coef[2] = {1, 1};
    a_rand_lcg48 lcg = A_RAND_LCG48_INIT;
    a_regress_linear ctx = A_REGRESS_LINEAR_0();
    a_size i, ii;

    for (i = 0; i < n; ++i)
    {
        x[i * 2 + 0] = a_cast_s(a_real, a_rand_lcg48f(&lcg) * x_n);
        x[i * 2 + 1] = a_cast_s(a_real, a_rand_lcg48f(&lcg) * x_n);
        y[i] = a * x[i * 2 + 0] + b * x[i * 2 + 1] + c +
               a_cast_s(a_real, a_rand_lcg48f(&lcg) * y_n) - a_cast_s(a_real, y_n >> 1);
    }

    a_regress_linear_init(&ctx, coef, A_LEN(coef), 1);
    a_regress_linear_zero(&ctx);

    switch (m)
    {
    default:
    case 's':
    {
        a_real r, s, lrcur = 0;
        a_real const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_real const lrper = A_REAL_PI / a_real_c(cfg->lrtim);
        a_regress_linear_err(&ctx, n, x, y, e);
        r = a_real_sum2(n, e);
        for (i = 0; i < cfg->epoch; ++i)
        {
            a_real alpha = cfg->lrmin + lramp * (a_real_cos(lrcur) + 1);
            a_regress_linear_sgd(&ctx, n, x, y, alpha);
            a_regress_linear_err(&ctx, n, x, y, e);
            s = a_real_sum2(n, e);
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
        a_real r, s, lrcur = 0;
        a_real const lramp = (cfg->lrmax - cfg->lrmin) / 2;
        a_real const lrper = A_REAL_PI / a_real_c(cfg->lrtim);
        a_regress_linear_err(&ctx, n, x, y, e);
        r = a_real_sum2(n, e);
        for (i = 0; i < cfg->epoch; ++i)
        {
            a_real alpha = cfg->lrmin + lramp * (a_real_cos(lrcur) + 1);
            a_regress_linear_bgd(&ctx, n, x, e, alpha);
            a_regress_linear_err(&ctx, n, x, y, e);
            s = a_real_sum2(n, e);
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
        a_regress_linear_mgd(&ctx, n, x, y, e, cfg->delta, cfg->lrmax, cfg->lrmin, cfg->lrtim, cfg->epoch, cfg->batch);
    }

    for (i = 0; i < n; ++i)
    {
        a_real u[2];
        u[0] = a_cast_s(a_real, i * 10);
        for (ii = 0; ii < n; ++ii)
        {
            a_real v;
            u[1] = a_cast_s(a_real, ii * 10);
            v = a_regress_linear_eval(&ctx, u);
            debug("%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f", u[0], u[1], v);
            debug("%c", i ? '\n' : ',');
            if (i == 0)
            {
                debug("%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f,%+.1" A_REAL_PRI "f\n",
                      x[ii * 2 + 0], x[ii * 2 + 1], y[ii], e[ii]);
            }
        }
        debug("\n");
    }

    a_regress_linear_zero(&ctx);

    a_die(x);
    a_die(y);
    a_die(e);
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_real a = A_REAL_C(0.7);
    a_real b = A_REAL_C(1.4);
    a_real c = 12;
    a_size n = 100;
    char *endptr;
    char m = 'm';
    int dim = 1;

    config cfg;
    cfg.delta = 1;
    cfg.lrmax = A_REAL_C(5e-7);
    cfg.lrmin = A_REAL_C(5e-9);
    cfg.lrtim = 100;
    cfg.epoch = 1000;
    cfg.batch = 16;

    main_init(argc, argv, 1);

    if (argc > 1)
    {
        char const *s = strstr(argv[1], "regress_linear_");
        if (s) { (void)sscanf(s, "regress_linear_%i%c", &dim, &m); } /* NOLINT */
        else
        {
            debug("regress_linear_1sgd.csv\n");
            debug("regress_linear_1bgd.csv\n");
            debug("regress_linear_1mgd.csv\n");
            debug("regress_linear_2sgd.csv\n");
            debug("regress_linear_2bgd.csv\n");
            debug("regress_linear_2mgd.csv\n");
            return 0;
        }
    }

    if (dim == 1)
    {
        if (argc > 2) { a = a_str2num(argv[2], &endptr); }
        if (argc > 3) { c = a_str2num(argv[3], &endptr); }
        if (argc > 4) { n = strtoul(argv[4], &endptr, 0); }
        main_1(m, a, c, n, &cfg);
    }
    if (dim == 2)
    {
        if (argc > 2) { a = a_str2num(argv[2], &endptr); }
        if (argc > 3) { b = a_str2num(argv[3], &endptr); }
        if (argc > 4) { c = a_str2num(argv[4], &endptr); }
        if (argc > 5) { n = strtoul(argv[5], &endptr, 0); }
        main_2(m, a, b, c, n, &cfg);
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_regress_linear>::value);
#endif /* __cplusplus */

    return 0;
}
