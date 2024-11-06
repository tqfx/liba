#include "a.h"
#include "a/regress_linear.h"

static JSClassID liba_regress_linear_class_id;

static void liba_regress_linear_finalizer(JSRuntime *rt, JSValue val)
{
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque(val, liba_regress_linear_class_id);
    js_free_rt(rt, self->coef_p);
    js_free_rt(rt, self);
}

static JSValue liba_regress_linear_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    double bias = 0;
    a_float *p = NULL;
    unsigned int n = 0;
    JSValue proto, clazz = JS_UNDEFINED;
    a_regress_linear *const self = (a_regress_linear *)js_mallocz(ctx, sizeof(a_regress_linear));
    if (!self) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        if (JS_ToFloat64(ctx, &bias, argv[1])) { goto fail; }
    }
    p = js_array_num_get(ctx, argv[0], NULL, &n, 1);
    a_regress_linear_init(self, p, n, bias);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_regress_linear_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    (void)argc;
    js_free(ctx, p);
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_regress_linear_eval(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float *p;
    double res = A_FLOAT_NAN;
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    p = js_array_num_get(ctx, argv[0], NULL, NULL, 1);
    if (p)
    {
        res = a_regress_linear_eval(self, p);
        js_free(ctx, p);
    }
    (void)argc;
    return JS_NewFloat64(ctx, res);
}

static JSValue liba_regress_linear_err(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue r;
    a_float *x, *y;
    unsigned int m = 0, n = 0;
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    x = js_array_num_get(ctx, argv[0], NULL, &m, 1);
    y = js_array_num_get(ctx, argv[1], NULL, &n, 1);
    m /= (unsigned int)self->coef_n;
    if (m < n) { n = m; }
    a_regress_linear_err(self, n, x, y, y);
    r = js_array_num_new(ctx, y, n);
    js_free(ctx, y);
    js_free(ctx, x);
    (void)argc;
    return r;
}

static JSValue liba_regress_linear_gd(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float *input;
    double error, alpha;
    JSValue r = JS_EXCEPTION;
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    input = js_array_num_get(ctx, argv[0], NULL, NULL, 1);
    if (JS_ToFloat64(ctx, &error, argv[1])) { goto fail; }
    if (JS_ToFloat64(ctx, &alpha, argv[2])) { goto fail; }
    a_regress_linear_gd(self, input, error, alpha);
    r = JS_UNDEFINED;
fail:
    js_free(ctx, input);
    (void)argc;
    return r;
}

static JSValue liba_regress_linear_sgd(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double alpha;
    a_float *x, *y;
    JSValue r = JS_EXCEPTION;
    unsigned int m = 0, n = 0;
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    x = js_array_num_get(ctx, argv[0], NULL, &m, 1);
    y = js_array_num_get(ctx, argv[1], NULL, &n, 1);
    if (JS_ToFloat64(ctx, &alpha, argv[2])) { goto fail; }
    m /= (unsigned int)self->coef_n;
    if (m < n) { n = m; }
    a_regress_linear_sgd(self, n, x, y, alpha);
    r = JS_UNDEFINED;
fail:
    js_free(ctx, y);
    js_free(ctx, x);
    (void)argc;
    return r;
}

static JSValue liba_regress_linear_bgd(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double alpha;
    a_float *x, *y;
    JSValue r = JS_EXCEPTION;
    unsigned int m = 0, n = 0;
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    x = js_array_num_get(ctx, argv[0], NULL, &m, 1);
    y = js_array_num_get(ctx, argv[1], NULL, &n, 1);
    if (JS_ToFloat64(ctx, &alpha, argv[2])) { goto fail; }
    m /= (unsigned int)self->coef_n;
    if (m < n) { n = m; }
    a_regress_linear_err(self, n, x, y, y);
    a_regress_linear_bgd(self, n, x, y, alpha);
    r = JS_UNDEFINED;
fail:
    js_free(ctx, y);
    js_free(ctx, x);
    (void)argc;
    return r;
}

