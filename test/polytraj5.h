#define MAIN_(x) A_CAST_2(x, _polytraj5)
#include "test.h"
#include "a/polytraj5.h"

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

    a_float arg[8] = {0};
    for (int i = start; i < argc; ++i)
    {
        arg[i - start] = strtonum(argv[i], A_NULL);
    }
    a_polytraj5 ctx;
    a_polytraj5_gen(&ctx, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    for (a_float dt = arg[0], delta = (arg[1] - arg[0]) / 1000; dt < arg[1]; dt += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              dt, a_polytraj5_pos(&ctx, dt), a_polytraj5_vel(&ctx, dt), a_polytraj5_acc(&ctx, dt));
    }

    return 0;
}
