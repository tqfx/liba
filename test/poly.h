#define MAIN(x) poly##x
#include "test.h"
#include "a/poly.h"
#include "a/linalg.h"

static void print_(a_real const *a, a_size n)
{
    a_size i;
    (void)putchar('{');
    A_FORENUM(a_size, i, n)
    {
        printf("%" A_REAL_PRI "g", a[i]);
        if (i < n - 1) { (void)putchar(','); }
    }
    (void)putchar('}');
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_uint i;
    a_real x = 2;
    a_real x4[] = {A_REAL_C(1.0), A_REAL_C(2.0), A_REAL_C(3.0), A_REAL_C(4.0)};
    a_real X[4], Y[4], A[A_LEN(x4) * A_LEN(x4)], b[A_LEN(x4)];
    print_(x4, 4);
    printf("=%" A_REAL_PRI "g\n", a_poly_eval(x4, 4, x));
    a_poly_swap(x4, 4);
    print_(x4, 4);
    printf("=%" A_REAL_PRI "g\n", a_poly_eval(x4, 4, x));
    print_(x4, 4);
    a_poly_swap(x4, 4);
    printf("=%" A_REAL_PRI "g\n", a_poly_evar(x4, 4, x));
    print_(x4, 3);
    printf("=%" A_REAL_PRI "g\n", a_poly_eval(x4, 3, x));
    a_poly_swap(x4, 3);
    print_(x4, 3);
    printf("=%" A_REAL_PRI "g\n", a_poly_eval(x4, 3, x));
    print_(x4, 3);
    printf("=%" A_REAL_PRI "g\n", a_poly_evar(x4, 3, x));
    a_poly_swap(x4, 3);
    for (i = 0; i < A_LEN(X); ++i)
    {
        X[i] = i;
        Y[i] = a_poly_eval(x4, A_LEN(x4), i);
    }
    a_poly_xTy(A_LEN(X), X, Y, A_LEN(b), b);
    a_poly_xTx(A_LEN(X), X, A_LEN(b), A);
    print_(A, A_LEN(A));
    (void)putchar('\n');
    print_(b, A_LEN(b));
    (void)putchar('\n');
    if (a_real_ldl(A_LEN(b), A) == 0)
    {
        a_real_ldl_solve(A_LEN(b), A, b);
    }
    print_(A, A_LEN(A));
    (void)putchar('\n');
    print_(b, A_LEN(b));
    (void)putchar('\n');
    print_(X, A_LEN(X));
    (void)putchar('\n');
    print_(Y, A_LEN(Y));
    (void)putchar('\n');
    (void)argc;
    (void)argv;
    return 0;
}
