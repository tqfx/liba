#define MAIN(x) math##x
#include "test.h"
#include "a/math.h"

#if A_PREREQ_GNUC(3, 0)
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif /* -Wfloat-conversion */
#if A_PREREQ_GNUC(4, 6) || __has_warning("-Wdouble-promotion")
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* -Wdouble-promotion */

static void test_u32_sqrt(void)
{
    TEST_BUG(a_u32_sqrt(A_U32_C(~0)) == A_U16_C(0xFFFF));
    TEST_BUG(a_u32_sqrt(A_U32_C(0x10000)) == A_U16_C(0x100));
    TEST_BUG(a_u32_sqrt(A_U32_C(0xFFFFFFFF)) == A_U16_C(0xFFFF));
}

static void test_u64_sqrt(void)
{
    TEST_BUG(a_u64_sqrt(A_U64_C(~0)) == A_U32_C(0xFFFFFFFF));
    TEST_BUG(a_u64_sqrt(A_U64_C(0x10000)) == A_U32_C(0x100));
    TEST_BUG(a_u64_sqrt(A_U64_C(0xFFFFFFFF)) == A_U32_C(0xFFFF));
    TEST_BUG(a_u64_sqrt(A_U64_C(0x100000000)) == A_U32_C(0x10000));
    TEST_BUG(a_u64_sqrt(A_U64_C(0xFFFFFFFFFFFFFFFF)) == A_U32_C(0xFFFFFFFF));
}

static void test_f32_rsqrt(void)
{
    a_f32 data[] = {
        A_F32_C(0.0),
        A_F32_C(-0.0),
        A_F32_C(-1.0),
        A_F32_C(1e-10),
        A_F32_C(1.0),
        A_F32_C(4.0),
        A_F32_C(2.5) * A_F32_C(2.5),
    };
    for (unsigned int i = 0; i != sizeof(data) / sizeof(a_f32); ++i)
    {
        debug("1/sqrt(%g):\t%-10g%-10g\n", data[i], 1 / a_f32_sqrt(data[i]), a_f32_rsqrt(data[i]));
    }
}

static void test_f64_rsqrt(void)
{
    a_f64 data[] = {
        A_F64_C(0.0),
        A_F64_C(-0.0),
        A_F64_C(-1.0),
        A_F64_C(1e-10),
        A_F64_C(1.0),
        A_F64_C(4.0),
        A_F64_C(2.5) * A_F64_C(2.5),
    };
    for (unsigned int i = 0; i != sizeof(data) / sizeof(a_f64); ++i)
    {
        debug("1/sqrt(%g):\t%-10g%-10g\n", data[i], 1 / a_f64_sqrt(data[i]), a_f64_rsqrt(data[i]));
    }
}

static void test_sum(int argc, char *argv[])
{
    a_size const n = a_cast_s(a_size, argc);
    a_float *p = a_new(a_float, A_NULL, n);
    for (a_size i = 0; i < n; ++i)
    {
        char *endptr;
        p[i] = strtonum(argv[i], &endptr);
    }

    debug("{");
    for (a_size i = 0; i < n; ++i)
    {
        debug("%c" A_FLOAT_PRI("", "g"), i ? ',' : 0, p[i]);
    }
    debug("}:" A_FLOAT_PRI("", "g,") A_FLOAT_PRI("", "g,") A_FLOAT_PRI("", "g\n"),
          a_float_sum(p, n), a_float_sum1(p, n), a_float_sum2(p, n));

    a_die(p);
}

static void test_mean(int argc, char *argv[])
{
    a_size const n = a_cast_s(a_size, argc);
    a_float *p = a_new(a_float, A_NULL, n);
    for (a_size i = 0; i < n; ++i)
    {
        char *endptr;
        p[i] = strtonum(argv[i], &endptr);
    }

    debug("{");
    for (a_size i = 0; i < n; ++i)
    {
        debug("%c" A_FLOAT_PRI("", "g"), i ? ',' : 0, p[i]);
    }
    debug("}:" A_FLOAT_PRI("", "g\n"), a_float_mean(p, n));

    a_die(p);
}

