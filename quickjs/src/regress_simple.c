#include "a.h"
#include "a/regress_simple.h"

static JSClassID liba_regress_simple_class_id;

static void liba_regress_simple_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_regress_simple_class_id));
}

static JSClassDef liba_regress_simple_class = {"regress_simple", .finalizer = liba_regress_simple_finalizer};

static JSValue liba_regress_simple_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    (void)argc;
    JSValue proto, clazz = JS_UNDEFINED;
    a_regress_simple *const self = (a_regress_simple *)js_mallocz(ctx, sizeof(a_regress_simple));
    if (!self) { return JS_EXCEPTION; }
    double args[] = {1, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { goto fail; }
    }
    a_regress_simple_init(self, args[0], args[1]);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_regress_simple_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_regress_simple_eval(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    return JS_NewFloat64(ctx, (double)a_regress_simple_eval(self, (a_float)x));
}

static JSValue liba_regress_simple_evar(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    return JS_NewFloat64(ctx, (double)a_regress_simple_evar(self, (a_float)x));
}

static JSValue liba_regress_simple_ols_(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    JSValue err = JS_EXCEPTION;
    a_float x_mean, y_mean;
    js_array_num x, y;
    js_array_num_init(&x, NULL, 0);
    js_array_num_init(&y, NULL, 0);
    if (js_array_num_get(ctx, argv[0], &x)) { goto fail; }
    if (js_array_num_get(ctx, argv[1], &y)) { goto fail; }
    if (JS_ToFloat64(ctx, &x_mean, argv[2])) { goto fail; }
    if (JS_ToFloat64(ctx, &y_mean, argv[3])) { goto fail; }
    a_regress_simple_ols_(self, A_MIN(x.num, y.num), x.ptr, y.ptr, x_mean, y_mean);
    err = JS_UNDEFINED;
fail:
    js_free(ctx, y.ptr);
    js_free(ctx, x.ptr);
    return err;
}

static JSValue liba_regress_simple_olsx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    JSValue err = JS_EXCEPTION;
    js_array_num x, y;
    a_float x_mean;
    js_array_num_init(&x, NULL, 0);
    js_array_num_init(&y, NULL, 0);
    if (js_array_num_get(ctx, argv[0], &x)) { goto fail; }
    if (js_array_num_get(ctx, argv[1], &y)) { goto fail; }
    if (JS_ToFloat64(ctx, &x_mean, argv[2])) { goto fail; }
    a_regress_simple_olsx(self, A_MIN(x.num, y.num), x.ptr, y.ptr, x_mean);
    err = JS_UNDEFINED;
fail:
    js_free(ctx, y.ptr);
    js_free(ctx, x.ptr);
    return err;
}

static JSValue liba_regress_simple_olsy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    JSValue err = JS_EXCEPTION;
    js_array_num x, y;
    a_float y_mean;
    js_array_num_init(&x, NULL, 0);
    js_array_num_init(&y, NULL, 0);
    if (js_array_num_get(ctx, argv[0], &x)) { goto fail; }
    if (js_array_num_get(ctx, argv[1], &y)) { goto fail; }
    if (JS_ToFloat64(ctx, &y_mean, argv[2])) { goto fail; }
    a_regress_simple_olsy(self, A_MIN(x.num, y.num), x.ptr, y.ptr, y_mean);
    err = JS_UNDEFINED;
fail:
    js_free(ctx, y.ptr);
    js_free(ctx, x.ptr);
    return err;
}

static JSValue liba_regress_simple_ols(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    JSValue err = JS_EXCEPTION;
    js_array_num x, y;
    js_array_num_init(&x, NULL, 0);
    js_array_num_init(&y, NULL, 0);
    if (js_array_num_get(ctx, argv[0], &x)) { goto fail; }
    if (js_array_num_get(ctx, argv[1], &y)) { goto fail; }
    a_regress_simple_ols(self, A_MIN(x.num, y.num), x.ptr, y.ptr);
    err = JS_UNDEFINED;
fail:
    js_free(ctx, y.ptr);
    js_free(ctx, x.ptr);
    return err;
}

static JSValue liba_regress_simple_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_regress_simple_zero(self);
    return JS_UNDEFINED;
}

enum
{
    self_coef,
    self_bias,
};

static JSValue liba_regress_simple_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case self_coef: x = (double)self->coef; break;
    case self_bias: x = (double)self->bias; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_regress_simple_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    a_regress_simple *const self = (a_regress_simple *)JS_GetOpaque2(ctx, this_val, liba_regress_simple_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, val)) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_coef: self->coef = (a_float)x; break;
    case self_bias: self->bias = (a_float)x; break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSCFunctionListEntry const liba_regress_simple_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.regress_simple", 0),
    JS_CGETSET_MAGIC_DEF("coef", liba_regress_simple_get, liba_regress_simple_set, self_coef),
    JS_CGETSET_MAGIC_DEF("bias", liba_regress_simple_get, liba_regress_simple_set, self_bias),
    JS_CFUNC_DEF("eval", 1, liba_regress_simple_eval),
    JS_CFUNC_DEF("evar", 1, liba_regress_simple_evar),
    JS_CFUNC_DEF("ols_", 4, liba_regress_simple_ols_),
    JS_CFUNC_DEF("olsx", 3, liba_regress_simple_olsx),
    JS_CFUNC_DEF("olsy", 3, liba_regress_simple_olsy),
    JS_CFUNC_DEF("ols", 2, liba_regress_simple_ols),
    JS_CFUNC_DEF("zero", 0, liba_regress_simple_zero),
};

int js_liba_regress_simple_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_regress_simple_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_regress_simple_class_id, &liba_regress_simple_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_regress_simple_proto, A_LEN(liba_regress_simple_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_regress_simple_ctor, "regress_simple", 2, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_regress_simple_class_id, proto);

    return JS_SetModuleExport(ctx, m, "regress_simple", clazz);
}
