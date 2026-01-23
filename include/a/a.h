/*!
 @file a.h
 @brief algorithm library
*/

#ifndef LIBA_A_H
#define LIBA_A_H

#if defined(A_HAVE_H)
#include A_HAVE_H
#endif /* A_HAVE_H */

/*! @cond */

#if !defined __has_attribute
#define __has_attribute(x) 0
#endif /* __has_attribute */
#if !defined __has_builtin
#define __has_builtin(x) 0
#endif /* __has_builtin */
#if !defined __has_feature
#define __has_feature(x) 0
#endif /* __has_feature */
#if !defined __has_include
#define __has_include(x) 0
#endif /* __has_include */
#if !defined __has_warning
#define __has_warning(x) 0
#endif /* __has_warning */
#if !defined A_HAVE_INLINE
#define A_HAVE_INLINE 1
#elif A_HAVE_INLINE + 0 < 1
#undef A_HAVE_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__GNUC__) || \
    defined(__clang__)
#pragma GCC system_header
#endif /* __GNUC__ */

#if defined(__MINGW32__)
#undef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO 1
#endif /* __MINGW32__ */

/* https://en.wikipedia.org/wiki/Microsoft_Visual_C++ */
#if defined(_MSC_VER)
#define A_PREREQ_MSVC(maj, min) (_MSC_VER >= (maj * 100 + min))
#else /* !_MSC_VER */
#define A_PREREQ_MSVC(maj, min) 0
#endif /* _MSC_VER */

/* https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#define A_PREREQ_GNUC(maj, min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else /* !__GNUC__ */
#define A_PREREQ_GNUC(maj, min) 0
#endif /* __GNUC__ */

/* https://clang.llvm.org/docs/LanguageExtensions.html */
#if defined(__clang_major__) && defined(__clang_minor__)
#define A_PREREQ_LLVM(maj, min) ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else /* !__clang__ */
#define A_PREREQ_LLVM(maj, min) 0
#endif /* __clang__ */

#if !defined A_FUNC
#if defined(_MSC_VER)
#define A_FUNC __FUNCTION__
#elif defined(__GNUC__)
#define A_FUNC (__extension__ __PRETTY_FUNCTION__)
#elif defined(__cplusplus) && (__cplusplus > 201100L) || \
    defined(__STDC_VERSION__) && (__STDC_VERSION__ > 199900L)
#define A_FUNC __func__
#else /* !__func__ */
#define A_FUNC __FUNCTION__
#endif /* __func__ */
#endif /* A_FUNC */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ > 199900L) || \
    defined(__cplusplus) && (__cplusplus > 201100L) || A_PREREQ_MSVC(18, 0)

#if !defined A_HAVE_LONG_LONG_TYPE
#define A_HAVE_LONG_LONG_TYPE 1
#endif /* A_HAVE_LONG_LONG_TYPE */

#endif /* C > 199900 or C++ > 201100 */
#if defined(A_HAVE_LONG_LONG_TYPE) && (A_HAVE_LONG_LONG_TYPE + 0 < 1)
#undef A_HAVE_LONG_LONG_TYPE
#endif /* A_HAVE_LONG_LONG_TYPE */

#if defined(__cplusplus) && (__cplusplus > 201100L)

#if !defined A_HAVE_NULLPTR
#define A_HAVE_NULLPTR 1
#endif /* A_HAVE_NULLPTR */

#endif /*  C++ > 201100 */
#if defined(A_HAVE_NULLPTR) && (A_HAVE_NULLPTR + 0 < 1)
#undef A_HAVE_NULLPTR
#endif /* A_HAVE_NULLPTR */

#if A_PREREQ_GNUC(2, 96) || __has_builtin(__builtin_expect)
#define A_UNLIKELY(x) __builtin_expect(!!(x), 0)
#define A_LIKELY(x) __builtin_expect(!!(x), 1)
#else /* !likely */
#define A_UNLIKELY(x) (!!(x))
#define A_LIKELY(x) (!!(x))
#endif /* likely */

#if defined(_WIN32) || defined(__CYGWIN__)
#define A_DECLSPEC(x) __declspec(x)
#else /* !__declspec */
#define A_DECLSPEC(x)
#endif /* __declspec */

#if defined(__GNUC__) || defined(__clang__)
#define A_ATTRIBUTE(x) __attribute__(x)
#else /* !__attribute__ */
#define A_ATTRIBUTE(x)
#endif /* __attribute__ */

#if __has_builtin(__builtin_assume)
#define A_ASSUME(x) __builtin_assume(x)
#elif A_PREREQ_GNUC(13, 0)
#define A_ASSUME(x) __attribute__((__assume__(x)))
#elif A_PREREQ_GNUC(4, 5)
#define A_ASSUME(x)                            \
    do {                                       \
        if (!(x)) { __builtin_unreachable(); } \
    } while (0)
#elif defined(_MSC_VER)
#define A_ASSUME(x) __assume(x)
#else /* !assume */
#define A_ASSUME(x) (void)0
#endif /* assume */

/* attribute nonnull */
#if A_PREREQ_GNUC(3, 3) || __has_attribute(__nonnull__)
#define A_NONULL(x) __attribute__((__nonnull__ x))
#else /* !nonnull */
#define A_NONULL(x)
#endif /* nonnull */

/* attribute format */
#if A_PREREQ_GNUC(2, 4) || __has_attribute(__format__)
#define A_FORMAT(_, a, b) __attribute__((__format__(_, a, b)))
#else /* !format */
#define A_FORMAT(_, a, b)
#endif /* format */

/* attribute fallthrough */
#if A_PREREQ_GNUC(7, 0) || __has_attribute(__fallthrough__)
#define A_FALLTHROUGH __attribute__((__fallthrough__))
#else /* !fallthrough */
#define A_FALLTHROUGH (void)0
#endif /* fallthrough */

/* attribute deprecated */
#if A_PREREQ_GNUC(3, 2) || __has_attribute(__deprecated__)
#define A_DEPRECATED __attribute__((__deprecated__))
#elif defined(_WIN32) || defined(__CYGWIN__)
#define A_DEPRECATED __declspec(deprecated)
#else /* !deprecated */
#define A_DEPRECATED
#endif /* deprecated */

/* attribute always inline */
#if A_PREREQ_GNUC(3, 2) || __has_attribute(__always_inline__)
#define A_INLINE __inline __attribute__((__always_inline__))
#elif defined(_MSC_VER)
#define A_INLINE __inline __forceinline
#else /* !_MSC_VER */
#define A_INLINE __inline
#endif /* _MSC_VER */
#if !defined A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_INTERN */

/* attribute visibility */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_EXPORT __declspec(dllexport)
#define A_IMPORT __declspec(dllimport)
#define A_HIDDEN
#elif A_PREREQ_GNUC(4, 0) || __has_attribute(__visibility__)
#define A_EXPORT __attribute__((__visibility__("default")))
#define A_IMPORT __attribute__((__visibility__("default")))
#define A_HIDDEN __attribute__((__visibility__("hidden")))
#else /* !visibility */
#define A_EXPORT
#define A_IMPORT
#define A_HIDDEN
#endif /* visibility */
#if defined(A_EXPORTS)
#define A_PUBLIC A_EXPORT
#elif defined(A_IMPORTS)
#define A_PUBLIC A_IMPORT
#else /* !A_PUBLIC */
#define A_PUBLIC
#endif /* A_PUBLIC */

#if !defined A_EXTERN
#define A_EXTERN A_PUBLIC extern
#endif /* A_EXTERN */
#if !defined __cplusplus
#define A_EXTERN_C
#define A_EXTERN_C_ENTER
#define A_EXTERN_C_LEAVE
#else /* !__cplusplus */
#define A_EXTERN_C extern "C"
#define A_EXTERN_C_ENTER extern "C" {
#define A_EXTERN_C_LEAVE }
#endif /* __cplusplus */

