#define MAIN(x) line2##x
#include "test.h"
#include "a/line2.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return a_real_abs(a - b) < A_REAL_EPS;
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
        TEST_BUG(iseq(ctx.dir.x, A_REAL_C(0.6)));
        TEST_BUG(iseq(ctx.dir.y, A_REAL_C(0.8)));
        TEST_BUG(iseq(ctx.max, 5));
        a_line2_org(&ctx, &b);
        TEST_BUG(iseq(b.x, 0));
        TEST_BUG(iseq(b.y, 0));
        a_line2_tgt(&ctx, &a);
        TEST_BUG(iseq(a.x, 3));
        TEST_BUG(iseq(a.y, 4));
        a_line2_dir(&ctx, &u);
        TEST_BUG(iseq(u.x, A_REAL_C(0.6)));
        TEST_BUG(iseq(u.y, A_REAL_C(0.8)));
        TEST_BUG(iseq(a_line2_len(&ctx), 5));
    }
    {
        a_line2 ctx;
        a_point2 p = A_POINT2_C(0, 0);
        a_vector2 v = A_VECTOR2_C(3, 4);
        TEST_BUG(a_line2_setv(&ctx, &p, &v) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.dir.x, A_REAL_C(0.6)));
        TEST_BUG(iseq(ctx.dir.y, A_REAL_C(0.8)));
        TEST_BUG(iseq(ctx.max, 5));
        a_line2_org(&ctx, &p);
        TEST_BUG(iseq(p.x, 0));
        TEST_BUG(iseq(p.y, 0));
        a_line2_tgt(&ctx, &p);
        TEST_BUG(iseq(p.x, 3));
        TEST_BUG(iseq(p.y, 4));
        a_line2_dir(&ctx, &v);
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
        TEST_BUG(iseq(a_line2_dist_(&ctx, &c), +A_REAL_SQRT1_2));
        TEST_BUG(iseq(a_line2_dist_(&ctx, &d), -A_REAL_SQRT1_2));
    }
    (void)argv;
    (void)argc;
    return 0;
}
