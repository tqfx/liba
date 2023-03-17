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

typedef a_vptr_t (*a_alloc_f)(a_vptr_t, a_size_t);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_alloc_f a_alloc_reg(a_alloc_f alloc);
A_EXTERN a_vptr_t a_alloc(a_vptr_t vptr, a_size_t size);
A_EXTERN a_vptr_t a_alloc_(a_vptr_t vptr, a_size_t size);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_new(T, ptr, num) a_cast_s(T *, a_alloc(ptr, sizeof(T) * (num)))
#define a_die(T, ptr) a_cast_s(T *, a_alloc(ptr, 0))

#endif /* host/a.h */
