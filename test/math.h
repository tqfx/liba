#define MAIN(x) math##x
#include "test.h"
#include "a/math.h"

#if A_PREREQ_GNUC(3, 0)
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif /* -Wfloat-conversion */
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#if A_PREREQ_GNUC(4, 6) || __has_warning("-Wdouble-promotion")
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* -Wdouble-promotion */

#if !defined __STDC_VERSION__ || (defined(_MSC_VER) && (_MSC_VER < 1800))
#if !defined isinf
#define isinf(x) isinf_(x)
static A_INLINE a_bool isinf_(a_real x) { return x + x == x && x != 0; }
#endif /* isinf */
#if !defined isnan
#define isnan(x) isnan_(x)
static A_INLINE a_bool isnan_(a_real x) { return x != x; }
#endif /* isnan */
#define sqrtf(x) sqrt(x)
#endif /* __STDC_VERSION__ */

static void test_u32_gcd(void)
{
    TEST_BUG(a_u32_gcd(0, 0) == 0);
    TEST_BUG(a_u32_gcd(0, 1) == 1);
    TEST_BUG(a_u32_gcd(1, 0) == 1);
    TEST_BUG(a_u32_gcd(6, 9) == 3);
}

static void test_u64_gcd(void)
{
    TEST_BUG(a_u64_gcd(0, 0) == 0);
    TEST_BUG(a_u64_gcd(0, 1) == 1);
    TEST_BUG(a_u64_gcd(1, 0) == 1);
    TEST_BUG(a_u64_gcd(6, 9) == 3);
}

static void test_u32_lcm(void)
{
    TEST_BUG(a_u32_lcm(0, 0) == 0);
    TEST_BUG(a_u32_lcm(0, 1) == 0);
    TEST_BUG(a_u32_lcm(1, 0) == 0);
    TEST_BUG(a_u32_lcm(6, 9) == 18);
}

static void test_u64_lcm(void)
{
    TEST_BUG(a_u64_lcm(0, 0) == 0);
    TEST_BUG(a_u64_lcm(0, 1) == 0);
    TEST_BUG(a_u64_lcm(1, 0) == 0);
    TEST_BUG(a_u64_lcm(6, 9) == 18);
}

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
    unsigned int i;
    a_f32 data[] = {
        A_F32_C(0.0),
        A_F32_C(-0.0),
        A_F32_C(-1.0),
        A_F32_C(1e-10),
        A_F32_C(1.0),
        A_F32_C(4.0),
        A_F32_C(2.5) * A_F32_C(2.5),
    };
    for (i = 0; i != A_LEN(data); ++i)
    {
        debug("1/sqrt(%g):\t%-10g%-10g\n", data[i], 1 / a_f32_sqrt(data[i]), a_f32_rsqrt(data[i]));
    }
}

static void test_f64_rsqrt(void)
{
    unsigned int i;
    a_f64 data[] = {
        A_F64_C(0.0),
        A_F64_C(-0.0),
        A_F64_C(-1.0),
        A_F64_C(1e-10),
        A_F64_C(1.0),
        A_F64_C(4.0),
        A_F64_C(2.5) * A_F64_C(2.5),
    };
    for (i = 0; i != A_LEN(data); ++i)
    {
        debug("1/sqrt(%g):\t%-10g%-10g\n", data[i], 1 / a_f64_sqrt(data[i]), a_f64_rsqrt(data[i]));
    }
}

static void test_1(int argc, char *argv[], a_real (*exec)(a_real))
{
    a_size i, n = a_cast_s(a_size, argc);
    a_real *p = a_new(a_real, A_NULL, n);

    for (i = 0; i < n; ++i)
    {
        char *endptr = argv[i];
        p[i] = a_str2num(argv[i], &endptr);
    }

    for (i = 0; i < n; ++i)
    {
        debug("%c%" A_REAL_PRI "g", i ? ',' : 0, exec(p[i]));
    }
    debug("\n");

    a_die(p);
}

static void test_cart2pol(int argc, char *argv[], void (*exec)(a_real, a_real, a_real *, a_real *))
{
    a_real a[2] = {0, 0}, b[2] = {0, 0};
    a_size i, n = a_cast_s(a_size, argc);

    if (n > 2) { n = 2; }
    for (i = 0; i < n; ++i)
    {
        char *endptr = argv[i];
        a[i] = a_str2num(argv[i], &endptr);
    }

    exec(a[0], a[1], b + 0, b + 1);

    debug("%" A_REAL_PRI "g,", a[0]);
    debug("%" A_REAL_PRI "g\t", a[1]);
    debug("%" A_REAL_PRI "g,", b[0]);
    debug("%" A_REAL_PRI "g\n", b[1]);
}