/*! @endcond */

#include <stddef.h>
#include <limits.h>
#include <float.h>

/*!
 @addtogroup liba algorithm library
 @{
*/

/*!
 @def A_ORDER_LITTLE
 @brief byte order of little endian architecture
*/
#if defined(__ORDER_LITTLE_ENDIAN__)
#define A_ORDER_LITTLE __ORDER_LITTLE_ENDIAN__
#else /* !__ORDER_LITTLE_ENDIAN__ */
#define A_ORDER_LITTLE 1234
#endif /* __ORDER_LITTLE_ENDIAN__ */
/*!
 @def A_ORDER_BIG
 @brief byte order of big endian architecture
*/
#if defined(__ORDER_BIG_ENDIAN__)
#define A_ORDER_BIG __ORDER_BIG_ENDIAN__
#else /* !__ORDER_BIG_ENDIAN__ */
#define A_ORDER_BIG 4321
#endif /* __ORDER_BIG_ENDIAN__ */
#if !defined A_BYTE_ORDER
/*!
 @def A_BYTE_ORDER
 @brief byte order of architecture
*/
#if defined(__BYTE_ORDER__)
#define A_BYTE_ORDER __BYTE_ORDER__
#else /* !__BYTE_ORDER__ */
#define A_BYTE_ORDER 1234
#endif /* __BYTE_ORDER__ */
#endif /* A_BYTE_ORDER */

#if !defined A_SIZE_POINTER
/*!
 @def A_SIZE_POINTER
 @brief size of void pointer
*/
#if defined(__SIZEOF_POINTER__)
#define A_SIZE_POINTER __SIZEOF_POINTER__
#elif defined(_WIN64) || defined(__LP64__)
#define A_SIZE_POINTER 8
#else /* !__SIZEOF_POINTER__ */
#define A_SIZE_POINTER 4
#endif /* __SIZEOF_POINTER__ */
#endif /* A_SIZE_POINTER */

/*! @brief assert a build-time dependency, as an expression */
#define A_BUILD_ASSERT(x) (void)(sizeof(char[1 - 2 * !(x)]))
/*! @brief assert a build-time dependency, as an expression */
#define A_BUILD_BUG_ON(x) (void)(sizeof(char[1 - 2 * !!(x)]))

#if defined(__cplusplus)
#define a_cast_r(T, x) reinterpret_cast<T>(x)
#define a_cast_d(T, x) dynamic_cast<T>(x)
#define a_cast_s(T, x) static_cast<T>(x)
#define a_cast_c(T, x) const_cast<T>(x)
#else /* !__cplusplus */
#define a_cast_r(T, x) ((T)(x))
#define a_cast_d(T, x) ((T)(x))
#define a_cast_s(T, x) ((T)(x))
#define a_cast_c(T, x) ((T)(x))
#endif /* __cplusplus */
#define A_CAST_3(a, b, c) a##b##c
#define A_CAST_2(a, b) a##b
#define A_CAST_1(a) #a

#if defined(__cplusplus) && defined(A_HAVE_NULLPTR)
#define A_NULL nullptr
#else /* !__cplusplus */
#define A_NULL NULL
#endif /* __cplusplus */
/*! @brief static cast to @ref a_void */
#define a_void_c(x) a_cast_s(void, x)
#define a_void_(_, x) a_cast_s(void _, x)
/*! @brief incomplete type or no parameter or no return value */
#define a_void void

#if defined(__cplusplus)
#define A_TRUE true
#define A_FALSE false
#if !defined A_BOOL
#define A_BOOL bool
#endif /* A_BOOL */
#else /* !__cplusplus */
#define A_TRUE 1
#define A_FALSE 0
#if !defined A_BOOL
#if defined(__STDC_VERSION__) || A_PREREQ_MSVC(18, 0)
#define A_BOOL _Bool
#else /* !__STDC_VERSION__ */
#define A_BOOL unsigned char
#endif /* __STDC_VERSION__ */
#endif /* A_BOOL */
#endif /* __cplusplus */
/*! @brief static cast to @ref a_bool */
#define a_bool_c(x) (!!(x))
/*! @brief type, capable of holding one of the two values: 1 and 0 */
typedef A_BOOL a_bool;

#define A_INT int
#define A_INT_MAX INT_MAX
#define A_INT_MIN INT_MIN
/*! @brief static cast to @ref a_int */
#define a_int_c(x) a_cast_s(a_int, x)
#define a_int_(_, x) a_cast_s(a_int _, x)
/*! @brief signed integer type is guaranteed to be at least 16 bits */
typedef A_INT a_int;

#define A_UINT unsigned int
#define A_UINT_MAX UINT_MAX
/*! @brief static cast to @ref a_uint */
#define a_uint_c(x) a_cast_s(a_uint, x)
#define a_uint_(_, x) a_cast_s(a_uint _, x)
/*! @brief unsigned integer type is guaranteed to be at least 16 bits */
typedef A_UINT a_uint;

#define A_SHRT short
#define A_SHRT_MAX SHRT_MAX
#define A_SHRT_MIN SHRT_MIN
/*! @brief static cast to @ref a_shrt */
#define a_shrt_c(x) a_cast_s(a_shrt, x)
#define a_shrt_(_, x) a_cast_s(a_shrt _, x)
/*! @brief signed integer type is guaranteed to be at least 16 bits */
typedef A_SHRT a_shrt;

#define A_USHRT unsigned short
#define A_USHRT_MAX USHRT_MAX
/*! @brief static cast to @ref a_ushrt */
#define a_ushrt_c(x) a_cast_s(a_ushrt, x)
#define a_ushrt_(_, x) a_cast_s(a_ushrt _, x)
/*! @brief unsigned integer type is guaranteed to be at least 16 bits */
typedef A_USHRT a_ushrt;

#define A_LONG long
#define A_LONG_MIN LONG_MIN
#define A_LONG_MAX LONG_MAX
/*! @brief static cast to @ref a_long */
#define a_long_c(x) a_cast_s(a_long, x)
#define a_long_(_, x) a_cast_s(a_long _, x)
/*! @brief signed integer type is guaranteed to be at least 32 bits */
typedef A_LONG a_long;

#define A_ULONG unsigned long
#define A_ULONG_MAX ULONG_MAX
/*! @brief static cast to @ref a_ulong */
#define a_ulong_c(x) a_cast_s(a_ulong, x)
#define a_ulong_(_, x) a_cast_s(a_ulong _, x)
/*! @brief unsigned integer type is guaranteed to be at least 32 bits */
typedef A_ULONG a_ulong;

#if defined(A_HAVE_LONG_LONG_TYPE)

#define A_LLONG long long
#define A_LLONG_MAX LLONG_MAX
#define A_LLONG_MIN LLONG_MIN
/*! @brief static cast to @ref a_llong */
#define a_llong_c(x) a_cast_s(a_llong, x)
#define a_llong_(_, x) a_cast_s(a_llong _, x)
/*! @brief signed integer type is guaranteed to be at least 64 bits */
typedef A_LLONG a_llong;

#define A_ULLONG unsigned long long
#define A_ULLONG_MAX ULLONG_MAX
/*! @brief static cast to @ref a_ullong */
#define a_ullong_c(x) a_cast_s(a_ullong, x)
#define a_ullong_(_, x) a_cast_s(a_ullong _, x)
/*! @brief unsigned integer type is guaranteed to be at least 64 bits */
typedef A_ULLONG a_ullong;

#endif /* A_HAVE_LONG_LONG_TYPE */

