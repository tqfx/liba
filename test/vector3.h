#define MAIN(x) vector3##x
#include "a/vector3.h"
#include "test.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return a_real_abs(a - b) < A_REAL_EPS;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_vector3 a;
        a_real x, y, z;
        a_vector3_set_xyz(&a, 1, 2, 3);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
        TEST_BUG(iseq(a.z, 3));
#if defined(__cplusplus)
        a.set_xyz(1, 2, 3);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
        TEST_BUG(iseq(a.z, 3));
#endif /* __cplusplus */
        a_vector3_xyz(&a, &x, &y, &z);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
        TEST_BUG(iseq(z, 3));
#if defined(__cplusplus)
        a.xyz(x, y, z);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
        TEST_BUG(iseq(z, 3));
#endif /* __cplusplus */
        a_vector3_set_pol(&a, A_REAL_SQRT2, A_REAL_PI_4, 1);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#if defined(__cplusplus)
        a.set_pol(A_REAL_SQRT2, A_REAL_PI_4, 1);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#endif /* __cplusplus */
        a_vector3_pol(&a, &x, &y, &z);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
        TEST_BUG(iseq(z, 1));
#if defined(__cplusplus)
        a.pol(x, y, z);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
        TEST_BUG(iseq(z, 1));
#endif /* __cplusplus */
        a_vector3_set_sph(&a, A_REAL_SQRT3, A_REAL_PI_4, a_real_atan(A_REAL_SQRT1_2));
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#if defined(__cplusplus)
        a.set_sph(A_REAL_SQRT3, A_REAL_PI_4, a_real_atan(A_REAL_SQRT1_2));
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
        TEST_BUG(iseq(a.z, 1));
#endif /* __cplusplus */
        a_vector3_sph(&a, &x, &y, &z);
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
        a_vector3 a = A_VECTOR3_C(1, 2, 3);
        a_vector3 b = A_VECTOR3_C(1, 2, 3);
        a_vector3 c = A_VECTOR3_C(0, 0, 0);
        TEST_BUG(iseq(a_vector3_angle(&a, &b), 0));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.angle(b), 0));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector3_dot(&a, &b), 14));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dot(b), 14));
#endif /* __cplusplus */
        TEST_BUG(a_vector3_ispar(&a, &b));
#if defined(__cplusplus)
        TEST_BUG(a.ispar(b));
#endif /* __cplusplus */
        a_vector3_cross(&a, &b, &c);
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 0));
        TEST_BUG(iseq(c.z, 0));
#if defined(__cplusplus)
        c = a ^ b;
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 0));
        TEST_BUG(iseq(c.z, 0));
#endif /* __cplusplus */
        a_vector3_add(&a, &b, &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#if defined(__cplusplus)
        c = a + b;
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#endif /* __cplusplus */
        a_vector3_sub(&a, &b, &c);
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 0));
        TEST_BUG(iseq(c.z, 0));
#if defined(__cplusplus)
        c = a - b;
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 0));
        TEST_BUG(iseq(c.z, 0));
#endif /* __cplusplus */
        a_vector3_mul(&a, 2, &c);
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
        a_vector3_div(&a, A_REAL_C(0.5), &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#if defined(__cplusplus)
        c = a / A_REAL_C(0.5);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
        TEST_BUG(iseq(c.z, 6));
#endif /* __cplusplus */
        a_vector3_neg(&a, &c);
#if defined(__cplusplus)
        c = -a;
        TEST_BUG(iseq(c.x, -1));
        TEST_BUG(iseq(c.y, -2));
        TEST_BUG(iseq(c.z, -3));
#endif /* __cplusplus */
    }
    {
        a_vector3 a = A_VECTOR3_C(3, 4, -12);
        TEST_BUG(iseq(a_vector3_norm(&a), 13));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.norm(), 13));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector3_norm1(&a), 19));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.norm1(), 19));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector3_norm2(&a), 13 * 13));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.norm2(), 13 * 13));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector3_unit(&a), 13));
        TEST_BUG(iseq(a_vector3_norm2(&a), 1));
#if defined(__cplusplus)
        a.set_xyz(3, 4, -12);
        TEST_BUG(iseq(a.unit(), 13));
        TEST_BUG(iseq(a.norm2(), 1));
#endif /* __cplusplus */
    }
    {
        a_vector3 a = A_VECTOR3_C(0, 0, 0);
        a_vector3 b = A_VECTOR3_C(3, 4, -12);
        TEST_BUG(iseq(a_vector3_dist(&a, &b), 13));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist(b), 13));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector3_dist1(&a, &b), 19));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist1(b), 19));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector3_dist2(&a, &b), 13 * 13));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist2(b), 13 * 13));
#endif /* __cplusplus */
    }
    {
        a_vector3 a = A_VECTOR3_C(1, 0, 0);
        a_vector3 b = A_VECTOR3_C(0, 1, 0);
        TEST_BUG(a_vector3_isver(&a, &b));
#if defined(__cplusplus)
        TEST_BUG(a.isver(b));
#endif /* __cplusplus */
    }
    (void)argv;
    (void)argc;
    return 0;
}
