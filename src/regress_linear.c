#include "a/regress_linear.h"
#include "a/math.h"

void a_regress_linear_init(a_regress_linear *ctx, a_real *coef_p, a_size coef_n, a_real bias)
{
    ctx->coef_p = coef_p;
    ctx->coef_n = coef_n;
    ctx->bias = bias;
}

a_real a_regress_linear_eval(a_regress_linear const *ctx, a_real const *val)
{
    a_size n;
    a_real res = ctx->bias;
    a_real const *coef = ctx->coef_p;
    for (n = ctx->coef_n; n; --n)
    {
        res += *coef++ * *val++;
    }
    return res;
}

void a_regress_linear_err(a_regress_linear const *ctx, a_size n, a_real const *x, a_real const *y, a_real *err)
{
    for (; n; --n, x += ctx->coef_n) { *err++ = *y++ - a_regress_linear_eval(ctx, x); }
}

void a_regress_linear_pdm(a_regress_linear const *ctx, a_size n, a_real const *x, a_real *pdm, a_real y_mean)
{
    for (; n; --n, x += ctx->coef_n) { *pdm++ = a_regress_linear_eval(ctx, x) - y_mean; }
}

void a_regress_linear_gd(a_regress_linear *ctx, a_real const *input, a_real error, a_real alpha)
{
    a_size n;
    a_real *coef = ctx->coef_p;
    a_real delta = alpha * error;
    for (n = ctx->coef_n; n; --n)
    {
        *coef++ += delta * *input++;
    }
    ctx->bias += delta;
}

void a_regress_linear_sgd(a_regress_linear *ctx, a_size n, a_real const *x, a_real const *y, a_real alpha)
{
    for (; n; --n, x += ctx->coef_n, ++y)
    {
        a_regress_linear_gd(ctx, x, *y - a_regress_linear_eval(ctx, x), alpha);
    }
}

void a_regress_linear_bgd(a_regress_linear *ctx, a_size n, a_real const *x, a_real const *err, a_real alpha)
{
    for (alpha /= (a_real)n; n; --n, x += ctx->coef_n, ++err)
    {
        a_regress_linear_gd(ctx, x, *err, alpha);
    }
}

a_real a_regress_linear_mgd(a_regress_linear *ctx, a_size n, a_real const *x_, a_real const *y_, a_real *err,
                            a_real delta, a_real lrmax, a_real lrmin, a_size lrtim, a_size epoch, a_size batch)
{
    a_real r, s = 0, lrcur = 0;
    a_real const lramp = (lrmax - lrmin) / 2;
    a_real const lrper = A_REAL_PI / (a_real)lrtim;
    a_size const q_ = n / batch, r_ = n % batch;
    a_size const xoffset = batch * ctx->coef_n;
    a_regress_linear_err(ctx, n, x_, y_, err);
    r = a_real_sum2(n, err);
    for (; epoch; --epoch)
    {
        a_size q;
        a_real const *x = x_, *y = y_;
        a_real alpha = lrmin + lramp * (a_real_cos(lrcur) + 1);
        for (q = q_; q; --q, x += xoffset, y += batch)
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
        s = a_real_sum2(n, err);
        if (A_ABS_(r, s) < delta) { break; }
        lrcur += lrper;
        r = s;
    }
    return r - s;
}

void a_regress_linear_zero(a_regress_linear *ctx)
{
    a_zero(ctx->coef_p, sizeof(a_real) * ctx->coef_n);
    ctx->bias = 0;
}
