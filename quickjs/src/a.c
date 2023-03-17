#include "a.h"
#include "a/math.h"
#include "a/version.h"

static JSValue js_hash_bkdr(JSContext *const ctx, JSValueConst const this_val, int const argc, JSValueConst *const argv)
{
    (void)this_val;
    a_umax_t max = 0;
    for (int i = 0; i < argc; ++i)
    {
        a_cstr_t str = JS_ToCString(ctx, argv[i]);
        max = a_hash_bkdr(str, max);
        JS_FreeCString(ctx, str);
    }
    return JS_NewUint32(ctx, a_u32_c(max));
}

static JSValue js_rsqrt(JSContext *const ctx, JSValueConst const this_val, int const argc, JSValueConst *const argv)
{
    double val;
    (void)(argc);
    (void)(this_val);
    if (JS_ToFloat64(ctx, &val, argv[0]))
    {
        return JS_EXCEPTION;
    }
    return JS_NewFloat64(ctx, a_f64_rsqrt(val));
}

static JSCFunctionListEntry const js_liba_funcs[] = {
    JS_PROP_STRING_DEF("VERSION", A_VERSION, 0),
    JS_CFUNC_DEF("hash_bkdr", 1, js_hash_bkdr),
    JS_CFUNC_DEF("rsqrt", 1, js_rsqrt),
};

static int js_liba_init(JSContext *const ctx, JSModuleDef *const m)
{
    return JS_SetModuleExportList(ctx, m, js_liba_funcs, countof(js_liba_funcs));
}

JSModuleDef *js_init_module(JSContext *const ctx, char const *const module_name)
{
    JSModuleDef *m = JS_NewCModule(ctx, module_name, js_liba_init);
    if (m)
    {
        JS_AddModuleExportList(ctx, m, js_liba_funcs, countof(js_liba_funcs));
    }
    return m;
}
