#include "a.h"
#include "a/lpf.h"

static JSClassID liba_lpf_class_id;

static void liba_lpf_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_lpf_class_id));
}

static JSClassDef liba_lpf_class = {"lpf", .finalizer = liba_lpf_finalizer};

static JSValue liba_lpf_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_lpf_s *const self = (a_lpf_s *)js_mallocz(ctx, sizeof(a_lpf_s));
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    if (argc > 1)
    {
        if (JS_ToFloat64(ctx, &args[0], argv[0])) { goto fail; }
        if (JS_ToFloat64(ctx, &args[1], argv[1])) { goto fail; }
        a_lpf_init(self, A_LPF_GEN(args[0], args[1]));
    }
    else
    {
        if (JS_ToFloat64(ctx, &args[0], argv[0])) { goto fail; }
        a_lpf_init(self, args[0]);
    }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_lpf_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_lpf_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_lpf_s *const self = (a_lpf_s *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case 0: x = (double)self->alpha; break;
    case 1: x = (double)self->output; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_lpf_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_lpf_s *const self = (a_lpf_s *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    if (argc > 1)
    {
        if (JS_ToFloat64(ctx, &args[0], argv[0])) { return JS_EXCEPTION; }
        if (JS_ToFloat64(ctx, &args[1], argv[1])) { return JS_EXCEPTION; }
        self->alpha = A_LPF_GEN(args[0], args[1]);
    }
    else
    {
        if (JS_ToFloat64(ctx, &args[0], argv[0])) { return JS_EXCEPTION; }
        self->alpha = args[0];
    }
    return JS_UNDEFINED;
}

static JSValue liba_lpf_iter(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_lpf_s *const self = (a_lpf_s *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    return JS_NewFloat64(ctx, (double)a_lpf_iter(self, (a_float_t)x));
}

static JSValue liba_lpf_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_lpf_s *const self = (a_lpf_s *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_lpf_zero(self);
    return JS_UNDEFINED;
}

static JSCFunctionListEntry const liba_lpf_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.lpf", 0),
    JS_CGETSET_MAGIC_DEF("alpha", liba_lpf_get, NULL, 0),
    JS_CGETSET_MAGIC_DEF("output", liba_lpf_get, NULL, 1),
    JS_CFUNC_DEF("gen", 2, liba_lpf_gen),
    JS_CFUNC_DEF("iter", 1, liba_lpf_iter),
    JS_CFUNC_DEF("zero", 0, liba_lpf_zero),
};

int js_liba_lpf_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&liba_lpf_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_lpf_class_id, &liba_lpf_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_lpf_proto, A_LEN(liba_lpf_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_lpf_ctor, "lpf", 2, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_lpf_class_id, proto);

    return JS_SetModuleExport(ctx, m, "lpf", clazz);
}
