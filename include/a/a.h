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

#if defined(__STDC_LIB_EXT1__)
#if !defined __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif /* __STDC_WANT_LIB_EXT1__ */
#endif /* __STDC_LIB_EXT1__ */

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

#if __has_warning("-Wdisabled-macro-expansion")
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif /* -Wdisabled-macro-expansion */

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

/* https://en.cppreference.com/w/cpp/preprocessor/replace */
#if !defined __cplusplus
/* https://en.cppreference.com/w/c/preprocessor/replace */
#if !defined __STDC_VERSION__ && A_PREREQ_MSVC(18, 0)
#define __STDC_VERSION__ 199901L /* C99 */
#elif !defined __STDC_VERSION__
#define __STDC_VERSION__ 199001L /* C90 */
#endif /* __STDC_VERSION__ */
#endif /* __cplusplus */

#if defined(__cplusplus) && (__cplusplus > 201100L) || \
    defined(__STDC_VERSION__) && (__STDC_VERSION__ > 199900L)

#if !defined A_HAVE_VARIADIC_MACROS
#define A_HAVE_VARIADIC_MACROS 1
#endif /* A_HAVE_VARIADIC_MACROS */

#if !defined A_HAVE_LONG_LONG_TYPE
#define A_HAVE_LONG_LONG_TYPE 1
#endif /* A_HAVE_LONG_LONG_TYPE */

#endif /* C > 199900 or C++ > 201100 */
#if defined(A_HAVE_VARIADIC_MACROS) && (A_HAVE_VARIADIC_MACROS + 0 < 1)
#undef A_HAVE_VARIADIC_MACROS
#endif /* A_HAVE_VARIADIC_MACROS */
#if defined(A_HAVE_LONG_LONG_TYPE) && (A_HAVE_LONG_LONG_TYPE + 0 < 1)
#undef A_HAVE_LONG_LONG_TYPE
#endif /* A_HAVE_LONG_LONG_TYPE */

#if defined(__cplusplus) && (__cplusplus > 201100L) || \
    defined(__STDC_VERSION__) && (__STDC_VERSION__ > 201100L)

#if !defined A_HAVE_STATIC_ASSERT
#define A_HAVE_STATIC_ASSERT 1
#endif /* A_HAVE_STATIC_ASSERT */

#endif /* C > 201100 or C++ > 201100 */
#if defined(A_HAVE_STATIC_ASSERT) && (A_HAVE_STATIC_ASSERT + 0 < 1)
#undef A_HAVE_STATIC_ASSERT
#endif /* A_HAVE_STATIC_ASSERT */

#if defined(__cplusplus) && (__cplusplus > 201100L)

#if !defined A_HAVE_NULLPTR
#define A_HAVE_NULLPTR 1
#endif /* A_HAVE_NULLPTR */

#endif /*  C++ > 201100 */
#if defined(A_HAVE_NULLPTR) && (A_HAVE_NULLPTR + 0 < 1)
#undef A_HAVE_NULLPTR
#endif /* A_HAVE_NULLPTR */

#if A_PREREQ_GNUC(2, 96) || __has_builtin(__builtin_expect)
#define a_unlikely(x) __builtin_expect(!!(x), 0)
#define a_likely(x) __builtin_expect(!!(x), 1)
#else /* !__GNUC__ */
#define a_unlikely(x) (x)
#define a_likely(x) (x)
#endif /* __GNUC__ */

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

/* attribute format */
#if A_PREREQ_GNUC(2, 4) || __has_attribute(format)
#define A_FORMAT(_, a, b) __attribute__((format(_, a, b)))
#else /* !format */
#define A_FORMAT(_, a, b)
#endif /* format */

/* attribute fallthrough */
#if A_PREREQ_GNUC(7, 1) || __has_attribute(fallthrough)
#define A_FALLTHROUGH __attribute__((fallthrough))
#else /* !fallthrough */
#define A_FALLTHROUGH ((void)(0))
#endif /* fallthrough */

/* attribute deprecated */
#if A_PREREQ_GNUC(3, 2) || __has_attribute(deprecated)
#define A_DEPRECATED __attribute__((deprecated))
#elif defined(_WIN32) || defined(__CYGWIN__)
#define A_DEPRECATED __declspec(deprecated)
#else /* !deprecated */
#define A_DEPRECATED
#endif /* deprecated */

/* attribute always inline */
#if A_PREREQ_GNUC(3, 2) || __has_attribute(always_inline)
#define A_INLINE __inline __attribute__((always_inline))
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
#elif A_PREREQ_GNUC(4, 0) || __has_attribute(visibility)
#define A_EXPORT __attribute__((visibility("default")))
#define A_IMPORT __attribute__((visibility("default")))
#define A_HIDDEN __attribute__((visibility("hidden")))
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

#if !defined __cplusplus
#define A_EXTERN_C
#define A_EXTERN_C_ENTER
#define A_EXTERN_C_LEAVE
#else /* !__cplusplus */
#define A_EXTERN_C extern "C"
#define A_EXTERN_C_ENTER extern "C" {
#define A_EXTERN_C_LEAVE }
#endif /* __cplusplus */
#if !defined A_EXTERN
#define A_EXTERN extern A_PUBLIC
#endif /* A_EXTERN */

