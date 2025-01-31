#define MAIN(x) trajpoly5##x
#include "test.h"
#include "a/trajpoly5.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_real arg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    a_real x, delta;
    int i, start = 1;
    a_trajpoly5 ctx;

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

    for (i = start; i < argc; ++i)
    {
        arg[i - start] = strtonum(argv[i], A_NULL);
    }
    a_trajpoly5_gen(&ctx, arg[1] - arg[0], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    for ((void)(x = arg[0]), delta = (arg[1] - arg[0]) / 1000; x < arg[1]; x += delta) /* NOLINT */
    {
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n",
              x, a_trajpoly5_pos(&ctx, x), a_trajpoly5_vel(&ctx, x), a_trajpoly5_acc(&ctx, x));
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_trajpoly5>::value);
#endif /* __cplusplus */

    return 0;
}
