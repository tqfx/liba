#include "a.h"
#include "a/trajpoly3.h"

static JSClassID liba_trajpoly3_class_id;

static void liba_trajpoly3_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajpoly3_class_id));
}

static JSValue liba_trajpoly3_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    JSValue proto, clazz = JS_UNDEFINED;
    a_trajpoly3 *const self = (a_trajpoly3 *)js_mallocz(ctx, sizeof(a_trajpoly3));
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
    a_trajpoly3_gen(self, (a_real)arg[0],
                    (a_real)arg[1], (a_real)arg[2],
                    (a_real)arg[3], (a_real)arg[4]);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_trajpoly3_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_trajpoly3_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    a_trajpoly3 *const self = (a_trajpoly3 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly3_class_id);
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
    a_trajpoly3_gen(self, (a_real)arg[0],
                    (a_real)arg[1], (a_real)arg[2],
                    (a_real)arg[3], (a_real)arg[4]);
    return JS_UNDEFINED;
}

static JSValue liba_trajpoly3_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real pos;
    a_trajpoly3 *const self = (a_trajpoly3 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly3_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    pos = a_trajpoly3_pos(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajpoly3_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real vel;
    a_trajpoly3 *const self = (a_trajpoly3 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly3_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    vel = a_trajpoly3_vel(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajpoly3_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real acc;
    a_trajpoly3 *const self = (a_trajpoly3 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly3_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    acc = a_trajpoly3_acc(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)acc);
}

enum
{
    self_c0,
    self_c1,
    self_c2
};

static JSValue liba_trajpoly3_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_trajpoly3 *const self = (a_trajpoly3 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly3_class_id);
    a_real c[A_LEN(self->c) - 1];
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_c0: return js_array_num_new(ctx, self->c, A_LEN(self->c));
    case self_c1:
        a_trajpoly3_c1(self, c);
        return js_array_num_new(ctx, c, A_LEN(self->c) - 1);
    case self_c2:
        a_trajpoly3_c2(self, c);
        return js_array_num_new(ctx, c, A_LEN(self->c) - 2);
    default: return JS_UNDEFINED;
    }
}

static JSClassDef liba_trajpoly3_class;
static JSCFunctionListEntry const liba_trajpoly3_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajpoly3", 0),
    JS_CGETSET_MAGIC_DEF("c0", liba_trajpoly3_get, NULL, self_c0),
    JS_CGETSET_MAGIC_DEF("c1", liba_trajpoly3_get, NULL, self_c1),
    JS_CGETSET_MAGIC_DEF("c2", liba_trajpoly3_get, NULL, self_c2),
    JS_CFUNC_DEF("gen", 5, liba_trajpoly3_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajpoly3_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajpoly3_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajpoly3_acc),
};

int js_liba_trajpoly3_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_trajpoly3_class.class_name = "trajpoly3";
    liba_trajpoly3_class.finalizer = liba_trajpoly3_finalizer;

    JS_NewClassID(&liba_trajpoly3_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajpoly3_class_id, &liba_trajpoly3_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajpoly3_proto, A_LEN(liba_trajpoly3_proto));

    clazz = JS_NewCFunction2(ctx, liba_trajpoly3_ctor, "trajpoly3", 5, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_trajpoly3_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "trajpoly3", clazz);
}