#if defined(__cplusplus)
#define A_REGISTER
#else /* !__cplusplus */
#define A_REGISTER __register
#endif /* __cplusplus */
#define A_VOLATILE __volatile
#define A_RESTRICT __restrict

/*! @endcond */

#if defined(__ORDER_LITTLE_ENDIAN__)
#define A_ORDER_LITTLE __ORDER_LITTLE_ENDIAN__
#else /* !__ORDER_LITTLE_ENDIAN__ */
#define A_ORDER_LITTLE 1234
#endif /* __ORDER_LITTLE_ENDIAN__ */
#if defined(__ORDER_BIG_ENDIAN__)
#define A_ORDER_BIG __ORDER_BIG_ENDIAN__
#else /* !__ORDER_BIG_ENDIAN__ */
#define A_ORDER_BIG 4321
#endif /* __ORDER_BIG_ENDIAN__ */
#if !defined A_BYTE_ORDER
#if defined(__BYTE_ORDER__)
#define A_BYTE_ORDER __BYTE_ORDER__
#endif /* __BYTE_ORDER__ */
#endif /* A_BYTE_ORDER */

/* size of void pointer */
#if !defined A_SIZE_POINTER
#if defined(__SIZEOF_POINTER__)
#define A_SIZE_POINTER __SIZEOF_POINTER__
#elif defined(_WIN64)
#define A_SIZE_POINTER 8
#elif defined(_WIN32)
#define A_SIZE_POINTER 4
#endif /* __SIZEOF_POINTER__ */
#endif /* A_SIZE_POINTER */

#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>

/*!
 @addtogroup A algorithm library
 @{
*/

/*! assert a build-time dependency, as an expression */
#define A_ASSERT_BUILD(x) (sizeof(char[1 - 2 * !(x)]) - 1)

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

#if defined(__cplusplus)
#define A_TRUE true
#define A_FALSE false
#if !defined A_BOOL_T
#define A_BOOL_T bool
#endif /* A_BOOL_T */
#else /* !__cplusplus */
#define A_TRUE 1
#define A_FALSE 0
#if !defined A_BOOL_T
#define A_BOOL_T _Bool
#endif /* A_BOOL_T */
#endif /* __cplusplus */
/*! static cast to \ref a_bool_t */
#define a_bool_c(x) (!!(x))
/*! type, capable of holding one of the two values: 1 and 0 */
#define a_bool_t A_BOOL_T

#define A_INT_T int
#define A_INT_MIN INT_MIN
#define A_INT_MAX INT_MAX
/*! static cast to \ref a_int_t . */
#define a_int_c(_, x) a_cast_s(A_INT_T _, x)
/*! signed integer type is guaranteed to be at least 16 bits */
#define a_int_t A_INT_T

#define A_UINT_T unsigned int
#define A_UINT_MAX UINT_MAX
/*! static cast to \ref a_uint_t . */
#define a_uint_c(_, x) a_cast_s(A_UINT_T _, x)
/*! unsigned integer type is guaranteed to be at least 16 bits */
#define a_uint_t A_UINT_T

#define A_SHRT_T short
#define A_SHRT_MIN SHRT_MIN
#define A_SHRT_MAX SHRT_MAX
/*! static cast to \ref a_shrt_t . */
#define a_shrt_c(_, x) a_cast_s(A_SHRT_T _, x)
/*! signed integer type is guaranteed to be at least 16 bits */
#define a_shrt_t A_SHRT_T

#define A_USHRT_T unsigned short
#define A_USHRT_MAX USHRT_MAX
/*! static cast to \ref a_ushrt_t . */
#define a_ushrt_c(_, x) a_cast_s(A_USHRT_T _, x)
/*! unsigned integer type is guaranteed to be at least 16 bits */
#define a_ushrt_t A_USHRT_T

#define A_LONG_T long
#define A_LONG_MIN LONG_MIN
#define A_LONG_MAX LONG_MAX
/*! static cast to \ref a_long_t . */
#define a_long_c(_, x) a_cast_s(A_LONG_T _, x)
/*! signed integer type is guaranteed to be at least 32 bits */
#define a_long_t A_LONG_T

#define A_ULONG_T unsigned long
#define A_ULONG_MAX ULONG_MAX
/*! static cast to \ref a_ulong_t . */
#define a_ulong_c(_, x) a_cast_s(A_ULONG_T _, x)
/*! unsigned integer type is guaranteed to be at least 32 bits */
#define a_ulong_t A_ULONG_T

#if defined(A_HAVE_LONG_LONG_TYPE)

#define A_LLONG_T long long
#define A_LLONG_MIN LLONG_MIN
#define A_LLONG_MAX LLONG_MAX
/*! static cast to \ref a_llong_t . */
#define a_llong_c(_, x) a_cast_s(A_LLONG_T _, x)
/*! signed integer type is guaranteed to be at least 64 bits */
#define a_llong_t A_LLONG_T

