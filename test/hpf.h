#ifndef TEST_HPF_H
#define TEST_HPF_H
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */
#define MAIN_(s, argc, argv) hpf##s(argc, argv)
#include "test.h"
#include "a/hpf.h"

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

    a_hpf_s ctx = A_HPF_INIT(A_HPF_GEN(10, 0.01));
    a_hpf_init(&ctx, a_hpf_gen(10, A_FLOAT_C(0.01)));
    for (a_float_t i = 0; i < A_FLOAT_PI * 10; i += A_FLOAT_PI / 10)
    {
        a_float_t x1 = a_float_sin(i);
        a_float_t x2 = a_hpf_iter(&ctx, x1);
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), i, x1, x2);
#else /* !MAIN_ONCE */
        (void)(x2);
#endif /* MAIN_ONCE */
    }
    a_hpf_zero(&ctx);

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

#endif /* hpf.h */
