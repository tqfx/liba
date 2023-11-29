#include "a.h"

static JSValue liba_hash_bkdr(JSContext *const ctx, JSValueConst const this_val, int const argc, JSValueConst *const argv)
{
    (void)this_val;
    a_umax_t x = 0;
    for (int i = 0; i < argc; ++i)
    {
        char const *str = JS_ToCString(ctx, argv[i]);
        x = a_hash_bkdr(str, x);
        JS_FreeCString(ctx, str);
    }
    return JS_NewUint32(ctx, (a_u32_t)x);
}

#include "a/math.h"

static JSValue liba_rsqrt(JSContext *const ctx, JSValueConst const this_val, int const argc, JSValueConst *const argv)
{
    (void)this_val;
    (void)argc;
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0]))
    {
        return JS_EXCEPTION;
    }
    return JS_NewFloat64(ctx, a_f64_rsqrt(x));
}

#include "mf.h"

static JSCFunctionListEntry const liba_mf_table[] = {
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

#include "a/version.h"

static JSCFunctionListEntry const liba_table[] = {
    JS_OBJECT_DEF("mf", liba_mf_table, A_LEN(liba_mf_table), 0),
    JS_PROP_STRING_DEF("VERSION", A_VERSION, 0),
    JS_CFUNC_DEF("hash_bkdr", 1, liba_hash_bkdr),
    JS_CFUNC_DEF("rsqrt", 1, liba_rsqrt),
};

int js_liba_init(JSContext *const ctx, JSModuleDef *const m)
{
    js_liba_pid_init(ctx, m);
    js_liba_pid_fuzzy_init(ctx, m);
    js_liba_pid_neuron_init(ctx, m);
    js_liba_polytraj3_init(ctx, m);
    js_liba_polytraj5_init(ctx, m);
    js_liba_polytraj7_init(ctx, m);
    js_liba_tf_init(ctx, m);
    js_liba_version_init(ctx, m);
    return JS_SetModuleExportList(ctx, m, liba_table, A_LEN(liba_table));
}

JSModuleDef *js_init_module(JSContext *const ctx, char const *const module_name)
{
    JSModuleDef *m = JS_NewCModule(ctx, module_name, js_liba_init);
    if (m)
    {
        JS_AddModuleExport(ctx, m, "pid");
        JS_AddModuleExport(ctx, m, "pid_fuzzy");
        JS_AddModuleExport(ctx, m, "pid_neuron");
        JS_AddModuleExport(ctx, m, "polytraj3");
        JS_AddModuleExport(ctx, m, "polytraj5");
        JS_AddModuleExport(ctx, m, "polytraj7");
        JS_AddModuleExport(ctx, m, "tf");
        JS_AddModuleExport(ctx, m, "version");
        JS_AddModuleExportList(ctx, m, liba_table, A_LEN(liba_table));
    }
    return m;
}

JSValue Jconcat(JSContext *const ctx, JSValueConst const val)
{
    JSValue this_val = JS_NewArray(ctx);
    JSValueConst argv[] = {this_val, val};
    JSValue concat = JS_GetPropertyStr(ctx, this_val, "concat");
    JSValue apply = JS_GetPropertyStr(ctx, concat, "apply");
    JSValue res = JS_Call(ctx, apply, this_val, A_LEN(argv), argv);
    JS_FreeValue(ctx, this_val);
    JS_FreeValue(ctx, concat);
    JS_FreeValue(ctx, apply);
    return res;
}

int JArrayLength(JSContext *const ctx, JSValueConst const val, a_u32_t *const plen)
{
    JSValue length = JS_GetPropertyStr(ctx, val, "length");
    if (JS_IsException(length))
    {
        return ~0;
    }
    int ret = JS_ToUint32(ctx, plen, length);
    JS_FreeValue(ctx, length);
    return ret;
}

int JArrayFloat(JSContext *const ctx, JSValueConst const val, a_float_t *const ptr, a_u32_t const len)
{
    for (unsigned int i = 0; i < len; ++i)
    {
        JSValue tmp = JS_GetPropertyUint32(ctx, val, i);
        if (JS_IsException(tmp))
        {
            return ~0;
        }
        double x;
        int ret = JS_ToFloat64(ctx, &x, tmp);
        JS_FreeValue(ctx, tmp);
        if (ret)
        {
            return ret;
        }
        ptr[i] = (a_float_t)x;
    }
    return 0;
}
