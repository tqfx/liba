#include "a.h"
#include "a/lpf.h"

static JSClassID liba_lpf_class_id;

static void liba_lpf_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_lpf_class_id));
}

static JSValue liba_lpf_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0};
    JSValue proto, clazz = JS_UNDEFINED;
    a_lpf *const self = (a_lpf *)js_mallocz(ctx, sizeof(a_lpf));
    if (!self) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { goto fail; }
        if (JS_ToFloat64(ctx, &arg[1], argv[1])) { goto fail; }
        a_lpf_init(self, A_LPF_GEN(arg[0], arg[1]));
    }
    else
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { goto fail; }
        a_lpf_init(self, (a_real)arg[0]);
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

static JSValue liba_lpf_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0};
    a_lpf *const self = (a_lpf *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { return JS_EXCEPTION; }
        if (JS_ToFloat64(ctx, &arg[1], argv[1])) { return JS_EXCEPTION; }
        self->alpha = A_LPF_GEN(arg[0], arg[1]);
    }
    else
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { return JS_EXCEPTION; }
        self->alpha = (a_real)arg[0];
    }
    return JS_UNDEFINED;
}

static JSValue liba_lpf_iter(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_lpf *const self = (a_lpf *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    (void)argc;
    return JS_NewFloat64(ctx, (double)a_lpf_iter(self, (a_real)x));
}

static JSValue liba_lpf_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_lpf *const self = (a_lpf *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_lpf_zero(self);
    (void)argc;
    (void)argv;
    return JS_UNDEFINED;
}

enum
{
    self_alpha,
    self_output
};

static JSValue liba_lpf_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    double x;
    a_lpf *const self = (a_lpf *)JS_GetOpaque2(ctx, this_val, liba_lpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_alpha: x = (double)self->alpha; break;
    case self_output: x = (double)self->output; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSClassDef liba_lpf_class;
static JSCFunctionListEntry const liba_lpf_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.lpf", 0),
    JS_CGETSET_MAGIC_DEF("alpha", liba_lpf_get, NULL, self_alpha),
    JS_CGETSET_MAGIC_DEF("output", liba_lpf_get, NULL, self_output),
    JS_CFUNC_DEF("gen", 2, liba_lpf_gen),
    JS_CFUNC_DEF("iter", 1, liba_lpf_iter),
    JS_CFUNC_DEF("zero", 0, liba_lpf_zero),
};

int js_liba_lpf_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_lpf_class.class_name = "lpf";
    liba_lpf_class.finalizer = liba_lpf_finalizer;

    JS_NewClassID(&liba_lpf_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_lpf_class_id, &liba_lpf_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_lpf_proto, A_LEN(liba_lpf_proto));

    clazz = JS_NewCFunction2(ctx, liba_lpf_ctor, "lpf", 2, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_lpf_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "lpf", clazz);
}
