#define MAIN_(x) A_CAST_2(x, _crc)
#include "test.h"
#include "a/crc.h"
#if !defined __cplusplus
#define WRITE_TABLE(bit, row, fmt)                                                  \
    static void write_table##bit(FILE *out, a_u##bit ctx[0x100], char const *label) \
    {                                                                               \
        (void)fprintf(out, "uint%i_t const %s[0x%X] = {\n", bit, label, 0x100);     \
        (void)fprintf(out, "    /* clang-format off */\n");                         \
        for (a_size i = 0; i != 0x100 / (row); ++i)                                 \
        {                                                                           \
            (void)fprintf(out, "    ");                                             \
            for (a_size j = 0; j != (row); ++j)                                     \
            {                                                                       \
                (void)fprintf(out, "0x%0" #fmt PRIX##bit ",", ctx[(row) * i + j]);  \
                if (j != (row)-1) { (void)fputc(' ', out); }                        \
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
    (void)fprintf(out, "#include <stdint.h>\n");

    a_u8 table8[0x100];
    a_crc8m_init(table8, 0x07);
    write_table8(out, table8, "CRC8M");
    a_crc8l_init(table8, 0xE0);
    write_table8(out, table8, "CRC8L");

    a_u16 table16[0x100];
    a_crc16m_init(table16, 0x8005);
    write_table16(out, table16, "CRC16M");
    a_crc16l_init(table16, 0xA001);
    write_table16(out, table16, "CRC16L");

    a_u32 table32[0x100];
    a_crc32m_init(table32, 0x04C11DB7);
    write_table32(out, table32, "CRC32M");
    a_crc32l_init(table32, 0xEDB88320);
    write_table32(out, table32, "CRC32L");

    a_u64 table64[0x100];
    a_crc64m_init(table64, 0x42F0E1EBA9EA3693);
    write_table64(out, table64, "CRC64M");
    a_crc64l_init(table64, 0xC96C5795D7870F42);
    write_table64(out, table64, "CRC64L");

    (void)fflush(out);
}
#endif /* __cplusplus */

static void test(void)
{
#define TEXT "123456789"
#define SIZE (sizeof(TEXT) - 1)

    a_u8 table8[0x100];
    a_crc8m_init(table8, A_U8_C(0x31));
    TEST_BUG(a_crc8(table8, TEXT, SIZE, 0) == A_U8_C(0xA2));
    a_crc8l_init(table8, A_U8_C(0x8C));
    TEST_BUG(a_crc8(table8, TEXT, SIZE, 0) == A_U8_C(0xA1));

    a_u16 table16[0x100];
    a_crc16m_init(table16, A_U16_C(0x8005));
    TEST_BUG(a_crc16m(table16, TEXT, SIZE, 0) == A_U16_C(0xFEE8));
    a_crc16l_init(table16, A_U16_C(0xA001));
    TEST_BUG(a_crc16l(table16, TEXT, SIZE, 0) == A_U16_C(0xBB3D));

    a_u32 table32[0x100];
    a_crc32m_init(table32, A_U32_C(0x04C11DB7));
    TEST_BUG(a_crc32m(table32, TEXT, SIZE, 0) == A_U32_C(0x89A1897F));
    a_crc32l_init(table32, A_U32_C(0xEDB88320));
    TEST_BUG(a_crc32l(table32, TEXT, SIZE, 0) == A_U32_C(0x2DFD2D88));

    a_u64 table64[0x100];
    a_crc64m_init(table64, A_U64_C(0x42F0E1EBA9EA3693));
    TEST_BUG(a_crc64m(table64, TEXT, SIZE, 0) == A_U64_C(0x6C40DF5F0B497347));
    a_crc64l_init(table64, A_U64_C(0xC96C5795D7870F42));
    TEST_BUG(a_crc64l(table64, TEXT, SIZE, 0) == A_U64_C(0x2B9C7EE4E2780C8A));

#undef TEXT
#undef SIZE
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
#if !defined __cplusplus
    FILE *out = stdout;
    if (argc > 1)
    {
        char const *name = argv[argc - 1];
        int file = a_cast_s(int, *name);
        if (file)
        {
            out = fopen(name, "wb");
            if (!out)
            {
                perror(name);
                exit(EXIT_FAILURE);
            }
        }
        create_table(out);
        if (file && fclose(out) == EOF)
        {
            perror(name);
        }
    }
#else /* !__cplusplus */
    (void)argc;
    (void)argv;
#endif /* __cplusplus */
    test();
    return 0;
}
