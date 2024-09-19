#include "a/regress_linear.h"

void a_regress_linear_init(a_regress_linear *ctx, a_float *coef_p, a_size coef_n, a_float bias)
{
    ctx->coef_p = coef_p;
    ctx->coef_n = coef_n;
    ctx->bias = bias;
}

a_float a_regress_linear_eval(a_regress_linear const *ctx, a_float const *val)
{
    a_float res = ctx->bias;
    a_float const *coef = ctx->coef_p;
    for (a_size n = ctx->coef_n; n; --n)
    {
        res += *coef++ * *val++;
    }
    return res;
}

void a_regress_linear_err1(a_regress_linear const *ctx, a_float *err, a_float const *y, a_float const *x, a_size n)
{
    for (; n; --n, x += ctx->coef_n) { *err++ = *y++ - a_regress_linear_eval(ctx, x); }
}

void a_regress_linear_err2(a_regress_linear const *ctx, a_float *err, a_float const *y, a_float const *const *x, a_size n)
{
    for (; n; --n) { *err++ = *y++ - a_regress_linear_eval(ctx, *x++); }
}

void a_regress_linear_pdm1(a_regress_linear const *ctx, a_float *pdm, a_float const *x, a_size n, a_float y_mean)
{
    for (; n; --n, x += ctx->coef_n) { *pdm++ = a_regress_linear_eval(ctx, x) - y_mean; }
}

void a_regress_linear_pdm2(a_regress_linear const *ctx, a_float *pdm, a_float const *const *x, a_size n, a_float y_mean)
{
    for (; n; --n) { *pdm++ = a_regress_linear_eval(ctx, *x++) - y_mean; }
}

void a_regress_linear_sgd_(a_regress_linear *ctx, a_float error, a_float const *input, a_float alpha)
{
    a_float delta = alpha * error;
    a_float *coef = ctx->coef_p;
    for (a_size n = ctx->coef_n; n; --n)
    {
        *coef++ += delta * *input++;
    }
    ctx->bias += delta;
}

void a_regress_linear_sgd(a_regress_linear *ctx, a_float y, a_float const *x, a_float alpha)
{
    a_float error = y - a_regress_linear_eval(ctx, x);
    a_regress_linear_sgd_(ctx, error, x, alpha);
}

void a_regress_linear_sgd1(a_regress_linear *ctx, a_float const *y, a_float const *x, a_size n, a_float alpha)
{
    for (; n; --n, x += ctx->coef_n)
    {
        a_float error = *y++ - a_regress_linear_eval(ctx, x);
        a_regress_linear_sgd_(ctx, error, x, alpha);
    }
}

void a_regress_linear_sgd2(a_regress_linear *ctx, a_float const *y, a_float const *const *x, a_size n, a_float alpha)
{
    for (; n; --n, ++x)
    {
        a_float error = *y++ - a_regress_linear_eval(ctx, *x);
        a_regress_linear_sgd_(ctx, error, *x, alpha);
    }
}

void a_regress_linear_bgd1(a_regress_linear *ctx, a_float const *err, a_float const *x, a_size n, a_float alpha)
{
    for (; n; --n)
    {
        a_float *coef = ctx->coef_p;
        a_float delta = alpha * *err++;
        for (a_size c = ctx->coef_n; c; --c)
        {
            *coef++ += delta * *x++;
        }
        ctx->bias += delta;
    }
}

void a_regress_linear_bgd2(a_regress_linear *ctx, a_float const *err, a_float const *const *x, a_size n, a_float alpha)
{
    for (; n; --n)
    {
        a_float const *p = *x++;
        a_float *coef = ctx->coef_p;
        a_float delta = alpha * *err++;
        for (a_size c = ctx->coef_n; c; --c)
        {
            *coef++ += delta * *p++;
        }
        ctx->bias += delta;
    }
}

void a_regress_linear_zero(a_regress_linear *ctx)
{
    a_zero(ctx->coef_p, sizeof(a_float) * ctx->coef_n);
    ctx->bias = 0;
}
