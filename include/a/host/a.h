/*!
 @file a.h
 @brief algorithm library on host
*/

#ifndef LIBA_HOST_A_H
#define LIBA_HOST_A_H

#include "../a.h"
#include <stdlib.h>
#if defined(A_HAVE_MIMALLOC_H)
#include <mimalloc-override.h>
#endif /* A_HAVE_MIMALLOC_H */

/*!
 @brief declare allocation function
*/
#define A_ALLOC(alloc, addr, size) \
    void *alloc(void *addr, a_size_t size)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief default allocation function
 @param[in] addr address of memory block
 @param[in] size new size of memory block
 @return new address of memory block or null
*/
A_EXTERN void *a_alloc_(void *addr, a_size_t size);

/*!
 @brief allocation function pointer
 @param[in] addr address of memory block
 @param[in] size new size of memory block
 @return new address of memory block or null
*/
A_EXTERN void *(*a_alloc)(void *addr, a_size_t size);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_new(T, ptr, num) a_cast_s(T *, a_alloc(ptr, sizeof(T) * (num)))
#define a_die(ptr) a_alloc(ptr, 0)

#endif /* a/host/a.h */
