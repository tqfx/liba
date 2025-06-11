#define MAIN(x) line2##x
#include "test.h"
#include "a/line2.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return A_ABS_(a, b) < A_REAL_EPS;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_line2 ctx;
        a_vector2 u;
        a_point2 a = A_POINT2_C(0, 0);
        a_point2 b = A_POINT2_C(3, 4);
        TEST_BUG(a_line2_set(&ctx, &a, &b) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.dir_.x, A_REAL_C(0.6)));
        TEST_BUG(iseq(ctx.dir_.y, A_REAL_C(0.8)));
        TEST_BUG(iseq(ctx.max, 5));
        b = *a_line2_org(&ctx);
        TEST_BUG(iseq(b.x, 0));
        TEST_BUG(iseq(b.y, 0));
        a_line2_tgt(&ctx, &a);
        TEST_BUG(iseq(a.x, 3));
        TEST_BUG(iseq(a.y, 4));
        u = *a_line2_dir(&ctx);
        TEST_BUG(iseq(u.x, A_REAL_C(0.6)));
        TEST_BUG(iseq(u.y, A_REAL_C(0.8)));
        TEST_BUG(iseq(a_line2_len(&ctx), 5));
#if defined(__cplusplus)
        ctx.set_org(1, 2);
        TEST_BUG(iseq(ctx.orig.x, 1));
        TEST_BUG(iseq(ctx.orig.y, 2));
        TEST_BUG(ctx.set_dir(1, 0) == 0);
        TEST_BUG(iseq(ctx.dir_.x, 1));
        TEST_BUG(iseq(ctx.dir_.y, 0));
#endif /* __cplusplus */
    }
    {
        a_line2 ctx;
        a_point2 p = A_POINT2_C(0, 0);
        a_vector2 v = A_VECTOR2_C(3, 4);
        TEST_BUG(a_line2_setv(&ctx, &p, &v) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.dir_.x, A_REAL_C(0.6)));
        TEST_BUG(iseq(ctx.dir_.y, A_REAL_C(0.8)));
        TEST_BUG(iseq(ctx.max, 5));
        p = *a_line2_org(&ctx);
        TEST_BUG(iseq(p.x, 0));
        TEST_BUG(iseq(p.y, 0));
        a_line2_tgt(&ctx, &p);
        TEST_BUG(iseq(p.x, 3));
        TEST_BUG(iseq(p.y, 4));
        v = *a_line2_dir(&ctx);
        TEST_BUG(iseq(v.x, A_REAL_C(0.6)));
        TEST_BUG(iseq(v.y, A_REAL_C(0.8)));
        TEST_BUG(iseq(a_line2_len(&ctx), 5));
    }
    {
        a_real w;
        a_line2 ctx;
        a_point2 a = A_POINT2_C(0, 0);
        a_point2 b = A_POINT2_C(1, 1);
        a_point2 c = A_POINT2_C(2, 0);
        TEST_BUG(a_line2_set(&ctx, &a, &b) == 0);
        w = a_line2_proj(&ctx, &c, &c);
        TEST_BUG(iseq(c.x, 1));
        TEST_BUG(iseq(c.y, 1));
        a_line2_eval(&ctx, w, &a);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
    }
    {
        a_line2 ctx;
        a_point2 const a = A_POINT2_C(0, 0);
        a_point2 const b = A_POINT2_C(1, 1);
        a_point2 const c = A_POINT2_C(0, 1);
        a_point2 const d = A_POINT2_C(1, 0);
        TEST_BUG(a_line2_set(&ctx, &a, &b) == 0);
        TEST_BUG(iseq(a_line2_dist(&ctx, &c), A_REAL_SQRT1_2));
        TEST_BUG(iseq(a_line2_sdist(&ctx, &c), +A_REAL_SQRT1_2));
        TEST_BUG(iseq(a_line2_sdist(&ctx, &d), -A_REAL_SQRT1_2));
    }
    {
        a_real t1, t2;
        a_line2 l1, l2;
        a_point2 p1, p2;
        a_point2 const p = A_POINT2_C(0, 0);
        a_point2 const q = A_POINT2_C(5, 3);
        a_vector2 const u = A_VECTOR2_C(1, 1);
        a_vector2 const v = A_VECTOR2_C(0, 1);
        a_point2 const w = A_POINT2_C(5, 5);
        a_line2_setv(&l1, &p, &u);
        a_line2_setv(&l2, &p, &u);
        TEST_BUG(a_line2_int1(&l1, &l2, 0, +1, 0, +1, &t1, &t2) == 2);
        TEST_BUG(a_line2_int1(&l1, &l2, -1, 0, 0, +1, &t1, &t2) == 1);
        TEST_BUG(iseq(t1, 0));
        TEST_BUG(iseq(t2, 0));
        a_line2_setv(&l2, &p, &v);
        TEST_BUG(a_line2_int1(&l1, &l2, -1, 0, -1, 0, &t1, &t2) == 1);
        TEST_BUG(iseq(t1, 0));
        TEST_BUG(iseq(t2, 0));
        a_line2_setv(&l2, &q, &u);
        TEST_BUG(a_line2_int1(&l1, &l2, 0, 10, 0, 10, &t1, &t2) == 0);
        a_line2_setv(&l2, &q, &v);
        TEST_BUG(a_line2_int1(&l1, &l2, 0, 10, 0, 10, &t1, &t2) == 1);
        a_line2_eval(&l1, t1, &p1);
        TEST_BUG(iseq(p1.x, w.x));
        TEST_BUG(iseq(p1.y, w.y));
        a_line2_eval(&l2, t2, &p2);
        TEST_BUG(iseq(p2.x, w.x));
        TEST_BUG(iseq(p2.y, w.y));
        TEST_BUG(a_line2_int0(&l1, &w, 0, 10, &t1) == 1);
        TEST_BUG(a_line2_int0(&l2, &w, 0, 10, &t2) == 1);
        a_line2_eval(&l1, t1, &p1);
        TEST_BUG(iseq(p1.x, w.x));
        TEST_BUG(iseq(p1.y, w.y));
        a_line2_eval(&l2, t2, &p2);
        TEST_BUG(iseq(p2.x, w.x));
        TEST_BUG(iseq(p2.y, w.y));
    }
    {
        a_line2 ctx;
        a_point2 o = A_POINT2_C(1, 1);
        a_point2 p = A_POINT2_C(3, 3);
        a_vector2 u = A_POINT2_C(1, 1);
        a_line2_setv(&ctx, &o, &u);
        a_line2_rot(&ctx, &p, +A_REAL_PI_2, &ctx);
        a_line2_rot(&ctx, &p, +A_REAL_PI_2, &ctx);
        TEST_BUG(iseq(ctx.dir_.x, -A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.dir_.y, -A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.orig.x, +5));
        TEST_BUG(iseq(ctx.orig.y, +5));
        a_line2_rot(&ctx, &p, -A_REAL_PI, &ctx);
        TEST_BUG(iseq(ctx.dir_.x, +A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.dir_.y, +A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.orig.x, +1));
        TEST_BUG(iseq(ctx.orig.y, +1));
    }
    (void)argv;
    (void)argc;
    return 0;
}
