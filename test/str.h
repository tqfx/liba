#define MAIN(x) str##x
#include "test.h"
#include "a/str.h"

static void test_str(void)
{
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_len(&ctx) == 0);
        TEST_BUG(a_str_mem(&ctx) == 0);
        TEST_BUG(!a_str_ptr(&ctx));
        TEST_BUG(!a_str_exit(&ctx));
    }
}

static void test_str_cmp(void)
{
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_puts(lhs, "");
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_puts(rhs, "");
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_puts(lhs, "0");
        TEST_BUG(a_str_cmp(lhs, rhs) > 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_puts(rhs, "0");
        TEST_BUG(a_str_cmp(lhs, rhs) < 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_puts(lhs, "0");
        a_str_puts(rhs, "00");
        TEST_BUG(a_str_cmp(lhs, rhs) < 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_puts(lhs, "00");
        a_str_puts(rhs, "0");
        TEST_BUG(a_str_cmp(lhs, rhs) > 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
}

static void test_str_getc(void)
{
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_getc_(&ctx) == ~0);
    }
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_getc(&ctx) == ~0);
    }
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_putn_(&ctx, A_NULL, 0) == 0);
        TEST_BUG(a_str_getc_(&ctx) == ~0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_putn(&ctx, A_NULL, 0) == 0);
        TEST_BUG(a_str_getc(&ctx) == ~0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_putc(void)
{
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_putc_(&ctx, 1) == 1);
        TEST_BUG(a_str_ptr(&ctx)[0] == 1);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;
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
        a_str ctx = A_STR_INIT;

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

        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn_(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, 1) == 1);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn_(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn_(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn_(&ctx, buf, 1) == 1);
        TEST_BUG(buf[0] == 0);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn_(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn_(&ctx, buf, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == '0');
        TEST_BUG(buf[1] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        char buf[2];
        a_str ctx = A_STR_INIT;

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

        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, A_NULL, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, A_NULL, 1) == 1);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, A_NULL, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, buf, 1) == 1);
        TEST_BUG(buf[0] == 0);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_putn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, buf, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == '0');
        TEST_BUG(buf[1] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_putn(void)
{
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_putn_(&ctx, A_NULL, 0) == 0);
        TEST_BUG(!a_str_ptr(&ctx));

        TEST_BUG(a_str_putn_(&ctx, "0", 0) == 0);
        TEST_BUG(!a_str_ptr(&ctx));

        TEST_BUG(a_str_putn_(&ctx, "0", 1) == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');

        TEST_BUG(a_str_putn_(&ctx, "1", 2) == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == '1');
        TEST_BUG(a_str_ptr(&ctx)[2] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_putn(&ctx, A_NULL, 0) == 0);
        TEST_BUG(a_str_ptr(&ctx));
        TEST_BUG(a_str_ptr(&ctx)[0] == 0);

        TEST_BUG(a_str_putn(&ctx, "0", 0) == 0);
        TEST_BUG(a_str_ptr(&ctx));
        TEST_BUG(a_str_ptr(&ctx)[0] == 0);

        TEST_BUG(a_str_putn(&ctx, "0", 1) == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);

        TEST_BUG(a_str_putn(&ctx, "1", 2) == 0);
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
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_puts_(&ctx, "") == 0);
        TEST_BUG(!a_str_ptr(&ctx));

        TEST_BUG(a_str_puts_(&ctx, "0") == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');

        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_puts(&ctx, "") == 0);
        TEST_BUG(a_str_ptr(&ctx));

        TEST_BUG(a_str_puts(&ctx, "0") == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_putf(void)
{
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_putf(&ctx, "%i", 0) == 1);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_put(void)
{
    {
        a_str ctx = A_STR_INIT;
        a_str obj = A_STR_INIT;

        a_str_put_(&ctx, &obj);
        TEST_BUG(!a_str_ptr(&ctx));

        a_str_puts_(&obj, "0");
        a_str_put_(&ctx, &obj);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');

        a_alloc(a_str_exit(&obj), 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;
        a_str obj = A_STR_INIT;

        a_str_put(&ctx, &obj);
        TEST_BUG(a_str_ptr(&ctx));

        a_str_puts(&obj, "0");
        a_str_put(&ctx, &obj);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);

        a_alloc(a_str_exit(&obj), 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    int i;
    puts(A_FUNC);
    test_str();
    test_str_cmp();
    test_str_getc();
    test_str_putc();
    test_str_getn();
    test_str_putn();
    test_str_puts();
    test_str_putf();
    test_str_put();
    {
        a_str *ctx = a_str_new();
        a_str_putf(ctx, "0123");
        TEST_BUG(a_str_idx(ctx, -1) == '3');
        TEST_BUG(a_str_at_(ctx, 0) == '0');
        TEST_BUG(a_str_at(ctx, 0) == '0');
        TEST_BUG(a_str_at(ctx, 4) == 0);
        a_str_die(ctx);
    }
    for (i = 1; i < argc; ++i)
    {
        a_str *ctx = a_str_new();
        a_str_puts(ctx, argv[i]);
        printf("%s %" A_PRIz "u\n", argv[i], a_str_utflen(ctx));
        a_str_die(ctx);
    }
    return 0;
}
