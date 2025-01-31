#define MAIN(x) poly##x
#include "test.h"
#include "a/poly.h"

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
    a_real x = 2;
    a_real x4[] = {A_REAL_C(1.0), A_REAL_C(2.0), A_REAL_C(3.0), A_REAL_C(4.0)};
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
    (void)argc;
    (void)argv;
    return 0;
}