#define A_ULLONG_T unsigned long long
#define A_ULLONG_MAX ULLONG_MAX
/*! static cast to \ref a_ullong_t . */
#define a_ullong_c(_, x) a_cast_s(A_ULLONG_T _, x)
/*! unsigned integer type is guaranteed to be at least 64 bits */
#define a_ullong_t A_ULLONG_T

#endif /* A_HAVE_LONG_LONG_TYPE */

#define A_BYTE_T unsigned char
#define A_BYTE_MAX UCHAR_MAX
/*! static cast to \ref a_byte_t . */
#define a_byte_c(_, x) a_cast_s(A_BYTE_T _, x)
/*! type for unsigned character representation */
#define a_byte_t A_BYTE_T

#define A_C8_T char
#define A_C8_MIN CHAR_MIN
#define A_C8_MAX CHAR_MAX
/*! static cast to \ref a_c8_t . */
#define a_c8_c(_, x) a_cast_s(A_C8_T _, x)
/*! type for character representation */
#define a_c8_t A_C8_T

#if !defined A_I8_T
#define A_I8_T int8_t
#endif /* A_I8_T */
#if !defined A_I8_C && defined(INT8_C)
#define A_I8_C(X) INT8_C(X)
#endif /* A_I8_C */
#if !defined A_I8_MIN && defined(INT8_MIN)
#define A_I8_MIN INT8_MIN
#endif /* A_I8_MIN */
#if !defined A_I8_MAX && defined(INT8_MAX)
#define A_I8_MAX INT8_MAX
#endif /* A_I8_MAX */
/*! static cast to \ref a_i8_t . */
#define a_i8_c(_, x) a_cast_s(A_I8_T _, x)
/*! signed integer type with width of exactly 8 bits */
#define a_i8_t A_I8_T

#if !defined A_U8_T
#define A_U8_T uint8_t
#endif /* A_U8_T */
#if !defined A_U8_C && defined(UINT8_C)
#define A_U8_C(X) UINT8_C(X)
#endif /* A_U8_C */
#if !defined A_U8_MAX && defined(UINT8_MAX)
#define A_U8_MAX UINT8_MAX
#endif /* A_U8_MAX */
/*! static cast to \ref a_u8_t . */
#define a_u8_c(_, x) a_cast_s(A_U8_T _, x)
/*! unsigned integer type with width of exactly 8 bits */
#define a_u8_t A_U8_T

#if !defined A_I16_T
#define A_I16_T int16_t
#endif /* A_I16_T */
#if !defined A_I16_C && defined(INT16_C)
#define A_I16_C(X) INT16_C(X)
#endif /* A_I16_C */
#if !defined A_I16_MIN && defined(INT16_MIN)
#define A_I16_MIN INT16_MIN
#endif /* A_I16_MIN */
#if !defined A_I16_MAX && defined(INT16_MAX)
#define A_I16_MAX INT16_MAX
#endif /* A_I16_MAX */
/*! static cast to \ref a_i16_t . */
#define a_i16_c(_, x) a_cast_s(A_I16_T _, x)
/*! signed integer type with width of exactly 16 bits */
#define a_i16_t A_I16_T

#if !defined A_U16_T
#define A_U16_T uint16_t
#endif /* A_U16_T */
#if !defined A_U16_C && defined(UINT16_C)
#define A_U16_C(X) UINT16_C(X)
#endif /* A_U16_C */
#if !defined A_U16_MAX && defined(UINT16_MAX)
#define A_U16_MAX UINT16_MAX
#endif /* A_U16_MAX */
/*! static cast to \ref a_u16_t . */
#define a_u16_c(_, x) a_cast_s(A_U16_T _, x)
/*! unsigned integer type with width of exactly 16 bits */
#define a_u16_t A_U16_T

#if !defined A_I32_T
#define A_I32_T int32_t
#endif /* A_I32_T */
#if !defined A_I32_C && defined(INT32_C)
#define A_I32_C(X) INT32_C(X)
#endif /* A_I32_C */
#if !defined A_I32_MIN && defined(INT32_MIN)
#define A_I32_MIN INT32_MIN
#endif /* A_I32_MIN */
#if !defined A_I32_MAX && defined(INT32_MAX)
#define A_I32_MAX INT32_MAX
#endif /* A_I32_MAX */
/*! static cast to \ref a_i32_t . */
#define a_i32_c(_, x) a_cast_s(A_I32_T _, x)
/*! signed integer type with width of exactly 32 bits */
#define a_i32_t A_I32_T

#if !defined A_U32_T
#define A_U32_T uint32_t
#endif /* A_U32_T */
#if !defined A_U32_C && defined(UINT32_C)
#define A_U32_C(X) UINT32_C(X)
#endif /* A_U32_C */
#if !defined A_U32_MAX && defined(UINT32_MAX)
#define A_U32_MAX UINT32_MAX
#endif /* A_U32_MAX */
/*! static cast to \ref a_u32_t . */
#define a_u32_c(_, x) a_cast_s(A_U32_T _, x)
/*! unsigned integer type with width of exactly 32 bits */
#define a_u32_t A_U32_T

