#ifndef TEST_MATH_H
#define TEST_MATH_H
#define MAIN_(s, argc, argv) A_CASE_2(math, s)(argc, argv)
#include "test.h"
#include "a/math.h"

#if A_PREREQ_GNUC(4, 6) || __has_warning("-Wdouble-promotion")
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* -Wdouble-promotion */

static void test_u32_sqrt(void)
{
    a_u32_t x;
    TEST_BUG(a_u32_sqrt(A_U32_C(~0), &x) == A_U16_C(0xFFFF));
    TEST_BUG(A_U32_C(0x1FFFE) == x);
    TEST_BUG(a_u32_sqrt(A_U32_C(0x10000), &x) == A_U16_C(0x100));
    TEST_BUG(A_U32_C(0) == x);
    TEST_BUG(a_u32_sqrt(A_U32_C(0xFFFFFFFF), &x) == A_U16_C(0xFFFF));
    TEST_BUG(A_U32_C(0x1FFFE) == x);
}

static void test_u64_sqrt(void)
{
    a_u64_t x;
    TEST_BUG(a_u64_sqrt(A_U64_C(~0), &x) == A_U32_C(0xFFFFFFFF));
    TEST_BUG(A_U64_C(0x1FFFFFFFE) == x);
    TEST_BUG(a_u64_sqrt(A_U64_C(0x100000000), &x) == A_U32_C(0x10000));
    TEST_BUG(A_U64_C(0) == x);
    TEST_BUG(a_u64_sqrt(A_U64_C(0xFFFFFFFFFFFFFFFF), &x) == A_U32_C(0xFFFFFFFF));
    TEST_BUG(A_U64_C(0x1FFFFFFFE) == x);
}

static void test_f32_rsqrt(void)
{
    a_f32_t data[] = {
        A_F32_C(-1.0),
        A_F32_C(-0.0),
        A_F32_C(1e-10),
        A_F32_C(1.0),
        A_F32_C(4.0),
        A_F32_C(2.5) * A_F32_C(2.5),
    };
    for (unsigned int i = 0; i != sizeof(data) / sizeof(a_f32_t); ++i)
    {
#if defined(MAIN_ONCE)
        printf("1/sqrt(%g):\t%-10g%-10g\n", data[i], 1 / a_f32_sqrt(data[i]), a_f32_rsqrt(data[i]));
#endif /* MAIN_ONCE */
    }
}

static void test_f64_rsqrt(void)
{
    a_f64_t data[] = {
        A_F64_C(-1.0),
        A_F64_C(-0.0),
        A_F64_C(1e-10),
        A_F64_C(1.0),
        A_F64_C(4.0),
        A_F64_C(2.5) * A_F64_C(2.5),
    };
    for (unsigned int i = 0; i != sizeof(data) / sizeof(a_f64_t); ++i)
    {
#if defined(MAIN_ONCE)
        printf("1/sqrt(%g):\t%-10g%-10g\n", data[i], 1 / a_f64_sqrt(data[i]), a_f64_rsqrt(data[i]));
#endif /* MAIN_ONCE */
    }
}

static void test_f32_hypot(void)
{
    a_f32_t x = A_F32_C(1e38);
    a_f32_t y = A_F32_C(1e38);
    a_f32_t z = a_f32_hypot(x, y);
#if defined(MAIN_ONCE)
    printf("hypot(%g,%g)=%g\n", x, y, z);
#else /* !MAIN_ONCE */
    (void)(x);
    (void)(y);
    (void)(z);
#endif /* MAIN_ONCE */
}

static void test_f64_hypot(void)
{
    a_f64_t x = A_F64_C(1e308);
    a_f64_t y = A_F64_C(1e308);
    a_f64_t z = a_f64_hypot(x, y);
#if defined(MAIN_ONCE)
    printf("hypot(%g,%g)=%g\n", x, y, z);
#else /* !MAIN_ONCE */
    (void)(x);
    (void)(y);
    (void)(z);
#endif /* MAIN_ONCE */
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    test_u32_sqrt();
    test_u64_sqrt();
    test_f32_rsqrt();
    test_f64_rsqrt();
    test_f32_hypot();
    test_f64_hypot();
    {
        a_f64_t min = A_F64_MIN;
        a_f64_t max = A_F64_MAX;
        a_f64_t inf = A_F64_INF;
        a_f64_t nan = A_F64_NAN;
#if defined(MAIN_ONCE)
        printf("64 min = %-12g max = %g\n", min, max);
        printf("64 inf = %-12g nan = %g\n", inf, nan);
#else /* !MAIN_ONCE */
        (void)(min);
        (void)(max);
        (void)(inf);
        (void)(nan);
#endif /* MAIN_ONCE */
    }
    {
        a_f32_t min = A_F32_MIN;
        a_f32_t max = A_F32_MAX;
        a_f32_t inf = A_F32_INF;
        a_f32_t nan = A_F32_NAN;
#if defined(MAIN_ONCE)
        printf("32 min = %-12g max = %g\n", min, max);
        printf("32 inf = %-12g nan = %g\n", inf, nan);
#else /* !MAIN_ONCE */
        (void)(min);
        (void)(max);
        (void)(inf);
        (void)(nan);
#endif /* MAIN_ONCE */
    }
    {
        a_float_t min = A_FLOAT_MIN;
        a_float_t max = A_FLOAT_MAX;
        a_float_t inf = A_FLOAT_INF;
        a_float_t nan = A_FLOAT_NAN;
#if defined(MAIN_ONCE)
        printf("min = " A_FLOAT_PRI("-12", "g ") "max = " A_FLOAT_PRI("", "g\n"), min, max);
        printf("inf = " A_FLOAT_PRI("-12", "g ") "nan = " A_FLOAT_PRI("", "g\n"), inf, nan);
#else /* !MAIN_ONCE */
        (void)(min);
        (void)(max);
        (void)(inf);
        (void)(nan);
#endif /* MAIN_ONCE */
    }
    return 0;
}

#endif /* test/math.h */
