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
namespace a
{
struct version;
}
typedef struct a::version a_version_s;
#define A_VERSION_C(maj, min, pat) a::version(maj, min, pat)
#define A_VERSION_EX(maj, min, pat, ext) a::version(maj, min, pat, ext)
#else /* !__cplusplus */
typedef struct a_version_s a_version_s;
// clang-format off
#define A_VERSION_C(maj, min, pat) {maj, min, pat, 0}
#define A_VERSION_EX(maj, min, pat, ext) {maj, min, pat, ext}
// clang-format on
#endif /* __cplusplus */

#if defined(__cplusplus)
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
 @brief version lhs is less than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool_t a_version_lt(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief version lhs is greater than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool_t a_version_gt(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief version lhs is less than or equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool_t a_version_le(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief version lhs is greater than or equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool_t a_version_ge(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief version lhs is equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool_t a_version_eq(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief version lhs is not equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool_t a_version_ne(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief algorithm library version parse
 @param[in,out] ctx points to an instance structure for version
 @param[in] ver version string to be parsed
 @return number of parsed characters
*/
A_EXTERN unsigned int a_version_parse(a_version_s *ctx, char const *ver);

#if defined(__cplusplus)
} /* extern "C" */
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
#if !defined __cplusplus
struct a_version_s
#else /* !__cplusplus */
struct version
#endif /* __cplusplus */
{
    unsigned int major; //!< major number
    unsigned int minor; //!< minor number
    unsigned int patch; //!< patch number
    unsigned int extra; //!< extra number
#if defined(__cplusplus)
    /*! algorithm library version major */
    A_PUBLIC static unsigned int const MAJOR;
    /*! algorithm library version minor */
    A_PUBLIC static unsigned int const MINOR;
    /*! algorithm library version patch */
    A_PUBLIC static unsigned int const PATCH;
    /*! algorithm library version tweak */
    A_PUBLIC static a_u32_t const TWEAK;
    A_INLINE bool operator<(version const &ver) const
    {
        return a_version_lt(this, &ver);
    }
    A_INLINE bool operator>(version const &ver) const
    {
        return a_version_gt(this, &ver);
    }
    A_INLINE bool operator<=(version const &ver) const
    {
        return a_version_le(this, &ver);
    }
    A_INLINE bool operator>=(version const &ver) const
    {
        return a_version_ge(this, &ver);
    }
    A_INLINE bool operator==(version const &ver) const
    {
        return a_version_eq(this, &ver);
    }
    A_INLINE bool operator!=(version const &ver) const
    {
        return a_version_ne(this, &ver);
    }
    A_INLINE version(unsigned int const maj = 0,
                     unsigned int const min = 0,
                     unsigned int const pat = 0,
                     unsigned int const ext = 0)
        : major(maj)
        , minor(min)
        , patch(pat)
        , extra(ext)
    {
    }
    A_INLINE version(char const *ver)
        : major(0)
        , minor(0)
        , patch(0)
        , extra(0)
    {
        a_version_parse(this, ver);
    }
#endif /* __cplusplus */
};

#if defined(__cplusplus)
} /* namespace a */
#endif /* __cplusplus */

/*! @} A_VERSION */

#endif /* a/version.h */