#if !defined A_I64_T
#define A_I64_T int64_t
#endif /* A_I64_T */
#if !defined A_I64_C && defined(INT64_C)
#define A_I64_C(X) INT64_C(X)
#endif /* A_I64_C */
#if !defined A_I64_MIN && defined(INT64_MIN)
#define A_I64_MIN INT64_MIN
#endif /* A_I64_MIN */
#if !defined A_I64_MAX && defined(INT64_MAX)
#define A_I64_MAX INT64_MAX
#endif /* A_I64_MAX */
/*! static cast to \ref a_i64_t . */
#define a_i64_c(_, x) a_cast_s(A_I64_T _, x)
/*! signed integer type with width of exactly 64 bits */
#define a_i64_t A_I64_T

#if !defined A_U64_T
#define A_U64_T uint64_t
#endif /* A_U64_T */
#if !defined A_U64_C && defined(UINT64_C)
#define A_U64_C(X) UINT64_C(X)
#endif /* A_U64_C */
#if !defined A_U64_MAX && defined(UINT64_MAX)
#define A_U64_MAX UINT64_MAX
#endif /* A_U64_MAX */
/*! static cast to \ref a_u64_t . */
#define a_u64_c(_, x) a_cast_s(A_U64_T _, x)
/*! unsigned integer type with width of exactly 64 bits */
#define a_u64_t A_U64_T

#if !defined A_IMAX_T
#define A_IMAX_T intmax_t
#endif /* A_IMAX_T */
#if !defined A_IMAX_C && defined(INTMAX_C)
#define A_IMAX_C(X) INTMAX_C(X)
#endif /* A_IMAX_C */
#if !defined A_IMAX_MIN && defined(INTMAX_MIN)
#define A_IMAX_MIN INTMAX_MIN
#endif /* A_IMAX_MIN */
#if !defined A_IMAX_MAX && defined(INTMAX_MAX)
#define A_IMAX_MAX INTMAX_MAX
#endif /* A_IMAX_MAX */
/*! static cast to \ref a_imax_t . */
#define a_imax_c(_, x) a_cast_s(A_IMAX_T _, x)
/*! maximum-width signed integer type */
#define a_imax_t A_IMAX_T

#if !defined A_UMAX_T
#define A_UMAX_T uintmax_t
#endif /* A_UMAX_T */
#if !defined A_UMAX_C && defined(UINTMAX_C)
#define A_UMAX_C(X) UINTMAX_C(X)
#endif /* A_UMAX_C */
#if !defined A_UMAX_MAX && defined(UINTMAX_MAX)
#define A_UMAX_MAX UINTMAX_MAX
#endif /* A_UMAX_MAX */
/*! static cast to \ref a_umax_t . */
#define a_umax_c(_, x) a_cast_s(A_UMAX_T _, x)
/*! maximum-width unsigned integer type */
#define a_umax_t A_UMAX_T

#if !defined A_IPTR_T
#define A_IPTR_T intptr_t
#endif /* A_IPTR_T */
#if !defined A_IPTR_MIN && defined(INTPTR_MIN)
#define A_IPTR_MIN INTPTR_MIN
#endif /* A_IPTR_MIN */
#if !defined A_IPTR_MAX && defined(INTPTR_MAX)
#define A_IPTR_MAX INTPTR_MAX
#endif /* A_IPTR_MAX */
/*! static cast to \ref a_iptr_t . */
#define a_iptr_c(_, x) a_cast_s(A_IPTR_T _, x)
/*! signed integer type capable of holding a pointer to void */
#define a_iptr_t A_IPTR_T

#if !defined A_UPTR_T
#define A_UPTR_T uintptr_t
#endif /* A_UPTR_T */
#if !defined A_UPTR_MAX && defined(UINTPTR_MAX)
#define A_UPTR_MAX UINTPTR_MAX
#endif /* A_UPTR_MAX */
/*! static cast to \ref a_uptr_t . */
#define a_uptr_c(_, x) a_cast_s(A_UPTR_T _, x)
/*! unsigned integer type capable of holding a pointer to void */
#define a_uptr_t A_UPTR_T

#if !defined A_DIFF_T
#define A_DIFF_T ptrdiff_t
#endif /* A_DIFF_T */
#if !defined A_DIFF_MIN && defined(PTRDIFF_MIN)
#define A_DIFF_MIN PTRDIFF_MIN
#endif /* A_DIFF_MIN */
#if !defined A_DIFF_MAX && defined(PTRDIFF_MAX)
#define A_DIFF_MAX PTRDIFF_MAX
#endif /* A_DIFF_MAX */
/*! static cast to \ref a_diff_t . */
#define a_diff_c(_, x) a_cast_s(A_DIFF_T _, x)
/*! signed integer type returned when subtracting two pointers */
#define a_diff_t A_DIFF_T

#if !defined A_SIZE_T
#define A_SIZE_T size_t
#endif /* A_SIZE_T */
#if !defined A_SIZE_MAX && defined(SIZE_MAX)
#define A_SIZE_MAX SIZE_MAX
#endif /* A_SIZE_MAX */
/*! static cast to \ref a_size_t . */
#define a_size_c(_, x) a_cast_s(A_SIZE_T _, x)
/*! unsigned integer type returned by the sizeof operator */
#define a_size_t A_SIZE_T

