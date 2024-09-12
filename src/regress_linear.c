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

a_float a_regress_linear_sdg(a_regress_linear *ctx, a_float alpha, a_float y, a_float const *x)
{
    a_float error = y - a_regress_linear_eval(ctx, x);
    a_float *coef = ctx->coef_p;
    a_float delta = alpha * error;
    for (a_size n = ctx->coef_n; n; --n)
    {
        *coef++ += delta * *x++;
    }
    ctx->bias += delta;
    return error;
}

a_float a_regress_linear_sdg1(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *x, a_size n, a_float *error)
{
    a_float res = 0;
    for (a_size i = 0; i < n; ++i, x += ctx->coef_n)
    {
        error[i] = a_regress_linear_sdg(ctx, alpha, y[i], x);
        if (error[i] < 0) { res -= error[i]; }
        else { res += error[i]; }
    }
    return res;
}

a_float a_regress_linear_sdg2(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *const *x, a_size n, a_float *error)
{
    a_float res = 0;
    for (a_size i = 0; i < n; ++i)
    {
        error[i] = a_regress_linear_sdg(ctx, alpha, y[i], x[i]);
        if (error[i] < 0) { res -= error[i]; }
        else { res += error[i]; }
    }
    return res;
}

a_float a_regress_linear_bdg1(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *x, a_size n, a_float *error)
{
    a_float res = 0;
    a_float const *p = x;
    for (a_size i = 0; i < n; ++i, x += ctx->coef_n)
    {
        error[i] = y[i] - a_regress_linear_eval(ctx, x);
        if (error[i] < 0) { res -= error[i]; }
        else { res += error[i]; }
    }
    for (; n; --n)
    {
        a_float *coef = ctx->coef_p;
        a_float delta = alpha * *error++;
        for (a_size c = ctx->coef_n; c; --c)
        {
            *coef++ += delta * *p++;
        }
        ctx->bias += delta;
    }
    return res;
}

a_float a_regress_linear_bdg2(a_regress_linear *ctx, a_float alpha, a_float const *y, a_float const *const *x, a_size n, a_float *error)
{
    a_float res = 0;
    for (a_size i = 0; i < n; ++i)
    {
        error[i] = y[i] - a_regress_linear_eval(ctx, x[i]);
        if (error[i] < 0) { res -= error[i]; }
        else { res += error[i]; }
    }
    for (; n; --n)
    {
        a_float const *p = *x++;
        a_float *coef = ctx->coef_p;
        a_float delta = alpha * *error++;
        for (a_size c = ctx->coef_n; c; --c)
        {
            *coef++ += delta * *p++;
        }
        ctx->bias += delta;
    }
    return res;
}

void a_regress_linear_zero(a_regress_linear *ctx)
{
    a_zero(ctx->coef_p, sizeof(a_float) * ctx->coef_n);
    ctx->bias = 0;
}