#define A_BYTE unsigned char
#define A_BYTE_MAX UCHAR_MAX
/*! @brief static cast to @ref a_byte */
#define a_byte_c(x) a_cast_s(a_byte, x)
#define a_byte_(_, x) a_cast_s(a_byte _, x)
/*! @brief type for unsigned character representation */
typedef A_BYTE a_byte;

#define A_C8 char
#define A_C8_MAX CHAR_MAX
#define A_C8_MIN CHAR_MIN
/*! @brief static cast to @ref a_c8 */
#define a_c8_c(x) a_cast_s(a_c8, x)
#define a_c8_(_, x) a_cast_s(a_c8 _, x)
/*! @brief type for character representation */
typedef A_C8 a_c8;

#if !defined A_I8
#define A_I8 signed char
#endif /* A_I8 */
#if !defined A_I8_C
#define A_I8_C(X) X
#endif /* A_I8_C */
#if !defined A_I8_MAX
#define A_I8_MAX A_I8_C(0x7F)
#endif /* A_I8_MAX */
#if !defined A_I8_MIN
#define A_I8_MIN A_I8_C(~0x7F)
#endif /* A_I8_MIN */
/*! @brief static cast to @ref a_i8 */
#define a_i8_c(x) a_cast_s(a_i8, x)
#define a_i8_(_, x) a_cast_s(a_i8 _, x)
/*! @brief signed integer type with width of exactly 8 bits */
typedef A_I8 a_i8;

#if !defined A_U8
#define A_U8 unsigned char
#endif /* A_U8 */
#if !defined A_U8_C
#define A_U8_C(X) X
#endif /* A_U8_C */
#if !defined A_U8_MAX
#define A_U8_MAX A_U8_C(0xFF)
#endif /* A_U8_MAX */
/*! @brief static cast to @ref a_u8 */
#define a_u8_c(x) a_cast_s(a_u8, x)
#define a_u8_(_, x) a_cast_s(a_u8 _, x)
/*! @brief unsigned integer type with width of exactly 8 bits */
typedef A_U8 a_u8;

#if !defined A_PRI8
#define A_PRI8
#endif /* A_PRI8 */
#if !defined A_SCN8
#define A_SCN8 "hh"
#endif /* A_SCN8 */

#if !defined A_I16 && (INT_MAX == 0x7FFFL)
#define A_I16 int
#elif !defined A_I16
#define A_I16 short
#endif /* A_I16 */
#if !defined A_I16_C
#define A_I16_C(X) X
#endif /* A_I16_C */
#if !defined A_I16_MAX
#define A_I16_MAX A_I16_C(0x7FFF)
#endif /* A_I16_MAX */
#if !defined A_I16_MIN
#define A_I16_MIN A_I16_C(~0x7FFF)
#endif /* A_I16_MIN */
/*! @brief static cast to @ref a_i16 */
#define a_i16_c(x) a_cast_s(a_i16, x)
#define a_i16_(_, x) a_cast_s(a_i16 _, x)
/*! @brief signed integer type with width of exactly 16 bits */
typedef A_I16 a_i16;

#if !defined A_U16 && (UINT_MAX == 0xFFFFUL)
#define A_U16 unsigned int
#elif !defined A_U16
#define A_U16 unsigned short
#endif /* A_U16 */
#if !defined A_U16_C
#define A_U16_C(X) X
#endif /* A_U16_C */
#if !defined A_U16_MAX
#define A_U16_MAX A_U16_C(0xFFFF)
#endif /* A_U16_MAX */
/*! @brief static cast to @ref a_u16 */
#define a_u16_c(x) a_cast_s(a_u16, x)
#define a_u16_(_, x) a_cast_s(a_u16 _, x)
/*! @brief unsigned integer type with width of exactly 16 bits */
typedef A_U16 a_u16;

#if !defined A_PRI16 && (UINT_MAX == 0xFFFFUL)
#define A_PRI16
#elif !defined A_PRI16
#define A_PRI16
#endif /* A_PRI16 */
#if !defined A_SCN16 && (UINT_MAX == 0xFFFFUL)
#define A_SCN16
#elif !defined A_SCN16
#define A_SCN16 "h"
#endif /* A_SCN16 */

#if !defined A_I32 && (INT_MAX == 0x7FFFFFFFL)
#define A_I32 int
#elif !defined A_I32
#define A_I32 long
#endif /* A_I32 */
#if !defined A_I32_C && (INT_MAX == 0x7FFFFFFFL)
#define A_I32_C(X) X
#elif !defined A_I32_C
#define A_I32_C(X) A_CAST_2(X, L)
#endif /* A_I32_C */
#if !defined A_I32_MAX
#define A_I32_MAX A_I32_C(0x7FFFFFFF)
#endif /* A_I32_MAX */
#if !defined A_I32_MIN
#define A_I32_MIN A_I32_C(~0x7FFFFFFF)
#endif /* A_I32_MIN */
/*! @brief static cast to @ref a_i32 */
#define a_i32_c(x) a_cast_s(a_i32, x)
#define a_i32_(_, x) a_cast_s(a_i32 _, x)
/*! @brief signed integer type with width of exactly 32 bits */
typedef A_I32 a_i32;

#if !defined A_U32 && (UINT_MAX == 0xFFFFFFFFUL)
#define A_U32 unsigned int
#elif !defined A_U32
#define A_U32 unsigned long
#endif /* A_U32 */
#if !defined A_U32_C && (UINT_MAX == 0xFFFFFFFFUL)
#define A_U32_C(X) A_CAST_2(X, U)
#elif !defined A_U32_C
#define A_U32_C(X) A_CAST_2(X, UL)
#endif /* A_U32_C */
#if !defined A_U32_MAX
#define A_U32_MAX A_U32_C(0xFFFFFFFF)
#endif /* A_U32_MAX */
/*! @brief static cast to @ref a_u32 */
#define a_u32_c(x) a_cast_s(a_u32, x)
#define a_u32_(_, x) a_cast_s(a_u32 _, x)
/*! @brief unsigned integer type with width of exactly 32 bits */
typedef A_U32 a_u32;

#if !defined A_PRI32 && (UINT_MAX == 0xFFFFFFFFUL)
#define A_PRI32
#elif !defined A_PRI32
#define A_PRI32 "l"
#endif /* A_PRI32 */
#if !defined A_SCN32 && (UINT_MAX == 0xFFFFFFFFUL)
#define A_SCN32
#elif !defined A_SCN32
#define A_SCN32 "l"
#endif /* A_SCN32 */

#if !defined A_I64 && (LONG_MAX == 0x7FFFFFFFL)
#if defined(_MSC_VER) && (_MSC_VER < 1800) ||        \
    defined(__WATCOMC__) && (__WATCOMC__ >= 1100) || \
    defined(__BORLANDC__) && (__BORLANDC__ >= 0x530)
#define A_I64 __int64
#else /* !extension */
#define A_I64 long long
#endif /* extension */
#elif !defined A_I64
#define A_I64 long
#endif /* A_I64 */
#if !defined A_I64_C && (LONG_MAX == 0x7FFFFFFFL)
#if defined(_MSC_VER) && (_MSC_VER < 1800) ||        \
    defined(__WATCOMC__) && (__WATCOMC__ >= 1100) || \
    defined(__BORLANDC__) && (__BORLANDC__ >= 0x530)
