#define MAIN(x) bounding##x
#include "test.h"
#include "a/bounding.h"

static A_INLINE a_bool iseq(a_real a, a_real b)
{
    return A_ABS_(a, b) < A_REAL_TOL;
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    TEST_BUG(a_bounding_box2(A_NULL, 0, A_NULL, A_NULL, A_NULL, A_NULL) < 0);
    TEST_BUG(a_bounding_box3(A_NULL, 0, A_NULL, A_NULL, A_NULL, A_NULL, A_NULL, A_NULL) < 0);
    {
        a_real xmin, xmax, ymin, ymax;
        a_point2 p[2] = {A_POINT2_C(0, 0), A_POINT2_C(1, 2)};
        TEST_BUG(a_bounding_box2(p, 1, &xmin, &xmax, &ymin, &ymax) == 0);
        TEST_BUG(iseq(xmin, 0));
        TEST_BUG(iseq(xmax, 0));
        TEST_BUG(iseq(ymin, 0));
        TEST_BUG(iseq(ymax, 0));
        TEST_BUG(a_bounding_box2(p, 2, &xmin, &xmax, &ymin, &ymax) == 0);
        TEST_BUG(iseq(xmin, 0));
        TEST_BUG(iseq(xmax, 1));
        TEST_BUG(iseq(ymin, 0));
        TEST_BUG(iseq(ymax, 2));
    }
    {
        a_real xmin, xmax, ymin, ymax, zmin, zmax;
        a_point3 p[2] = {A_POINT3_C(0, 0, 0), A_POINT3_C(1, 2, 3)};
        TEST_BUG(a_bounding_box3(p, 1, &xmin, &xmax, &ymin, &ymax, &zmin, &zmax) == 0);
        TEST_BUG(iseq(xmin, 0));
        TEST_BUG(iseq(xmax, 0));
        TEST_BUG(iseq(ymin, 0));
        TEST_BUG(iseq(ymax, 0));
        TEST_BUG(iseq(zmin, 0));
        TEST_BUG(iseq(zmax, 0));
        TEST_BUG(a_bounding_box3(p, 2, &xmin, &xmax, &ymin, &ymax, &zmin, &zmax) == 0);
        TEST_BUG(iseq(xmin, 0));
        TEST_BUG(iseq(xmax, 1));
        TEST_BUG(iseq(ymin, 0));
        TEST_BUG(iseq(ymax, 2));
        TEST_BUG(iseq(zmin, 0));
        TEST_BUG(iseq(zmax, 3));
    }
    (void)argc;
    (void)argv;
    return 0;
}
