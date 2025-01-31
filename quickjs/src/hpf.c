#include "a.h"
#include "a/hpf.h"

static JSClassID liba_hpf_class_id;

static void liba_hpf_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_hpf_class_id));
}

static JSValue liba_hpf_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0};
    JSValue proto, clazz = JS_UNDEFINED;
    a_hpf *const self = (a_hpf *)js_mallocz(ctx, sizeof(a_hpf));
    if (!self) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { goto fail; }
        if (JS_ToFloat64(ctx, &arg[1], argv[1])) { goto fail; }
        a_hpf_init(self, A_HPF_GEN(arg[0], arg[1]));
    }
    else
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { goto fail; }
        a_hpf_init(self, (a_real)arg[0]);
    }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_hpf_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_hpf_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0};
    a_hpf *const self = (a_hpf *)JS_GetOpaque2(ctx, this_val, liba_hpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { return JS_EXCEPTION; }
        if (JS_ToFloat64(ctx, &arg[1], argv[1])) { return JS_EXCEPTION; }
        self->alpha = A_HPF_GEN(arg[0], arg[1]);
    }
    else
    {
        if (JS_ToFloat64(ctx, &arg[0], argv[0])) { return JS_EXCEPTION; }
        self->alpha = (a_real)arg[0];
    }
    return JS_UNDEFINED;
}

static JSValue liba_hpf_iter(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_hpf *const self = (a_hpf *)JS_GetOpaque2(ctx, this_val, liba_hpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    (void)argc;
    return JS_NewFloat64(ctx, (double)a_hpf_iter(self, (a_real)x));
}

static JSValue liba_hpf_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_hpf *const self = (a_hpf *)JS_GetOpaque2(ctx, this_val, liba_hpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_hpf_zero(self);
    (void)argc;
    (void)argv;
    return JS_UNDEFINED;
}

enum
{
    self_alpha,
    self_output,
    self_input
};

static JSValue liba_hpf_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    double x;
    a_hpf *const self = (a_hpf *)JS_GetOpaque2(ctx, this_val, liba_hpf_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_alpha: x = (double)self->alpha; break;
    case self_output: x = (double)self->output; break;
    case self_input: x = (double)self->input; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSClassDef liba_hpf_class;
static JSCFunctionListEntry const liba_hpf_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.hpf", 0),
    JS_CGETSET_MAGIC_DEF("alpha", liba_hpf_get, NULL, self_alpha),
    JS_CGETSET_MAGIC_DEF("output", liba_hpf_get, NULL, self_output),
    JS_CGETSET_MAGIC_DEF("input", liba_hpf_get, NULL, self_input),
    JS_CFUNC_DEF("gen", 2, liba_hpf_gen),
    JS_CFUNC_DEF("iter", 1, liba_hpf_iter),
    JS_CFUNC_DEF("zero", 0, liba_hpf_zero),
};

int js_liba_hpf_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_hpf_class.class_name = "hpf";
    liba_hpf_class.finalizer = liba_hpf_finalizer;

    JS_NewClassID(&liba_hpf_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_hpf_class_id, &liba_hpf_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_hpf_proto, A_LEN(liba_hpf_proto));

    clazz = JS_NewCFunction2(ctx, liba_hpf_ctor, "hpf", 2, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_hpf_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "hpf", clazz);
}
