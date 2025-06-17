#define MAIN(x) plane##x
#include "test.h"
#include "a/plane.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return A_ABS_(a, b) < A_REAL_EPS;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_plane ctx;
        a_point3 p = A_POINT3_C(0, 0, 0);
        a_vector3 u = A_VECTOR3_C(10, 0, 0);
        a_vector3 v = A_VECTOR3_C(0, 10, 0);
        a_vector3 n = A_VECTOR3_C(0, 0, 10);
        TEST_BUG(a_plane_set(&ctx, &p, &n) == 0);
        TEST_BUG(iseq(ctx.orig.x, 0));
        TEST_BUG(iseq(ctx.orig.y, 0));
        TEST_BUG(iseq(ctx.orig.z, 0));
        TEST_BUG(iseq(ctx.dir_.x, 0));
        TEST_BUG(iseq(ctx.dir_.y, 0));
        TEST_BUG(iseq(ctx.dir_.z, 1));
        TEST_BUG(iseq(a_plane_org(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->z, 0));
        TEST_BUG(iseq(a_plane_dir(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_dir(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_dir(&ctx)->z, 1));
        TEST_BUG(iseq(ctx.u_.x, +1));
        TEST_BUG(iseq(ctx.u_.y, 0));
        TEST_BUG(iseq(ctx.u_.z, 0));
        TEST_BUG(iseq(ctx.v_.x, 0));
        TEST_BUG(iseq(ctx.v_.y, +1));
        TEST_BUG(iseq(ctx.v_.z, 0));
        a_plane_rot2d(&ctx, A_REAL_PI);
        TEST_BUG(a_plane_set_uv(&ctx, &n, &n) != 0);
        TEST_BUG(iseq(ctx.u_.x, -1));
        TEST_BUG(iseq(ctx.u_.y, 0));
        TEST_BUG(iseq(ctx.u_.z, 0));
        TEST_BUG(iseq(ctx.v_.x, 0));
        TEST_BUG(iseq(ctx.v_.y, -1));
        TEST_BUG(iseq(ctx.v_.z, 0));
        TEST_BUG(a_plane_set_uv(&ctx, &u, &v) == 0);
        TEST_BUG(iseq(ctx.u_.x, +1));
        TEST_BUG(iseq(ctx.u_.y, 0));
        TEST_BUG(iseq(ctx.u_.z, 0));
        TEST_BUG(iseq(ctx.v_.x, 0));
        TEST_BUG(iseq(ctx.v_.y, +1));
        TEST_BUG(iseq(ctx.v_.z, 0));
        a_plane_rot2d(&ctx, A_REAL_PI);
        TEST_BUG(a_plane_set_u(&ctx, &u, &u) != 0);
        TEST_BUG(iseq(ctx.u_.x, -1));
        TEST_BUG(iseq(ctx.u_.y, 0));
        TEST_BUG(iseq(ctx.u_.z, 0));
        TEST_BUG(iseq(ctx.v_.x, 0));
        TEST_BUG(iseq(ctx.v_.y, -1));
        TEST_BUG(iseq(ctx.v_.z, 0));
        TEST_BUG(a_plane_set_u(&ctx, &n, &u) == 0);
        TEST_BUG(iseq(ctx.u_.x, +1));
        TEST_BUG(iseq(ctx.u_.y, 0));
        TEST_BUG(iseq(ctx.u_.z, 0));
        TEST_BUG(iseq(ctx.v_.x, 0));
        TEST_BUG(iseq(ctx.v_.y, +1));
        TEST_BUG(iseq(ctx.v_.z, 0));
        a_plane_rot2d(&ctx, A_REAL_PI);
        TEST_BUG(a_plane_set_v(&ctx, &v, &v) != 0);
        TEST_BUG(iseq(ctx.u_.x, -1));
        TEST_BUG(iseq(ctx.u_.y, 0));
        TEST_BUG(iseq(ctx.u_.z, 0));
        TEST_BUG(iseq(ctx.v_.x, 0));
        TEST_BUG(iseq(ctx.v_.y, -1));
        TEST_BUG(iseq(ctx.v_.z, 0));
        TEST_BUG(a_plane_set_v(&ctx, &n, &v) == 0);
        TEST_BUG(iseq(ctx.u_.x, +1));
        TEST_BUG(iseq(ctx.u_.y, 0));
        TEST_BUG(iseq(ctx.u_.z, 0));
        TEST_BUG(iseq(ctx.v_.x, 0));
        TEST_BUG(iseq(ctx.v_.y, +1));
        TEST_BUG(iseq(ctx.v_.z, 0));
#if defined(__cplusplus)
        ctx.set_org(1, 2, 3);
        TEST_BUG(iseq(ctx.orig.x, 1));
        TEST_BUG(iseq(ctx.orig.y, 2));
        TEST_BUG(iseq(ctx.orig.z, 3));
        TEST_BUG(ctx.set_dir(0, 0, 1) == 0);
        TEST_BUG(iseq(ctx.dir_.x, 0));
        TEST_BUG(iseq(ctx.dir_.y, 0));
        TEST_BUG(iseq(ctx.dir_.z, 1));
#endif /* __cplusplus */
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
        TEST_BUG(iseq(ctx.dir_.x, 0));
        TEST_BUG(iseq(ctx.dir_.y, 0));
        TEST_BUG(iseq(ctx.dir_.z, 1));
        TEST_BUG(iseq(a_plane_org(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_org(&ctx)->z, 0));
        TEST_BUG(iseq(a_plane_dir(&ctx)->x, 0));
        TEST_BUG(iseq(a_plane_dir(&ctx)->y, 0));
        TEST_BUG(iseq(a_plane_dir(&ctx)->z, 1));
    }
    {
        a_plane ctx;
        TEST_BUG(a_plane_set4(&ctx, 1, 1, 1, -3) == 0);
        TEST_BUG(iseq(ctx.orig.x, 1));
        TEST_BUG(iseq(ctx.orig.y, 1));
        TEST_BUG(iseq(ctx.orig.z, 1));
        TEST_BUG(iseq(ctx.dir_.x, A_REAL_SQRT1_3));
        TEST_BUG(iseq(ctx.dir_.y, A_REAL_SQRT1_3));
        TEST_BUG(iseq(ctx.dir_.z, A_REAL_SQRT1_3));
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
    {
        a_line3 l;
        a_point3 o;
        a_plane ctx;
        a_real s, t;
        a_point3 const p = A_POINT3_C(0, 0, 0);
        a_point3 const q = A_POINT3_C(0, 0, -4);
        a_vector3 const n = A_VECTOR3_C(0, 0, 1);
        a_vector3 const u = A_VECTOR3_C(0, 3, 4);
        a_vector3 const v = A_VECTOR3_C(1, 0, 0);
        a_plane_set(&ctx, &p, &n);
        a_line3_setv(&l, &p, &v);
        TEST_BUG(a_plane_int1(&ctx, &l, 0, 10, &t) == 2);
        a_line3_setv(&l, &q, &v);
        TEST_BUG(a_plane_int1(&ctx, &l, 0, 10, &t) == 0);
        a_line3_setv(&l, &q, &u);
        TEST_BUG(a_plane_int1(&ctx, &l, 0, 10, &t) == 1);
        a_line3_eval(&l, t, &o);
        TEST_BUG(iseq(o.x, 0));
        TEST_BUG(iseq(o.y, 3));
        TEST_BUG(iseq(o.z, 0));
        TEST_BUG(iseq(t, 5));
        TEST_BUG(a_plane_int0(&ctx, &q, &s, &t) == 0);
        TEST_BUG(a_plane_int0(&ctx, &o, &s, &t) == 1);
        a_plane_eval(&ctx, s, t, &o);
        TEST_BUG(iseq(o.x, 0));
        TEST_BUG(iseq(o.y, 3));
        TEST_BUG(iseq(o.z, 0));
        TEST_BUG(iseq(s, 0));
        TEST_BUG(iseq(t, 3));
    }
    {
        a_line3 res;
        a_plane ctx, rhs;
        a_point3 o = A_POINT3_C(0, 1, 0);
        a_point3 p = A_POINT3_C(1, 2, 3);
        a_vector3 u = A_VECTOR3_C(1, 0, 0);
        a_vector3 v = A_VECTOR3_C(1, 1, 0);
        a_plane_set(&ctx, &o, &u);
        a_plane_set(&rhs, &p, &u);
        TEST_BUG(a_plane_int2(&ctx, &rhs, &res) == 0);
        a_plane_set(&rhs, &o, &u);
        TEST_BUG(a_plane_int2(&ctx, &rhs, &res) == 2);
        a_plane_set(&rhs, &p, &v);
        TEST_BUG(a_plane_int2(&ctx, &rhs, &res) == 1);
        TEST_BUG(iseq(res.orig.x, 0));
        TEST_BUG(iseq(res.orig.y, 3));
        TEST_BUG(iseq(res.orig.z, 0));
        TEST_BUG(iseq(res.dir_.x, 0));
        TEST_BUG(iseq(res.dir_.y, 0));
        TEST_BUG(iseq(res.dir_.z, 1));
        TEST_BUG(iseq(res.max, 1));
    }
    (void)argv;
    (void)argc;
    return 0;
}