#define A_I64_C(X) A_CAST_2(X, i64)
#elif defined(__GNUC__)
#define A_I64_C(X) (A_CAST_2(__extension__ X, LL))
#else /* !extension */
#define A_I64_C(X) A_CAST_2(X, LL)
#endif /* extension */
#elif !defined A_I64_C
#define A_I64_C(X) A_CAST_2(X, L)
#endif /* A_I64_C */
#if !defined A_I64_MAX
#define A_I64_MAX A_I64_C(0x7FFFFFFFFFFFFFFF)
#endif /* A_I64_MAX */
#if !defined A_I64_MIN
#define A_I64_MIN A_I64_C(~0x7FFFFFFFFFFFFFFF)
#endif /* A_I64_MIN */
/*! @brief static cast to @ref a_i64 */
#define a_i64_c(x) a_cast_s(a_i64, x)
#define a_i64_(_, x) a_cast_s(a_i64 _, x)
/* clang-format off */
#if defined(__GNUC__)
__extension__
#endif /* __GNUC__ */
/*! @brief signed integer type with width of exactly 64 bits */
typedef A_I64 a_i64;
/* clang-format on */

#if !defined A_U64 && (ULONG_MAX == 0xFFFFFFFFUL)
#if defined(_MSC_VER) && (_MSC_VER < 1800) ||        \
    defined(__WATCOMC__) && (__WATCOMC__ >= 1100) || \
    defined(__BORLANDC__) && (__BORLANDC__ >= 0x530)
#define A_U64 unsigned __int64
#else /* !extension */
#define A_U64 unsigned long long
#endif /* extension */
#elif !defined A_U64
#define A_U64 unsigned long
#endif /* A_U64 */
#if !defined A_U64_C && (ULONG_MAX == 0xFFFFFFFFUL)
#if defined(_MSC_VER) && (_MSC_VER < 1800) ||        \
    defined(__WATCOMC__) && (__WATCOMC__ >= 1100) || \
    defined(__BORLANDC__) && (__BORLANDC__ >= 0x530)
#define A_U64_C(X) A_CAST_2(X, ui64)
#elif defined(__GNUC__)
#define A_U64_C(X) (A_CAST_2(__extension__ X, ULL))
#else /* !extension */
#define A_U64_C(X) A_CAST_2(X, ULL)
#endif /* extension */
#elif !defined A_U64_C
#define A_U64_C(X) A_CAST_2(X, UL)
#endif /* A_U64_C */
#if !defined A_U64_MAX
#define A_U64_MAX A_U64_C(0xFFFFFFFFFFFFFFFF)
#endif /* A_U64_MAX */
/*! @brief static cast to @ref a_u64 */
#define a_u64_c(x) a_cast_s(a_u64, x)
#define a_u64_(_, x) a_cast_s(a_u64 _, x)
/* clang-format off */
#if defined(__GNUC__)
__extension__
#endif /* __GNUC__ */
/*! @brief unsigned integer type with width of exactly 64 bits */
typedef A_U64 a_u64;
/* clang-format on */

#if !defined A_PRI64 && (ULONG_MAX == 0xFFFFFFFFUL)
#if defined(_MSC_VER) && (_MSC_VER < 1800) ||        \
    defined(__WATCOMC__) && (__WATCOMC__ >= 1100) || \
    defined(__BORLANDC__) && (__BORLANDC__ >= 0x530)
#define A_PRI64 "I64"
#else /* !extension */
#define A_PRI64 "ll"
#endif /* extension */
#elif !defined A_PRI64
#define A_PRI64 "l"
#endif /* A_PRI64 */
#if !defined A_SCN64 && (ULONG_MAX == 0xFFFFFFFFUL)
#if defined(_MSC_VER) && (_MSC_VER < 1800) ||        \
    defined(__WATCOMC__) && (__WATCOMC__ >= 1100) || \
    defined(__BORLANDC__) && (__BORLANDC__ >= 0x530)
#define A_SCN64 "I64"
#else /* !extension */
#define A_SCN64 "ll"
#endif /* extension */
#elif !defined A_SCN64
#define A_SCN64 "l"
#endif /* A_SCN64 */

#if !defined A_IMAX
#define A_IMAX A_I64
#endif /* A_IMAX */
#if !defined A_IMAX_C
#define A_IMAX_C(X) A_I64_C(X)
#endif /* A_IMAX_C */
#if !defined A_IMAX_MAX
#define A_IMAX_MAX A_I64_MAX
#endif /* A_IMAX_MAX */
#if !defined A_IMAX_MIN
#define A_IMAX_MIN A_I64_MIN
#endif /* A_IMAX_MIN */
/*! @brief static cast to @ref a_imax */
#define a_imax_c(x) a_cast_s(a_imax, x)
#define a_imax_(_, x) a_cast_s(a_imax _, x)
/*! @brief maximum-width signed integer type */
typedef A_IMAX a_imax;

#if !defined A_UMAX
#define A_UMAX A_U64
#endif /* A_UMAX */
#if !defined A_UMAX_C
#define A_UMAX_C(X) A_U64_C(X)
#endif /* A_UMAX_C */
#if !defined A_UMAX_MAX
#define A_UMAX_MAX A_U64_MAX
#endif /* A_UMAX_MAX */
/*! @brief static cast to @ref a_umax */
#define a_umax_c(x) a_cast_s(a_umax, x)
#define a_umax_(_, x) a_cast_s(a_umax _, x)
/*! @brief maximum-width unsigned integer type */
typedef A_UMAX a_umax;

#if !defined A_PRIMAX
#define A_PRIMAX A_PRI64
#endif /* A_PRIMAX */
#if !defined A_SCNMAX
#define A_SCNMAX A_SCN64
#endif /* A_SCNMAX */

#if !defined A_IPTR && (A_SIZE_POINTER == 2)
#define A_IPTR A_I16
#elif !defined A_IPTR && (A_SIZE_POINTER == 4)
#define A_IPTR A_I32
#elif !defined A_IPTR
#define A_IPTR A_I64
#endif /* A_IPTR */
#if !defined A_IPTR_MAX && (A_SIZE_POINTER == 2)
#define A_IPTR_MAX A_I16_MAX
#elif !defined A_IPTR_MAX && (A_SIZE_POINTER == 4)
#define A_IPTR_MAX A_I32_MAX
#elif !defined A_IPTR_MAX
#define A_IPTR_MAX A_I64_MAX
#endif /* A_IPTR_MAX */
#if !defined A_IPTR_MIN && (A_SIZE_POINTER == 2)
#define A_IPTR_MIN A_I16_MIN
#elif !defined A_IPTR_MIN && (A_SIZE_POINTER == 4)
#define A_IPTR_MIN A_I32_MIN
#elif !defined A_IPTR_MIN
#define A_IPTR_MIN A_I64_MIN
#endif /* A_IPTR_MIN */
/*! @brief static cast to @ref a_iptr */
#define a_iptr_c(x) a_cast_s(a_iptr, x)
#define a_iptr_(_, x) a_cast_s(a_iptr _, x)
/*! @brief signed integer type capable of holding a pointer to void */
typedef A_IPTR a_iptr;

#if !defined A_UPTR && (A_SIZE_POINTER == 2)
#define A_UPTR A_U16
#elif !defined A_UPTR && (A_SIZE_POINTER == 4)
#define A_UPTR A_U32
#elif !defined A_UPTR
#define A_UPTR A_U64
#endif /* A_UPTR */
#if !defined A_UPTR_MAX && (A_SIZE_POINTER == 2)
#define A_UPTR_MAX A_U16_MAX
#elif !defined A_UPTR_MAX && (A_SIZE_POINTER == 4)
#define A_UPTR_MAX A_U32_MAX
#elif !defined A_UPTR_MAX
#define A_UPTR_MAX A_U64_MAX
#endif /* A_UPTR_MAX */
/*! @brief static cast to @ref a_uptr */
#define a_uptr_c(x) a_cast_s(a_uptr, x)
#define a_uptr_(_, x) a_cast_s(a_uptr _, x)
/*! @brief unsigned integer type capable of holding a pointer to void */
typedef A_UPTR a_uptr;

