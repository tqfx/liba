#define MAIN(x) vector2##x
#include "test.h"
#include "a/vector2.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return a_real_abs(a - b) < A_REAL_EPS;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_vector2 a;
        a_real x, y;
        a_vector2_set_xy(&a, 1, 2);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
#if defined(__cplusplus)
        a.set_xy(1, 2);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
#endif /* __cplusplus */
        a_vector2_xy(&a, &x, &y);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
#if defined(__cplusplus)
        a.xy(x, y);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
#endif /* __cplusplus */
        a_vector2_set_pol(&a, A_REAL_SQRT2, A_REAL_PI_4);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
#if defined(__cplusplus)
        a.set_pol(A_REAL_SQRT2, A_REAL_PI_4);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
#endif /* __cplusplus */
        a_vector2_pol(&a, &x, &y);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
#if defined(__cplusplus)
        a.pol(x, y);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
#endif /* __cplusplus */
    }
    {
        a_vector2 a = A_VECTOR2_C(1, 2);
        a_vector2 b = A_VECTOR2_C(1, 2);
        a_vector2 c = A_VECTOR2_C(0, 0);
        TEST_BUG(iseq(a_vector2_angle(&a, &b), 0));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.angle(b), 0));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector2_dot(&a, &b), 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dot(b), 5));
#endif /* __cplusplus */
        TEST_BUG(a_vector2_ispar(&a, &b));
#if defined(__cplusplus)
        TEST_BUG(a.ispar(b));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector2_cross(&a, &b), 0));
#if defined(__cplusplus)
        TEST_BUG(iseq(a ^ b, 0));
#endif /* __cplusplus */
        a_vector2_add(&a, &b, &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#if defined(__cplusplus)
        c = a + b;
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#endif /* __cplusplus */
        a_vector2_sub(&a, &b, &c);
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 0));
#if defined(__cplusplus)
        c = a - b;
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 0));
#endif /* __cplusplus */
        a_vector2_mul(&a, 2, &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#if defined(__cplusplus)
        c = a * 3;
        TEST_BUG(iseq(c.x, 3));
        TEST_BUG(iseq(c.y, 6));
        c = 2 * a;
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#endif /* __cplusplus */
        a_vector2_div(&a, A_REAL_C(0.5), &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#if defined(__cplusplus)
        c = a / A_REAL_C(0.5);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#endif /* __cplusplus */
        a_vector2_neg(&a, &c);
#if defined(__cplusplus)
        c = -a;
        TEST_BUG(iseq(c.x, -1));
        TEST_BUG(iseq(c.y, -2));
#endif /* __cplusplus */
    }
    {
        a_vector2 a = A_VECTOR2_C(3, -4);
        TEST_BUG(iseq(a_vector2_norm(&a), 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.norm(), 5));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector2_norm1(&a), 7));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.norm1(), 7));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector2_norm2(&a), 5 * 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.norm2(), 5 * 5));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector2_unit(&a), 5));
        TEST_BUG(iseq(a_vector2_norm2(&a), 1));
#if defined(__cplusplus)
        a.set_xy(3, -4);
        TEST_BUG(iseq(a.unit(), 5));
        TEST_BUG(iseq(a.norm2(), 1));
#endif /* __cplusplus */
    }
    {
        a_vector2 a = A_VECTOR2_C(0, 0);
        a_vector2 b = A_VECTOR2_C(3, -4);
        TEST_BUG(iseq(a_vector2_dist(&a, &b), 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist(b), 5));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector2_dist1(&a, &b), 7));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist1(b), 7));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_vector2_dist2(&a, &b), 5 * 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist2(b), 5 * 5));
#endif /* __cplusplus */
    }
    {
        a_vector2 a = A_VECTOR2_C(1, 0);
        a_vector2 b = A_VECTOR2_C(0, 1);
        TEST_BUG(a_vector2_isver(&a, &b));
#if defined(__cplusplus)
        TEST_BUG(a.isver(b));
#endif /* __cplusplus */
    }
    (void)argv;
    (void)argc;
    return 0;
}
