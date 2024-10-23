#include "a.h"
#include "a/hash.h"

static JSValue liba_hash_bkdr(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_u32 x = 0;
    (void)this_val;
    if (argc > 1)
    {
        if (JS_ToUint32(ctx, &x, argv[1])) { return JS_EXCEPTION; }
    }
    if (argc > 0)
    {
        char const *str = JS_ToCString(ctx, argv[0]);
        x = a_hash_bkdr(str, x);
        JS_FreeCString(ctx, str);
    }
    return JS_NewUint32(ctx, x);
}

static JSValue liba_hash_sdbm(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_u32 x = 0;
    (void)this_val;
    if (argc > 1)
    {
        if (JS_ToUint32(ctx, &x, argv[1])) { return JS_EXCEPTION; }
    }
    if (argc > 0)
    {
        char const *str = JS_ToCString(ctx, argv[0]);
        x = a_hash_sdbm(str, x);
        JS_FreeCString(ctx, str);
    }
    return JS_NewUint32(ctx, x);
}

#include "a/math.h"

static JSValue liba_isqrt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)this_val;
    (void)argc;
    uint64_t x;
    if (JS_ToIndex(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    return JS_NewUint32(ctx, a_u64_sqrt(x));
}

static JSValue liba_rsqrt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)this_val;
    (void)argc;
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    return JS_NewFloat64(ctx, a_f64_rsqrt(x));
}

#include "mf.h"

static JSCFunctionListEntry const liba_mf_proto[] = {
    JS_PROP_INT32_DEF("NUL", A_MF_NUL, 0),
    JS_PROP_INT32_DEF("GAUSS", A_MF_GAUSS, 0),
    JS_PROP_INT32_DEF("GAUSS2", A_MF_GAUSS2, 0),
    JS_PROP_INT32_DEF("GBELL", A_MF_GBELL, 0),
    JS_PROP_INT32_DEF("SIG", A_MF_SIG, 0),
    JS_PROP_INT32_DEF("DSIG", A_MF_DSIG, 0),
    JS_PROP_INT32_DEF("PSIG", A_MF_PSIG, 0),
    JS_PROP_INT32_DEF("TRAP", A_MF_TRAP, 0),
    JS_PROP_INT32_DEF("TRI", A_MF_TRI, 0),
    JS_PROP_INT32_DEF("LINS", A_MF_LINS, 0),
    JS_PROP_INT32_DEF("LINZ", A_MF_LINZ, 0),
    JS_PROP_INT32_DEF("S", A_MF_S, 0),
    JS_PROP_INT32_DEF("Z", A_MF_Z, 0),
    JS_PROP_INT32_DEF("PI", A_MF_PI, 0),
    JS_CFUNC_DEF("gauss", 3, liba_mf_gauss),
    JS_CFUNC_DEF("gauss2", 5, liba_mf_gauss2),
    JS_CFUNC_DEF("gbell", 4, liba_mf_gbell),
    JS_CFUNC_DEF("sig", 3, liba_mf_sig),
    JS_CFUNC_DEF("dsig", 5, liba_mf_dsig),
    JS_CFUNC_DEF("psig", 5, liba_mf_psig),
    JS_CFUNC_DEF("trap", 5, liba_mf_trap),
    JS_CFUNC_DEF("tri", 4, liba_mf_tri),
    JS_CFUNC_DEF("lins", 3, liba_mf_lins),
    JS_CFUNC_DEF("linz", 3, liba_mf_linz),
    JS_CFUNC_DEF("s", 3, liba_mf_s),
    JS_CFUNC_DEF("z", 3, liba_mf_z),
    JS_CFUNC_DEF("pi", 5, liba_mf_pi),
};

#if !defined A_VERSION
#include "a/version.h"
#endif /* A_VERSION */

static JSCFunctionListEntry const liba_proto[] = {
    JS_OBJECT_DEF("mf", liba_mf_proto, A_LEN(liba_mf_proto), 0),
    JS_PROP_STRING_DEF("VERSION", A_VERSION, 0),
    JS_CFUNC_DEF("hash_sdbm", 1, liba_hash_sdbm),
    JS_CFUNC_DEF("hash_bkdr", 1, liba_hash_bkdr),
    JS_CFUNC_DEF("isqrt", 1, liba_isqrt),
    JS_CFUNC_DEF("rsqrt", 1, liba_rsqrt),
};

int js_liba_init(JSContext *ctx, JSModuleDef *m)
{
    js_liba_crc16_init(ctx, m);
    js_liba_crc32_init(ctx, m);
    js_liba_crc64_init(ctx, m);
    js_liba_crc8_init(ctx, m);
    js_liba_hpf_init(ctx, m);
    js_liba_lpf_init(ctx, m);
    js_liba_pid_init(ctx, m);
    js_liba_pid_fuzzy_init(ctx, m);
    js_liba_pid_neuro_init(ctx, m);
    js_liba_regress_linear_init(ctx, m);
    js_liba_regress_simple_init(ctx, m);
    js_liba_tf_init(ctx, m);
    js_liba_trajbell_init(ctx, m);
    js_liba_trajpoly3_init(ctx, m);
    js_liba_trajpoly5_init(ctx, m);
    js_liba_trajpoly7_init(ctx, m);
    js_liba_trajtrap_init(ctx, m);
    js_liba_version_init(ctx, m);
    return JS_SetModuleExportList(ctx, m, liba_proto, A_LEN(liba_proto));
}

JSModuleDef *js_init_module(JSContext *ctx, char const *module_name)
{
    JSModuleDef *m = JS_NewCModule(ctx, module_name, js_liba_init);
    if (m)
    {
        JS_AddModuleExport(ctx, m, "crc16");
        JS_AddModuleExport(ctx, m, "crc32");
        JS_AddModuleExport(ctx, m, "crc64");
        JS_AddModuleExport(ctx, m, "crc8");
        JS_AddModuleExport(ctx, m, "hpf");
        JS_AddModuleExport(ctx, m, "lpf");
        JS_AddModuleExport(ctx, m, "pid");
        JS_AddModuleExport(ctx, m, "pid_fuzzy");
        JS_AddModuleExport(ctx, m, "pid_neuro");
        JS_AddModuleExport(ctx, m, "regress_linear");
        JS_AddModuleExport(ctx, m, "regress_simple");
        JS_AddModuleExport(ctx, m, "tf");
        JS_AddModuleExport(ctx, m, "trajbell");
        JS_AddModuleExport(ctx, m, "trajpoly3");
        JS_AddModuleExport(ctx, m, "trajpoly5");
        JS_AddModuleExport(ctx, m, "trajpoly7");
        JS_AddModuleExport(ctx, m, "trajtrap");
        JS_AddModuleExport(ctx, m, "version");
        JS_AddModuleExportList(ctx, m, liba_proto, A_LEN(liba_proto));
    }
    return m;
}
