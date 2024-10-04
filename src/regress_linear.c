#include "a/regress_linear.h"
#include "a/math.h"

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

void a_regress_linear_err(a_regress_linear const *ctx, a_size n, a_float const *x, a_float const *y, a_float *err)
{
    for (; n; --n, x += ctx->coef_n) { *err++ = *y++ - a_regress_linear_eval(ctx, x); }
}

void a_regress_linear_pdm(a_regress_linear const *ctx, a_size n, a_float const *x, a_float *pdm, a_float y_mean)
{
    for (; n; --n, x += ctx->coef_n) { *pdm++ = a_regress_linear_eval(ctx, x) - y_mean; }
}

void a_regress_linear_gd(a_regress_linear *ctx, a_float const *input, a_float error, a_float alpha)
{
    a_float *coef = ctx->coef_p;
    a_float delta = alpha * error;
    for (a_size n = ctx->coef_n; n; --n)
    {
        *coef++ += delta * *input++;
    }
    ctx->bias += delta;
}

void a_regress_linear_sgd(a_regress_linear *ctx, a_size n, a_float const *x, a_float const *y, a_float alpha)
{
    for (; n; --n, x += ctx->coef_n, ++y)
    {
        a_regress_linear_gd(ctx, x, *y - a_regress_linear_eval(ctx, x), alpha);
    }
}

void a_regress_linear_bgd(a_regress_linear *ctx, a_size n, a_float const *x, a_float const *err, a_float alpha)
{
    for (alpha /= (a_float)n; n; --n, x += ctx->coef_n, ++err)
    {
        a_regress_linear_gd(ctx, x, *err, alpha);
    }
}

a_float a_regress_linear_mgd(a_regress_linear *ctx, a_size n, a_float const *x_, a_float const *y_, a_float *err,
                             a_float delta, a_float lrmax, a_float lrmin, a_size lrtim, a_size epoch, a_size batch)
{
    a_float r, s = 0, lrcur = 0;
    a_float const lramp = (lrmax - lrmin) / 2;
    a_float const lrper = A_FLOAT_PI / (a_float)lrtim;
    a_size const q_ = n / batch, r_ = n % batch;
    a_size const xoffset = batch * ctx->coef_n;
    a_regress_linear_err(ctx, n, x_, y_, err);
    r = a_float_sum2(err, n);
    for (; epoch; --epoch)
    {
        a_float const *x = x_, *y = y_;
        a_float alpha = lrmin + lramp * (a_float_cos(lrcur) + 1);
        for (a_size q = q_; q; --q, x += xoffset, y += batch)
        {
            a_regress_linear_err(ctx, batch, x, y, err);
            a_regress_linear_bgd(ctx, batch, x, err, alpha);
        }
        if (r_)
        {
            a_regress_linear_err(ctx, r_, x, y, err);
            a_regress_linear_bgd(ctx, r_, x, err, alpha);
        }
        a_regress_linear_err(ctx, n, x_, y_, err);
        s = a_float_sum2(err, n);
        if (A_ABS_(r, s) < delta) { break; }
        lrcur += lrper;
        r = s;
    }
    return r - s;
}

void a_regress_linear_zero(a_regress_linear *ctx)
{
    a_zero(ctx->coef_p, sizeof(a_float) * ctx->coef_n);
    ctx->bias = 0;
}
