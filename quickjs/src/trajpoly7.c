#include "a.h"
#include "a/trajpoly7.h"

static JSClassID liba_trajpoly7_class_id;

static void liba_trajpoly7_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajpoly7_class_id));
}

static JSValue liba_trajpoly7_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    JSValue proto, clazz = JS_UNDEFINED;
    a_trajpoly7 *const self = (a_trajpoly7 *)js_mallocz(ctx, sizeof(a_trajpoly7));
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
    a_trajpoly7_gen(self, (a_real)arg[0],
                    (a_real)arg[1], (a_real)arg[2],
                    (a_real)arg[3], (a_real)arg[4],
                    (a_real)arg[5], (a_real)arg[6],
                    (a_real)arg[7], (a_real)arg[8]);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_trajpoly7_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_trajpoly7_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    a_trajpoly7 *const self = (a_trajpoly7 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly7_class_id);
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
    a_trajpoly7_gen(self, (a_real)arg[0],
                    (a_real)arg[1], (a_real)arg[2],
                    (a_real)arg[3], (a_real)arg[4],
                    (a_real)arg[5], (a_real)arg[6],
                    (a_real)arg[7], (a_real)arg[8]);
    return JS_UNDEFINED;
}

static JSValue liba_trajpoly7_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real pos;
    a_trajpoly7 *const self = (a_trajpoly7 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly7_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    pos = a_trajpoly7_pos(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajpoly7_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real vel;
    a_trajpoly7 *const self = (a_trajpoly7 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly7_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    vel = a_trajpoly7_vel(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajpoly7_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real acc;
    a_trajpoly7 *const self = (a_trajpoly7 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly7_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    acc = a_trajpoly7_acc(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)acc);
}

static JSValue liba_trajpoly7_jer(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_real jer;
    a_trajpoly7 *const self = (a_trajpoly7 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly7_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    jer = a_trajpoly7_jer(self, (a_real)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)jer);
}

enum
{
    trajpoly7_c0,
    trajpoly7_c1,
    trajpoly7_c2,
    trajpoly7_c3
};

static JSValue liba_trajpoly7_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_trajpoly7 *const self = (a_trajpoly7 *)JS_GetOpaque2(ctx, this_val, liba_trajpoly7_class_id);
    a_real c[A_LEN(self->c) - 1];
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case trajpoly7_c0: return js_array_num_new(ctx, self->c, A_LEN(self->c));
    case trajpoly7_c1:
        a_trajpoly7_c1(self, c);
        return js_array_num_new(ctx, c, A_LEN(self->c) - 1);
    case trajpoly7_c2:
        a_trajpoly7_c2(self, c);
        return js_array_num_new(ctx, c, A_LEN(self->c) - 2);
    case trajpoly7_c3:
        a_trajpoly7_c3(self, c);
        return js_array_num_new(ctx, c, A_LEN(self->c) - 3);
    default: return JS_UNDEFINED;
    }
}

static JSClassDef liba_trajpoly7_class;
static JSCFunctionListEntry const liba_trajpoly7_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajpoly7", 0),
    JS_CGETSET_MAGIC_DEF("c0", liba_trajpoly7_get, NULL, trajpoly7_c0),
    JS_CGETSET_MAGIC_DEF("c1", liba_trajpoly7_get, NULL, trajpoly7_c1),
    JS_CGETSET_MAGIC_DEF("c2", liba_trajpoly7_get, NULL, trajpoly7_c2),
    JS_CGETSET_MAGIC_DEF("c3", liba_trajpoly7_get, NULL, trajpoly7_c3),
    JS_CFUNC_DEF("gen", 9, liba_trajpoly7_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajpoly7_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajpoly7_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajpoly7_acc),
    JS_CFUNC_DEF("jer", 1, liba_trajpoly7_jer),
};

int js_liba_trajpoly7_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_trajpoly7_class.class_name = "trajpoly7";
    liba_trajpoly7_class.finalizer = liba_trajpoly7_finalizer;

    JS_NewClassID(&liba_trajpoly7_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajpoly7_class_id, &liba_trajpoly7_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajpoly7_proto, A_LEN(liba_trajpoly7_proto));

    clazz = JS_NewCFunction2(ctx, liba_trajpoly7_ctor, "trajpoly7", 9, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_trajpoly7_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "trajpoly7", clazz);
}
