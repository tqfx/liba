#ifndef QJS_MF_H
#define QJS_MF_H

#include "a.h"
#include "a/mf.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN JSValue liba_mf_gauss(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_gauss2(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_gbell(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_sig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_dsig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_psig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_trap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_tri(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_lins(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_linz(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_s(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_z(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
A_HIDDEN JSValue liba_mf_pi(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* mf.h */
