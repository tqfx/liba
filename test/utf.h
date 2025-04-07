#define MAIN(x) utf##x
#include "test.h"
#include "a/utf.h"
#include <string.h>

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    int i;
    for (i = 1; i < argc; ++i)
    {
        char buf[7];
        a_u32 val = 0;
        char const *s = argv[i];
        a_size length = strlen(s);
        a_size number = a_utf_length(s, length, A_NULL);
        unsigned int offset = a_utf_decode(s, length, &val);
        debug("%s %u", s, a_cast_s(unsigned int, number));
        for (; offset; offset = a_utf_decode(s, length, &val))
        {
            a_utf_encode(val, A_NULL);
            buf[a_utf_encode(val, buf)] = 0;
            debug(" %s:%" A_PRI32 "u", buf, val);
            length -= offset;
            s += offset;
        }
        debug("\n");
    }
    return 0;
}
