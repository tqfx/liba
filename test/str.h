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
        a_str_cats(lhs, "");
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_cats(rhs, "");
        TEST_BUG(a_str_cmp(lhs, rhs) == 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_cats(lhs, "0");
        TEST_BUG(a_str_cmp(lhs, rhs) > 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_cats(rhs, "0");
        TEST_BUG(a_str_cmp(lhs, rhs) < 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_cats(lhs, "0");
        a_str_cats(rhs, "00");
        TEST_BUG(a_str_cmp(lhs, rhs) < 0);
        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str *lhs = a_str_new();
        a_str *rhs = a_str_new();
        a_str_cats(lhs, "00");
        a_str_cats(rhs, "0");
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
        TEST_BUG(a_str_catn_(&ctx, A_NULL, 0) == 0);
        TEST_BUG(a_str_getc_(&ctx) == ~0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_catn(&ctx, A_NULL, 0) == 0);
        TEST_BUG(a_str_getc(&ctx) == ~0);
        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_catc(void)
{
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_catc_(&ctx, 1) == 1);
        TEST_BUG(a_str_ptr(&ctx)[0] == 1);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;
        TEST_BUG(a_str_catc(&ctx, 1) == 1);
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
        TEST_BUG(a_str_catn_(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, 1) == 1);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_catn_(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn_(&ctx, A_NULL, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn_(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_catn_(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn_(&ctx, buf, 1) == 1);
        TEST_BUG(buf[0] == 0);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_catn_(&ctx, "0", 2) == 0);
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
        TEST_BUG(a_str_catn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, A_NULL, 1) == 1);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_catn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, A_NULL, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_getn(&ctx, buf, 0) == 0);
        TEST_BUG(buf[0] == 1);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_catn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, buf, 1) == 1);
        TEST_BUG(buf[0] == 0);
        TEST_BUG(buf[1] == 1);

        a_str_setn_(&ctx, 0);
        a_fill(buf, sizeof(buf), 1);
        TEST_BUG(a_str_catn(&ctx, "0", 2) == 0);
        TEST_BUG(a_str_getn(&ctx, buf, A_SIZE_MAX) == 2);
        TEST_BUG(buf[0] == '0');
        TEST_BUG(buf[1] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_catn(void)
{
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_catn_(&ctx, A_NULL, 0) == 0);
        TEST_BUG(!a_str_ptr(&ctx));

        TEST_BUG(a_str_catn_(&ctx, "0", 0) == 0);
        TEST_BUG(!a_str_ptr(&ctx));

        TEST_BUG(a_str_catn_(&ctx, "0", 1) == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');

        TEST_BUG(a_str_catn_(&ctx, "1", 2) == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == '1');
        TEST_BUG(a_str_ptr(&ctx)[2] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_catn(&ctx, A_NULL, 0) == 0);
        TEST_BUG(a_str_ptr(&ctx));
        TEST_BUG(a_str_ptr(&ctx)[0] == 0);

        TEST_BUG(a_str_catn(&ctx, "0", 0) == 0);
        TEST_BUG(a_str_ptr(&ctx));
        TEST_BUG(a_str_ptr(&ctx)[0] == 0);

        TEST_BUG(a_str_catn(&ctx, "0", 1) == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);

        TEST_BUG(a_str_catn(&ctx, "1", 2) == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == '1');
        TEST_BUG(a_str_ptr(&ctx)[2] == 0);
        TEST_BUG(a_str_ptr(&ctx)[3] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_cats(void)
{
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_cats_(&ctx, "") == 0);
        TEST_BUG(!a_str_ptr(&ctx));

        TEST_BUG(a_str_cats_(&ctx, "0") == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');

        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_cats(&ctx, "") == 0);
        TEST_BUG(a_str_ptr(&ctx));

        TEST_BUG(a_str_cats(&ctx, "0") == 0);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_catf(void)
{
    {
        a_str ctx = A_STR_INIT;

        TEST_BUG(a_str_catf(&ctx, "%i", 0) == 1);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');
        TEST_BUG(a_str_ptr(&ctx)[1] == 0);

        a_alloc(a_str_exit(&ctx), 0);
    }
}

static void test_str_cat(void)
{
    {
        a_str ctx = A_STR_INIT;
        a_str obj = A_STR_INIT;

        a_str_cat_(&ctx, &obj);
        TEST_BUG(!a_str_ptr(&ctx));

        a_str_cats_(&obj, "0");
        a_str_cat_(&ctx, &obj);
        TEST_BUG(a_str_ptr(&ctx)[0] == '0');

        a_alloc(a_str_exit(&obj), 0);
        a_alloc(a_str_exit(&ctx), 0);
    }
    {
        a_str ctx = A_STR_INIT;
        a_str obj = A_STR_INIT;

        a_str_cat(&ctx, &obj);
        TEST_BUG(a_str_ptr(&ctx));

        a_str_cats(&obj, "0");
        a_str_cat(&ctx, &obj);
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
    test_str_catc();
    test_str_getn();
    test_str_catn();
    test_str_cats();
    test_str_catf();
    test_str_cat();
    {
        a_str *ctx = a_str_new();
        a_str_catf(ctx, "0123");
        TEST_BUG(*a_str_at_(ctx, 0) == '0');
        TEST_BUG(*a_str_at_(ctx, 1) == '1');
        TEST_BUG(*a_str_at_(ctx, 2) == '2');
        TEST_BUG(*a_str_at_(ctx, 3) == '3');
        TEST_BUG(*a_str_at_(ctx, 4) == 0);
        TEST_BUG(a_str_at(ctx, 2) == a_str_of(ctx, -2));
        a_str_die(ctx);
    }
    for (i = 1; i < argc; ++i)
    {
        a_str *ctx = a_str_new();
        a_str_cats(ctx, argv[i]);
        a_str_trim(ctx, A_NULL, 0);
        printf("%s %" A_PRIz "u\n", a_str_ptr(ctx), a_utf_len(ctx, A_NULL));
        a_str_die(ctx);
    }
    return 0;
}
