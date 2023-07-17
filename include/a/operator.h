/*!
 @file operator.h
 @brief algorithm library operators
*/

#ifndef LIBA_OPERATOR_H
#define LIBA_OPERATOR_H

/*!
 @ingroup A
 @addtogroup A_OPERATOR algorithm library operators
 @{
*/

// clang-format off

#define a_inc(x) (++(x)) //!< prefix increment
#define a_dec(x) (--(x)) //!< prefix decrement

#define a_pos(x) (+(x)) //!< positive
#define a_neg(x) (-(x)) //!< negative

#define a_not(x)   (!(x)) //!< logical NOT
#define a_compl(x) (~(x)) //!< bitwise NOT

#define a_mul(a, b) ((a) * (b)) //!< multiplication
#define a_div(a, b) ((a) / (b)) //!< division
#define a_mod(a, b) ((a) % (b)) //!< remainder

#define a_add(a, b) ((a) + (b)) //!< addition
#define a_sub(a, b) ((a) - (b)) //!< subtraction

#define a_lshift(a, b) ((a) << (b)) //!< bitwise left shift
#define a_rshift(a, b) ((a) >> (b)) //!< bitwise right shift

#define a_eq(a, b) ((a) == (b)) //!< equal
#define a_ne(a, b) ((a) != (b)) //!< not equal
#define a_lt(a, b) ((a) < (b))  //!< less than
#define a_gt(a, b) ((a) > (b))  //!< greater than
#define a_le(a, b) ((a) <= (b)) //!< less than or equal
#define a_ge(a, b) ((a) >= (b)) //!< greater than or equal

#define a_bitand(a, b) ((a) & (b)) //!< bitwise AND
#define a_bitxor(a, b) ((a) ^ (b)) //!< bitwise XOR (exclusive or)
#define a_bitor(a, b)  ((a) | (b)) //!< bitwise OR (inclusive or)

#define a_and(a, b) ((a) && (b)) //!< logical AND
#define a_or(a, b)  ((a) || (b)) //!< logical OR

#define a_add_eq(a, b) ((a) += (b)) //!< in-place assignment by sum
#define a_sub_eq(a, b) ((a) -= (b)) //!< in-place assignment by difference
#define a_mul_eq(a, b) ((a) *= (b)) //!< in-place assignment by product
#define a_div_eq(a, b) ((a) /= (b)) //!< in-place assignment by quotient
#define a_mod_eq(a, b) ((a) %= (b)) //!< in-place assignment by remainder

#define a_shl_eq(a, b) ((a) <<= (b)) //!< in-place assignment by bitwise left shift
#define a_shr_eq(a, b) ((a) >>= (b)) //!< in-place assignment by bitwise right shift

#define a_and_eq(a, b) ((a) &= (b)) //!< in-place assignment by bitwise AND
#define a_xor_eq(a, b) ((a) ^= (b)) //!< in-place assignment by bitwise XOR (exclusive or)
#define a_or_eq(a, b)  ((a) |= (b)) //!< in-place assignment by bitwise OR (inclusive or)

// clang-format on

/*! @} A_OPERATOR */

#endif /* a/operator.h */