#if !defined A_PRIPTR && (A_SIZE_POINTER == 2)
#define A_PRIPTR A_PRI16
#elif !defined A_PRIPTR && (A_SIZE_POINTER == 4)
#define A_PRIPTR A_PRI32
#elif !defined A_PRIPTR
#define A_PRIPTR A_PRI64
#endif /* A_PRIPTR */
#if !defined A_SCNPTR && (A_SIZE_POINTER == 2)
#define A_SCNPTR A_SCN16
#elif !defined A_SCNPTR && (A_SIZE_POINTER == 4)
#define A_SCNPTR A_SCN32
#elif !defined A_SCNPTR
#define A_SCNPTR A_SCN64
#endif /* A_SCNPTR */

#if !defined A_DIFF
#define A_DIFF ptrdiff_t
#endif /* A_DIFF */
#if !defined A_DIFF_MAX && defined(__PTRDIFF_MAX__)
#define A_DIFF_MAX __PTRDIFF_MAX__
#elif !defined A_DIFF_MAX && (A_SIZE_POINTER == 2)
#define A_DIFF_MAX A_I16_MAX
#elif !defined A_DIFF_MAX && (A_SIZE_POINTER == 4)
#define A_DIFF_MAX A_I32_MAX
#elif !defined A_DIFF_MAX
#define A_DIFF_MAX A_I64_MAX
#endif /* A_DIFF_MAX */
#if !defined A_DIFF_MIN && defined(__PTRDIFF_MAX__)
#define A_DIFF_MIN (~__PTRDIFF_MAX__)
#elif !defined A_DIFF_MIN && (A_SIZE_POINTER == 2)
#define A_DIFF_MIN A_I16_MIN
#elif !defined A_DIFF_MIN && (A_SIZE_POINTER == 4)
#define A_DIFF_MIN A_I32_MIN
#elif !defined A_DIFF_MIN
#define A_DIFF_MIN A_I64_MIN
#endif /* A_DIFF_MIN */
/*! @brief static cast to @ref a_diff */
#define a_diff_c(x) a_cast_s(a_diff, x)
#define a_diff_(_, x) a_cast_s(a_diff _, x)
/*! @brief signed integer type returned when subtracting two pointers */
typedef A_DIFF a_diff;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ > 199900L) || \
    defined(__cplusplus) && (__cplusplus > 201100L) || A_PREREQ_MSVC(19, 0)
#if !defined A_PRIt
#define A_PRIt "t"
#endif /* A_PRIt */
#if !defined A_SCNt
#define A_SCNt "t"
#endif /* A_SCNt */
#else /* C < 199900 and C++ < 201100 */
#if !defined A_PRIt && (A_SIZE_POINTER == 2)
#define A_PRIt A_PRI16
#elif !defined A_PRIt && (A_SIZE_POINTER == 4)
#define A_PRIt A_PRI32
#elif !defined A_PRIt
#define A_PRIt A_PRI64
#endif /* A_PRIt */
#if !defined A_SCNt && (A_SIZE_POINTER == 2)
#define A_SCNt A_SCN16
#elif !defined A_SCNt && (A_SIZE_POINTER == 4)
#define A_SCNt A_SCN32
#elif !defined A_SCNt
#define A_SCNt A_SCN64
#endif /* A_SCNt */
#endif /* C > 199900 or C++ > 201100 */

#if !defined A_SIZE
#define A_SIZE size_t
#endif /* A_SIZE */
#if !defined A_SIZE_MAX && defined(__SIZE_MAX__)
#define A_SIZE_MAX __SIZE_MAX__
#elif !defined A_SIZE_MAX && (A_SIZE_POINTER == 2)
#define A_SIZE_MAX A_U16_MAX
#elif !defined A_SIZE_MAX && (A_SIZE_POINTER == 4)
#define A_SIZE_MAX A_U32_MAX
#elif !defined A_SIZE_MAX
#define A_SIZE_MAX A_U64_MAX
#endif /* A_SIZE_MAX */
/*! @brief static cast to @ref a_size */
#define a_size_c(x) a_cast_s(a_size, x)
#define a_size_(_, x) a_cast_s(a_size _, x)
/*! @brief unsigned integer type returned by the sizeof operator */
typedef A_SIZE a_size;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ > 199900L) || \
    defined(__cplusplus) && (__cplusplus > 201100L) || A_PREREQ_MSVC(19, 0)
#if !defined A_PRIz
#define A_PRIz "z"
#endif /* A_PRIz */
#if !defined A_SCNz
#define A_SCNz "z"
#endif /* A_SCNz */
#else /* C < 199900 and C++ < 201100 */
#if !defined A_PRIz && (A_SIZE_POINTER == 2)
#define A_PRIz A_PRI16
#elif !defined A_PRIz && (A_SIZE_POINTER == 4)
#define A_PRIz A_PRI32
#elif !defined A_PRIz
#define A_PRIz A_PRI64
#endif /* A_PRIz */
#if !defined A_SCNz && (A_SIZE_POINTER == 2)
#define A_SCNz A_SCN16
#elif !defined A_SCNz && (A_SIZE_POINTER == 4)
#define A_SCNz A_SCN32
#elif !defined A_SCNz
#define A_SCNz A_SCN64
#endif /* A_SCNz */
#endif /* C > 199900 or C++ > 201100 */

#define A_F16_NNAN A_U16_C(0xFE00)
#define A_F16_PNAN A_U16_C(0x7E00)
#define A_F16_NINF A_U16_C(0xFC00)
#define A_F16_PINF A_U16_C(0x7C00)

#define A_F32 float
#define A_F32_C(X) A_CAST_2(X, F)
#define A_F32_F(F) A_CAST_2(F, f)
#define A_F32_DIG FLT_DIG
#define A_F32_EPSILON FLT_EPSILON
#define A_F32_MANT_DIG FLT_MANT_DIG
#define A_F32_MAX FLT_MAX
#define A_F32_MAX_10_EXP FLT_MAX_10_EXP
#define A_F32_MAX_EXP FLT_MAX_EXP
#define A_F32_MIN FLT_MIN
#define A_F32_MIN_10_EXP FLT_MIN_10_EXP
#define A_F32_MIN_EXP FLT_MIN_EXP
#define A_F32_INF a_cast_s(A_F32, 1e300 * 1e300)
#define A_F32_NAN a_cast_s(A_F32, A_F32_INF * 0)
#define A_F32_NNAN A_U32_C(0xFFC00000)
#define A_F32_PNAN A_U32_C(0x7FC00000)
#define A_F32_NINF A_U32_C(0xFF800000)
#define A_F32_PINF A_U32_C(0x7F800000)
/*! @brief static cast to @ref a_f32 */
#define a_f32_c(x) a_cast_s(a_f32, x)
#define a_f32_(_, x) a_cast_s(a_f32 _, x)
/*! @brief single precision floating point type. Matches IEEE-754 binary32 format if supported. */
typedef A_F32 a_f32;

#define A_F64 double
#define A_F64_C(X) X
#define A_F64_F(F) F
#define A_F64_DIG DBL_DIG
#define A_F64_EPSILON DBL_EPSILON
#define A_F64_MANT_DIG DBL_MANT_DIG
#define A_F64_MAX DBL_MAX
#define A_F64_MAX_10_EXP DBL_MAX_10_EXP
#define A_F64_MAX_EXP DBL_MAX_EXP
#define A_F64_MIN DBL_MIN
#define A_F64_MIN_10_EXP DBL_MIN_10_EXP
#define A_F64_MIN_EXP DBL_MIN_EXP
#define A_F64_INF a_cast_s(double, A_F32_INF)
#define A_F64_NAN a_cast_s(double, A_F32_NAN)
#define A_F64_NNAN A_U64_C(0xFFF8000000000000)
#define A_F64_PNAN A_U64_C(0x7FF8000000000000)
#define A_F64_NINF A_U64_C(0xFFF0000000000000)
#define A_F64_PINF A_U64_C(0x7FF0000000000000)
/*! @brief static cast to @ref a_f64 */
#define a_f64_c(x) a_cast_s(a_f64, x)
#define a_f64_(_, x) a_cast_s(a_f64 _, x)
/*! @brief double precision floating point type. Matches IEEE-754 binary64 format if supported. */
typedef A_F64 a_f64;