#define A_F16_NNAN A_U16_C(0xFE00)
#define A_F16_PNAN A_U16_C(0x7E00)
#define A_F16_NINF A_U16_C(0xFC00)
#define A_F16_PINF A_U16_C(0x7C00)

#define A_F32_T float
#define A_F32_C(X) A_CAST_2(X, F)
#define A_F32_F(F) A_CAST_2(F, f)
#define A_F32_F1(F, a) A_CAST_2(F, f)(a)
#define A_F32_F2(F, a, b) A_CAST_2(F, f)(a, b)
#define A_F32_F3(F, a, b, c) A_CAST_2(F, f)(a, b, c)
#if defined(A_HAVE_VARIADIC_MACROS)
#define A_F32_FN(F, ...) A_CAST_2(F, f)(__VA_ARGS__)
#endif /* A_HAVE_VARIADIC_MACROS */
#define A_F32_DIG FLT_DIG
#define A_F32_EPSILON FLT_EPSILON
#define A_F32_MANT_DIG FLT_MANT_DIG
#define A_F32_MAX FLT_MAX
#define A_F32_MAX_10_EXP FLT_MAX_10_EXP
#define A_F32_MAX_EXP FLT_MAX_EXP
#define A_F32_MIN FLT_MIN
#define A_F32_MIN_10_EXP FLT_MIN_10_EXP
#define A_F32_MIN_EXP FLT_MIN_EXP
#define A_F32_INF a_f32_c(, A_F64_INF)
#define A_F32_NAN (A_F32_C(0.0) * A_F32_INF)
#define A_F32_NNAN A_U32_C(0xFFC00000)
#define A_F32_PNAN A_U32_C(0x7FC00000)
#define A_F32_NINF A_U32_C(0xFF800000)
#define A_F32_PINF A_U32_C(0x7F800000)
/*! format constants for the fprintf family of functions */
#define A_F32_PRI(F, C) "%" F C
/*! format constants for the fscanf family of functions */
#define A_F32_SCN(F, C) "%" F C
/*! static cast to \ref a_f32_t . */
#define a_f32_c(_, x) a_cast_s(A_F32_T _, x)
/*! single precision floating point type. Matches IEEE-754 binary32 format if supported. */
#define a_f32_t A_F32_T

#define A_F64_T double
#define A_F64_C(X) X
#define A_F64_F(F) F
#define A_F64_F1(F, a) F(a)
#define A_F64_F2(F, a, b) F(a, b)
#define A_F64_F3(F, a, b, c) F(a, b, c)
#if defined(A_HAVE_VARIADIC_MACROS)
#define A_F64_FN(F, ...) F(__VA_ARGS__)
#endif /* A_HAVE_VARIADIC_MACROS */
#define A_F64_DIG DBL_DIG
#define A_F64_EPSILON DBL_EPSILON
#define A_F64_MANT_DIG DBL_MANT_DIG
#define A_F64_MAX DBL_MAX
#define A_F64_MAX_10_EXP DBL_MAX_10_EXP
#define A_F64_MAX_EXP DBL_MAX_EXP
#define A_F64_MIN DBL_MIN
#define A_F64_MIN_10_EXP DBL_MIN_10_EXP
#define A_F64_MIN_EXP DBL_MIN_EXP
#define A_F64_INF (DBL_MAX * DBL_MAX)
#define A_F64_NAN (A_F64_C(0.0) * A_F64_INF)
#define A_F64_NNAN A_U64_C(0xFFF8000000000000)
#define A_F64_PNAN A_U64_C(0x7FF8000000000000)
#define A_F64_NINF A_U64_C(0xFFF0000000000000)
#define A_F64_PINF A_U64_C(0x7FF0000000000000)
/*! format constants for the fprintf family of functions */
#define A_F64_PRI(F, C) "%" F "l" C
/*! format constants for the fscanf family of functions */
#define A_F64_SCN(F, C) "%" F "l" C
/*! static cast to \ref a_f64_t . */
#define a_f64_c(_, x) a_cast_s(A_F64_T _, x)
/*! double precision floating point type. Matches IEEE-754 binary64 format if supported. */
#define a_f64_t A_F64_T

/*!
 @addtogroup A_FLOAT floating-point number
 @{
*/

/*! floating-point number bytes */
#if !defined A_FLOAT_TYPE
#if !defined A_SIZE_FLOAT
#define A_FLOAT_TYPE A_FLOAT_DOUBLE
#else /* !A_SIZE_FLOAT */
#define A_FLOAT_TYPE A_SIZE_FLOAT
#endif /* A_SIZE_FLOAT */
#endif /* A_FLOAT_TYPE */
#define A_FLOAT_SINGLE 0x04
#define A_FLOAT_DOUBLE 0x08
#define A_FLOAT_EXTEND 0x10
#if defined(A_FLOAT_T)
#elif A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE

