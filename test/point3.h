#define MAIN(x) point3##x
#include "test.h"
#include "a/point3.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return A_ABS_(a, b) < A_REAL_TOL;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_point3 a;
        a_real x, y, z;
        a_point3_set_val(&a, 1, 2, 3);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
        TEST_BUG(iseq(a.z, 3));
#if defined(__cplusplus)
        a.set_val(1, 2, 3);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
        TEST_BUG(iseq(a.z, 3));
#endif /* __cplusplus */
        a_point3_val(&a, &x, &y, &z);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
        TEST_BUG(iseq(z, 3));
#if defined(__cplusplus)
        a.val(x, y, z);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
        TEST_BUG(iseq(z, 3));
#endif /* __cplusplus */
        a_point3_set_cyl(&a, A_REAL_SQRT2, A_REAL_PI_4, 1);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#if defined(__cplusplus)
        a.set_cyl(A_REAL_SQRT2, A_REAL_PI_4, 1);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#endif /* __cplusplus */
        a_point3_cyl(&a, &x, &y, &z);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
        TEST_BUG(iseq(z, 1));
#if defined(__cplusplus)
        a.cyl(x, y, z);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
        TEST_BUG(iseq(z, 1));
#endif /* __cplusplus */
        a_point3_set_sph(&a, A_REAL_SQRT3, A_REAL_PI_4, a_real_atan(A_REAL_SQRT1_2));
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#if defined(__cplusplus)
        a.set_sph(A_REAL_SQRT3, A_REAL_PI_4, a_real_atan(A_REAL_SQRT1_2));
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#endif /* __cplusplus */
        a_point3_sph(&a, &x, &y, &z);
        TEST_BUG(iseq(x, A_REAL_SQRT3));
        TEST_BUG(iseq(y, A_REAL_PI_4));
        TEST_BUG(iseq(z, a_real_atan(A_REAL_SQRT1_2)));
#if defined(__cplusplus)
        a.sph(x, y, z);
        TEST_BUG(iseq(x, A_REAL_SQRT3));
        TEST_BUG(iseq(y, A_REAL_PI_4));
        TEST_BUG(iseq(z, a_real_atan(A_REAL_SQRT1_2)));
#endif /* __cplusplus */
    }
    {
        a_vector3 v = A_VECTOR3_C(1, 1, 1);
        a_point3 a = A_POINT3_C(1, 2, 3);
        a_point3 c = A_POINT3_C(2, 3, 4);
        a_vector3_set(&v, &a, &c);
        TEST_BUG(iseq(v.x, 1));
        TEST_BUG(iseq(v.y, 1));
        TEST_BUG(iseq(v.z, 1));
#if defined(__cplusplus)
        v = c - a;
        TEST_BUG(iseq(v.x, 1));
        TEST_BUG(iseq(v.y, 1));
        TEST_BUG(iseq(v.z, 1));
#endif /* __cplusplus */
        a_point3_add(&a, &v, &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 3));
        TEST_BUG(iseq(c.z, 4));
#if defined(__cplusplus)
        c = a + v;
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 3));
        TEST_BUG(iseq(c.z, 4));
#endif /* __cplusplus */
        a_point3_sub(&a, &v, &c);
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 1));
        TEST_BUG(iseq(c.z, 2));
#if defined(__cplusplus)
        c = a - v;
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 1));
        TEST_BUG(iseq(c.z, 2));
#endif /* __cplusplus */
        a_point3_mul(&a, 2, &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#if defined(__cplusplus)
        c = a * 3;
        TEST_BUG(iseq(c.x, 3));
        TEST_BUG(iseq(c.y, 6));
        TEST_BUG(iseq(c.z, 9));
        c = 2 * a;
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#endif /* __cplusplus */
        a_point3_div(&a, A_REAL_C(0.5), &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#if defined(__cplusplus)
        c = a / A_REAL_C(0.5);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#endif /* __cplusplus */
    }
    {
        a_point3 a = A_VECTOR3_C(0, 0, 0);
        a_point3 b = A_VECTOR3_C(3, 4, -12);
        TEST_BUG(iseq(a_point3_dist(&a, &b), 13));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist(b), 13));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_point3_dist2(&a, &b), 13 * 13));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist2(b), 13 * 13));
#endif /* __cplusplus */
    }
    (void)argv;
    (void)argc;
    return 0;
}