/*!
 @addtogroup a_real floating-point number
 @{
*/

/*!
 @def A_REAL_TYPE
 @brief floating-point number bytes
*/
#if !defined A_REAL_TYPE
#if !defined A_SIZE_REAL
#define A_REAL_TYPE A_REAL_DOUBLE
#else /* !A_SIZE_REAL */
#define A_REAL_TYPE A_SIZE_REAL
#endif /* A_SIZE_REAL */
#endif /* A_REAL_TYPE */
#define A_REAL_SINGLE 0x04
#define A_REAL_DOUBLE 0x08
#define A_REAL_EXTEND 0x10
#if defined(A_REAL)
#elif A_REAL_TYPE + 0 == A_REAL_SINGLE

/*! @brief floating-point number stored using `float` */
#define A_REAL float
#define A_REAL_DIG FLT_DIG
#define A_REAL_EPSILON FLT_EPSILON
#define A_REAL_MANT_DIG FLT_MANT_DIG
#define A_REAL_MAX FLT_MAX
#define A_REAL_MAX_10_EXP FLT_MAX_10_EXP
#define A_REAL_MAX_EXP FLT_MAX_EXP
#define A_REAL_MIN FLT_MIN
#define A_REAL_MIN_10_EXP FLT_MIN_10_EXP
#define A_REAL_MIN_EXP FLT_MIN_EXP
#define A_REAL_C(X) A_CAST_2(X, F)
#define A_REAL_F(F) A_CAST_2(F, f)
#define A_REAL_PRI
#define A_REAL_SCN
#define A_REAL_TOL 1e-3F
#define A_REAL_EPS 1e-6F
#define a_str2num strtof

#elif A_REAL_TYPE + 0 == A_REAL_DOUBLE

/*! @brief floating-point number stored using `double` */
#define A_REAL double
#define A_REAL_DIG DBL_DIG
#define A_REAL_EPSILON DBL_EPSILON
#define A_REAL_MANT_DIG DBL_MANT_DIG
#define A_REAL_MAX DBL_MAX
#define A_REAL_MAX_10_EXP DBL_MAX_10_EXP
#define A_REAL_MAX_EXP DBL_MAX_EXP
#define A_REAL_MIN DBL_MIN
#define A_REAL_MIN_10_EXP DBL_MIN_10_EXP
#define A_REAL_MIN_EXP DBL_MIN_EXP
#define A_REAL_C(X) X
#define A_REAL_F(F) F
#define A_REAL_PRI
#define A_REAL_SCN "l"
#define A_REAL_TOL 1e-6
#define A_REAL_EPS 1e-12
#define a_str2num strtod

#elif A_REAL_TYPE + 0 == A_REAL_EXTEND

/*! @brief floating-point number stored using `long double` */
#define A_REAL long double
#define A_REAL_DIG LDBL_DIG
#define A_REAL_EPSILON LDBL_EPSILON
#define A_REAL_MANT_DIG LDBL_MANT_DIG
#define A_REAL_MAX LDBL_MAX
#define A_REAL_MAX_10_EXP LDBL_MAX_10_EXP
#define A_REAL_MAX_EXP LDBL_MAX_EXP
#define A_REAL_MIN LDBL_MIN
#define A_REAL_MIN_10_EXP LDBL_MIN_10_EXP
#define A_REAL_MIN_EXP LDBL_MIN_EXP
#define A_REAL_C(X) A_CAST_2(X, L)
#define A_REAL_F(F) A_CAST_2(F, l)
#define A_REAL_PRI "L"
#define A_REAL_SCN "L"
#define A_REAL_TOL 1e-9L
#define A_REAL_EPS 1e-18L
#define a_str2num strtold

#else /* !A_REAL_TYPE */
#error unsupported precision
#endif /* A_REAL_TYPE */

#define A_REAL_INF a_cast_s(A_REAL, A_F32_INF)
#define A_REAL_NAN a_cast_s(A_REAL, A_F32_NAN)
/*!
 @def A_REAL_C(X)
 @brief expands to a floating-point constant expression having the value specified by its argument and the type @ref a_real
*/
/*!
 @def A_REAL_F(F)
 @brief expands to a floating-point function expression having the value specified by its argument and the type @ref a_real
*/
/*!
 @def A_REAL_SCN
 @brief format constants for the fscanf family of functions
*/
/*!
 @def A_REAL_PRI
 @brief format constants for the fprintf family of functions
*/
/*! @brief static cast to @ref a_real */
#define a_real_c(x) a_cast_s(a_real, x)
#define a_real_(_, x) a_cast_s(a_real _, x)
/*! @brief compiler built-in floating-point number type */
typedef A_REAL a_real;

/*! @} a_real */

typedef union a_cast
{
    a_c8 c;
    a_int i;
    a_uint u;
    a_shrt ih;
    a_ushrt uh;
    a_long il;
    a_ulong ul;
#if defined(A_HAVE_LONG_LONG_TYPE)
    a_llong ill;
    a_ullong ull;
#endif /* A_HAVE_LONG_LONG_TYPE */
    a_i8 i8;
    a_u8 u8;
    a_i16 i16;
    a_u16 u16;
    a_i32 i32;
    a_u32 u32;
    a_i64 i64;
    a_u64 u64;
    a_f32 f32;
    a_f64 f64;
    a_imax imax;
    a_umax umax;
    a_iptr iptr;
    a_uptr uptr;
    a_diff diff;
    a_size size;
    void const *PTR;
    void *ptr;
    char const *STR;
    char *str;
#if defined(A_REAL_TYPE) && (A_REAL_TYPE + 0 < A_REAL_EXTEND)
    a_real f;
#endif /* A_REAL_TYPE */
} a_cast;

/*!
 @brief square of x, \f$ x^2 \f$
*/
#define A_SQ(x) ((x) * (x))

/*!
 @brief absolute value of x, \f$ |x| \f$
*/
#define A_ABS(x) ((x) < 0 ? -(x) : (x))
/*!
 @brief absolute value of f-g, \f$ |f-g| \f$
*/
#define A_ABS_(f, g) ((f) < (g) ? (g) - (f) : (f) - (g))

/*!
 @brief minimum value between x and y
*/
#define A_MIN(x, y) (((x) < (y)) ? (x) : (y))

/*!
 @brief maximum value between x and y
*/
#define A_MAX(x, y) (((x) > (y)) ? (x) : (y))

/*!
 @brief signum function, \f$ \texttt{sgn}(x)=\begin{cases}+1&x>0\\0&0\\-1&x<0\end{cases} \f$
*/
#define A_SGN(x) ((0 < (x)) - ((x) < 0))
/*!
 @brief signum function, \f$ \texttt{sgn}(f,g)=\begin{cases}+1&f>g\\0&f=g\\-1&f<g\end{cases} \f$
*/
#define A_SGN_(f, g) (((f) > (g)) - ((f) < (g)))

/*!
 @brief saturation value of x, \f$ \texttt{sat}(x,min,max)=\begin{cases}min&min>x\\max&x>max\\x&else\end{cases} \f$
*/
#define A_SAT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

/*!
 @brief number of elements in a visible array
 @param a must be a visible array
*/
#define A_LEN(a) (sizeof(a) / sizeof(*(a)))

