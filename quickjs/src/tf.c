#include "a.h"
#include "a/tf.h"

static int liba_tf_set_num_(JSContext *const ctx, a_tf_s *const self, JSValueConst num)
{
    a_u32_t num_n = 0;
    a_float_t *num_p = self->input;
    int ret = js_array_length(ctx, num, &num_n);
    if (ret) { return ret; }
    if (num_n > self->num_n)
    {
        num_p = (a_float_t *)js_realloc(ctx, num_p, sizeof(a_float_t) * num_n * 2);
        if (!num_p) { return ~0; }
        self->input = num_p;
        num_p += num_n;
        self->num_p = num_p;
    }
    else { num_p += self->num_n; }
    self->num_n = (unsigned int)num_n;
    a_zero(self->input, sizeof(a_float_t) * num_n);
    return js_array_num_get(ctx, num, num_p, num_n);
}

static int liba_tf_set_den_(JSContext *const ctx, a_tf_s *const self, JSValueConst den)
{
    a_u32_t den_n = 0;
    a_float_t *den_p = self->output;
    int ret = js_array_length(ctx, den, &den_n);
    if (ret) { return ret; }
    if (den_n > self->den_n)
    {
        den_p = (a_float_t *)js_realloc(ctx, den_p, sizeof(a_float_t) * den_n * 2);
        if (!den_p) { return ~0; }
        self->output = den_p;
        den_p += den_n;
        self->den_p = den_p;
    }
    else { den_p += self->den_n; }
    self->den_n = (unsigned int)den_n;
    a_zero(self->output, sizeof(a_float_t) * den_n);
    return js_array_num_get(ctx, den, den_p, den_n);
}

static JSClassID liba_tf_class_id;

static void liba_tf_finalizer(JSRuntime *const rt, JSValue const val)
{
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque(val, liba_tf_class_id);
    js_free_rt(rt, self->output);
    js_free_rt(rt, self->input);
    js_free_rt(rt, self);
}

static JSClassDef liba_tf_class = {"tf", .finalizer = liba_tf_finalizer};

static JSValue liba_tf_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    (void)argc;
    JSValue clazz = JS_UNDEFINED;
    a_tf_s *const self = (a_tf_s *)js_mallocz(ctx, sizeof(a_tf_s));
    if (!self) { return JS_EXCEPTION; }
    if (JS_IsObject(argv[0]) && liba_tf_set_num_(ctx, self, argv[0])) { goto fail; }
    if (JS_IsObject(argv[1]) && liba_tf_set_den_(ctx, self, argv[1])) { goto fail; }
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_tf_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_tf_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case 0: return js_array_num_new(ctx, self->num_p, self->num_n);
    case 1: return js_array_num_new(ctx, self->den_p, self->den_n);
    case 2: return js_array_num_new(ctx, self->input, self->num_n);
    case 3: return js_array_num_new(ctx, self->output, self->den_n);
    default: return JS_UNDEFINED;
    }
}

static JSValue liba_tf_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case 0:
        if (JS_IsObject(val)) { liba_tf_set_num_(ctx, self, val); }
        break;
    case 1:
        if (JS_IsObject(val)) { liba_tf_set_den_(ctx, self, val); }
        break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSValue liba_tf_iter(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    return JS_NewFloat64(ctx, (double)a_tf_iter(self, (a_float_t)x));
}

static JSValue liba_tf_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, liba_tf_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_tf_zero(self);
    return JS_UNDEFINED;
}

static JSCFunctionListEntry const liba_tf_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.tf", 0),
    JS_CGETSET_MAGIC_DEF("num", liba_tf_get, liba_tf_set, 0),
    JS_CGETSET_MAGIC_DEF("den", liba_tf_get, liba_tf_set, 1),
    JS_CGETSET_MAGIC_DEF("input", liba_tf_get, liba_tf_set, 2),
    JS_CGETSET_MAGIC_DEF("output", liba_tf_get, liba_tf_set, 3),
    JS_CFUNC_DEF("iter", 1, liba_tf_iter),
    JS_CFUNC_DEF("zero", 0, liba_tf_zero),
};

int js_liba_tf_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&liba_tf_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_tf_class_id, &liba_tf_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_tf_proto, A_LEN(liba_tf_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_tf_ctor, "tf", 2, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_tf_class_id, proto);

    return JS_SetModuleExport(ctx, m, "tf", clazz);
}