static void test_push(int argc, char *argv[])
{
    a_float array[] = {0, 1, 2, 3, 4, 5, 6, 7};
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_push_fore(array, A_LEN(array), -1);
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_push_back(array, A_LEN(array), -1);
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float cache[] = {-1, -2};
        a_float_push_fore_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float cache[] = {-2, -1};
        a_float_push_back_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float cache[] = {-0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
        a_float_push_fore_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_float cache[] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, -0};
        a_float_push_fore_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI("+", "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    (void)argc;
    (void)argv;
}

static void test_roll(int argc, char *argv[])
{
    a_float array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_float shift[16];
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll_fore(array, A_LEN(array));
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll_back(array, A_LEN(array));
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll_fore_(array, A_LEN(array), shift, 2);
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll_back_(array, A_LEN(array), shift, 2);
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll_fore_(array, A_LEN(array), shift, 15);
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_float_roll_back_(array, A_LEN(array), shift, 15);
    for (a_size i = 0; i < A_LEN(array); ++i)
    {
        debug(A_FLOAT_PRI(, "g") "%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    (void)argc;
    (void)argv;
}

#include "a/hash.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    test_u32_sqrt();
    test_u64_sqrt();
    test_f32_rsqrt();
    test_f64_rsqrt();
    {
        a_f64 min = A_F64_MIN;
        a_f64 max = A_F64_MAX;
        a_f64 inf = A_F64_INF;
        a_f64 nan = A_F64_NAN;
        debug("64 min = %-12g max = %g\n", min, max);
        debug("64 inf = %-12g nan = %g\n", inf, nan);
    }
    {
        a_f32 min = A_F32_MIN;
        a_f32 max = A_F32_MAX;
        a_f32 inf = A_F32_INF;
        a_f32 nan = A_F32_NAN;
        debug("32 min = %-12g max = %g\n", min, max);
        debug("32 inf = %-12g nan = %g\n", inf, nan);
    }
    {
        a_float min = A_FLOAT_MIN;
        a_float max = A_FLOAT_MAX;
        a_float inf = A_FLOAT_INF;
        a_float nan = A_FLOAT_NAN;
        debug("min = " A_FLOAT_PRI("-12", "g ") "max = " A_FLOAT_PRI("", "g\n"), min, max);
        debug("inf = " A_FLOAT_PRI("-12", "g ") "nan = " A_FLOAT_PRI("", "g\n"), inf, nan);
    }
    {
#undef a_float_expm1
        a_float x = A_FLOAT_EPSILON / 2;
        TEST_BUG(isinf(a_float_expm1(A_FLOAT_INF)));
        TEST_BUG(isnan(a_float_expm1(A_FLOAT_NAN)));
        debug("expm1(" A_FLOAT_PRI(".15", "g") ")=" A_FLOAT_PRI(".15", "g\n"), x, a_float_expm1(x));
        debug("exp(" A_FLOAT_PRI(".15", "g") ")-1=" A_FLOAT_PRI(".15", "g\n"), x, a_float_exp(x) - 1);
    }
    {
#undef a_float_log1p
        a_float x = A_FLOAT_EPSILON / 2;
        TEST_BUG(isinf(a_float_log1p(A_FLOAT_INF)));
        TEST_BUG(isnan(a_float_log1p(A_FLOAT_NAN)));
        debug("log1p(" A_FLOAT_PRI(".15", "g") ")=" A_FLOAT_PRI(".15", "g\n"), x, a_float_log1p(x));
        debug("log(1+" A_FLOAT_PRI(".15", "g") ")=" A_FLOAT_PRI(".15", "g\n"), x, a_float_log(x + 1));
    }
    {
#undef a_float_hypot
        a_float x = A_FLOAT_MAX / A_FLOAT_SQRT2;
        a_float y = A_FLOAT_MAX / A_FLOAT_SQRT2;
        TEST_BUG(!isinf(a_float_hypot(x, y)));
        TEST_BUG(isinf(a_float_hypot(A_FLOAT_INF, A_FLOAT_NAN)));
        TEST_BUG(isinf(a_float_hypot(A_FLOAT_NAN, A_FLOAT_INF)));
        TEST_BUG(isnan(a_float_hypot(A_FLOAT_NAN, A_FLOAT_NAN)));
    }
    {
        a_float x = A_FLOAT_MAX / A_FLOAT_SQRT3;
        a_float y = A_FLOAT_MAX / A_FLOAT_SQRT3;
        a_float z = A_FLOAT_MAX / A_FLOAT_SQRT3;
        TEST_BUG(!isinf(a_float_hypot3(x, y, z)));
        TEST_BUG(isinf(a_float_hypot3(A_FLOAT_INF, A_FLOAT_NAN, A_FLOAT_NAN)));
        TEST_BUG(isinf(a_float_hypot3(A_FLOAT_NAN, A_FLOAT_INF, A_FLOAT_NAN)));
        TEST_BUG(isinf(a_float_hypot3(A_FLOAT_NAN, A_FLOAT_NAN, A_FLOAT_INF)));
        TEST_BUG(isnan(a_float_hypot3(A_FLOAT_NAN, A_FLOAT_NAN, A_FLOAT_NAN)));
    }
    if (argc < 2)
    {
        test_sum(argc - 1, argv + 1);
        test_mean(argc - 1, argv + 1);
        test_push(argc - 1, argv + 1);
        test_roll(argc - 1, argv + 1);
        return 0;
    }
    switch (a_hash_bkdr(argv[1], 0))
    {
    case 0x001E5957: /* sum */
        test_sum(argc - 2, argv + 2);
        break;
    case 0x0EB5AF9D: /* mean */
        test_mean(argc - 2, argv + 2);
        break;
    case 0x0F20D22E: /* push */
        test_push(argc - 1, argv + 1);
        break;
    case 0x0F63D79D: /* roll */
        test_roll(argc - 1, argv + 1);
        break;
    default:
        debug("sum\n");
        debug("mean\n");
        debug("push\n");
        debug("roll\n");
    }
    return 0;
}
