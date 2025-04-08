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
    {
        char buf[7];
        a_size length;
        a_u32 val = 0;
        /* 0x00 */
        length = a_utf_encode(A_U32_C(0x00), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x00) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x00) == val);
        /* 0x7F */
        length = a_utf_encode(A_U32_C(0x7F), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x7F) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x7F) == val);
        /* 0x80 */
        length = a_utf_encode(A_U32_C(0x80), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x80) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x80) == val);
        /* 0x7FF */
        length = a_utf_encode(A_U32_C(0x7FF), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x7FF) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x7FF) == val);
        /* 0x800 */
        length = a_utf_encode(A_U32_C(0x800), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x800) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x800) == val);
        /* 0xFFF */
        length = a_utf_encode(A_U32_C(0xFFF), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0xFFF) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0xFFF) == val);
        /* 0x10000 */
        length = a_utf_encode(A_U32_C(0x10000), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x10000) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x10000) == val);
        /* 0x1FFFFF */
        length = a_utf_encode(A_U32_C(0x1FFFFF), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x1FFFFF) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x1FFFFF) == val);
        /* 0x200000 */
        length = a_utf_encode(A_U32_C(0x200000), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x200000) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x200000) == val);
        /* 0x3FFFFFF */
        length = a_utf_encode(A_U32_C(0x3FFFFFF), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x3FFFFFF) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x3FFFFFF) == val);
        /* 0x4000000 */
        length = a_utf_encode(A_U32_C(0x4000000), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x4000000) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x4000000) == val);
        /* 0x7FFFFFFF */
        length = a_utf_encode(A_U32_C(0x7FFFFFFF), buf);
        TEST_BUG(a_utf_decode(buf, length, &val) == length);
        TEST_BUG(A_U32_C(0x7FFFFFFF) == val);
        TEST_BUG(a_utf_decode(buf, length, A_NULL) == length);
        TEST_BUG(A_U32_C(0x7FFFFFFF) == val);
    }
    return 0;
}
