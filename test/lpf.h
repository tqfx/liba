#ifndef TEST_LPF_H
#define TEST_LPF_H
#define MAIN_(s, argc, argv) A_CAST_2(lpf, s)(argc, argv)
#include "test.h"
#include "a/lpf.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
#if defined(MAIN_ONCE)
    FILE *log = A_NULL;
    if (argc > 1)
    {
        log = freopen(argv[1], "wb", stdout);
    }
#else /* !MAIN_ONCE */
    (void)(argc);
    (void)(argv);
#endif /* MAIN_ONCE */

    a_lpf_s ctx = A_LPF_INIT(A_LPF_GEN(10, 0.01));
    a_lpf_init(&ctx, a_lpf_gen(10, A_FLOAT_C(0.01)));
    for (a_float_t i = 0; i < A_FLOAT_PI * 10; i += A_FLOAT_PI / 10)
    {
        a_float_t x1 = a_float_sin(i);
        a_float_t x2 = a_lpf_iter(&ctx, x1);

#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), i, x1, x2);
#else /* !MAIN_ONCE */
        (void)(x2);
#endif /* MAIN_ONCE */
    }
    a_lpf_zero(&ctx);

#if defined(MAIN_ONCE)
    if (log)
    {
        if (fclose(log))
        {
            perror(A_FUNC);
        }
    }
#endif /* MAIN_ONCE */

    return 0;
}

#endif /* test/lpf.h */
