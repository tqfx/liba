#include "a/tf.h"
#include "a/math.h"

void a_tf_set_num(a_tf *ctx, unsigned int num_n, a_real const *num_p, a_real *input)
{
    ctx->num_p = num_p;
    ctx->num_n = num_n;
    ctx->input = input;
    a_zero(ctx->input, sizeof(a_real) * ctx->num_n);
}

void a_tf_set_den(a_tf *ctx, unsigned int den_n, a_real const *den_p, a_real *output)
{
    ctx->den_p = den_p;
    ctx->den_n = den_n;
    ctx->output = output;
    a_zero(ctx->output, sizeof(a_real) * ctx->den_n);
}

void a_tf_init(a_tf *ctx,
               unsigned int num_n, a_real const *num_p, a_real *input,
               unsigned int den_n, a_real const *den_p, a_real *output)
{
    a_tf_set_num(ctx, num_n, num_p, input);
    a_tf_set_den(ctx, den_n, den_p, output);
}

a_real a_tf_iter(a_tf const *ctx, a_real x)
{
    a_real y = 0;
    unsigned int i;
    a_real_push_fore(ctx->input, ctx->num_n, x);
    for (i = 0; i != ctx->num_n; ++i)
    {
        y += ctx->num_p[i] * ctx->input[i];
    }
    for (i = 0; i != ctx->den_n; ++i)
    {
        y -= ctx->den_p[i] * ctx->output[i];
    }
    a_real_push_fore(ctx->output, ctx->den_n, y);
    return y;
}

void a_tf_zero(a_tf const *ctx)
{
    a_zero(ctx->input, sizeof(a_real) * ctx->num_n);
    a_zero(ctx->output, sizeof(a_real) * ctx->den_n);
}
