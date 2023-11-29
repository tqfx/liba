#define MAIN_(x) A_CAST_2(x, _polytraj)
#include "test.h"
#include "a/polytraj.h"
#include <string.h>

static void test(void)
{
    a_float_t out[4];
    {
        a_polytraj3_s ctx;
        a_polytraj3_gen(&ctx, 0, 10, 0, 10, 0, 10);
        a_polytraj3_pos(&ctx, 0);
        a_polytraj3_vel(&ctx, 0);
        a_polytraj3_acc(&ctx, 0);
        a_polytraj3_out(&ctx, 0, out);
    }
    {
        a_polytraj5_s ctx;
        a_polytraj5_gen(&ctx, 0, 10, 0, 10, 0, 10, 0, 10);
        a_polytraj5_pos(&ctx, 0);
        a_polytraj5_vel(&ctx, 0);
        a_polytraj5_acc(&ctx, 0);
        a_polytraj5_out(&ctx, 0, out);
    }
    {
        a_polytraj7_s ctx;
        a_polytraj7_gen(&ctx, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10);
        a_polytraj7_pos(&ctx, 0);
        a_polytraj7_vel(&ctx, 0);
        a_polytraj7_acc(&ctx, 0);
        a_polytraj7_jer(&ctx, 0);
        a_polytraj7_out(&ctx, 0, out);
    }
}

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

    a_float_t arg[10] = {0};
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
    a_polytraj3_s pt3;
    a_polytraj3_gen(&pt3, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
    a_polytraj5_s pt5;
    a_polytraj5_gen(&pt5, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    a_polytraj7_s pt7;
    a_polytraj7_gen(&pt7, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
    for (a_float_t dt = arg[0], delta = (arg[1] - arg[0]) / 1000; dt < arg[1]; dt += delta) // NOLINT
    {
        a_float_t out3[3];
        a_polytraj3_out(&pt3, dt, out3);
        a_float_t out5[3];
        a_polytraj5_out(&pt5, dt, out5);
        a_float_t out7[4];
        a_polytraj7_out(&pt7, dt, out7);
        debug(A_FLOAT_PRI("+", "f "), dt);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f "), out3[0], out3[1], out3[2]);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f "), out5[0], out5[1], out5[2]);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), out7[0], out7[1], out7[2], out7[3]);
    }

    test();

    return 0;
}