/*! floating-point number stored using `float` */
#define A_FLOAT_T float
#define A_FLOAT_DIG FLT_DIG
#define A_FLOAT_EPSILON FLT_EPSILON
#define A_FLOAT_MANT_DIG FLT_MANT_DIG
#define A_FLOAT_MAX FLT_MAX
#define A_FLOAT_MAX_10_EXP FLT_MAX_10_EXP
#define A_FLOAT_MAX_EXP FLT_MAX_EXP
#define A_FLOAT_MIN FLT_MIN
#define A_FLOAT_MIN_10_EXP FLT_MIN_10_EXP
#define A_FLOAT_MIN_EXP FLT_MIN_EXP

/*!
 expands to a floating-point constant expression having the value specified by its argument and the type \ref a_float_t
*/
#define A_FLOAT_C(X) A_CAST_2(X, F)
/*!
 expands to a floating-point function expression having the value specified by its argument and the type \ref a_float_t
*/
#define A_FLOAT_F(F) A_CAST_2(F, f)
#define A_FLOAT_F1(F, a) A_CAST_2(F, f)(a)
#define A_FLOAT_F2(F, a, b) A_CAST_2(F, f)(a, b)
#define A_FLOAT_F3(F, a, b, c) A_CAST_2(F, f)(a, b, c)
#if defined(A_HAVE_VARIADIC_MACROS)
#define A_FLOAT_FN(F, ...) A_CAST_2(F, f)(__VA_ARGS__)
#endif /* A_HAVE_VARIADIC_MACROS */

/*! format constants for the fprintf family of functions */
#define A_FLOAT_PRI(F, C) "%" F C
/*! format constants for the fscanf family of functions */
#define A_FLOAT_SCN(F, C) "%" F C

#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE

/*! floating-point number stored using `double` */
#define A_FLOAT_T double
#define A_FLOAT_DIG DBL_DIG
#define A_FLOAT_EPSILON DBL_EPSILON
#define A_FLOAT_MANT_DIG DBL_MANT_DIG
#define A_FLOAT_MAX DBL_MAX
#define A_FLOAT_MAX_10_EXP DBL_MAX_10_EXP
#define A_FLOAT_MAX_EXP DBL_MAX_EXP
#define A_FLOAT_MIN DBL_MIN
#define A_FLOAT_MIN_10_EXP DBL_MIN_10_EXP
#define A_FLOAT_MIN_EXP DBL_MIN_EXP

/*!
 expands to a floating-point constant expression having the value specified by its argument and the type \ref a_float_t
*/
#define A_FLOAT_C(X) X
/*!
 expands to a floating-point function expression having the value specified by its argument and the type \ref a_float_t
*/
#define A_FLOAT_F(F) F
#define A_FLOAT_F1(F, a) F(a)
#define A_FLOAT_F2(F, a, b) F(a, b)
#define A_FLOAT_F3(F, a, b, c) F(a, b, c)
#if defined(A_HAVE_VARIADIC_MACROS)
#define A_FLOAT_FN(F, ...) F(__VA_ARGS__)
#endif /* A_HAVE_VARIADIC_MACROS */

/*! format constants for the fprintf family of functions */
#define A_FLOAT_PRI(F, C) "%" F C
/*! format constants for the fscanf family of functions */
#define A_FLOAT_SCN(F, C) "%" F "l" C

#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND

/*! floating-point number stored using `long double` */
#define A_FLOAT_T long double
#define A_FLOAT_DIG LDBL_DIG
#define A_FLOAT_EPSILON LDBL_EPSILON
#define A_FLOAT_MANT_DIG LDBL_MANT_DIG
#define A_FLOAT_MAX LDBL_MAX
#define A_FLOAT_MAX_10_EXP LDBL_MAX_10_EXP
#define A_FLOAT_MAX_EXP LDBL_MAX_EXP
#define A_FLOAT_MIN LDBL_MIN
#define A_FLOAT_MIN_10_EXP LDBL_MIN_10_EXP
#define A_FLOAT_MIN_EXP LDBL_MIN_EXP

/*!
 expands to a floating-point constant expression having the value specified by its argument and the type \ref a_float_t
*/
#define A_FLOAT_C(X) A_CAST_2(X, L)
/*!
 expands to a floating-point function expression having the value specified by its argument and the type \ref a_float_t
*/
#define A_FLOAT_F(F) A_CAST_2(F, l)
#define A_FLOAT_F1(F, a) A_CAST_2(F, l)(a)
#define A_FLOAT_F2(F, a, b) A_CAST_2(F, l)(a, b)
#define A_FLOAT_F3(F, a, b, c) A_CAST_2(F, l)(a, b, c)
#if defined(A_HAVE_VARIADIC_MACROS)
#define A_FLOAT_FN(F, ...) A_CAST_2(F, l)(__VA_ARGS__)
#endif /* A_HAVE_VARIADIC_MACROS */

/*! format constants for the fprintf family of functions */
#define A_FLOAT_PRI(F, C) "%" F "L" C
/*! format constants for the fscanf family of functions */
#define A_FLOAT_SCN(F, C) "%" F "L" C

