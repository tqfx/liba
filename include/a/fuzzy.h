/*!
 @file fuzzy.h
 @brief fuzzy operator
*/

#ifndef LIBA_FUZZY_H
#define LIBA_FUZZY_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_FUZZY fuzzy operator
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_FUZZY_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_FUZZY_C */

/*!
 @brief complementary operator
 @param[in] x membership
 @return = \f$ 1-x \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_FUZZY_C)
A_EXTERN a_float a_fuzzy_not(a_float x);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FUZZY_C)
A_INTERN a_float a_fuzzy_not(a_float x) { return 1 - x; }
#endif /* A_HAVE_INLINE */

/*!
 @brief fuzzy intersection operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ \min(a,b) \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_FUZZY_C)
A_EXTERN a_float a_fuzzy_cap(a_float a, a_float b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FUZZY_C)
A_INTERN a_float a_fuzzy_cap(a_float a, a_float b) { return A_MIN(a, b); }
#endif /* A_HAVE_INLINE */

/*!
 @brief algebraic product operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ ab \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_FUZZY_C)
A_EXTERN a_float a_fuzzy_cap_algebra(a_float a, a_float b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FUZZY_C)
A_INTERN a_float a_fuzzy_cap_algebra(a_float a, a_float b) { return a * b; }
#endif /* A_HAVE_INLINE */

/*!
 @brief bounded product operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ \max(a+b-1,0) \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_FUZZY_C)
A_EXTERN a_float a_fuzzy_cap_bounded(a_float a, a_float b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FUZZY_C)
A_INTERN a_float a_fuzzy_cap_bounded(a_float a, a_float b)
{
    a_float const c = a + b - 1;
    return A_MAX(c, 0);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief fuzzy union operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ \max(a,b) \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_FUZZY_C)
A_EXTERN a_float a_fuzzy_cup(a_float a, a_float b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FUZZY_C)
A_INTERN a_float a_fuzzy_cup(a_float a, a_float b) { return A_MAX(a, b); }
#endif /* A_HAVE_INLINE */

/*!
 @brief algebraic sum operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ a+b-ab \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_FUZZY_C)
A_EXTERN a_float a_fuzzy_cup_algebra(a_float a, a_float b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FUZZY_C)
A_INTERN a_float a_fuzzy_cup_algebra(a_float a, a_float b) { return a + b - a * b; }
#endif /* A_HAVE_INLINE */

/*!
 @brief bounded sum operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ \min(a+b,1) \f$
*/
#if !defined A_HAVE_INLINE || defined(LIBA_FUZZY_C)
A_EXTERN a_float a_fuzzy_cup_bounded(a_float a, a_float b);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_FUZZY_C)
A_INTERN a_float a_fuzzy_cup_bounded(a_float a, a_float b)
{
    a_float const c = a + b;
    return A_MIN(c, 1);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief equilibrium operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ \sqrt{ab}\sqrt{1-(1-a)(1-b)} \f$
*/
A_EXTERN a_float a_fuzzy_equ(a_float a, a_float b);

/*!
 @brief equilibrium operator
 @param[in] gamma gamma operator
 @param[in] a left-hand operand
 @param[in] b right-hand operand
 @return = \f$ (ab)^{1-\gamma}(1-(1-a)(1-b))^{\gamma} \f$
*/
A_EXTERN a_float a_fuzzy_equ_(a_float gamma, a_float a, a_float b);

#if defined(LIBA_FUZZY_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_FUZZY_C */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_FUZZY */

#endif /* a/fuzzy.h */
