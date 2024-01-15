#include "a/rbf.h"
#include "a/math.h"

a_float const *a_rbf_iter(a_rbf const *ctx)
{
    a_size const input_hidden_n = ctx->input_n * ctx->hidden_n;
    for (a_size hidden_i = 0; hidden_i != ctx->hidden_n; ++hidden_i)
    {
        a_float num = 0;
        if (ctx->center_n == input_hidden_n)
        {
            a_float const *center_p = ctx->center_p + hidden_i;
            for (a_size input_i = 0; input_i != ctx->input_n; ++input_i, center_p += ctx->input_n)
            {
                a_float const r = ctx->input_p[input_i] - *center_p;
                num += r * r;
            }
        }
        else if (ctx->center_n == ctx->hidden_n)
        {
            for (a_size input_i = 0; input_i != ctx->input_n; ++input_i)
            {
                a_float const r = ctx->input_p[input_i] - ctx->center_p[hidden_i];
                num += r * r;
            }
        }
        else if (ctx->center_n == 1)
        {
            for (a_size input_i = 0; input_i != ctx->input_n; ++input_i)
            {
                a_float const r = ctx->input_p[input_i] - *ctx->center_p;
                num += r * r;
            }
        }
        a_float den = 1;
        if (ctx->height_n == ctx->hidden_n)
        {
            den = ctx->height_p[hidden_i] * ctx->height_p[hidden_i];
        }
        else if (ctx->height_n == 1)
        {
            den = *ctx->height_p * *ctx->height_p;
        }
        ctx->hidden_p[hidden_i] = a_float_exp(-num / den);
    }
    a_float const *weight_p = ctx->weight;
    for (a_size output_i = 0; output_i != ctx->output_n; ++output_i)
    {
        ctx->output_p[output_i] = 0;
        for (a_size hidden = 0; hidden != ctx->hidden_n; ++hidden)
        {
            ctx->output_p[output_i] += *weight_p++ * ctx->hidden_p[hidden];
        }
    }
    return ctx->output_p;
}

void a_rbf_tune(a_rbf const *ctx, a_float const *out)
{
    a_float *weight = ctx->weight;
    a_float *deltaw = ctx->deltaw;
    for (a_size output_i = 0; output_i != ctx->output_n; ++output_i)
    {
        a_float error = out[output_i] - ctx->output_p[output_i];
        for (a_size hidden_i = 0; hidden_i != ctx->hidden_n; ++hidden_i)
        {
            *deltaw = ctx->learn * error * ctx->hidden_p[hidden_i] + ctx->alpha * *deltaw;
            *weight++ += *deltaw++;
        }
    }
}

void a_rbf_zero(a_rbf const *ctx)
{
    a_size const hidden_output_n = ctx->hidden_n * ctx->output_n;
    a_zero(ctx->input_p, sizeof(a_float) * ctx->input_n);
    a_zero(ctx->hidden_p, sizeof(a_float) * ctx->hidden_n);
    a_zero(ctx->output_p, sizeof(a_float) * ctx->output_n);
    a_zero(ctx->weight, sizeof(a_float) * hidden_output_n);
    a_zero(ctx->deltaw, sizeof(a_float) * hidden_output_n);
}
