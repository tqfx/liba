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

/*! algorithm library version string */
#ifndef A_VERSION
#define A_VERSION "0.0.0"
#endif /* A_VERSION */

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
#define A_VERSION_TWEAK A_U64_C(0)
#endif /* A_VERSION_TWEAK */

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
cstr_t const VERSION = A_VERSION;
/*! algorithm library version major */
uint_t const VERSION_MAJOR = A_VERSION_MAJOR;
/*! algorithm library version minor */
uint_t const VERSION_MINOR = A_VERSION_MINOR;
/*! algorithm library version patch */
uint_t const VERSION_PATCH = A_VERSION_PATCH;
/*! algorithm library version tweak */
u64_t const VERSION_TWEAK = A_VERSION_TWEAK;
#endif /* __cplusplus */

/*!
 @brief instance structure for version
*/
#if defined(__cplusplus)
struct version
{
    A_PUBLIC a_bool_t operator<(version const &ver) const;
    A_PUBLIC a_bool_t operator>(version const &ver) const;
    A_PUBLIC a_bool_t operator<=(version const &ver) const;
    A_PUBLIC a_bool_t operator>=(version const &ver) const;
    A_PUBLIC a_bool_t operator==(version const &ver) const;
    A_PUBLIC a_bool_t operator!=(version const &ver) const;
    A_PUBLIC version(a_uint_t const maj = 0,
                     a_uint_t const min = 0,
                     a_uint_t const pat = 0)
        : major(maj)
        , minor(min)
        , patch(pat)
    {
    }
#else /* !__cplusplus */
typedef struct a_version_s
{
#endif /* __cplusplus */
    a_uint_t major; //!< major number
    a_uint_t minor; //!< minor number
    a_uint_t patch; //!< patch number
#if defined(__cplusplus)
};
#else /* !__cplusplus */
} a_version_s;
#endif /* __cplusplus */

#if defined(__cplusplus)
/*!
 @brief algorithm library version major
*/
A_EXTERN uint_t version_major(void);
/*!
 @brief algorithm library version minor
*/
A_EXTERN uint_t version_minor(void);
/*!
 @brief algorithm library version patch
*/
A_EXTERN uint_t version_patch(void);
} /* namespace a */
typedef a::version a_version_s;
extern "C" {
#endif /* __cplusplus */

/*!
 @brief algorithm library version string
*/
A_EXTERN a_cstr_t a_version(void);

/*!
 @brief algorithm library version major
*/
A_EXTERN a_uint_t a_version_major(void);

/*!
 @brief algorithm library version minor
*/
A_EXTERN a_uint_t a_version_minor(void);

/*!
 @brief algorithm library version patch
*/
A_EXTERN a_uint_t a_version_patch(void);

/*!
 @brief compare the version lhs with the version rhs
 @param[in] lhs version structure to be compared
 @param[in] rhs version structure to be compared
 @return relationship between the versions
  @retval <0 version lhs < version rhs
  @retval >0 version lhs > version rhs
  @retval 0 version lhs == version rhs
*/
A_EXTERN a_int_t a_version_cmp(a_version_s const *lhs, a_version_s const *rhs);

/*!
 @brief algorithm library version check
*/
A_EXTERN a_int_t a_version_check(a_uint_t major, a_uint_t minor, a_uint_t patch);
#define a_version_check() a_version_check(A_VERSION_MAJOR, A_VERSION_MINOR, A_VERSION_PATCH)

#if defined(LIBA_VERSION_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_VERSION_C */

/*!
 @brief version lhs less than version rhs
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
 @brief version lhs greater than version rhs
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
 @brief version lhs less than or equal version rhs
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
 @brief version lhs greater than or equal version rhs
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
 @brief version lhs equal version rhs
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
 @brief version lhs not equal version rhs
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

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_VERSION */

#endif /* version.h */