static JSValue liba_regress_linear_mgd(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float *x, *y, *err;
    JSValue r = JS_EXCEPTION;
    unsigned int m = 0, n = 0;
    double delta, lrmax, lrmin;
    a_u32 lrtim = 100, epoch = 1000, batch = 10;
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    x = js_array_num_get(ctx, argv[0], NULL, &m, 1);
    y = js_array_num_get(ctx, argv[1], NULL, &n, 1);
    m /= (unsigned int)self->coef_n;
    if (m < n) { n = m; }
    err = (a_float *)js_malloc(ctx, sizeof(a_float) * n);
    if (JS_ToFloat64(ctx, &delta, argv[2])) { goto fail; }
    if (JS_ToFloat64(ctx, &lrmax, argv[3])) { goto fail; }
    if (JS_ToFloat64(ctx, &lrmin, argv[4])) { goto fail; }
    if (argc > 5)
    {
        if (JS_ToUint32(ctx, &lrtim, argv[5])) { goto fail; }
    }
    if (argc > 6)
    {
        if (JS_ToUint32(ctx, &epoch, argv[6])) { goto fail; }
    }
    if (argc > 7)
    {
        if (JS_ToUint32(ctx, &batch, argv[7])) { goto fail; }
    }
    /* clang-format off */
    r = JS_NewFloat64(ctx, a_regress_linear_mgd(self,
        n, x, y, err, delta, lrmax, lrmin, lrtim, epoch, batch
    ));
    /* clang-format on */
fail:
    js_free(ctx, err);
    js_free(ctx, y);
    js_free(ctx, x);
    return r;
}

static JSValue liba_regress_linear_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_regress_linear_zero(self);
    (void)argc;
    (void)argv;
    return JS_UNDEFINED;
}

enum
{
    self_coef,
    self_bias
};

static JSValue liba_regress_linear_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (magic == self_coef)
    {
        return js_array_num_new(ctx, self->coef_p, (a_u32)self->coef_n);
    }
    if (magic == self_bias)
    {
        return JS_NewFloat64(ctx, (double)self->bias);
    }
    return JS_UNDEFINED;
}

static JSValue liba_regress_linear_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    a_regress_linear *const self = (a_regress_linear *)JS_GetOpaque2(ctx, this_val, liba_regress_linear_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (magic == self_coef)
    {
        unsigned int n = (unsigned int)self->coef_n;
        self->coef_p = js_array_num_get(ctx, val, self->coef_p, &n, 1);
        self->coef_n = n;
    }
    else
    {
        double x;
        if (JS_ToFloat64(ctx, &x, val)) { return JS_EXCEPTION; }
        self->bias = (a_float)x;
    }
    return JS_UNDEFINED;
}

static JSClassDef liba_regress_linear_class;
static JSCFunctionListEntry const liba_regress_linear_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.regress_linear", 0),
    JS_CGETSET_MAGIC_DEF("coef", liba_regress_linear_get, liba_regress_linear_set, self_coef),
    JS_CGETSET_MAGIC_DEF("bias", liba_regress_linear_get, liba_regress_linear_set, self_bias),
    JS_CFUNC_DEF("eval", 1, liba_regress_linear_eval),
    JS_CFUNC_DEF("err", 1, liba_regress_linear_err),
    JS_CFUNC_DEF("gd", 3, liba_regress_linear_gd),
    JS_CFUNC_DEF("sgd", 3, liba_regress_linear_sgd),
    JS_CFUNC_DEF("bgd", 3, liba_regress_linear_bgd),
    JS_CFUNC_DEF("mgd", 8, liba_regress_linear_mgd),
    JS_CFUNC_DEF("zero", 0, liba_regress_linear_zero),
};

int js_liba_regress_linear_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_regress_linear_class.class_name = "regress_linear";
    liba_regress_linear_class.finalizer = liba_regress_linear_finalizer;

    JS_NewClassID(&liba_regress_linear_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_regress_linear_class_id, &liba_regress_linear_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_regress_linear_proto, A_LEN(liba_regress_linear_proto));

    clazz = JS_NewCFunction2(ctx, liba_regress_linear_ctor, "regress_linear", 2, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_regress_linear_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "regress_linear", clazz);
}
