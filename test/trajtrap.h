#define MAIN(x) trajtrap##x
#include "test.h"
#include "a/trajtrap.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_real arg[7] = {0, 0, 0, 0, 0, 0, 0};
    a_real t, x, delta;
    int i, start = 1;
    a_trajtrap ctx;

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
    t = a_trajtrap_gen(&ctx, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6]);
    for ((void)(x = 0), delta = t / 1000; x < t; x += delta) /* NOLINT */
    {
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n",
              x, a_trajtrap_pos(&ctx, x), a_trajtrap_vel(&ctx, x), a_trajtrap_acc(&ctx, x));
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_trajtrap>::value);
#endif /* __cplusplus */

    return 0;
}
