#ifndef TEST_TEST_H
#define TEST_TEST_H

#if !defined _CRT_SECURE_NO_WARNINGS && defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS /* NOLINT */
#endif /* _CRT_SECURE_NO_WARNINGS */
#include "a/a.h"
#include <stdio.h>
#include <stdlib.h>
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
#if defined(A_REAL_TYPE) && (A_REAL_TYPE + 0 == A_REAL_SINGLE)
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* A_REAL_TYPE + 0 == 0x04 */
#endif /* -Wdouble-promotion */

#if A_REAL_TYPE + 0 == A_REAL_SINGLE
#define strtonum(string, endptr) strtof(string, endptr)
#elif A_REAL_TYPE + 0 == A_REAL_DOUBLE
#define strtonum(string, endptr) strtod(string, endptr)
#elif A_REAL_TYPE + 0 == A_REAL_EXTEND
#define strtonum(string, endptr) strtold(string, endptr)
#endif /* A_REAL_TYPE */

#define TEST_IS1(expression, message)                                         \
    do {                                                                      \
        if (!(expression))                                                    \
        {                                                                     \
            (void)fprintf(stderr, "%s:%i:%s\n", __FILE__, __LINE__, message); \
        }                                                                     \
    } while (0)

#define TEST_IS0(expression, message)                                         \
    do {                                                                      \
        if (expression)                                                       \
        {                                                                     \
            (void)fprintf(stderr, "%s:%i:%s\n", __FILE__, __LINE__, message); \
        }                                                                     \
    } while (0)

#define TEST_BUG(expression) TEST_IS1(expression, #expression)

#if defined(MAIN)
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
int MAIN(_c)(int argc, char *argv[]);
int MAIN(_x)(int argc, char *argv[]);
int main_init(int argc, char *argv[], int arg1);
int debug(char const *fmt, ...) A_FORMAT(printf, 1, 2);
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */
#if !defined __cplusplus
static void main_exit(void);
int main_init(int argc, char *argv[], int arg1)
{
    static FILE *out = A_NULL;
    if (!out && argc > arg1)
    {
        out = freopen(argv[arg1], "wb", stdout);
        if (out) { arg1 = atexit(main_exit); }
    }
    return arg1;
}
int main(int argc, char *argv[])
{
    int status = 0;
#if defined(HAS_CXX)
    status += MAIN(_x)(argc, argv);
#endif /* HAS_CXX */
    status += MAIN(_c)(argc, argv);
    return status;
}
int debug(char const *fmt, ...)
{
    return (void)fmt, 0;
}
static void main_exit(void)
{
    if (fclose(stdout)) {}
}
#define main MAIN(_c)
#else /* !__cplusplus */
#define main MAIN(_x)
#endif /* __cplusplus */
#if defined(HAS_CXX) == \
    defined(__cplusplus)
#define debug printf
#endif /* __cplusplus */
#endif /* MAIN */

#endif /* test/test.h */
