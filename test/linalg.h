#define MAIN(x) linalg##x
#include "test.h"
#include "a/linalg.h"
#include "a/math.h"

static void show(a_real const *p, a_size m, a_size n)
{
    a_size r, c;
    for (r = 0; r < m; ++r)
    {
        debug("\t");
        for (c = 0; c < n; ++c)
        {
            a_real const x = *p++;
            if (c) { debug(","); }
            debug("%+.6" A_REAL_PRI "f", x);
        }
        debug("\n");
    }
}

static void test_eye(void)
{
    a_real E[3 * 3];
    a_real_eye1(3, E);
    debug("eye(3)=\n");
    show(E, 3, 3);
    a_real_eye2(2, 3, E);
    debug("eye(2,3)=\n");
    show(E, 2, 3);
    a_real_eye2(3, 2, E);
    debug("eye(3,2)=\n");
    show(E, 3, 2);
}

static void test_tri(void)
{
    a_real L[3 * 3];
    a_real_tri1(3, L);
    debug("tri(3)=\n");
    show(L, 3, 3);
    a_real_tri2(2, 3, L);
    debug("tri(2,3)=\n");
    show(L, 2, 3);
    a_real_tri2(3, 2, L);
    debug("tri(3,2)=\n");
    show(L, 3, 2);
}

static void test_triLU(void)
{
    a_real A[3 * 3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_real T[3 * 3];
    a_real_triL(3, A, T);
    debug("triL(3x3)=\n");
    show(T, 3, 3);
    a_real_triU(3, A, T);
    debug("triU(3x3)=\n");
    show(T, 3, 3);
    a_real_triL1(3, A, T);
    debug("triL1(3x3)=\n");
    show(T, 3, 3);
    a_real_triU1(3, A, T);
    debug("triU1(3x3)=\n");
    show(T, 3, 3);
    a_real_triL2(2, 3, A, T);
    debug("triL2(2x3)=\n");
    show(T, 2, 3);
    a_real_triU2(2, 3, A, T);
    debug("triU2(2x3)=\n");
    show(T, 2, 3);
    a_real_triL2(3, 2, A, T);
    debug("triL2(3x2)=\n");
    show(T, 3, 2);
    a_real_triU2(3, 2, A, T);
    debug("triU2(3x2)=\n");
    show(T, 3, 2);
}

static void test_diag(void)
{
    a_real A[3 * 3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_real D[3 * 3];
    a_real_diag(3, A, D);
    debug("diag({1,2,3})=\n");
    show(D, 3, 3);
    a_real_diag1(3, A, D);
    debug("diag1(3x3)=\n");
    show(D, 1, 3);
    a_real_diag2(2, 3, A, D);
    debug("diag2(2x3)=\n");
    show(D, 1, 2);
    a_real_diag2(3, 2, A, D);
    debug("diag2(3x2)=\n");
    show(D, 1, 2);
}

static void test_mul(void)
{
    a_real z[3 * 3];
    a_real x[3 * 3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_real y[3 * 3] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    debug("X=\n");
    show(x, 3, 3);
    debug("Y=\n");
    show(y, 3, 3);
    a_real_mulmm(3, 3, 3, x, y, z);
    debug("XY=\n");
    show(z, 3, 3);
    a_real_mulTm(3, 3, 3, x, y, z);
    debug("X'Y=\n");
    show(z, 3, 3);
    a_real_mulmT(3, 3, 3, x, y, z);
    debug("XY'=\n");
    show(z, 3, 3);
    a_real_mulTT(3, 3, 3, x, y, z);
    debug("X'Y'=\n");
    show(z, 3, 3);
    debug("X.Y=%" A_REAL_PRI "g\n", a_real_dot(9, x, y));
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    main_init(argc, argv, 1);
    test_eye();
    test_tri();
    test_triLU();
    test_diag();
    test_mul();
    return 0;
}
