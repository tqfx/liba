#define MAIN(x) plane##x
#include "test.h"
#include "a/plane.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return a_real_abs(a - b) < A_REAL_EPS;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_plane ctx;
        a_point3 p = A_POINT3_C(0, 0, 0);
        a_vector3 v = A_VECTOR3_C(0, 0, 10);
        TEST_BUG(a_plane_set(&ctx, &p, &v) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.orig.z, 0));
        TEST_BUG(iseq(ctx.nor_.x, 0));
        TEST_BUG(iseq(ctx.nor_.y, 0));
        TEST_BUG(iseq(ctx.nor_.z, 1));
        TEST_BUG(iseq(a_plane_org(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->z, 0));
        TEST_BUG(iseq(a_plane_nor(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_nor(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_nor(&ctx)->z, 1));
    }
    {
        a_plane ctx;
        a_point3 a = A_POINT3_C(0, 0, 0);
        a_point3 b = A_POINT3_C(1, 0, 0);
        a_point3 c = A_POINT3_C(1, 1, 0);
        TEST_BUG(a_plane_set3(&ctx, &a, &b, &c) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.orig.z, 0));
        TEST_BUG(iseq(ctx.nor_.x, 0));
        TEST_BUG(iseq(ctx.nor_.y, 0));
        TEST_BUG(iseq(ctx.nor_.z, 1));
        TEST_BUG(iseq(a_plane_org(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->z, 0));
        TEST_BUG(iseq(a_plane_nor(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_nor(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_nor(&ctx)->z, 1));
    }
    {
        a_plane ctx;
        TEST_BUG(a_plane_set4(&ctx, 1, 1, 1, -3) == 0);
        TEST_BUG(iseq(ctx.orig.x, 1));
        TEST_BUG(iseq(ctx.orig.y, 1));
        TEST_BUG(iseq(ctx.orig.z, 1));
        TEST_BUG(iseq(ctx.nor_.x, A_REAL_SQRT1_3));
        TEST_BUG(iseq(ctx.nor_.y, A_REAL_SQRT1_3));
        TEST_BUG(iseq(ctx.nor_.z, A_REAL_SQRT1_3));
    }
    {
        a_plane ctx;
        a_point3 a = A_POINT3_C(0, 0, 0);
        a_point3 b = A_POINT3_C(1, 0, 0);
        a_point3 c = A_POINT3_C(1, 1, 0);
        a_point3 p = A_POINT3_C(1, 1, 2);
        TEST_BUG(a_plane_set3(&ctx, &a, &b, &c) == 0);
        TEST_BUG(iseq(a_plane_proj(&ctx, &p, &p), 2));
        TEST_BUG(iseq(p.x, 1));
        TEST_BUG(iseq(p.y, 1));
        TEST_BUG(iseq(p.z, 0));
    }
    {
        a_plane ctx;
        a_point3 p = A_POINT3_C(0, 0, 0);
        a_point3 a = A_POINT3_C(0, 0, 2);
        a_point3 b = A_POINT3_C(0, 0, -2);
        a_vector3 v = A_VECTOR3_C(0, 0, 10);
        TEST_BUG(a_plane_set(&ctx, &p, &v) == 0);
        TEST_BUG(iseq(a_plane_dist(&ctx, &a), 2));
        TEST_BUG(iseq(a_plane_sdist(&ctx, &a), +2));
        TEST_BUG(iseq(a_plane_dist(&ctx, &b), 2));
        TEST_BUG(iseq(a_plane_sdist(&ctx, &b), -2));
    }
    (void)argv;
    (void)argc;
    return 0;
}
