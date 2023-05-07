#include "a/tf.h"

static void a_tf_roll(a_real_t *const p, a_uint_t n, a_real_t const x)
{
    for (a_uint_t i = --n; i; n = i)
    {
        p[n] = p[--i];
    }
    *p = x;
}

a_void_t a_tf_set_num(a_tf_s *const ctx, a_uint_t const m, a_real_t const *const num, a_real_t *const u)
{
    a_zero(u, sizeof(a_real_t) * m);
    ctx->num = num;
    ctx->m = m;
    ctx->u = u;
}

a_void_t a_tf_set_den(a_tf_s *const ctx, a_uint_t const n, a_real_t const *const den, a_real_t *const v)
{
    a_zero(v, sizeof(a_real_t) * n);
    ctx->den = den;
    ctx->n = n;
    ctx->v = v;
}

a_tf_s *a_tf_init(a_tf_s *const ctx,
                  a_uint_t const m, a_real_t const *const num, a_real_t *const u,
                  a_uint_t const n, a_real_t const *const den, a_real_t *const v)
{
    a_tf_set_num(ctx, m, num, u);
    a_tf_set_den(ctx, n, den, v);
    return ctx;
}

a_real_t a_tf_iter(a_tf_s *const ctx, a_real_t const x)
{
    a_real_t y = 0;
    a_tf_roll(ctx->u, ctx->m, x);
    for (a_uint_t i = 0; i != ctx->m; ++i)
    {
        y += ctx->num[i] * ctx->u[i];
    }
    for (a_uint_t i = 0; i != ctx->n; ++i)
    {
        y -= ctx->den[i] * ctx->v[i];
    }
    a_tf_roll(ctx->v, ctx->n, y);
    return y;
}

a_tf_s *a_tf_exit(a_tf_s *const ctx) { return a_tf_zero(ctx); }

a_tf_s *a_tf_zero(a_tf_s *const ctx)
{
    a_zero(ctx->u, sizeof(a_real_t) * ctx->m);
    a_zero(ctx->v, sizeof(a_real_t) * ctx->n);
    return ctx;
}
