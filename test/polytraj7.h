#define MAIN_(x) A_CAST_2(x, _polytraj7)
#include "test.h"
#include "a/polytraj7.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    int start = 1;
    if (argc > 1)
    {
        char *endptr = A_NULL;
        (void)strtonum(argv[1], &endptr);
        if (argv[1] == endptr)
        {
            main_init(argc, argv, 1);
            ++start;
        }
    }

    a_float arg[10] = {0};
    for (int i = start; i < argc; ++i)
    {
        arg[i - start] = strtonum(argv[i], A_NULL);
    }
    a_polytraj7 pt7;
    a_polytraj7_gen(&pt7, arg[1] - arg[0], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
    for (a_float dt = arg[0], delta = (arg[1] - arg[0]) / 1000; dt < arg[1]; dt += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f\n"),
              dt, a_polytraj7_pos(&pt7, dt), a_polytraj7_vel(&pt7, dt), a_polytraj7_acc(&pt7, dt), a_polytraj7_jer(&pt7, dt));
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_ASSERT_BUILD(std::is_pod<a_polytraj7>::value);
#endif /* __cplusplus */

    return 0;
}
