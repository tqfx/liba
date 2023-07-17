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

/*!
 @brief instance enumeration for fuzzy operator
*/
typedef enum a_fuzzy_e
{
    A_FUZZY_DEFAULT /*!< default operator */,
    A_FUZZY_ALGEBRA /*!< algebra operator */,
    A_FUZZY_BOUNDED /*!< bounded operator */
} a_fuzzy_e;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief union operator
 @param[in] e enumeration of operator
  @arg 0 fuzzy union
  @arg 1 algebraic sum
  @arg 2 bounded sum
 @param[in] l left-hand operand
 @param[in] r right-hand operand
 @return result of operation
*/
A_EXTERN a_float_t a_fuzzy_or(unsigned int e, a_float_t l, a_float_t r);

/*!
 @brief Intersection operator
 @param[in] e enumeration of operator
  @arg 0 fuzzy intersection
  @arg 1 algebraic product
  @arg 2 bounded product
 @param[in] l left-hand operand
 @param[in] r right-hand operand
 @return result of operation
*/
A_EXTERN a_float_t a_fuzzy_and(unsigned int e, a_float_t l, a_float_t r);

/*!
 @brief Equilibrium operator
 @param[in] gamma gamma operator
 @param[in] l left-hand operand
 @param[in] r right-hand operand
 @return result of operation
*/
A_EXTERN a_float_t a_fuzzy_equ(a_float_t gamma, a_float_t l, a_float_t r);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_FUZZY */

#endif /* a/fuzzy.h */