/*!
 @brief offset of a structure member
 @param type structure type
 @param member member variable
*/
#if defined(offsetof)
#define a_offsetof(type, member) offsetof(type, member)
#else /* !offsetof */
#define a_offsetof(type, member) a_cast_r(a_size, &a_cast_r(type *, 0)->member)
#endif /* offsetof */

/*!
 @brief container of a structure member
 @param ptr pointer to a member variable
 @param type structure type
 @param member member variable
*/
#define a_container_of(ptr, type, member) a_cast_r(type *, a_cast_r(a_uptr, ptr) - a_offsetof(type, member))

/*!
 @brief round down size `n` to be a multiple of `a`
*/
#define a_size_down(a, n) (a_cast_s(a_size, n) & ~a_cast_s(a_size, (a) - 1))

/*!
 @brief round up size `n` to be a multiple of `a`
*/
#define a_size_up(a, n) ((a_cast_s(a_size, n) + (a) - 1) & ~a_cast_s(a_size, (a) - 1))

/*!
 @brief round pointer `p` down to the closest `a`, aligned address <= `p`
*/
#define a_align_down(a, p) a_cast_r(void *, a_cast_r(a_uptr, p) & ~a_cast_s(a_uptr, (a) - 1))

/*!
 @brief round pointer `p` up to the closest `a`, aligned address >= `p`
*/
#define a_align_up(a, p) a_cast_r(void *, (a_cast_r(a_uptr, p) + (a) - 1) & ~a_cast_s(a_uptr, (a) - 1))

