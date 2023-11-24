/*!
 @file version.h
 @brief algorithm library version
*/

#ifndef LIBA_VERSION_H
#define LIBA_VERSION_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_VERSION algorithm library version
 @{
*/

/*! algorithm library version major */
#ifndef A_VERSION_MAJOR
#define A_VERSION_MAJOR 0
#endif /* A_VERSION_MAJOR */
#undef major

/*! algorithm library version minor */
#ifndef A_VERSION_MINOR
#define A_VERSION_MINOR 0
#endif /* A_VERSION_MINOR */
#undef minor

/*! algorithm library version patch */
#ifndef A_VERSION_PATCH
#define A_VERSION_PATCH 0
#endif /* A_VERSION_PATCH */
#undef patch

/*! algorithm library version tweak */
#ifndef A_VERSION_TWEAK
#define A_VERSION_TWEAK 0
#endif /* A_VERSION_TWEAK */

#define A_VERSION_TOSTR(X) A_CAST_1(X)
/*! algorithm library version string */
#ifndef A_VERSION
#define A_VERSION A_VERSION_TOSTR(A_VERSION_MAJOR) "." A_VERSION_TOSTR(A_VERSION_MINOR) "." A_VERSION_TOSTR(A_VERSION_PATCH)
#endif /* A_VERSION */

#if defined(__cplusplus)
#define A_VERSION_C(maj, min, pat) a::version(maj, min, pat)
#else /* !__cplusplus */
// clang-format off
#define A_VERSION_C(maj, min, pat) {maj, min, pat}
// clang-format on
#endif /* __cplusplus */

#if defined(__cplusplus)
namespace a
{
/*! algorithm library version string */
A_EXTERN char const *const VERSION;
#endif /* __cplusplus */

/*!
 @brief instance structure for version
*/
#if defined(__cplusplus)
struct version
{
    A_PUBLIC bool operator<(version const &ver) const;
    A_PUBLIC bool operator>(version const &ver) const;
    A_PUBLIC bool operator<=(version const &ver) const;
    A_PUBLIC bool operator>=(version const &ver) const;
    A_PUBLIC bool operator==(version const &ver) const;
    A_PUBLIC bool operator!=(version const &ver) const;
    A_PUBLIC version(unsigned int const maj = 0,
                     unsigned int const min = 0,
                     unsigned int const pat = 0)
        : major(maj)
        , minor(min)
        , patch(pat)
    {
    }
    /*! algorithm library version major */
    A_PUBLIC static unsigned int const MAJOR;
    /*! algorithm library version minor */
    A_PUBLIC static unsigned int const MINOR;
    /*! algorithm library version patch */
    A_PUBLIC static unsigned int const PATCH;
    /*! algorithm library version tweak */
    A_PUBLIC static a_u32_t const TWEAK;
    A_PUBLIC version(char const *ver);
#else /* !__cplusplus */
typedef struct a_version_s
{
#endif /* __cplusplus */
    unsigned int major; //!< major number
    unsigned int minor; //!< minor number
    unsigned int patch; //!< patch number
#if defined(__cplusplus)
};
#else /* !__cplusplus */
} a_version_s;
#endif /* __cplusplus */

#if defined(__cplusplus)
} /* namespace a */
typedef a::version a_version_s;
extern "C" {
#endif /* __cplusplus */

/*! algorithm library version string */
A_EXTERN char const *const a_version;
/*! algorithm library version major */
A_EXTERN unsigned int const a_version_major;
/*! algorithm library version minor */
A_EXTERN unsigned int const a_version_minor;
/*! algorithm library version patch */
A_EXTERN unsigned int const a_version_patch;
/*! algorithm library version tweak */
A_EXTERN a_u32_t const a_version_tweak;

/*!
 @brief algorithm library version check
 @param[in] major required major number
 @param[in] minor required minor number
 @param[in] patch required patch number
 @return result of comparison
  @retval <0 library version is higher than required version
  @retval >0 library version is lower than required version
  @retval 0 library version is equal to required version
*/
A_EXTERN int a_version_check(unsigned int major, unsigned int minor, unsigned int patch);
#define a_version_check() a_version_check(A_VERSION_MAJOR, A_VERSION_MINOR, A_VERSION_PATCH)

#if defined(LIBA_VERSION_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_VERSION_C */

/*!
 @brief version lhs is less than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_lt(a_version_s const *lhs, a_version_s const *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_lt(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major < rhs->major)
    {
        return A_TRUE;
    }
    if (lhs->minor < rhs->minor)
    {
        return A_TRUE;
    }
    if (lhs->patch < rhs->patch)
    {
        return A_TRUE;
    }
    return A_FALSE;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs is greater than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_gt(a_version_s const *lhs, a_version_s const *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_gt(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major > rhs->major)
    {
        return A_TRUE;
    }
    if (lhs->minor > rhs->minor)
    {
        return A_TRUE;
    }
    if (lhs->patch > rhs->patch)
    {
        return A_TRUE;
    }
    return A_FALSE;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs is less than or equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_le(a_version_s const *lhs, a_version_s const *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_le(a_version_s const *const lhs, a_version_s const *const rhs)
{
    return !a_version_lt(rhs, lhs);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs is greater than or equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_ge(a_version_s const *lhs, a_version_s const *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_ge(a_version_s const *const lhs, a_version_s const *const rhs)
{
    return !a_version_gt(rhs, lhs);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs is equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_eq(a_version_s const *lhs, a_version_s const *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_eq(a_version_s const *const lhs, a_version_s const *const rhs)
{
    return (lhs->major == rhs->major) && (lhs->minor == rhs->minor) && (lhs->patch == rhs->patch);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs is not equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_ne(a_version_s const *lhs, a_version_s const *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_ne(a_version_s const *const lhs, a_version_s const *const rhs)
{
    return (lhs->major != rhs->major) || (lhs->minor != rhs->minor) || (lhs->patch != rhs->patch);
}
#endif /* A_HAVE_INLINE */

#if defined(LIBA_VERSION_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_VERSION_C */

/*!
 @brief compare the version lhs with the version rhs
 @param[in] lhs version structure to be compared
 @param[in] rhs version structure to be compared
 @return relationship between the versions
  @retval <0 version lhs < version rhs
  @retval >0 version lhs > version rhs
  @retval 0 version lhs == version rhs
*/
A_EXTERN int a_version_cmp(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief algorithm library version parse
 @param[in,out] ctx points to an instance structure for version
 @param[in] ver version string to be parsed
 @return number of characters parsed
*/
A_EXTERN unsigned int a_version_parse(a_version_s *ctx, char const *ver);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_VERSION */

#endif /* a/version.h */
