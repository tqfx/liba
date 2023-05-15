#ifndef TEST_MATH_H
#define TEST_MATH_H
#define MAIN_(s, argc, argv) math##s(argc, argv)
#include "test.h"
#include "a/math.h"

static void test_sq(void)
{
    a_int_t x = 2;
    TEST_BUG(A_SQ(x) == 4);
}

static void test_abs(void)
{
    a_extend_t x = A_EXTEND_C(-1.0);
    TEST_BUG(A_ABS(x) > 0);
}

static void test_sgn(void)
{
    a_double_t pos = A_DOUBLE_C(+10.0);
    a_double_t neg = A_DOUBLE_C(-10.0);
    a_double_t zero = A_DOUBLE_C(0.0);
    TEST_BUG(A_SGN(pos) == 1);
    TEST_BUG(A_SGN(neg) == -1);
    TEST_BUG(A_SGN(zero) == 0);
}

static void test_sat(void)
{
    a_double_t max = A_DOUBLE_C(+10.0);
    a_double_t min = A_DOUBLE_C(-10.0);
    TEST_BUG(A_SAT(0, min, max) >= 0);
    TEST_BUG(A_SAT(+100, min, max) <= max);
    TEST_BUG(A_SAT(-100, min, max) >= min);
}

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
    for (a_uint_t i = 0; i != sizeof(data) / sizeof(a_f32_t); ++i)
    {
#if defined(MAIN_ONCE)
        printf("1/sqrt(%g):\t%-10g%-10g\n", a_double_c(data[i]),
               1 / a_double_c(A_F32_F1(sqrt, data[i])),
               a_double_c(a_f32_rsqrt(data[i])));
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
    for (a_uint_t i = 0; i != sizeof(data) / sizeof(a_f64_t); ++i)
    {
#if defined(MAIN_ONCE)
        printf("1/sqrt(%g):\t%-10g%-10g\n", a_double_c(data[i]),
               1 / a_double_c(A_F64_F1(sqrt, data[i])),
               a_double_c(a_f64_rsqrt(data[i])));
#endif /* MAIN_ONCE */
    }
}

static void test_f32_hypot(void)
{
    a_f32_t x = A_F32_C(1e38);
    a_f32_t y = A_F32_C(1e38);
    a_f32_t z = a_f32_hypot(x, y);
#if defined(MAIN_ONCE)
    printf("hypot(%g,%g)=%g\n", a_f64_c(x), a_f64_c(y), a_f64_c(z));
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
    test_sq();
    test_abs();
    test_sgn();
    test_sat();
    test_u32_sqrt();
    test_u64_sqrt();
    test_f32_rsqrt();
    test_f64_rsqrt();
    test_f32_hypot();
    test_f64_hypot();
    return 0;
}

#endif /* math.h */
