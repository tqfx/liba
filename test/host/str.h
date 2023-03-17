#ifndef TEST_HOST_STR_H
#define TEST_HOST_STR_H
#define MAIN_(s, argc, argv) str##s(argc, argv)
#include "../test.h"
#include "a/host/str.h"

static void tests(void)
{
    a_str_s ctx[1] = {A_STR_NUL};
    a_str_t str = a_str_exit(ctx);
    printf("0x%" PRIXPTR " ", a_cast_r(a_uptr_t, str));
    a_str_getc(ctx);
    a_str_getc_(ctx);
    a_str_putc_(ctx, 0);
    a_str_putn_(ctx, A_NULL, 0);
    a_str_putc(ctx, 0);
    a_str_puts(ctx, "");
    a_str_putn(ctx, A_NULL, 0);
    TEST_BUG(a_str_idx(ctx, 0) == 0);
    TEST_BUG(a_str_at(ctx, 0) == 0);
    str = a_str_ptr(ctx);
    printf("0x%" PRIXPTR " ", a_cast_r(a_uptr_t, str));
    a_str_dtor(ctx);
}

static void testt(void)
{
    a_str_t str = A_NULL;
    a_str_s *ctx = a_str_new();
    a_str_init(ctx, "4321+-/\\", 0);
    a_str_getc(ctx);
    a_str_getc_(ctx);
    a_str_putc(ctx, '-');
    a_str_putc_(ctx, '+');
    a_str_putn(ctx, "12", 1);
    a_str_putn_(ctx, "23", 1);
    a_str_puts(ctx, "3");
    a_str_printf(ctx, "%u", 4);
    TEST_BUG(a_str_at(ctx, 0) == '-');
    TEST_BUG(a_str_idx(ctx, -1) == '4');
    str = a_str_exit(ctx);
    printf("%s\n", str);
    a_alloc(str, 0);
    a_str_die(ctx);
}

static void testc(void)
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

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    tests();
    testt();
    testc();
    return 0;
}

#endif /* host/str.h */
