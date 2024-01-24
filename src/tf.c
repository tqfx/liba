#include "a/tf.h"

void a_tf_set_num(a_tf *ctx, unsigned int num_n, a_float const *num_p, a_float *input)
{
    ctx->num_p = num_p;
    ctx->num_n = num_n;
    ctx->input = input;
    a_zero(ctx->input, sizeof(a_float) * ctx->num_n);
}

void a_tf_set_den(a_tf *ctx, unsigned int den_n, a_float const *den_p, a_float *output)
{
    ctx->den_p = den_p;
    ctx->den_n = den_n;
    ctx->output = output;
    a_zero(ctx->output, sizeof(a_float) * ctx->den_n);
}

void a_tf_init(a_tf *ctx,
               unsigned int num_n, a_float const *num_p, a_float *input,
               unsigned int den_n, a_float const *den_p, a_float *output)
{
    a_tf_set_num(ctx, num_n, num_p, input);
    a_tf_set_den(ctx, den_n, den_p, output);
}

a_float a_tf_iter(a_tf const *ctx, a_float x)
{
    a_float y = 0;
    a_float_push(ctx->input, ctx->num_n, &x, 1);
    for (unsigned int i = 0; i != ctx->num_n; ++i)
    {
        y += ctx->num_p[i] * ctx->input[i];
    }
    for (unsigned int i = 0; i != ctx->den_n; ++i)
    {
        y -= ctx->den_p[i] * ctx->output[i];
    }
    a_float_push(ctx->output, ctx->den_n, &y, 1);
    return y;
}

void a_tf_zero(a_tf const *ctx)
{
    a_zero(ctx->input, sizeof(a_float) * ctx->num_n);
    a_zero(ctx->output, sizeof(a_float) * ctx->den_n);
}
