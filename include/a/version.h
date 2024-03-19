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
#define A_VERSION_MINOR 1
#endif /* A_VERSION_MINOR */
#undef minor

/*! algorithm library version patch */
#ifndef A_VERSION_PATCH
#define A_VERSION_PATCH 8
#endif /* A_VERSION_PATCH */
#undef patch

/*! algorithm library version tweak */
#ifndef A_VERSION_TWEAK
#define A_VERSION_TWEAK 20240320
#endif /* A_VERSION_TWEAK */

#define A_VERSION_TOSTR(X) A_CAST_1(X)
/*! algorithm library version string */
#ifndef A_VERSION
#define A_VERSION A_VERSION_TOSTR(A_VERSION_MAJOR) "." A_VERSION_TOSTR(A_VERSION_MINOR) "." A_VERSION_TOSTR(A_VERSION_PATCH)
#endif /* A_VERSION */

typedef struct a_version a_version;
// clang-format off
#if defined(__cplusplus)
#define A_VERSION_C(major, minor, third) {major, minor, third, 0, {'.', 0, 0, 0}}
#define A_VERSION_EX(major, minor, third, extra) {major, minor, third, extra, {'.', 0, 0, 0}}
#else /* !__cplusplus */
#define A_VERSION_C(major, minor, third) (a_version){major, minor, third, 0, {'.', 0, 0, 0}}
#define A_VERSION_EX(major, minor, third, extra) (a_version){major, minor, third, extra, {'.', 0, 0, 0}}
#endif /* __cplusplus */
// clang-format on

#if defined(__cplusplus)
namespace a
{
typedef a_version version;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */

/*! algorithm library version major */
A_EXTERN unsigned int const a_version_major;
/*! algorithm library version minor */
A_EXTERN unsigned int const a_version_minor;
/*! algorithm library version patch */
A_EXTERN unsigned int const a_version_patch;
/*! algorithm library version tweak */
A_EXTERN a_u32 const a_version_tweak;

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
 @brief convert version to string
 @param[in] ctx points to an instance structure for version
 @param[in] pdata points to string buffer
 @param[in] nbyte length of string buffer
 @return number of used characters
*/
A_EXTERN unsigned int a_version_tostr(a_version const *ctx, void *pdata, a_size nbyte);

/*!
 @brief parse version string to version
 @param[in,out] ctx points to an instance structure for version
 @param[in] ver version string to be parsed
 @return number of parsed characters
*/
A_EXTERN unsigned int a_version_parse(a_version *ctx, char const *ver);

/*!
 @brief compare the version lhs with the version rhs
 @param[in] lhs version structure to be compared
 @param[in] rhs version structure to be compared
 @return relationship between the versions
  @retval <0 version lhs < version rhs
  @retval >0 version lhs > version rhs
  @retval 0 version lhs == version rhs
*/
A_EXTERN int a_version_cmp(a_version const *lhs, a_version const *rhs);

/*!
 @brief version lhs is less than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool a_version_lt(a_version const *lhs, a_version const *rhs);

/*!
 @brief version lhs is greater than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool a_version_gt(a_version const *lhs, a_version const *rhs);

/*!
 @brief version lhs is less than or equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool a_version_le(a_version const *lhs, a_version const *rhs);

/*!
 @brief version lhs is greater than or equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool a_version_ge(a_version const *lhs, a_version const *rhs);

/*!
 @brief version lhs is equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool a_version_eq(a_version const *lhs, a_version const *rhs);

/*!
 @brief version lhs is not equal to version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
A_EXTERN a_bool a_version_ne(a_version const *lhs, a_version const *rhs);

/*!
 @brief set alphabet for version
 @param[in,out] ctx points to an instance structure for version
 @param[in] alpha new alphabet
*/
A_EXTERN void a_version_set_alpha(a_version *ctx, char const *alpha);

/*!
 @brief get alphabet for version
 @param[in] ctx points to an instance structure for version
 @param[out] alpha string buffer, >sizeof(ctx->alpha)
*/
A_EXTERN void a_version_alpha(a_version const *ctx, char alpha[5]);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for version
*/
struct a_version
{
    unsigned int major; //!< major number
    unsigned int minor; //!< minor number
    unsigned int third; //!< third number
    unsigned int extra; //!< extra number
    char alpha[4]; //!< alphabet
#if defined(__cplusplus)
    A_INLINE void set_alpha(char const *str)
    {
        a_version_set_alpha(this, str);
    }
    A_INLINE void get_alpha(char str[5]) const
    {
        a_version_alpha(this, str);
    }
    A_INLINE unsigned int parse(char const *ver)
    {
        return a_version_parse(this, ver);
    }
    A_INLINE unsigned int tostr(void *p, a_size n) const
    {
        return a_version_tostr(this, p, n);
    }
    A_INLINE bool operator<(a_version const &ver) const
    {
        return a_version_lt(this, &ver);
    }
    A_INLINE bool operator>(a_version const &ver) const
    {
        return a_version_gt(this, &ver);
    }
    A_INLINE bool operator<=(a_version const &ver) const
    {
        return a_version_le(this, &ver);
    }
    A_INLINE bool operator>=(a_version const &ver) const
    {
        return a_version_ge(this, &ver);
    }
    A_INLINE bool operator==(a_version const &ver) const
    {
        return a_version_eq(this, &ver);
    }
    A_INLINE bool operator!=(a_version const &ver) const
    {
        return a_version_ne(this, &ver);
    }
    A_INLINE int cmp(a_version const &ver) const
    {
        return a_version_cmp(this, &ver);
    }
#endif /* __cplusplus */
};

/*! @} A_VERSION */

#endif /* a/version.h */