/*!
 @brief iterate from 0 to n and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum(I, i, n) for (I i = 0; i < (n); ++i)
#define A_FORENUM(I, i, n) for (i = 0; i < a_cast_s(I, n); ++i)

/*!
 @brief iterate from n to 0 and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum_reverse(I, i, n) for (I i = (n); i-- > 0;)
#define A_FORENUM_REVERSE(I, i, n) for (i = a_cast_s(I, n); i-- > 0;)

/*!
 @brief iterate over an array
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach(T, S, it, ptr, num) \
    for (T S it = a_cast_s(T S, ptr), S it##_ = it + (num); it < it##_; ++it)
#define A_FOREACH(T, it, at, ptr, num) \
    for (it = a_cast_s(T, ptr), at = it + (num); it < at; ++it)
/*! @copydoc a_foreach */
#define a_forsafe(T, S, it, ptr, num) \
    for (T S it = a_cast_s(T S, ptr), S it##_ = (num) ? it + (num) : it; it < it##_; ++it)
#define A_FORSAFE(T, it, at, ptr, num) \
    for (it = a_cast_s(T, ptr), at = (num) ? it + (num) : it; it < at; ++it)

/*!
 @brief iterate over an array in reverse
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach_reverse(T, S, it, ptr, num) \
    for (T S it##_ = a_cast_s(T S, ptr) - 1, S it = it##_ + (num); it > it##_; --it)
#define A_FOREACH_REVERSE(T, it, at, ptr, num) \
    for (at = a_cast_s(T, ptr) - 1, it = at + (num); it > at; --it)
/*! @copydoc a_foreach_reverse */
#define a_forsafe_reverse(T, S, it, ptr, num)                             \
    for (T S it##_ = (num) ? a_cast_s(T S, ptr) - 1 : a_cast_s(T S, ptr), \
             S it = (num) ? it##_ + (num) : it##_;                        \
         it > it##_; --it)
#define A_FORSAFE_REVERSE(T, it, at, ptr, num)                 \
    for (at = (num) ? a_cast_s(T, ptr) - 1 : a_cast_s(T, ptr), \
        it = (num) ? at + (num) : at;                          \
         it > at; --it)

/*!
 @brief iterate over an array
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate(T, S, it, ptr, end) \
    for (T S it = a_cast_s(T S, ptr), S it##_ = a_cast_s(T S, end); it < it##_; ++it)
#define A_ITERATE(T, it, at, ptr, end) \
    for (it = a_cast_s(T, ptr), at = a_cast_s(T, end); it < at; ++it)

/*!
 @brief iterate over an array in reverse
 @param T the prefix of the element type
 @param S the suffix of the element type
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate_reverse(T, S, it, ptr, end) \
    for (T S it = a_cast_s(T S, end) - 1, S it##_ = a_cast_s(T S, ptr) - 1; it > it##_; --it)
#define A_ITERATE_REVERSE(T, it, at, ptr, end) \
    for (it = a_cast_s(T, end) - 1, at = a_cast_s(T, ptr) - 1; it > at; --it)

/*!
 @brief enumeration for return values
*/
enum a_return_code
{
    A_SUCCESS,
    A_FAILURE,
    A_INVALID,
    A_OBOUNDS,
    A_OMEMORY
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_A_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_A_C */

/*!
 @brief reverse the bits in an 8-bit unsigned integer
 @param x an 8-bit unsigned integer to be reversed
 @return reversed 8-bit unsigned integer
*/
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_u8 a_u8_rev(a_u8 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_u8 a_u8_rev(a_u8 x)
{
    x = a_cast_s(a_u8, (x >> 4) | (x << 4));
    x = a_cast_s(a_u8, ((x & 0xCC) >> 2) | ((x & 0x33) << 2));
    x = a_cast_s(a_u8, ((x & 0xAA) >> 1) | ((x & 0x55) << 1));
    return x;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief reverse the bits in a 16-bit unsigned integer
 @param x a 16-bit unsigned integer to be reversed
 @return reversed 16-bit unsigned integer
*/
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_u16 a_u16_rev(a_u16 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_u16 a_u16_rev(a_u16 x)
{
    x = a_cast_s(a_u16, (x >> 8) | (x << 8));
    x = a_cast_s(a_u16, ((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));
    x = a_cast_s(a_u16, ((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));
    x = a_cast_s(a_u16, ((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));
    return x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) a_u16 a_u16_getl(void const *b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) a_u16 a_u16_getl(void const *b)
{
    a_byte const *p = a_cast_s(a_byte const *, b);
    return a_cast_s(a_u16, (p[0] << 0) | (p[1] << 8));
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) a_u16 a_u16_getb(void const *b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) a_u16 a_u16_getb(void const *b)
{
    a_byte const *p = a_cast_s(a_byte const *, b);
    return a_cast_s(a_u16, (p[1] << 0) | (p[0] << 8));
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) void a_u16_setl(void *b, a_u16 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) void a_u16_setl(void *b, a_u16 x)
{
    a_byte *p = a_cast_s(a_byte *, b);
    p[0] = a_cast_s(a_byte, x >> 0);
    p[1] = a_cast_s(a_byte, x >> 8);
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) void a_u16_setb(void *b, a_u16 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) void a_u16_setb(void *b, a_u16 x)
{
    a_byte *p = a_cast_s(a_byte *, b);
    p[0] = a_cast_s(a_byte, x >> 8);
    p[1] = a_cast_s(a_byte, x >> 0);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief reverse the bits in a 32-bit unsigned integer
 @param x a 32-bit unsigned integer to be reversed
 @return reversed 32-bit unsigned integer
*/
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_u32 a_u32_rev(a_u32 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_u32 a_u32_rev(a_u32 x)
{
    x = (x >> 16) | (x << 16);
    x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);
    x = ((x & 0xF0F0F0F0) >> 4) | ((x & 0x0F0F0F0F) << 4);
    x = ((x & 0xCCCCCCCC) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xAAAAAAAA) >> 1) | ((x & 0x55555555) << 1);
    return x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) a_u32 a_u32_getl(void const *b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) a_u32 a_u32_getl(void const *b)
{
    a_byte const *p = a_cast_s(a_byte const *, b);
    return (a_cast_s(a_u32, p[0]) << 0x00) |
           (a_cast_s(a_u32, p[1]) << 0x08) |
           (a_cast_s(a_u32, p[2]) << 0x10) |
           (a_cast_s(a_u32, p[3]) << 0x18);
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) a_u32 a_u32_getb(void const *b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) a_u32 a_u32_getb(void const *b)
{
    a_byte const *p = a_cast_s(a_byte const *, b);
    return (a_cast_s(a_u32, p[0]) << 0x18) |
           (a_cast_s(a_u32, p[1]) << 0x10) |
           (a_cast_s(a_u32, p[2]) << 0x08) |
           (a_cast_s(a_u32, p[3]) << 0x00);
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) void a_u32_setl(void *b, a_u32 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) void a_u32_setl(void *b, a_u32 x)
{
    a_byte *p = a_cast_s(a_byte *, b);
    p[0] = a_cast_s(a_byte, x >> 0x00);
    p[1] = a_cast_s(a_byte, x >> 0x08);
    p[2] = a_cast_s(a_byte, x >> 0x10);
    p[3] = a_cast_s(a_byte, x >> 0x18);
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) void a_u32_setb(void *b, a_u32 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) void a_u32_setb(void *b, a_u32 x)
{
    a_byte *p = a_cast_s(a_byte *, b);
    p[0] = a_cast_s(a_byte, x >> 0x18);
    p[1] = a_cast_s(a_byte, x >> 0x10);
    p[2] = a_cast_s(a_byte, x >> 0x08);
    p[3] = a_cast_s(a_byte, x >> 0x00);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief reverse the bits in a 64-bit unsigned integer
 @param x a 64-bit unsigned integer to be reversed
 @return reversed 64-bit unsigned integer
*/
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_u64 a_u64_rev(a_u64 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_u64 a_u64_rev(a_u64 x)
{
    x = (x >> 32) | (x << 32);
    x = ((x & 0xFFFF0000FFFF0000) >> 0x10) | ((x & 0x0000FFFF0000FFFF) << 0x10);
    x = ((x & 0xFF00FF00FF00FF00) >> 0x08) | ((x & 0x00FF00FF00FF00FF) << 0x08);
    x = ((x & 0xF0F0F0F0F0F0F0F0) >> 0x04) | ((x & 0x0F0F0F0F0F0F0F0F) << 0x04);
    x = ((x & 0xCCCCCCCCCCCCCCCC) >> 0x02) | ((x & 0x3333333333333333) << 0x02);
    x = ((x & 0xAAAAAAAAAAAAAAAA) >> 0x01) | ((x & 0x5555555555555555) << 0x01);
    return x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) a_u64 a_u64_getl(void const *b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) a_u64 a_u64_getl(void const *b)
{
    a_byte const *p = a_cast_s(a_byte const *, b);
    return (a_cast_s(a_u64, p[0]) << 0x00) |
           (a_cast_s(a_u64, p[1]) << 0x08) |
           (a_cast_s(a_u64, p[2]) << 0x10) |
           (a_cast_s(a_u64, p[3]) << 0x18) |
           (a_cast_s(a_u64, p[4]) << 0x20) |
           (a_cast_s(a_u64, p[5]) << 0x28) |
           (a_cast_s(a_u64, p[6]) << 0x30) |
           (a_cast_s(a_u64, p[7]) << 0x38);
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) a_u64 a_u64_getb(void const *b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) a_u64 a_u64_getb(void const *b)
{
    a_byte const *p = a_cast_s(a_byte const *, b);
    return (a_cast_s(a_u64, p[0]) << 0x38) |
           (a_cast_s(a_u64, p[1]) << 0x30) |
           (a_cast_s(a_u64, p[2]) << 0x28) |
           (a_cast_s(a_u64, p[3]) << 0x20) |
           (a_cast_s(a_u64, p[4]) << 0x18) |
           (a_cast_s(a_u64, p[5]) << 0x10) |
           (a_cast_s(a_u64, p[6]) << 0x08) |
           (a_cast_s(a_u64, p[7]) << 0x00);
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) void a_u64_setl(void *b, a_u64 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) void a_u64_setl(void *b, a_u64 x)
{
    a_byte *p = a_cast_s(a_byte *, b);
    p[0] = a_cast_s(a_byte, x >> 0x00);
    p[1] = a_cast_s(a_byte, x >> 0x08);
    p[2] = a_cast_s(a_byte, x >> 0x10);
    p[3] = a_cast_s(a_byte, x >> 0x18);
    p[4] = a_cast_s(a_byte, x >> 0x20);
    p[5] = a_cast_s(a_byte, x >> 0x28);
    p[6] = a_cast_s(a_byte, x >> 0x30);
    p[7] = a_cast_s(a_byte, x >> 0x38);
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN A_NONULL((1)) void a_u64_setb(void *b, a_u64 x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN A_NONULL((1)) void a_u64_setb(void *b, a_u64 x)
{
    a_byte *p = a_cast_s(a_byte *, b);
    p[0] = a_cast_s(a_byte, x >> 0x38);
    p[1] = a_cast_s(a_byte, x >> 0x30);
    p[2] = a_cast_s(a_byte, x >> 0x28);
    p[3] = a_cast_s(a_byte, x >> 0x20);
    p[4] = a_cast_s(a_byte, x >> 0x18);
    p[5] = a_cast_s(a_byte, x >> 0x10);
    p[6] = a_cast_s(a_byte, x >> 0x08);
    p[7] = a_cast_s(a_byte, x >> 0x00);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief copy one buffer to another
 @param[in] dst pointer to the object to copy to
 @param[in] src pointer to the object to copy from
 @param[in] siz number of bytes to copy
 @return a copy of dest
*/
A_EXTERN A_NONULL((1, 2)) void *a_copy(void *__restrict dst, void const *__restrict src, a_size siz);

/*!
 @brief move one buffer to another
 @param[in] dst pointer to the object to copy to
 @param[in] src pointer to the object to copy from
 @param[in] siz number of bytes to copy
 @return a copy of dest
*/
A_EXTERN A_NONULL((1, 2)) void *a_move(void *dst, void const *src, a_size siz);

/*!
 @brief fill a buffer with a character
 @param[in] ptr pointer to the object to fill
 @param[in] siz number of bytes to fill
 @param[in] val fill byte
 @return a copy of dest
*/
A_EXTERN A_NONULL((1)) void *a_fill(void *ptr, a_size siz, int val);

/*!
 @brief fill a buffer with zero
 @param[in] ptr pointer to the object to fill
 @param[in] siz number of bytes to fill
 @return a copy of dest
*/
A_EXTERN A_NONULL((1)) void *a_zero(void *ptr, a_size siz);

/*!
 @brief swap two different memory blocks of the same size
 @param[in,out] lhs points to memory block on the left
 @param[in,out] rhs points to memory block on the right
 @param[in] siz the size of memory block being swapped
*/
A_EXTERN A_NONULL((1, 2)) void a_swap(void *lhs, void *rhs, a_size siz);

/*!
 @brief allocation function pointer
 @param[in] addr address of memory block
 @param[in] size new size of memory block
 @return new address of memory block or null
*/
A_EXTERN void *(*a_alloc)(void *addr, a_size size);

/*!
 @brief default allocation function
 @param[in] addr address of memory block
 @param[in] size new size of memory block
 @return new address of memory block or null
*/
A_EXTERN void *a_alloc_(void *addr, a_size size);

#if defined(LIBA_A_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_A_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @brief declare allocation function */
#define A_ALLOC(alloc, addr, size) void *alloc(void *addr, a_size size)
#define a_new(T, ptr, num) a_cast_s(T *, a_alloc(ptr, sizeof(T) * (num)))
#define a_die(ptr) a_alloc(ptr, 0)

/*! @} liba */

#endif /* a/a.h */