#else /* !A_FLOAT_TYPE */
#error unknown precision
#endif /* A_FLOAT_TYPE */

#define A_FLOAT_INF a_cast_s(A_FLOAT_T, A_F64_INF)
#define A_FLOAT_NAN (A_FLOAT_C(0.0) * A_FLOAT_INF)

/*! static cast to \ref a_float_t . */
#define a_float_c(_, x) a_cast_s(A_FLOAT_T _, x)
/*! compiler built-in floating-point number type */
#define a_float_t A_FLOAT_T

typedef union a_float_u
{
    a_float_t f; //!< as a floating-point number
    a_float_t *p; //!< as a floating-point array
} a_float_u;

/*! @} A_FLOAT */

typedef union a_cast_u
{
    a_c8_t c;
    a_int_t i;
    a_uint_t u;
    a_shrt_t ih;
    a_ushrt_t uh;
    a_long_t il;
    a_ulong_t ul;
#if defined(A_HAVE_LONG_LONG_TYPE)
    a_llong_t ill;
    a_ullong_t ull;
#endif /* A_HAVE_LONG_LONG_TYPE */
    a_i8_t i8;
    a_u8_t u8;
    a_i16_t i16;
    a_u16_t u16;
    a_i32_t i32;
    a_u32_t u32;
    a_i64_t i64;
    a_u64_t u64;
    a_f32_t f32;
    a_f64_t f64;
    a_imax_t imax;
    a_umax_t umax;
    a_iptr_t iptr;
    a_uptr_t uptr;
    a_diff_t diff;
    a_size_t size;
    void const *PTR;
    void *ptr;
    char const *STR;
    char *str;
#if defined(A_FLOAT_TYPE) && (A_FLOAT_TYPE + 0 < A_FLOAT_EXTEND)
    a_float_t f;
#endif /* A_FLOAT_TYPE */
} a_cast_u;

/*!
 @brief square of x, \f$ x^2 \f$
*/
#define A_SQ(x) ((x) * (x))

/*!
 @brief minimum value between x and y
*/
#define A_MIN(x, y) (((x) < (y)) ? (x) : (y))

/*!
 @brief maximum value between x and y
*/
#define A_MAX(x, y) (((x) > (y)) ? (x) : (y))

/*!
 @brief absolute value of x, \f$ |x| \f$
*/
#define A_ABS(x) ((x) < 0 ? -(x) : (x))

/*!
 @brief signum function, \f$ \texttt{sgn}{x}=\begin{cases}+1&x>0\\0&0\\-1&x<0\end{cases} \f$
*/
#define A_SGN(x) ((0 < (x)) - ((x) < 0))

/*!
 @brief saturation value of x, \f$ \texttt{sat}(x,min,max)=\begin{cases}min&min>x\\max&x>max\\x&else\end{cases} \f$
*/
#define A_SAT(x, min, max) ((min) < (x) ? (x) < (max) ? (x) : (max) : (min))

/*!
 @brief number of elements in a visible array
 @param array must be a visible array
*/
#define a_array_n(array) (sizeof(array) / sizeof(*(array)))

/*!
 @brief offset of a structure member
 @param type structure type
 @param member member variable
*/
#if defined(offsetof)
#define a_offsetof(type, member) offsetof(type, member)
#else /* !offsetof */
#define a_offsetof(type, member) a_cast_r(a_size_t, &a_cast_r(type *, 0)->member)
#endif /* offsetof */

/*!
 @brief container of a structure member
 @param ptr pointer to a member variable
 @param type structure type
 @param member member variable
*/
#define a_container_of(ptr, type, member) a_cast_r(type *, a_cast_r(a_uptr_t, ptr) - a_offsetof(type, member))

/*!
 @brief round down size "n" to be a multiple of "a"
*/
#define a_size_down(a, n) (a_cast_s(a_size_t, n) & ~a_cast_s(a_size_t, (a)-1))

/*!
 @brief round up size "n" to be a multiple of "a"
*/
#define a_size_up(a, n) ((a_cast_s(a_size_t, n) + (a)-1) & ~a_cast_s(a_size_t, (a)-1))

/*!
 @brief round pointer "p" down to the closest "a"-aligned address <= "p"
*/
#define a_align_down(a, p) a_cast_r(void *, a_cast_r(a_uptr_t, p) & ~a_cast_s(a_uptr_t, (a)-1))

/*!
 @brief round pointer "p" up to the closest "a"-aligned address >= "p"
*/
#define a_align_up(a, p) a_cast_r(void *, (a_cast_r(a_uptr_t, p) + (a)-1) & ~a_cast_s(a_uptr_t, (a)-1))

