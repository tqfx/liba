#include "a.h"
#include "a/trajpoly5.h"

static JSClassID liba_trajpoly5_class_id;

static void liba_trajpoly5_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajpoly5_class_id));
}

static JSValue liba_trajpoly5_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    JSValue proto, clazz = JS_UNDEFINED;
    a_trajpoly5 *const self = (a_trajpoly5 *)js_mallocz(ctx, sizeof(a_trajpoly5));
    if (!self) { return JS_EXCEPTION; }
    if (argc > i) { argc = i; }
    for (i = 0; i < 3; ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { goto fail; }
    }
    for (i = 3; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { goto fail; }
    }
    a_trajpoly5_gen(self, (a_real)arg[0],
                    (a_real)arg[1], (a_real)arg[2],
                    (a_real)arg[3], (a_real)arg[4],
                    (a_real)arg[5], (a_real)arg[6]);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_trajpoly5_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_trajpoly5_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (argc > i) { argc = i; }
    for (i = 0; i < 3; ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    for (i = 3; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_trajpoly5_gen(self, (a_real)arg[0],
                    (a_real)arg[1], (a_real)arg[2],
                    (a_real)arg[3], (a_real)arg[4],
                    (a_real)arg[5], (a_real)arg[6]);
    return JS_UNDEFINED;
}

static JSValue liba_trajpoly5_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real pos;
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    pos = a_trajpoly5_pos(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajpoly5_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real vel;
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    vel = a_trajpoly5_vel(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajpoly5_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real acc;
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    acc = a_trajpoly5_acc(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)acc);
}

enum
{
    self_p,
    self_v,
    self_a
};

static JSValue liba_trajpoly5_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_p: return js_array_num_new(ctx, self->p, A_LEN(self->p));
    case self_v: return js_array_num_new(ctx, self->v, A_LEN(self->v));
    case self_a: return js_array_num_new(ctx, self->a, A_LEN(self->a));
    default: return JS_UNDEFINED;
    }
}

static JSClassDef liba_trajpoly5_class;
static JSCFunctionListEntry const liba_trajpoly5_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajpoly5", 0),
    JS_CGETSET_MAGIC_DEF("p", liba_trajpoly5_get, NULL, self_p),
    JS_CGETSET_MAGIC_DEF("v", liba_trajpoly5_get, NULL, self_v),
    JS_CGETSET_MAGIC_DEF("a", liba_trajpoly5_get, NULL, self_a),
    JS_CFUNC_DEF("gen", 7, liba_trajpoly5_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajpoly5_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajpoly5_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajpoly5_acc),
};

int js_liba_trajpoly5_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_trajpoly5_class.class_name = "trajpoly5";
    liba_trajpoly5_class.finalizer = liba_trajpoly5_finalizer;

    JS_NewClassID(&liba_trajpoly5_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajpoly5_class_id, &liba_trajpoly5_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajpoly5_proto, A_LEN(liba_trajpoly5_proto));

    clazz = JS_NewCFunction2(ctx, liba_trajpoly5_ctor, "trajpoly5", 7, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_trajpoly5_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "trajpoly5", clazz);
}
