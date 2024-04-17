#define MAIN(x) trajpoly7##x
#include "test.h"
#include "a/trajpoly7.h"

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
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
    a_trajpoly7 pt7;
    a_trajpoly7_gen(&pt7, arg[1] - arg[0], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
    for (a_float x = arg[0], delta = (arg[1] - arg[0]) / 1000; x < arg[1]; x += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f\n"),
              x, a_trajpoly7_pos(&pt7, x), a_trajpoly7_vel(&pt7, x), a_trajpoly7_acc(&pt7, x), a_trajpoly7_jer(&pt7, x));
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_trajpoly7>::value);
#endif /* __cplusplus */

    return 0;
}
