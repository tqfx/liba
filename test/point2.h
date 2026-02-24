#define MAIN(x) point2##x
#include "test.h"
#include "a/point2.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return A_ABS_(a, b) < A_REAL_TOL;
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
        TEST_BUG(iseq(a_point2_dist2(&a, &b), 5 * 5));
#if defined(__cplusplus)
        TEST_BUG(iseq(a.dist2(b), 5 * 5));
#endif /* __cplusplus */
    }
    {
        a_size i;
        a_point2 p;
        a_point2 const o = A_POINT2_C(0, 0);
        a_point2 const a[4] = {
            A_POINT2_C(2, 0),
            A_POINT2_C(0, 2),
            A_POINT2_C(3, 0),
            A_POINT2_C(0, 3),
        };
        TEST_BUG(a_point2_mindist(&o, a, 0, A_NULL, A_NULL) > +A_REAL_MAX);
        TEST_BUG(iseq(a_point2_mindist(&o, a, A_LEN(a), A_NULL, A_NULL), 2));
        TEST_BUG(iseq(a_point2_mindist(&o, a, A_LEN(a), &p, &i), 2));
#if defined(__cplusplus)
        TEST_BUG(iseq(o.mindist(a, A_LEN(a)), 2));
        TEST_BUG(iseq(o.mindist(a, A_LEN(a), &p, &i), 2));
#endif /* __cplusplus */
        TEST_BUG(iseq(p.x, 2));
        TEST_BUG(iseq(p.y, 0));
        TEST_BUG(i == 0);
        TEST_BUG(a_point2_maxdist(&o, a, 0, A_NULL, A_NULL) < -A_REAL_MAX);
        TEST_BUG(iseq(a_point2_maxdist(&o, a, A_LEN(a), A_NULL, A_NULL), 3));
        TEST_BUG(iseq(a_point2_maxdist(&o, a, A_LEN(a), &p, &i), 3));
#if defined(__cplusplus)
        TEST_BUG(iseq(o.maxdist(a, A_LEN(a)), 3));
        TEST_BUG(iseq(o.maxdist(a, A_LEN(a), &p, &i), 3));
#endif /* __cplusplus */
        TEST_BUG(iseq(p.x, 3));
        TEST_BUG(iseq(p.y, 0));
        TEST_BUG(i == 2);
    }
    {
        a_point2 a, b, p;
        a_point2_set_val(&a, -1, -2);
        a_point2_set_val(&b, +1, +2);
        a_point2_lerp(&a, &b, A_REAL_C(0.5), &p);
        TEST_BUG(iseq(p.x, 0));
        TEST_BUG(iseq(p.y, 0));
    }
    {
        a_real r;
        a_point2 a, b, c, p;
        a_point2_set_val(&a, +2, 0);
        a_point2_set_val(&b, -2, 0);
        a_point2_set_val(&c, 0, +2);
        r = a_point2_tricir(&a, &b, &c, &p);
        TEST_BUG(iseq(p.x, 0));
        TEST_BUG(iseq(p.y, 0));
        TEST_BUG(iseq(r, 2));
    }
    (void)argv;
    (void)argc;
    return 0;
}
