/*!
 @file hash.h
 @brief hash function
*/

#ifndef LIBA_HASH_H
#define LIBA_HASH_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_hash hash function
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief a hash function whose prime number is 131
 @param[in] str string to be processed
 @param[in] val initial value
 @return hash value
*/
A_EXTERN a_u32 a_hash_bkdr(void const *str, a_u32 val);

/*!
 @brief a hash function whose prime number is 131
 @param[in] ptr points to string to be processed
 @param[in] siz length of string to be processed
 @param[in] val initial value
 @return hash value
*/
A_EXTERN a_u32 a_hash_bkdr_(void const *ptr, a_size siz, a_u32 val);

/*!
 @brief a hash function whose prime number is 65599
 @param[in] str string to be processed
 @param[in] val initial value
 @return hash value
*/
A_EXTERN a_u32 a_hash_sdbm(void const *str, a_u32 val);

/*!
 @brief a hash function whose prime number is 65599
 @param[in] ptr points to string to be processed
 @param[in] siz length of string to be processed
 @param[in] val initial value
 @return hash value
*/
A_EXTERN a_u32 a_hash_sdbm_(void const *ptr, a_size siz, a_u32 val);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_hash */

#endif /* a/hash.h */
