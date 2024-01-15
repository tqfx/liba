#ifndef TEST_TEST_H
#define TEST_TEST_H

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */
#include "a/a.h"
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#if defined(_MSC_VER)
#pragma warning(disable : 4127)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#if defined(__cplusplus) && (__cplusplus > 201100L)
#include <type_traits>
#endif /* __cplusplus */
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Winline")
#pragma GCC diagnostic ignored "-Winline"
#endif /* -Winline */
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Wpadded")
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* -Wpadded */
#if A_PREREQ_GNUC(4, 6) || __has_warning("-Wdouble-promotion")
#if defined(A_FLOAT_TYPE) && (A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE)
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* A_FLOAT_TYPE + 0 == 0x04 */
#endif /* -Wdouble-promotion */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ > 199900L) || \
    defined(__cplusplus) && (__cplusplus > 201100L) || A_PREREQ_MSVC(19, 0)
#define PRIj "j"
#define SCNj "j"
#define PRIz "z"
#define SCNz "z"
#define PRIt "t"
#define SCNt "t"
#elif defined(_MSC_VER)
#define PRIj "I64"
#define SCNj "I64"
#define PRIz "I"
#define SCNz "I"
#define PRIt "I"
#define SCNt "I"
#else /* C < 199900 and C++ < 201100 */
#if LONG_MAX < INT64_MAX
#define PRIj "ll"
#define SCNj "ll"
#else
#define PRIj "l"
#define SCNj "l"
#endif
#define PRIz "l"
#define SCNz "l"
#define PRIt "l"
#define SCNt "l"
#endif /* C > 199900 or C++ > 201100 */

#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
#define strtonum(string, endptr) strtof(string, endptr)
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
#define strtonum(string, endptr) strtod(string, endptr)
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
#define strtonum(string, endptr) strtold(string, endptr)
#endif /* A_FLOAT_TYPE */

#define TEST_IS_TRUE(expression, message)                   \
    do {                                                    \
        if (!(expression))                                  \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_IS_FASLE(expression, message)                  \
    do {                                                    \
        if (expression)                                     \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_BUG(expression) TEST_IS_TRUE(expression, "bug")

#if defined(MAIN_)
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
int MAIN_(c)(int argc, char *argv[]);
int MAIN_(cpp)(int argc, char *argv[]);
int test_init(int argc, char *argv[], int out);
int debug(char const *fmt, ...) A_FORMAT(printf, 1, 2);
#if defined(__cplusplus)
} /* extern "C" */
#define MAIN(argc, argv) MAIN_(cpp)(argc, argv)
#else /* !__cplusplus */
#define MAIN(argc, argv) MAIN_(c)(argc, argv)
#endif /* __cplusplus */
#if !defined __cplusplus
static void test_exit(void);
int debug(char const *fmt, ...)
{
    return (void)fmt, 0;
}
int test_init(int argc, char *argv[], int out)
{
    static FILE *log = A_NULL;
    if (!log && argc > out)
    {
        log = freopen(argv[out], "wb", stdout);
        if (log) { out = atexit(test_exit); }
    }
    return out;
}
int main(int argc, char *argv[])
{
#if defined(HAS_CXX)
    return MAIN_(cpp)(argc, argv) + MAIN_(c)(argc, argv);
#else /* !HAS_CXX */
    return MAIN_(c)(argc, argv);
#endif /* HAS_CXX */
}
static void test_exit(void)
{
    if (fclose(stdout)) {}
}
#endif /* __cplusplus */
#if defined(__cplusplus) == defined(HAS_CXX)
#define debug printf
#endif /* __cplusplus */
#endif /* MAIN_ */

#endif /* test/test.h */
