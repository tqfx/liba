#include "a/regress_simple.h"
#include "a/math.h"

void a_regress_simple_init(a_regress_simple *ctx, a_real coef, a_real bias)
{
    ctx->coef = coef;
    ctx->bias = bias;
}

a_real a_regress_simple_eval(a_regress_simple const *ctx, a_real val)
{
    return ctx->coef * val + ctx->bias;
}

a_real a_regress_simple_evar(a_regress_simple const *ctx, a_real val)
{
    return (val - ctx->bias) / ctx->coef;
}

void a_regress_simple_ols_(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y, a_real x_mean, a_real y_mean)
{
    a_real num = 0, den = 0;
    for (; n; --n)
    {
        a_real dy = *y++ - y_mean;
        a_real dx = *x++ - x_mean;
        num += dx * dy;
        den += dx * dx;
    }
    ctx->coef = num / den;
    ctx->bias = y_mean - ctx->coef * x_mean;
}

void a_regress_simple_olsx(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y, a_real x_mean)
{
    a_real const y_mean = a_real_mean(n, y);
    a_regress_simple_ols_(ctx, n, x, y, x_mean, y_mean);
}

void a_regress_simple_olsy(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y, a_real y_mean)
{
    a_real const x_mean = a_real_mean(n, x);
    a_regress_simple_ols_(ctx, n, x, y, x_mean, y_mean);
}

void a_regress_simple_ols(a_regress_simple *ctx, a_size n, a_real const *x, a_real const *y)
{
    a_real const x_mean = a_real_mean(n, x);
    a_real const y_mean = a_real_mean(n, y);
    a_regress_simple_ols_(ctx, n, x, y, x_mean, y_mean);
}

void a_regress_simple_zero(a_regress_simple *ctx)
{
    ctx->coef = 0;
    ctx->bias = 0;
}