/*!
 @brief iterate from 0 to n and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum(I, i, n) for (I i = 0; i < (n); ++i)

/*!
 @brief iterate from n to 0 and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum_reverse(I, i, n) for (I i = (n); i-- > 0;)

/*!
 @brief iterate over an array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach(T, it, ptr, num)                      \
    for (T *it = a_cast_s(T *, ptr),                    \
           *it##_ = a_likely(it) ? it + (num) : A_NULL; \
         it < it##_; ++it)

/*!
 @brief iterate over an array in reverse
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach_reverse(T, it, ptr, num)                           \
    for (T *it##_ = a_likely(ptr) ? a_cast_s(T *, ptr) - 1 : A_NULL, \
           *it = a_likely(ptr) ? it##_ + (num) : A_NULL;             \
         it > it##_; --it)

/*!
 @brief iterate over an array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate(T, it, ptr, end) \
    for (T *it = a_cast_s(T *, ptr), *it##_ = a_cast_s(T *, end); it < it##_; ++it)

/*!
 @brief iterate over an array in reverse
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate_reverse(T, it, ptr, end)                           \
    for (T *it##_ = a_likely(ptr) ? a_cast_s(T *, ptr) - 1 : A_NULL, \
           *it = a_likely(end) ? a_cast_s(T *, end) - 1 : A_NULL;    \
         it > it##_; --it)

/*!
 @brief enumeration for return values
*/
enum
{
    A_SUCCESS /*!< return success */,
    A_FAILURE /*!< return failure */,
    A_INVALID /*!< return invalid */
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_A_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_A_C */

#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_f32_t a_f32_from(a_u32_t x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_f32_t a_f32_from(a_u32_t const x)
{
    union
    {
        a_u32_t u;
        a_f32_t x;
    } u;
    u.u = x;
    return u.x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_u32_t a_f32_into(a_f32_t x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_u32_t a_f32_into(a_f32_t const x)
{
    union
    {
        a_f32_t x;
        a_u32_t u;
    } u;
    u.x = x;
    return u.u;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_f64_t a_f64_from(a_u64_t x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_f64_t a_f64_from(a_u64_t const x)
{
    union
    {
        a_u64_t u;
        a_f64_t x;
    } u;
    u.u = x;
    return u.x;
}
#endif /* A_HAVE_INLINE */
#if !defined A_HAVE_INLINE || defined(LIBA_A_C)
A_EXTERN a_u64_t a_f64_into(a_f64_t x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_A_C)
A_INTERN a_u64_t a_f64_into(a_f64_t const x)
{
    union
    {
        a_f64_t x;
        a_u64_t u;
    } u;
    u.x = x;
    return u.u;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief copy one buffer to another
 @param[in] dst pointer to the object to copy to
 @param[in] src pointer to the object to copy from
 @param[in] siz number of bytes to copy
 @return a copy of dest
*/
A_EXTERN void *a_copy(void *A_RESTRICT dst, void const *A_RESTRICT src, a_size_t siz);

/*!
 @brief move one buffer to another
 @param[in] dst pointer to the object to copy to
 @param[in] src pointer to the object to copy from
 @param[in] siz number of bytes to copy
 @return a copy of dest
*/
A_EXTERN void *a_move(void *dst, void const *src, a_size_t siz);

/*!
 @brief fill a buffer with a character
 @param[in] ptr pointer to the object to fill
 @param[in] siz number of bytes to fill
 @param[in] val fill byte
 @return a copy of dest
*/
A_EXTERN void *a_fill(void *ptr, a_size_t siz, int val);

/*!
 @brief fill a buffer with zero
 @param[in] ptr pointer to the object to fill
 @param[in] siz number of bytes to fill
 @return a copy of dest
*/
A_EXTERN void *a_zero(void *ptr, a_size_t siz);

/*!
 @brief swap two different memory blocks of the same size
 @param[in] siz the size of memory block being swapped
 @param[in,out] lhs points to memory block on the left
 @param[in,out] rhs points to memory block on the right
*/
A_EXTERN void a_swap(void *lhs, void *rhs, a_size_t siz);

/*!
 @brief Brian Kernighan and Dennis Ritchie
 @param[in] str string to be processed
 @param[in] val initial value
 @return hash value
*/
A_EXTERN a_umax_t a_hash_bkdr(void const *str, a_umax_t val);

/*!
 @brief Brian Kernighan and Dennis Ritchie
 @param[in] ptr points to string to be processed
 @param[in] siz length of string to be processed
 @param[in] val initial value
 @return hash value
*/
A_EXTERN a_umax_t a_hash_bkdrn(void const *ptr, a_size_t siz, a_umax_t val);

/*!
 @brief roll back the elements of a float array and save the cache array
 @param[in] array_p points to a float array
 @param[in] array_n number of a float array
 @param[in] cache_p points to a cache array
 @param[in] cache_n number of a cache array
*/
A_EXTERN void a_float_save(a_float_t *array_p, a_size_t array_n,
                           a_float_t const *cache_p, a_size_t cache_n);

/*!
 @brief roll back the elements of a float array circularly, array>>shift
 @param[in] array_p points to a float array
 @param[in] array_n number of a float array
 @param[in] shift_p points to a shift array
 @param[in] shift_n number of a shift array
*/
A_EXTERN void a_float_roll(a_float_t *array_p, a_size_t array_n,
                           a_float_t *shift_p, a_size_t shift_n);

#if defined(LIBA_A_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_A_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A */

#endif /* a/a.h */
