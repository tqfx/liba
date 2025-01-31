#include "a.h"
#include "a/tf.h"

static JSClassID liba_tf_class_id;

static void liba_tf_finalizer(JSRuntime *rt, JSValue val)
{
    union
    {
        a_real const *p;
        a_real *o;
    } u;
    a_tf *const self = (a_tf *)JS_GetOpaque(val, liba_tf_class_id);
    js_free_rt(rt, ((void)(u.p = self->num_p), u.o));
    js_free_rt(rt, ((void)(u.p = self->den_p), u.o));
    js_free_rt(rt, self);
}

static int liba_tf_set_num_(JSContext *ctx, a_tf *self, JSValueConst num)
{
    union
    {
        a_real const *p;
        a_real *o;
    } u;
    unsigned int n = 0;
    int r = js_array_num_len(ctx, num, &n, 1);
    if (r == 0)
    {
        u.p = self->num_p;
        if (n > self->num_n)
        {
            u.o = (a_real *)js_realloc(ctx, u.o, sizeof(a_real) * n * 2);
            a_tf_set_num(self, n, u.o, u.o + n);
        }
        else { self->num_n = n; }
        js_array_num_ptr(ctx, num, u.o, 1);
    }
    return r;
}

static int liba_tf_set_den_(JSContext *ctx, a_tf *self, JSValueConst den)
{
    union
    {
        a_real const *p;
        a_real *o;
    } u;
    unsigned int n = 0;
    int r = js_array_num_len(ctx, den, &n, 1);
    if (r == 0)
    {
        u.p = self->den_p;
        if (n > self->den_n)
        {
            u.o = (a_real *)js_realloc(ctx, u.o, sizeof(a_real) * n * 2);
            a_tf_set_den(self, n, u.o, u.o + n);
        }
        else { self->den_n = n; }
        js_array_num_ptr(ctx, den, u.o, 1);
    }
    return r;
}

static JSValue liba_tf_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_tf *const self = (a_tf *)js_mallocz(ctx, sizeof(a_tf));
    if (!self) { return JS_EXCEPTION; }
    if (liba_tf_set_num_(ctx, self, argv[0])) { goto fail; }
    if (liba_tf_set_den_(ctx, self, argv[1])) { goto fail; }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_tf_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    (void)argc;
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_tf_iter(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_tf *const self = (a_tf *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    (void)argc;
    return JS_NewFloat64(ctx, (double)a_tf_iter(self, (a_real)x));
}

static JSValue liba_tf_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_tf *const self = (a_tf *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_tf_zero(self);
    (void)argc;
    (void)argv;
    return JS_UNDEFINED;
}

enum
{
    self_coef,
    self_bias,
    self_input,
    self_output
};

static JSValue liba_tf_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_tf *const self = (a_tf *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_coef: return js_array_num_new(ctx, self->num_p, self->num_n);
    case self_bias: return js_array_num_new(ctx, self->den_p, self->den_n);
    case self_input: return js_array_num_new(ctx, self->input, self->num_n);
    case self_output: return js_array_num_new(ctx, self->output, self->den_n);
    default: return JS_UNDEFINED;
    }
}

static JSValue liba_tf_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    a_tf *const self = (a_tf *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_coef:
        liba_tf_set_num_(ctx, self, val);
        break;
    case self_bias:
        liba_tf_set_den_(ctx, self, val);
        break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSClassDef liba_tf_class;
static JSCFunctionListEntry const liba_tf_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.tf", 0),
    JS_CGETSET_MAGIC_DEF("num", liba_tf_get, liba_tf_set, self_coef),
    JS_CGETSET_MAGIC_DEF("den", liba_tf_get, liba_tf_set, self_bias),
    JS_CGETSET_MAGIC_DEF("input", liba_tf_get, liba_tf_set, self_input),
    JS_CGETSET_MAGIC_DEF("output", liba_tf_get, liba_tf_set, self_output),
    JS_CFUNC_DEF("iter", 1, liba_tf_iter),
    JS_CFUNC_DEF("zero", 0, liba_tf_zero),
};

int js_liba_tf_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_tf_class.class_name = "tf";
    liba_tf_class.finalizer = liba_tf_finalizer;

    JS_NewClassID(&liba_tf_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_tf_class_id, &liba_tf_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_tf_proto, A_LEN(liba_tf_proto));

    clazz = JS_NewCFunction2(ctx, liba_tf_ctor, "tf", 2, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_tf_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "tf", clazz);
}
