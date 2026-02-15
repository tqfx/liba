#define MAIN(x) convexhull##x
#include "test.h"
#include "a/convexhull.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    TEST_BUG(a_convexhull2(A_NULL, 0, A_NULL, 0, 'x', 0) == 0);
    {
        a_point2 p[3] = {A_POINT2_C(0, 0), A_POINT2_C(0, 0), A_POINT2_C(1, 1)}, q[3];
        TEST_BUG(a_convexhull2(p, 1, q, 1, 'x', 0) == 1);
        TEST_BUG(a_convexhull2(p, 1, q, 1, 'y', 0) == 1);
        TEST_BUG(a_convexhull2(p, 2, q, 2, 'x', 0) == 0);
        TEST_BUG(a_convexhull2(p, 2, q, 2, 'y', 0) == 0);
        TEST_BUG(a_convexhull2(p, 2, q, 3, 'x', 0) == 2);
        TEST_BUG(a_convexhull2(p, 2, q, 3, 'y', 0) == 2);
        TEST_BUG(a_convexhull2(p, 3, q, 3, 'x', 0) == 2);
        TEST_BUG(a_convexhull2(p, 3, q, 3, 'y', 0) == 2);
    }
    (void)argc;
    (void)argv;
    return 0;
}
