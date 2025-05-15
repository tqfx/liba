#define MAIN(x) point2##x
#include "test.h"
#include "a/point2.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return a_real_abs(a - b) < A_REAL_EPS;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    {
        a_point2 a;
        a_real x, y;
        a_point2_set_val(&a, 1, 2);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
#if defined(__cplusplus)
        a.set_val(1, 2);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 2));
#endif /* __cplusplus */
        a_point2_val(&a, &x, &y);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
#if defined(__cplusplus)
        a.val(x, y);
        TEST_BUG(iseq(x, 1));
        TEST_BUG(iseq(y, 2));
#endif /* __cplusplus */
        a_point2_set_pol(&a, A_REAL_SQRT2, A_REAL_PI_4);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
#if defined(__cplusplus)
        a.set_pol(A_REAL_SQRT2, A_REAL_PI_4);
        TEST_BUG(iseq(a.x, 1));
        TEST_BUG(iseq(a.y, 1));
#endif /* __cplusplus */
        a_point2_pol(&a, &x, &y);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
#if defined(__cplusplus)
        a.pol(x, y);
        TEST_BUG(iseq(x, A_REAL_SQRT2));
        TEST_BUG(iseq(y, A_REAL_PI_4));
#endif /* __cplusplus */
    }
    {
        a_vector2 v = A_VECTOR2_C(1, 1);
        a_point2 a = A_POINT2_C(1, 2);
        a_point2 c = A_POINT2_C(2, 3);
        a_vector2_set(&v, &a, &c);
        TEST_BUG(iseq(v.x, 1));
        TEST_BUG(iseq(v.y, 1));
#if defined(__cplusplus)
        v = c - a;
        TEST_BUG(iseq(v.x, 1));
        TEST_BUG(iseq(v.y, 1));
#endif /* __cplusplus */
        a_point2_add(&a, &v, &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 3));
#if defined(__cplusplus)
        c = a + v;
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 3));
#endif /* __cplusplus */
        a_point2_sub(&a, &v, &c);
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 1));
#if defined(__cplusplus)
        c = a - v;
        TEST_BUG(iseq(c.x, 0));
        TEST_BUG(iseq(c.y, 1));
#endif /* __cplusplus */
        a_point2_mul(&a, 2, &c);
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
        a_point2_div(&a, A_REAL_C(0.5), &c);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#if defined(__cplusplus)
        c = a / A_REAL_C(0.5);
        TEST_BUG(iseq(c.x, 2));
        TEST_BUG(iseq(c.y, 4));
#endif /* __cplusplus */
    }
    {
        a_point2 a = A_VECTOR2_C(0, 0);
        a_point2 b = A_VECTOR2_C(3, -4);
        TEST_BUG(iseq(a_point2_dist(&a, &b), 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist(b), 5));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_point2_dist1(&a, &b), 7));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist1(b), 7));
#endif /* __cplusplus */
        TEST_BUG(iseq(a_point2_dist2(&a, &b), 5 * 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist2(b), 5 * 5));
#endif /* __cplusplus */
    }
    (void)argv;
    (void)argc;
    return 0;
}
