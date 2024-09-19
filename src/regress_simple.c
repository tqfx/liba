#include "a/regress_simple.h"

void a_regress_simple_init(a_regress_simple *ctx, a_float coef, a_float bias)
{
    ctx->coef = coef;
    ctx->bias = bias;
}

a_float a_regress_simple_eval(a_regress_simple const *ctx, a_float val)
{
    return ctx->coef * val + ctx->bias;
}

void a_regress_simple_olsm_(a_regress_simple *ctx, a_float const *y, a_float const *x, a_size n, a_float y_mean, a_float x_mean)
{
    a_float num = 0, den = 0;
    for (; n; --n)
    {
        a_float dy = *y++ - y_mean;
        a_float dx = *x++ - x_mean;
        num += dx * dy;
        den += dx * dx;
    }
    ctx->coef = num / den;
    ctx->bias = y_mean - ctx->coef * x_mean;
}

void a_regress_simple_olsm(a_regress_simple *ctx, a_float const *y, a_float const *x, a_size n)
{
    a_float const y_mean = a_float_mean(y, n);
    a_float const x_mean = a_float_mean(x, n);
    a_regress_simple_olsm_(ctx, y, x, n, y_mean, x_mean);
}

void a_regress_simple_zero(a_regress_simple *ctx)
{
    ctx->coef = 0;
    ctx->bias = 0;
}
