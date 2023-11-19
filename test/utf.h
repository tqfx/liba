#define MAIN_(x) A_CAST_2(x, _utf)
#include "test.h"
#include "a/utf.h"
#include <stdio.h>

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    for (int i = 1; i < argc; ++i)
    {
        char buf[7];
        a_u32_t val = 0;
        unsigned int offset = 0;
        debug("%s %u", argv[i], a_cast_s(unsigned int, a_utf_length(argv[i])));
        for (char const *s = argv[i]; (void)(offset = a_utf_decode(s, &val)), offset; s += offset)
        {
            a_utf_encode(A_NULL, val);
            buf[a_utf_encode(buf, val)] = 0;
            debug(" %s:%" PRIu32, buf, val);
            if (!*s)
            {
                break;
            }
        }
        debug("\n");
    }
    return 0;
}
