#define MAIN_(x) A_CAST_2(x, _str)
#include "test.h"
#include "a/str.h"

static void test_str_init(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_init(&ctx, A_NULL, 0) == A_SUCCESS);
        TEST_BUG(a_str_len(&ctx) == 0);
        TEST_BUG(a_str_mem(&ctx) > 0);
        TEST_BUG(a_str_ptr(&ctx));
        TEST_BUG(a_str_ptr(&ctx)[0] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_init(&ctx, "0", 0) == A_SUCCESS);
        TEST_BUG(a_str_len(&ctx) == 0);
        TEST_BUG(a_str_mem(&ctx) > 0);
        TEST_BUG(a_str_ptr(&ctx));
        TEST_BUG(a_str_ptr(&ctx)[0] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_init(&ctx, "0", 2) == A_SUCCESS);
        TEST_BUG(a_str_len(&ctx) == 2);
        TEST_BUG(a_str_mem(&ctx) > 0);
        TEST_BUG(a_str_ptr(&ctx));
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);
        TEST_BUG(a_str_ptr(&ctx)[2] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_exit(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(!a_str_exit(&ctx));
    }
}

static void test_str_cmp(void)
{
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(lhs, "");
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(rhs, "");
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(lhs, "0");
        TEST_BUG(a_str_cmp(lhs, rhs) > 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(rhs, "0");
        TEST_BUG(a_str_cmp(lhs, rhs) < 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(lhs, "0");
        a_str_puts(rhs, "00");
        TEST_BUG(a_str_cmp(lhs, rhs) < 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(rhs, "0");
        a_str_puts(lhs, "00");
        TEST_BUG(a_str_cmp(lhs, rhs) > 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
}

static void test_str_getc(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_getc_(&ctx) == ~0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_getc(&ctx) == ~0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_init(&ctx, A_NULL, 0) == A_SUCCESS);
        TEST_BUG(a_str_getc_(&ctx) == ~0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_init(&ctx, A_NULL, 0) == A_SUCCESS);
        TEST_BUG(a_str_getc(&ctx) == ~0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_putc(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_putc_(&ctx, 1) == 1);
        TEST_BUG(a_str_ptr(&ctx)[0] == 1);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_putc(&ctx, 1) == 1);
        TEST_BUG(a_str_ptr(&ctx)[0] == 1);
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_getn(void)
{
    {
        char buf[2];
        a_str_s ctx = A_STR_NUL;
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, 1) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, A_SIZE_MAX) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, 1) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, A_SIZE_MAX) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        TEST_BUG(a_str_init(&ctx, "0", 2) == A_SUCCESS);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, 1) == 1);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, 1) == 1);
        TEST_BUG(buf[0] == 0);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, A_SIZE_MAX) == 1);
        TEST_BUG(buf[0] == '0');
        TEST_BUG(buf[1] == 1);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        char buf[2];
        a_str_s ctx = A_STR_NUL;
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, A_NULL, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, A_NULL, 1) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, A_NULL, A_SIZE_MAX) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, 1) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, A_SIZE_MAX) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        TEST_BUG(a_str_init(&ctx, "0", 2) == A_SUCCESS);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, A_NULL, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, A_NULL, 1) == 1);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, A_NULL, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, 1) == 1);
        TEST_BUG(buf[0] == 0);
        TEST_BUG(buf[1] == 1);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, A_SIZE_MAX) == 1);
        TEST_BUG(buf[0] == '0');
        TEST_BUG(buf[1] == 1);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_putn(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_putn_(&ctx, A_NULL, 0) == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_putn_(&ctx, A_NULL, 1) == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_putn_(&ctx, "0", 0) == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_putn_(&ctx, "0", 1) == A_SUCCESS);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_putn_(&ctx, "1", 2) == A_SUCCESS);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == '1');
        TEST_BUG(a_str_ptr(&ctx)[2] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_putn(&ctx, A_NULL, 0) == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_putn(&ctx, A_NULL, 1) == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_putn(&ctx, "0", 0) == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_putn(&ctx, "0", 1) == A_SUCCESS);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);
        TEST_BUG(a_str_putn(&ctx, "1", 2) == A_SUCCESS);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == '1');
        TEST_BUG(a_str_ptr(&ctx)[2] == 0);
        TEST_BUG(a_str_ptr(&ctx)[3] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_puts(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_puts_(&ctx, "") == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_puts_(&ctx, "0") == A_SUCCESS);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_puts(&ctx, "") == A_SUCCESS);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(a_str_puts(&ctx, "0") == A_SUCCESS);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_cat(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        a_str_s obj = A_STR_NUL;
        a_str_cat_(&ctx, &obj);
        TEST_BUG(!a_str_ptr(&ctx));
        a_str_puts(&obj, "0");
        a_str_cat_(&ctx, &obj);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        a_alloc(a_str_exit(&obj), 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str_s ctx = A_STR_NUL;
        a_str_s obj = A_STR_NUL;
        a_str_cat(&ctx, &obj);
        TEST_BUG(!a_str_ptr(&ctx));
        a_str_puts(&obj, "0");
        a_str_cat(&ctx, &obj);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);
        a_alloc(a_str_exit(&obj), 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_putf(void)
{
    {
        a_str_s ctx = A_STR_NUL;
        TEST_BUG(a_str_putf(&ctx, "%i", 0) == 1);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s\n", A_FUNC);
    test_str_init();
    test_str_exit();
    test_str_cmp();
    test_str_getc();
    test_str_putc();
    test_str_getn();
    test_str_putn();
    test_str_puts();
    test_str_cat();
    test_str_putf();
    {
        a_str_s *ctx = a_str_new();
        a_str_putf(ctx, "0123");
        TEST_BUG(a_str_idx(ctx, -1) == '3');
        TEST_BUG(a_str_at_(ctx, 0) == '0');
        TEST_BUG(a_str_at(ctx, 0) == '0');
        TEST_BUG(a_str_at(ctx, 4) == 0);
        a_str_die(ctx);
    }
    for (int i = 1; i < argc; ++i)
    {
        a_str_s *ctx = a_str_new();
        a_str_putn_(ctx, argv[i], strlen(argv[i]));
        printf("%s %u\n", argv[i], a_cast_s(unsigned int, a_str_utflen(ctx)));
        a_str_die(ctx);
    }
    return 0;
}
