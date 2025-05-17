#define MAIN(x) line3##x
#include "test.h"
#include "a/line3.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return A_ABS_(a, b) < A_REAL_EPS;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_line3 ctx;
        a_vector3 u;
        a_point3 a = A_POINT3_C(0, 0, 0);
        a_point3 b = A_POINT3_C(0, 3, 4);
        TEST_BUG(a_line3_set(&ctx, &a, &b) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.orig.z, 0));
        TEST_BUG(iseq(ctx.dir_.x, 0));
        TEST_BUG(iseq(ctx.dir_.y, A_REAL_C(0.6)));
        TEST_BUG(iseq(ctx.dir_.z, A_REAL_C(0.8)));
        TEST_BUG(iseq(ctx.max, 5));
        b = *a_line3_org(&ctx);
        TEST_BUG(iseq(b.x, 0));
        TEST_BUG(iseq(b.y, 0));
        TEST_BUG(iseq(b.z, 0));
        a_line3_tgt(&ctx, &a);
        TEST_BUG(iseq(a.x, 0));
        TEST_BUG(iseq(a.y, 3));
        TEST_BUG(iseq(a.z, 4));
        u = *a_line3_dir(&ctx);
        TEST_BUG(iseq(u.x, 0));
        TEST_BUG(iseq(u.y, A_REAL_C(0.6)));
        TEST_BUG(iseq(u.z, A_REAL_C(0.8)));
        TEST_BUG(iseq(a_line3_len(&ctx), 5));
#if defined(__cplusplus)
        ctx.set_org(1, 2, 3);
        TEST_BUG(iseq(ctx.orig.x, 1));
        TEST_BUG(iseq(ctx.orig.y, 2));
        TEST_BUG(iseq(ctx.orig.z, 3));
        TEST_BUG(ctx.set_dir(1, 0, 0) == 0);
        TEST_BUG(iseq(ctx.dir_.x, 1));
        TEST_BUG(iseq(ctx.dir_.y, 0));
        TEST_BUG(iseq(ctx.dir_.z, 0));
#endif /* __cplusplus */
    }
    {
        a_line3 ctx;
        a_point3 p = A_POINT3_C(0, 0, 0);
        a_vector3 v = A_VECTOR3_C(0, 3, 4);
        TEST_BUG(a_line3_setv(&ctx, &p, &v) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.orig.z, 0));
        TEST_BUG(iseq(ctx.dir_.x, 0));
        TEST_BUG(iseq(ctx.dir_.y, A_REAL_C(0.6)));
        TEST_BUG(iseq(ctx.dir_.z, A_REAL_C(0.8)));
        TEST_BUG(iseq(ctx.max, 5));
        p = *a_line3_org(&ctx);
        TEST_BUG(iseq(p.x, 0));
        TEST_BUG(iseq(p.y, 0));
        TEST_BUG(iseq(p.z, 0));
        a_line3_tgt(&ctx, &p);
        TEST_BUG(iseq(p.x, 0));
        TEST_BUG(iseq(p.y, 3));
        TEST_BUG(iseq(p.z, 4));
        v = *a_line3_dir(&ctx);
        TEST_BUG(iseq(v.x, 0));
        TEST_BUG(iseq(v.y, A_REAL_C(0.6)));
        TEST_BUG(iseq(v.z, A_REAL_C(0.8)));
        TEST_BUG(iseq(a_line3_len(&ctx), 5));
    }
    {
        a_real w;
        a_line3 ctx;
        a_point3 a = A_POINT3_C(0, 0, 0);
        a_point3 b = A_POINT3_C(1, 1, 0);
        a_point3 c = A_POINT3_C(2, 0, 0);
        TEST_BUG(a_line3_set(&ctx, &a, &b) == 0);
        w = a_line3_proj(&ctx, &c, &c);
        TEST_BUG(iseq(c.x, 1));
        TEST_BUG(iseq(c.y, 1));
        TEST_BUG(iseq(c.z, 0));
        a_line3_eval(&ctx, w, &a);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 0));
    }
    {
        a_line3 ctx;
        a_point3 const a = A_POINT3_C(0, 0, 0);
        a_point3 const b = A_POINT3_C(1, 1, 1);
        a_point3 const c = A_POINT3_C(0, 1, 2);
        TEST_BUG(a_line3_set(&ctx, &a, &b) == 0);
        TEST_BUG(iseq(a_line3_dist2(&ctx, &c), 2));
        TEST_BUG(iseq(a_line3_dist1(&ctx, &c), A_REAL_SQRT1_3 * 4));
        TEST_BUG(iseq(a_line3_dist(&ctx, &c), A_REAL_SQRT2));
    }
    (void)argv;
    (void)argc;
    return 0;
}
