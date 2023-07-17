#ifndef TEST_TEST_H
#define TEST_TEST_H

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */

#include "a/a.h"
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include "a/host/a.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4127)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
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
    defined(__cplusplus) && (__cplusplus > 201100L) || defined(_MSC_VER)

#define PRIjd "jd"
#define PRIji "ji"
#define PRIjo "jo"
#define PRIju "ju"
#define PRIjx "jx"
#define PRIjX "jX"

#define SCNjd "jd"
#define SCNji "ji"
#define SCNjo "jo"
#define SCNju "ju"
#define SCNjx "jx"
#define SCNjX "jX"

#define PRIzd "zd"
#define PRIzi "zi"
#define PRIzo "zo"
#define PRIzu "zu"
#define PRIzx "zx"
#define PRIzX "zX"

#define SCNzd "zd"
#define SCNzi "zi"
#define SCNzo "zo"
#define SCNzu "zu"
#define SCNzx "zx"
#define SCNzX "zX"

#define PRItd "td"
#define PRIti "ti"
#define PRIto "to"
#define PRItu "tu"
#define PRItx "tx"
#define PRItX "tX"

#define SCNtd "td"
#define SCNti "ti"
#define SCNto "to"
#define SCNtu "tu"
#define SCNtx "tx"
#define SCNtX "tX"

#else /* C < 199900 and C++ < 201100 */

#define PRIjd PRIdMAX
#define PRIji PRIiMAX
#define PRIjo PRIoMAX
#define PRIju PRIuMAX
#define PRIjx PRIxMAX
#define PRIjX PRIXMAX

#define SCNjd PRIdMAX
#define SCNji PRIiMAX
#define SCNjo PRIoMAX
#define SCNju PRIuMAX
#define SCNjx PRIxMAX
#define SCNjX PRIXMAX

#define PRIzd PRIdPTR
#define PRIzi PRIiPTR
#define PRIzo PRIoPTR
#define PRIzu PRIuPTR
#define PRIzx PRIxPTR
#define PRIzX PRIXPTR

#define SCNzd PRIdPTR
#define SCNzi PRIiPTR
#define SCNzo PRIoPTR
#define SCNzu PRIuPTR
#define SCNzx PRIxPTR
#define SCNzX PRIXPTR

#define PRItd PRIdPTR
#define PRIti PRIiPTR
#define PRIto PRIoPTR
#define PRItu PRIuPTR
#define PRItx PRIxPTR
#define PRItX PRIXPTR

#define SCNtd PRIdPTR
#define SCNti PRIiPTR
#define SCNto PRIoPTR
#define SCNtu PRIuPTR
#define SCNtx PRIxPTR
#define SCNtX PRIXPTR

#endif /* C > 199900 or C++ > 201100 */

#define TEST_IS_TRUE(expression, message)                   \
    do                                                      \
    {                                                       \
        if (!(expression))                                  \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_IS_FASLE(expression, message)                  \
    do                                                      \
    {                                                       \
        if (expression)                                     \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_BUG(expression) TEST_IS_TRUE(expression, "bug")

#if defined(MAIN_)
#define MAIN_C(argc, argv) MAIN_(_c, argc, argv)
#define MAIN_CPP(argc, argv) MAIN_(_cpp, argc, argv)
#if defined(__cplusplus) == defined(HAS_CXX)
#define MAIN_ONCE 1
#endif /* __cplusplus */
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
int MAIN_C(int argc, char *argv[]);
int MAIN_CPP(int argc, char *argv[]);
#if defined(__cplusplus)
} /* extern "C" */
#define MAIN(argc, argv) MAIN_CPP(argc, argv)
#else /* !__cplusplus */
#define MAIN(argc, argv) MAIN_C(argc, argv)
#endif /* __cplusplus */
#if !defined __cplusplus
int main(int argc, char *argv[])
{
#if defined(HAS_CXX)
    return MAIN_CPP(argc, argv) + MAIN_C(argc, argv);
#else /* !HAS_CXX */
    return MAIN_C(argc, argv);
#endif /* HAS_CXX */
}
#endif /* __cplusplus */
#endif /* MAIN_ */

#endif /* test/test.h */
