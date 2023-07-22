#ifndef TEST_UTF_H
#define TEST_UTF_H
#define MAIN_(s, argc, argv) A_CAST_2(utf, s)(argc, argv)
#include "test.h"
#include "a/utf.h"
#include <stdio.h>

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
#if defined(MAIN_ONCE)
    for (int i = 1; i < argc; ++i)
    {
        char buf[7];
        a_u32_t val = 0;
        unsigned int offset = 0;
        printf("%s %zu", argv[i], a_utf_length(argv[i]));
        for (char const *s = argv[i]; (void)(offset = a_utf_decode(s, &val)), offset; s += offset)
        {
            a_utf_encode(A_NULL, val);
            buf[a_utf_encode(buf, val)] = 0;
            printf(" %s:%" PRIu32, buf, val);
            if (!*s)
            {
                break;
            }
        }
        putchar('\n');
    }
#else /* !MAIN_ONCE */
    (void)(argc);
    (void)(argv);
#endif /* MAIN_ONCE */
    return 0;
}

#endif /* test/utf.h */
