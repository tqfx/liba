#define MAIN(x) line3##x
#include "test.h"
#include "a/line3.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return A_ABS_(a, b) < A_REAL_TOL;
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
        TEST_BUG(iseq(a_line3_lim(&ctx), 5));
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
        TEST_BUG(iseq(a_line3_lim(&ctx), 5));
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
        TEST_BUG(iseq(a_line3_dist(&ctx, &c), A_REAL_SQRT2));
    }
    {
        a_real t1, t2;
        a_line3 l1, l2;
        a_point3 p1, p2;
        a_point3 const p = A_POINT3_C(0, 0, 0);
        a_point3 const q = A_POINT3_C(5, 3, 0);
        a_vector3 const u = A_VECTOR3_C(1, 1, 0);
        a_vector3 const v = A_VECTOR3_C(0, 1, 0);
        a_point3 const w = A_POINT3_C(5, 5, 0);
        a_line3_setv(&l1, &p, &u);
        a_line3_setv(&l2, &p, &u);
        TEST_BUG(a_line3_int1(&l1, &l2, 0, +1, 0, +1, &t1, &t2) == 2);
        TEST_BUG(a_line3_int1(&l1, &l2, -1, 0, 0, +1, &t1, &t2) == 1);
        TEST_BUG(iseq(t1, 0));
        TEST_BUG(iseq(t2, 0));
        a_line3_setv(&l2, &p, &v);
        TEST_BUG(a_line3_int1(&l1, &l2, -1, 0, -1, 0, &t1, &t2) == 1);
        TEST_BUG(iseq(t1, 0));
        TEST_BUG(iseq(t2, 0));
        a_line3_setv(&l2, &q, &u);
        TEST_BUG(a_line3_int1(&l1, &l2, 0, 10, 0, 10, &t1, &t2) == 0);
        a_line3_setv(&l2, &q, &v);
        TEST_BUG(a_line3_int1(&l1, &l2, 0, 10, 0, 10, &t1, &t2) == 1);
        a_line3_eval(&l1, t1, &p1);
        TEST_BUG(iseq(p1.x, w.x));
        TEST_BUG(iseq(p1.y, w.y));
        TEST_BUG(iseq(p1.z, w.z));
        a_line3_eval(&l2, t2, &p2);
        TEST_BUG(iseq(p2.x, w.x));
        TEST_BUG(iseq(p2.y, w.y));
        TEST_BUG(iseq(p2.z, w.z));
        TEST_BUG(a_line3_int0(&l1, &w, 0, 10, &t1) == 1);
        TEST_BUG(a_line3_int0(&l2, &w, 0, 10, &t2) == 1);
        a_line3_eval(&l1, t1, &p1);
        TEST_BUG(iseq(p1.x, w.x));
        TEST_BUG(iseq(p1.y, w.y));
        TEST_BUG(iseq(p1.z, w.z));
        a_line3_eval(&l2, t2, &p2);
        TEST_BUG(iseq(p2.x, w.x));
        TEST_BUG(iseq(p2.y, w.y));
        TEST_BUG(iseq(p2.z, w.z));
    }
    {
        a_line3 ctx, rhs;
        a_point3 o = A_POINT3_C(1, 1, 0);
        a_point3 p = A_POINT3_C(3, 3, 3);
        a_vector3 u = A_POINT3_C(1, 1, 0);
        a_vector3 v = A_POINT3_C(0, 0, 1);
        a_line3_setv(&ctx, &o, &u);
        a_line3_setv(&rhs, &p, &v);
        a_line3_rot(&ctx, &rhs, +A_REAL_PI_2, &ctx);
        a_line3_rot(&ctx, &rhs, +A_REAL_PI_2, &ctx);
        TEST_BUG(iseq(ctx.dir_.x, -A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.dir_.y, -A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.dir_.z, 0));
        TEST_BUG(iseq(ctx.orig.x, +5));
        TEST_BUG(iseq(ctx.orig.y, +5));
        TEST_BUG(iseq(ctx.orig.z, 0));
        a_line3_rot(&ctx, &rhs, -A_REAL_PI, &ctx);
        TEST_BUG(iseq(ctx.dir_.x, +A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.dir_.y, +A_REAL_SQRT1_2));
        TEST_BUG(iseq(ctx.dir_.z, 0));
        TEST_BUG(iseq(ctx.orig.x, +1));
        TEST_BUG(iseq(ctx.orig.y, +1));
        TEST_BUG(iseq(ctx.orig.z, 0));
    }
    {
        a_vector3 v1 = A_VECTOR3_C(1, 0, 0);
        a_vector3 v2 = A_VECTOR3_C(0, 1, 0);
        a_point3 p1 = A_POINT3_C(0, 0, 0);
        a_point3 p2 = A_POINT3_C(0, 0, 0);
        a_point3 q1, q2;
        a_line3 l1, l2;
        a_real w1, w2, s;
        a_line3_setv(&l1, &p1, &v1);
        a_line3_setv(&l2, &p2, &v2);
        a_line3_set_dir(&l2, 0, 1, 0);
        s = a_line3_segdist2(&l1, &l2, -10, +10, -10, +10, &w1, &w2, &q1, &q2);
        TEST_BUG(iseq(q2.x, 0));
        TEST_BUG(iseq(q2.y, 0));
        TEST_BUG(iseq(q2.z, 0));
        TEST_BUG(iseq(q1.x, 0));
        TEST_BUG(iseq(q1.y, 0));
        TEST_BUG(iseq(q1.z, 0));
        TEST_BUG(iseq(w2, 0));
        TEST_BUG(iseq(w1, 0));
        TEST_BUG(iseq(s, 0));
        a_line3_set_dir(&l2, 1, 0, 0);
        s = a_line3_segdist2(&l1, &l2, -10, +10, -10, +10, &w1, &w2, &q1, &q2);
        TEST_BUG(iseq(q2.x, -10));
        TEST_BUG(iseq(q2.y, 0));
        TEST_BUG(iseq(q2.z, 0));
        TEST_BUG(iseq(q1.x, -10));
        TEST_BUG(iseq(q1.y, 0));
        TEST_BUG(iseq(q1.z, 0));
        TEST_BUG(iseq(w2, -10));
        TEST_BUG(iseq(w1, -10));
        TEST_BUG(iseq(s, 0));
        a_line3_set_org(&l1, 0, +1, +1);
        a_line3_set_org(&l2, +1, 0, -1);
        a_line3_set_dir(&l2, 0, 1, 0);
        s = a_line3_segdist(&l1, &l2, -10, +10, -10, +10, &w1, &w2, &q1, &q2);
        TEST_BUG(iseq(q2.z, -1));
        TEST_BUG(iseq(q2.y, 1));
        TEST_BUG(iseq(q2.x, 1));
        TEST_BUG(iseq(q1.z, 1));
        TEST_BUG(iseq(q1.y, 1));
        TEST_BUG(iseq(q1.x, 1));
        TEST_BUG(iseq(w2, 1));
        TEST_BUG(iseq(w1, 1));
        TEST_BUG(iseq(s, 2));
    }
    (void)argv;
    (void)argc;
    return 0;
}
