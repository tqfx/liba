#include "a.h"
#include "a/trajpoly5.h"

static JSClassID liba_trajpoly5_class_id;

static void liba_trajpoly5_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajpoly5_class_id));
}

static JSClassDef liba_trajpoly5_class = {"trajpoly5", .finalizer = liba_trajpoly5_finalizer};

static JSValue liba_trajpoly5_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_trajpoly5 *const self = (a_trajpoly5 *)js_mallocz(ctx, sizeof(a_trajpoly5));
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < 3; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { goto fail; }
    }
    for (int i = 3; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { goto fail; }
    }
    a_trajpoly5_gen(self, (a_float)args[0],
                    (a_float)args[1], (a_float)args[2],
                    (a_float)args[3], (a_float)args[4],
                    (a_float)args[5], (a_float)args[6]);
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
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < 3; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    for (int i = 3; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_trajpoly5_gen(self, (a_float)args[0],
                    (a_float)args[1], (a_float)args[2],
                    (a_float)args[3], (a_float)args[4],
                    (a_float)args[5], (a_float)args[6]);
    return JS_UNDEFINED;
}

static JSValue liba_trajpoly5_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    a_float pos = a_trajpoly5_pos(self, (a_float)x);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajpoly5_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    a_float vel = a_trajpoly5_vel(self, (a_float)x);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajpoly5_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    a_float acc = a_trajpoly5_acc(self, (a_float)x);
    return JS_NewFloat64(ctx, (double)acc);
}

enum
{
    self_p_,
    self_v_,
    self_a_,
};

static JSValue liba_trajpoly5_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_trajpoly5 *const self = (a_trajpoly5 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly5_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_p_: return js_array_num_new(ctx, self->p, A_LEN(self->p));
    case self_v_: return js_array_num_new(ctx, self->v, A_LEN(self->v));
    case self_a_: return js_array_num_new(ctx, self->a, A_LEN(self->a));
    default: return JS_UNDEFINED;
    }
}

static JSCFunctionListEntry const liba_trajpoly5_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajpoly5", 0),
    JS_CGETSET_MAGIC_DEF("p", liba_trajpoly5_get, NULL, self_p_),
    JS_CGETSET_MAGIC_DEF("v", liba_trajpoly5_get, NULL, self_v_),
    JS_CGETSET_MAGIC_DEF("a", liba_trajpoly5_get, NULL, self_a_),
    JS_CFUNC_DEF("gen", 7, liba_trajpoly5_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajpoly5_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajpoly5_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajpoly5_acc),
};

int js_liba_trajpoly5_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_trajpoly5_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajpoly5_class_id, &liba_trajpoly5_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajpoly5_proto, A_LEN(liba_trajpoly5_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_trajpoly5_ctor, "trajpoly5", 7, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_trajpoly5_class_id, proto);

    return JS_SetModuleExport(ctx, m, "trajpoly5", clazz);
}
