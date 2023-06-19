#include "a/tf.h"

static void a_tf_roll(a_float_t *const p, unsigned int n, a_float_t const x)
{
    for (unsigned int i = --n; i; n = i)
    {
        p[n] = p[--i];
    }
    *p = x;
}

void a_tf_set_num(a_tf_s *const ctx, unsigned int const m, a_float_t const *const num, a_float_t *const u)
{
    a_zero(u, sizeof(a_float_t) * m);
    ctx->num = num;
    ctx->m = m;
    ctx->u = u;
}

void a_tf_set_den(a_tf_s *const ctx, unsigned int const n, a_float_t const *const den, a_float_t *const v)
{
    a_zero(v, sizeof(a_float_t) * n);
    ctx->den = den;
    ctx->n = n;
    ctx->v = v;
}

a_tf_s *a_tf_init(a_tf_s *const ctx,
                  unsigned int const m, a_float_t const *const num, a_float_t *const u,
                  unsigned int const n, a_float_t const *const den, a_float_t *const v)
{
    a_tf_set_num(ctx, m, num, u);
    a_tf_set_den(ctx, n, den, v);
    return ctx;
}

a_float_t a_tf_iter(a_tf_s *const ctx, a_float_t const x)
{
    a_float_t y = 0;
    a_tf_roll(ctx->u, ctx->m, x);
    for (unsigned int i = 0; i != ctx->m; ++i)
    {
        y += ctx->num[i] * ctx->u[i];
    }
    for (unsigned int i = 0; i != ctx->n; ++i)
    {
        y -= ctx->den[i] * ctx->v[i];
    }
    a_tf_roll(ctx->v, ctx->n, y);
    return y;
}

a_tf_s *a_tf_zero(a_tf_s *const ctx)
{
    a_zero(ctx->u, sizeof(a_float_t) * ctx->m);
    a_zero(ctx->v, sizeof(a_float_t) * ctx->n);
    return ctx;
}
