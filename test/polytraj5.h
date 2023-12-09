#define MAIN_(x) A_CAST_2(x, _polytraj5)
#include "test.h"
#include "a/polytraj5.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    int start = 1;
    if (argc > 1)
    {
        char *endptr = A_NULL;
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
        (void)strtof(argv[1], &endptr);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
        (void)strtod(argv[1], &endptr);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
        (void)strtold(argv[1], &endptr);
#endif /* A_FLOAT_TYPE */
        if (argv[1] == endptr)
        {
            test_init(argc, argv, 1);
            ++start;
        }
    }

    a_float_t arg[8] = {0};
    for (int i = start; i < argc; ++i)
    {
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
        arg[i - start] = strtof(argv[i], A_NULL);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
        arg[i - start] = strtod(argv[i], A_NULL);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
        arg[i - start] = strtold(argv[i], A_NULL);
#endif /* A_FLOAT_TYPE */
    }
    a_polytraj5_s ctx;
    a_polytraj5_gen(&ctx, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    for (a_float_t dt = arg[0], delta = (arg[1] - arg[0]) / 1000; dt < arg[1]; dt += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              dt, a_polytraj5_pos(&ctx, dt), a_polytraj5_vel(&ctx, dt), a_polytraj5_acc(&ctx, dt));
    }

    return 0;
}