static void test_cart2sph(int argc, char *argv[], void (*exec)(a_real, a_real, a_real, a_real *, a_real *, a_real *))
{
    a_real a[3] = {0, 0, 0}, b[3] = {0, 0, 0};
    a_size i, n = a_cast_s(a_size, argc);

    if (n > 3) { n = 3; }
    for (i = 0; i < n; ++i)
    {
        char *endptr = argv[i];
        a[i] = a_str2num(argv[i], &endptr);
    }

    exec(a[0], a[1], a[2], b + 0, b + 1, b + 2);

    debug("%" A_REAL_PRI "g,", a[0]);
    debug("%" A_REAL_PRI "g,", a[1]);
    debug("%" A_REAL_PRI "g\t", a[2]);
    debug("%" A_REAL_PRI "g,", b[0]);
    debug("%" A_REAL_PRI "g,", b[1]);
    debug("%" A_REAL_PRI "g\n", b[2]);
}

static void test_sum(int argc, char *argv[])
{
    a_size i, n = a_cast_s(a_size, argc);
    a_real *p = a_new(a_real, A_NULL, n);

    for (i = 0; i < n; ++i)
    {
        char *endptr = argv[i];
        p[i] = a_str2num(argv[i], &endptr);
    }

    debug("{");
    for (i = 0; i < n; ++i)
    {
        debug("%c%" A_REAL_PRI "g", i ? ',' : 0, p[i]);
    }
    debug("}:%" A_REAL_PRI "g,%" A_REAL_PRI "g,%" A_REAL_PRI "g\n",
          a_real_sum(n, p), a_real_sum1(n, p), a_real_sum2(n, p));

    a_die(p);
}

static void test_norm(int argc, char *argv[])
{
    a_size i, n = a_cast_s(a_size, argc);
    a_real *p = a_new(a_real, A_NULL, n);

    for (i = 0; i < n; ++i)
    {
        char *endptr = argv[i];
        p[i] = a_str2num(argv[i], &endptr);
    }

    debug("{");
    for (i = 0; i < n; ++i)
    {
        debug("%c%" A_REAL_PRI "g", i ? ',' : 0, p[i]);
    }
    debug("}:%" A_REAL_PRI "g\n", a_real_norm(n, p));

    a_die(p);
}

static void test_mean(int argc, char *argv[])
{
    a_size i, n = a_cast_s(a_size, argc);
    a_real *p = a_new(a_real, A_NULL, n);

    for (i = 0; i < n; ++i)
    {
        char *endptr = argv[i];
        p[i] = a_str2num(argv[i], &endptr);
    }

    debug("{");
    for (i = 0; i < n; ++i)
    {
        debug("%c%" A_REAL_PRI "g", i ? ',' : 0, p[i]);
    }
    debug("}:%" A_REAL_PRI "g\n", a_real_mean(n, p));

    a_die(p);
}

static void test_push(int argc, char *argv[])
{
    a_size i;
    a_real array[] = {0, 1, 2, 3, 4, 5, 6, 7};
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%+" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_push_fore(array, A_LEN(array), -1);
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%+" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_push_back(array, A_LEN(array), -1);
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%+" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_real cache[] = {-1, -2};
        a_real_push_fore_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%+" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_real cache[] = {-2, -1};
        a_real_push_back_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%+" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_real cache[] = {-0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
        a_real_push_fore_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%+" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    {
        a_real cache[] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, -0};
        a_real_push_fore_(array, A_LEN(array), cache, A_LEN(cache));
    }
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%+" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    (void)argc;
    (void)argv;
}

static void test_roll(int argc, char *argv[])
{
    a_size i;
    a_real array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    a_real shift[16];
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_roll_fore(array, A_LEN(array));
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_roll_back(array, A_LEN(array));
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_roll_fore_(array, A_LEN(array), shift, 2);
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_roll_back_(array, A_LEN(array), shift, 2);
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_roll_fore_(array, A_LEN(array), shift, 15);
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    a_real_roll_back_(array, A_LEN(array), shift, 15);
    for (i = 0; i < A_LEN(array); ++i)
    {
        debug("%" A_REAL_PRI "g%c", array[i], i + 1 < A_LEN(array) ? ' ' : '\n');
    }
    (void)argc;
    (void)argv;
}

