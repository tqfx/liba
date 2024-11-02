#ifndef QUICKJS_LIBA_A_H
#define QUICKJS_LIBA_A_H

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC system_header
#endif /* __GNUC__ */
#include "a/a.h"
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Waggregate-return")
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* -Waggregate-return */
#undef inline
#define inline __inline
#include "quickjs.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int js_array_length(JSContext *ctx, JSValueConst val, a_u32 *plen);
JSValue js_array_u8_new(JSContext *ctx, a_u8 const *ptr, a_u32 len);
JSValue js_array_u16_new(JSContext *ctx, a_u16 const *ptr, a_u32 len);
JSValue js_array_u32_new(JSContext *ctx, a_u32 const *ptr, a_u32 len);
JSValue js_array_u64_new(JSContext *ctx, a_u64 const *ptr, a_u32 len);
JSValue js_array_num_new(JSContext *ctx, a_float const *ptr, a_u32 len);

int js_array_num_len(JSContext *ctx, JSValueConst val, unsigned int *num, int dim);
a_float *js_array_num_ptr(JSContext *ctx, JSValueConst val, a_float *ptr, int dim);
a_float *js_array_num_get(JSContext *ctx, JSValueConst val, a_float *ptr, unsigned int *num, int dim);

A_PUBLIC JSModuleDef *js_init_module(JSContext *ctx, char const *module_name);

int js_liba_init(JSContext *ctx, JSModuleDef *m);
int js_liba_crc16_init(JSContext *ctx, JSModuleDef *m);
int js_liba_crc32_init(JSContext *ctx, JSModuleDef *m);
int js_liba_crc64_init(JSContext *ctx, JSModuleDef *m);
int js_liba_crc8_init(JSContext *ctx, JSModuleDef *m);
int js_liba_hpf_init(JSContext *ctx, JSModuleDef *m);
int js_liba_lpf_init(JSContext *ctx, JSModuleDef *m);
int js_liba_pid_init(JSContext *ctx, JSModuleDef *m);
int js_liba_pid_fuzzy_init(JSContext *ctx, JSModuleDef *m);
int js_liba_pid_neuro_init(JSContext *ctx, JSModuleDef *m);
int js_liba_regress_linear_init(JSContext *ctx, JSModuleDef *m);
int js_liba_regress_simple_init(JSContext *ctx, JSModuleDef *m);
int js_liba_tf_init(JSContext *ctx, JSModuleDef *m);
int js_liba_trajbell_init(JSContext *ctx, JSModuleDef *m);
int js_liba_trajpoly3_init(JSContext *ctx, JSModuleDef *m);
int js_liba_trajpoly5_init(JSContext *ctx, JSModuleDef *m);
int js_liba_trajpoly7_init(JSContext *ctx, JSModuleDef *m);
int js_liba_trajtrap_init(JSContext *ctx, JSModuleDef *m);
int js_liba_version_init(JSContext *ctx, JSModuleDef *m);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* a.h */
