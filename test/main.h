#ifndef TEST_MAIN_H
#define TEST_MAIN_H
#define MAIN_(s, argc, argv) A_CAST_2(main, s)(argc, argv)
#include "test.h"

static int test(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    return 0;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s", A_FUNC);
#if defined(MAIN_ONCE)
    printf(" ok");
#endif /* MAIN_ONCE */
    putchar('\n');
    test(argc, argv);
    return 0;
}

#endif /* test/main.h */