#include "a/hash.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    test_u32_gcd();
    test_u64_gcd();
    test_u32_lcm();
    test_u64_lcm();
    test_u32_sqrt();
    test_u64_sqrt();
    if (argc < 2)
    {
        test_f32_rsqrt();
        test_f64_rsqrt();
    }
    if (argc < 2)
    {
        a_f64 const min = A_F64_MIN;
        a_f64 const max = A_F64_MAX;
        a_f64 const inf = A_F64_INF;
        a_f64 const nan = A_F64_NAN;
        debug("64 min = %-12g max = %g\n", min, max);
        debug("64 inf = %-12g nan = %g\n", inf, nan);
    }
    if (argc < 2)
    {
        a_f32 const min = A_F32_MIN;
        a_f32 const max = A_F32_MAX;
        a_f32 const inf = A_F32_INF;
        a_f32 const nan = A_F32_NAN;
        debug("32 min = %-12g max = %g\n", min, max);
        debug("32 inf = %-12g nan = %g\n", inf, nan);
    }
    if (argc < 2)
    {
        a_real const min = A_REAL_MIN;
        a_real const max = A_REAL_MAX;
        a_real const inf = A_REAL_INF;
        a_real const nan = A_REAL_NAN;
        debug("min = %-12" A_REAL_PRI "g max = %" A_REAL_PRI "g\n", min, max);
        debug("inf = %-12" A_REAL_PRI "g nan = %" A_REAL_PRI "g\n", inf, nan);
    }
    if (argc < 2)
    {
#undef a_real_expm1
        a_real x = A_REAL_EPSILON / 2;
        TEST_BUG(isinf(a_real_expm1(A_REAL_INF)));
        TEST_BUG(isnan(a_real_expm1(A_REAL_NAN)));
        debug("expm1(%.15" A_REAL_PRI "g)=%.15" A_REAL_PRI "g\n", x, a_real_expm1(x));
        debug("exp(%.15" A_REAL_PRI "g)-1=%.15" A_REAL_PRI "g\n", x, a_real_exp(x) - 1);
    }
    if (argc < 2)
    {
#undef a_real_log1p
        a_real x = A_REAL_EPSILON / 2;
        TEST_BUG(isinf(a_real_log1p(A_REAL_INF)));
        TEST_BUG(isnan(a_real_log1p(A_REAL_NAN)));
        debug("log1p(%.15" A_REAL_PRI "g)=%.15" A_REAL_PRI "g\n", x, a_real_log1p(x));
        debug("log(1+%.15" A_REAL_PRI "g)=%.15" A_REAL_PRI "g\n", x, a_real_log(x + 1));
    }
    if (argc < 2)
    {
        a_real x = A_REAL_MAX / A_REAL_SQRT2;
        a_real y = A_REAL_MAX / A_REAL_SQRT2;
        TEST_BUG(!isinf(a_real_norm2(x, y)));
        TEST_BUG(isinf(a_real_norm2(A_REAL_INF, A_REAL_NAN)));
        TEST_BUG(isinf(a_real_norm2(A_REAL_NAN, A_REAL_INF)));
        TEST_BUG(isnan(a_real_norm2(A_REAL_NAN, A_REAL_NAN)));
    }
    if (argc < 2)
    {
        a_real x = A_REAL_MAX / A_REAL_SQRT3;
        a_real y = A_REAL_MAX / A_REAL_SQRT3;
        a_real z = A_REAL_MAX / A_REAL_SQRT3;
        TEST_BUG(!isinf(a_real_norm3(x, y, z)));
        TEST_BUG(isinf(a_real_norm3(A_REAL_INF, A_REAL_NAN, A_REAL_NAN)));
        TEST_BUG(isinf(a_real_norm3(A_REAL_NAN, A_REAL_INF, A_REAL_NAN)));
        TEST_BUG(isinf(a_real_norm3(A_REAL_NAN, A_REAL_NAN, A_REAL_INF)));
        TEST_BUG(isnan(a_real_norm3(A_REAL_NAN, A_REAL_NAN, A_REAL_NAN)));
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
    case 0xA6D2C0B9: /* rad2deg */
        test_1(argc - 2, argv + 2, a_real_rad2deg);
        break;
    case 0xE7CC3409: /* deg2rad */
        test_1(argc - 2, argv + 2, a_real_deg2rad);
        break;
    case 0x9FF73CD3: /* cart2pol */
        test_cart2pol(argc - 2, argv + 2, a_real_cart2pol);
        break;
    case 0x2CD0AC61: /* pol2cart */
        test_cart2pol(argc - 2, argv + 2, a_real_pol2cart);
        break;
    case 0x9FF8066D: /* cart2sph */
        test_cart2sph(argc - 2, argv + 2, a_real_cart2sph);
        break;
    case 0x59A35A8F: /* sph2cart */
        test_cart2sph(argc - 2, argv + 2, a_real_sph2cart);
        break;
    case 0x001E5957: /* sum */
        test_sum(argc - 2, argv + 2);
        break;
    case 0x0EDAA444: /* norm */
        test_norm(argc - 2, argv + 2);
        break;
    case 0x0EB5AF9D: /* mean */
        test_mean(argc - 2, argv + 2);
        break;
    case 0x0F20D22E: /* push */
        test_push(argc - 2, argv + 2);
        break;
    case 0x0F63D79D: /* roll */
        test_roll(argc - 2, argv + 2);
        break;
    default:
        debug("rad2deg\n");
        debug("deg2rad\n");
        debug("cart2pol\n");
        debug("pol2cart\n");
        debug("cart2sph\n");
        debug("sph2cart\n");
        debug("sum\n");
        debug("norm\n");
        debug("mean\n");
        debug("push\n");
        debug("roll\n");
    }
    return 0;
}
