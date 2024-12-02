#define MAIN(x) crc##x
#include "test.h"
#include "a/crc.h"
#if !defined __cplusplus
#define WRITE_TABLE(bit, row, fmt)                                                  \
    static void write_table##bit(FILE *out, a_u##bit ctx[0x100], char const *label) \
    {                                                                               \
        a_size i, ii;                                                               \
        (void)fprintf(out, "uint%i_t const %s[0x%X] = {\n", bit, label, 0x100U);    \
        (void)fprintf(out, "    /* clang-format off */\n");                         \
        for (i = 0; i != 0x100 / (row); ++i)                                        \
        {                                                                           \
            a_size r = (row) * i;                                                   \
            (void)fprintf(out, "    ");                                             \
            for (ii = 0; ii != (row); ++ii)                                         \
            {                                                                       \
                (void)fprintf(out, "0x%0" #fmt A_PRI##bit "X,", ctx[r + ii]);       \
                if (ii != (row) - 1) { (void)fputc(' ', out); }                     \
            }                                                                       \
            (void)fputc('\n', out);                                                 \
        }                                                                           \
        (void)fprintf(out, "    /* clang-format on */\n");                          \
        (void)fprintf(out, "};\n");                                                 \
    }
WRITE_TABLE(8, 8, 2)
WRITE_TABLE(16, 8, 4)
WRITE_TABLE(32, 8, 8)
WRITE_TABLE(64, 4, 16)
static void create_table(FILE *out)
{
    a_u8 table8[0x100];
    a_u16 table16[0x100];
    a_u32 table32[0x100];
    a_u64 table64[0x100];

    (void)fprintf(out, "#include <stdint.h>\n");

    a_crc8m_init(table8, A_U8_C(0x07));
    write_table8(out, table8, "CRC8M");
    a_crc8l_init(table8, A_U8_C(0x07)); /* 0xE0 */
    write_table8(out, table8, "CRC8L");

    a_crc16m_init(table16, A_U16_C(0x8005));
    write_table16(out, table16, "CRC16M");
    a_crc16l_init(table16, A_U16_C(0x8005)); /* 0xA001 */
    write_table16(out, table16, "CRC16L");

    a_crc32m_init(table32, A_U32_C(0x04C11DB7));
    write_table32(out, table32, "CRC32M");
    a_crc32l_init(table32, A_U32_C(0x04C11DB7)); /* 0xEDB88320 */
    write_table32(out, table32, "CRC32L");

    a_crc64m_init(table64, A_U64_C(0x42F0E1EBA9EA3693));
    write_table64(out, table64, "CRC64M");
    a_crc64l_init(table64, A_U64_C(0x42F0E1EBA9EA3693)); /* 0xC96C5795D7870F42 */
    write_table64(out, table64, "CRC64L");

    (void)fflush(out);
}
#endif /* __cplusplus */

static void test(void)
{
#define TEXT "0123456789"
#define SIZE (sizeof(TEXT) - 1)

    a_u8 table8[0x100];
    a_u16 table16[0x100];
    a_u32 table32[0x100];
    a_u64 table64[0x100];

    a_crc8m_init(table8, A_U8_C(0x07));
    TEST_BUG(a_crc8(table8, TEXT, SIZE, 0) == A_U8_C(0x45));
    a_crc8l_init(table8, A_U8_C(0x31)); /* 0x8C */
    TEST_BUG(a_crc8(table8, TEXT, SIZE, 0) == A_U8_C(0x75));

    a_crc16m_init(table16, A_U16_C(0x1021));
    TEST_BUG(a_crc16m(table16, TEXT, SIZE, 0) == A_U16_C(0x9C58));
    a_crc16l_init(table16, A_U16_C(0x8005)); /* 0xA001 */
    TEST_BUG(a_crc16l(table16, TEXT, SIZE, 0) == A_U16_C(0x443D));

    a_crc32m_init(table32, A_U32_C(0x1EDC6F41));
    TEST_BUG(a_crc32m(table32, TEXT, SIZE, 0) == A_U32_C(0x512B456E));
    a_crc32l_init(table32, A_U32_C(0x04C11DB7)); /* 0xEDB88320 */
    TEST_BUG(a_crc32l(table32, TEXT, SIZE, 0) == A_U32_C(0x450EAFB0));

    a_crc64m_init(table64, A_U64_C(0x000000000000001B));
    TEST_BUG(a_crc64m(table64, TEXT, SIZE, 0) == A_U64_C(0xE4FFBEA588AFC790));
    a_crc64l_init(table64, A_U64_C(0x42F0E1EBA9EA3693)); /* 0xC96C5795D7870F42 */
    TEST_BUG(a_crc64l(table64, TEXT, SIZE, 0) == A_U64_C(0xDA60676A5CDE0008));

#undef TEXT
#undef SIZE
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
#if !defined __cplusplus
    if (argc > 1)
    {
        char c = argv[argc - 1][0];
        if (c)
        {
            FILE *out = fopen(argv[argc - 1], "wb");
            if (out)
            {
                create_table(out);
                (void)fclose(out);
            }
        }
        else
        {
            create_table(stdout);
        }
    }
#else /* !__cplusplus */
    (void)argc;
    (void)argv;
#endif /* __cplusplus */
    test();
    return 0;
}
