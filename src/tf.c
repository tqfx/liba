#include "a/tf.h"

static void a_tf_roll(a_float_t *const p, unsigned int n, a_float_t const x)
{
    for (unsigned int i = --n; i; n = i)
    {
        p[n] = p[--i];
    }
    *p = x;
}

void a_tf_set_num(a_tf_s *const ctx, unsigned int const num_n, a_float_t const *const num_p, a_float_t *const input)
{
    a_zero(input, sizeof(a_float_t) * num_n);
    ctx->num_p = num_p;
    ctx->num_n = num_n;
    ctx->input = input;
}

void a_tf_set_den(a_tf_s *const ctx, unsigned int const den_n, a_float_t const *const den_p, a_float_t *const output)
{
    a_zero(output, sizeof(a_float_t) * den_n);
    ctx->den_p = den_p;
    ctx->den_n = den_n;
    ctx->output = output;
}

a_tf_s *a_tf_init(a_tf_s *const ctx,
                  unsigned int const num_n, a_float_t const *const num_p, a_float_t *const input,
                  unsigned int const den_n, a_float_t const *const den_p, a_float_t *const output)
{
    a_tf_set_num(ctx, num_n, num_p, input);
    a_tf_set_den(ctx, den_n, den_p, output);
    return ctx;
}

a_float_t a_tf_iter(a_tf_s *const ctx, a_float_t const x)
{
    a_float_t y = 0;
    a_tf_roll(ctx->input, ctx->num_n, x);
    for (unsigned int i = 0; i != ctx->num_n; ++i)
    {
        y += ctx->num_p[i] * ctx->input[i];
    }
    for (unsigned int i = 0; i != ctx->den_n; ++i)
    {
        y -= ctx->den_p[i] * ctx->output[i];
    }
    a_tf_roll(ctx->output, ctx->den_n, y);
    return y;
}

a_tf_s *a_tf_zero(a_tf_s *const ctx)
{
    a_zero(ctx->input, sizeof(a_float_t) * ctx->num_n);
    a_zero(ctx->output, sizeof(a_float_t) * ctx->den_n);
    return ctx;
}
