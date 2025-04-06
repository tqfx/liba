#define MAIN(x) trajpoly7##x
#include "test.h"
#include "a/trajpoly7.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_real arg[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    a_real x, delta;
    int i, start = 1;
    a_trajpoly7 ctx;

    if (argc > 1)
    {
        char *endptr = argv[1];
        (void)strtod(argv[1], &endptr);
        if (argv[1] == endptr)
        {
            main_init(argc, argv, 1);
            ++start;
        }
    }

    for (i = start; i < argc; ++i)
    {
        arg[i - start] = a_str2num(argv[i], A_NULL);
    }
    a_trajpoly7_gen(&ctx, arg[1] - arg[0], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
    for ((void)(x = arg[0]), delta = (arg[1] - arg[0]) / 1000; x < arg[1]; x += delta) /* NOLINT */
    {
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n",
              x, a_trajpoly7_pos(&ctx, x), a_trajpoly7_vel(&ctx, x), a_trajpoly7_acc(&ctx, x), a_trajpoly7_jer(&ctx, x));
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_trajpoly7>::value);
#endif /* __cplusplus */

    return 0;
}
