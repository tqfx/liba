#define MAIN_(x) A_CAST_2(x, _crc)
#include "test.h"
#include "a/crc.h"
#if !defined __cplusplus
#include <stdlib.h>
#define WRITE_TABLE(bit, row, fmt)                                                                \
    static void write_table##bit(FILE *out, a_u##bit##_t ctx[A_CRC_SIZ], char const *const label) \
    {                                                                                             \
        (void)fprintf(out, "uint%i_t const %s[0x%X] = {\n", bit, label, A_CRC_SIZ);               \
        (void)fprintf(out, "    /* clang-format off */\n");                                       \
        for (a_size_t i = 0; i != A_CRC_SIZ / (row); ++i)                                         \
        {                                                                                         \
            (void)fprintf(out, "    ");                                                           \
            for (a_size_t j = 0; j != (row); ++j)                                                 \
            {                                                                                     \
                (void)fprintf(out, "0x%0" #fmt PRIX##bit ",", ctx[(row) * i + j]);                \
                if (j != (row)-1)                                                                 \
                {                                                                                 \
                    (void)fputc(' ', out);                                                        \
                }                                                                                 \
            }                                                                                     \
            (void)fputc('\n', out);                                                               \
        }                                                                                         \
        (void)fprintf(out, "    /* clang-format on */\n");                                        \
        (void)fprintf(out, "};\n");                                                               \
    }
WRITE_TABLE(8, 8, 2)
WRITE_TABLE(16, 8, 4)
WRITE_TABLE(32, 8, 8)
WRITE_TABLE(64, 4, 16)
#undef WRITE_TABLE
#endif /* __cplusplus */

static void create_table(FILE *out)
{
#if !defined __cplusplus
    (void)fprintf(out, "#include <stdint.h>\n");

    a_u8_t table8[A_CRC_SIZ];
    a_crc8le_init(table8, A_CRC8_POLY);
    write_table8(out, table8, "CRC8LE");
    a_crc8be_init(table8, A_CRC8_POLY);
    write_table8(out, table8, "CRC8BE");

    a_u16_t table16[A_CRC_SIZ];
    a_crc16le_init(table16, A_CRC16_POLY);
    write_table16(out, table16, "CRC16LE");
    a_crc16be_init(table16, A_CRC16_POLY);
    write_table16(out, table16, "CRC16BE");

    a_u32_t table32[A_CRC_SIZ];
    a_crc32le_init(table32, A_CRC32_POLY);
    write_table32(out, table32, "CRC32LE");
    a_crc32be_init(table32, A_CRC32_POLY);
    write_table32(out, table32, "CRC32BE");

    a_u64_t table64[A_CRC_SIZ];
    a_crc64le_init(table64, A_CRC64_POLY);
    write_table64(out, table64, "CRC64LE");
    a_crc64be_init(table64, A_CRC64_POLY);
    write_table64(out, table64, "CRC64BE");

#else /* !__cplusplus */
    (void)out;
#endif /* __cplusplus */
}

static void test(void)
{
#define TEXT "123456789"
#define SIZE (sizeof(TEXT) - 1)

    a_u8_t table8[A_CRC_SIZ];
    debug("POLY: 0x%02u\n", A_CRC8_POLY);
    debug("INIT: 0x%02u\n", A_CRC8_INIT);
    a_crc8le_init(table8, A_CRC8_POLY);
    debug("LSB: 0x%02" PRIX8 "\n", a_crc8(table8, TEXT, SIZE, A_CRC8_INIT));
    a_crc8be_init(table8, A_CRC8_POLY);
    debug("MSB: 0x%02" PRIX8 "\n", a_crc8(table8, TEXT, SIZE, A_CRC8_INIT));

    a_u16_t table16[A_CRC_SIZ];
    debug("POLY: 0x%04u\n", A_CRC16_POLY);
    debug("INIT: 0x%04u\n", A_CRC16_INIT);
    a_crc16le_init(table16, A_CRC16_POLY);
    debug("LSB: 0x%04" PRIX16 "(LE) 0x%04" PRIX16 "(BE)\n",
          a_crc16le(table16, TEXT, SIZE, A_CRC16_INIT),
          a_crc16be(table16, TEXT, SIZE, A_CRC16_INIT));
    a_crc16be_init(table16, A_CRC16_POLY);
    debug("MSB: 0x%04" PRIX16 "(LE) 0x%04" PRIX16 "(BE)\n",
          a_crc16le(table16, TEXT, SIZE, A_CRC16_INIT),
          a_crc16be(table16, TEXT, SIZE, A_CRC16_INIT));

    a_u32_t table32[A_CRC_SIZ];
    debug("POLY: 0x%08" PRIX32 "\n", A_CRC32_POLY);
    debug("INIT: 0x%08" PRIX32 "\n", A_CRC32_INIT);
    a_crc32le_init(table32, A_CRC32_POLY);
    debug("LSB: 0x%08" PRIX32 "(LE) 0x%08" PRIX32 "(BE)\n",
          a_crc32le(table32, TEXT, SIZE, A_CRC32_INIT),
          a_crc32be(table32, TEXT, SIZE, A_CRC32_INIT));
    a_crc32be_init(table32, A_CRC32_POLY);
    debug("MSB: 0x%08" PRIX32 "(LE) 0x%08" PRIX32 "(BE)\n",
          a_crc32le(table32, TEXT, SIZE, A_CRC32_INIT),
          a_crc32be(table32, TEXT, SIZE, A_CRC32_INIT));

    a_u64_t table64[A_CRC_SIZ];
    debug("POLY: 0x%016" PRIX64 "\n", A_CRC64_POLY);
    debug("INIT: 0x%016" PRIX64 "\n", A_CRC64_INIT);
    a_crc64le_init(table64, A_CRC64_POLY);
    debug("LSB: 0x%016" PRIX64 "(LE) 0x%016" PRIX64 "(BE)\n",
          a_crc64le(table64, TEXT, SIZE, A_CRC64_INIT),
          a_crc64be(table64, TEXT, SIZE, A_CRC64_INIT));
    a_crc64be_init(table64, A_CRC64_POLY);
    debug("MSB: 0x%016" PRIX64 "(LE) 0x%016" PRIX64 "(BE)\n",
          a_crc64le(table64, TEXT, SIZE, A_CRC64_INIT),
          a_crc64be(table64, TEXT, SIZE, A_CRC64_INIT));

#undef TEXT
#undef SIZE
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    FILE *out = stdout;
    if (argc > 1)
    {
        char const *name = argv[argc - 1];
        if (*name)
        {
            out = fopen(name, "wb");
            if (!out)
            {
                perror(name);
                exit(EXIT_FAILURE);
            }
        }
        create_table(out);
        if (*name && fclose(out) == EOF)
        {
            perror(argv[argc - 1]);
        }
    }
    test();
    return 0;
}
