#ifndef QJS_A_H
#define QJS_A_H

#include "a/a.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC system_header
#endif /* __GNUC__ */
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Waggregate-return")
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* -Waggregate-return */
#include "quickjs.h"

#define countof(x) (sizeof(x) / sizeof(*(x)))

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC JSModuleDef *js_init_module(JSContext *ctx, char const *module_name);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* a.h */
