#define MAIN(x) trajbell##x
#include "test.h"
#include "a/trajbell.h"

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

    a_float arg[7] = {0};
    for (int i = start; i < argc; ++i)
    {
        arg[i - start] = strtonum(argv[i], A_NULL);
    }
    a_trajbell ctx;
    a_float t = a_trajbell_gen(&ctx, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6]);
    for (a_float x = 0, delta = t / 1000; x < t; x += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f\n"),
              x, a_trajbell_pos(&ctx, x), a_trajbell_vel(&ctx, x), a_trajbell_acc(&ctx, x), a_trajbell_jer(&ctx, x));
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_trajbell>::value);
#endif /* __cplusplus */

    return 0;
}
