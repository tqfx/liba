#define MAIN_(x) A_CAST_2(x, _polytraj3)
#include "test.h"
#include "a/polytraj3.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    int start = 1;
    if (argc > 1)
    {
        char *endptr = A_NULL;
        (void)strtonum(argv[1], &endptr);
        if (argv[1] == endptr)
        {
            test_init(argc, argv, 1);
            ++start;
        }
    }

    a_float_t arg[6] = {0};
    for (int i = start; i < argc; ++i)
    {
        arg[i - start] = strtonum(argv[i], A_NULL);
    }
    a_polytraj3_s ctx;
    a_polytraj3_gen(&ctx, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
    for (a_float_t dt = arg[0], delta = (arg[1] - arg[0]) / 1000; dt < arg[1]; dt += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              dt, a_polytraj3_pos(&ctx, dt), a_polytraj3_vel(&ctx, dt), a_polytraj3_acc(&ctx, dt));
    }

    return 0;
}
