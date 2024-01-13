#include "a.h"
#include "a/polytraj3.h"

static JSClassID liba_polytraj3_class_id;

static void liba_polytraj3_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_polytraj3_class_id));
}

static JSClassDef liba_polytraj3_class = {"polytraj3", .finalizer = liba_polytraj3_finalizer};

static JSValue liba_polytraj3_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_polytraj3 *const self = (a_polytraj3 *)js_mallocz(ctx, sizeof(a_polytraj3));
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { goto fail; }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { goto fail; }
    }
    a_polytraj3_gen(self,
                    (a_float)args[0], (a_float)args[1],
                    (a_float)args[2], (a_float)args[3],
                    (a_float)args[4], (a_float)args[5]);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_polytraj3_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_polytraj3_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_polytraj3 *const self = (a_polytraj3 *)JS_GetOpaque2(ctx, this_val, liba_polytraj3_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case 0: return js_array_num_new(ctx, self->q, A_LEN(self->q));
    case 1: return js_array_num_new(ctx, self->v, A_LEN(self->v));
    case 2: return js_array_num_new(ctx, self->a, A_LEN(self->a));
    default: return JS_UNDEFINED;
    }
}

static JSValue liba_polytraj3_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_polytraj3 *const self = (a_polytraj3 *)JS_GetOpaque2(ctx, this_val, liba_polytraj3_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_polytraj3_gen(self,
                    (a_float)args[0], (a_float)args[1],
                    (a_float)args[2], (a_float)args[3],
                    (a_float)args[4], (a_float)args[5]);
    return JS_UNDEFINED;
}

static JSValue liba_polytraj3_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj3 *const self = (a_polytraj3 *)JS_GetOpaque2(ctx, this_val, liba_polytraj3_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float pos = a_polytraj3_pos(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_polytraj3_vel(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj3 *const self = (a_polytraj3 *)JS_GetOpaque2(ctx, this_val, liba_polytraj3_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float vel = a_polytraj3_vel(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_polytraj3_acc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj3 *const self = (a_polytraj3 *)JS_GetOpaque2(ctx, this_val, liba_polytraj3_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float acc = a_polytraj3_acc(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const liba_polytraj3_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.polytraj3", 0),
    JS_CGETSET_MAGIC_DEF("q", liba_polytraj3_get, NULL, 0),
    JS_CGETSET_MAGIC_DEF("v", liba_polytraj3_get, NULL, 1),
    JS_CGETSET_MAGIC_DEF("a", liba_polytraj3_get, NULL, 2),
    JS_CFUNC_DEF("gen", 6, liba_polytraj3_gen),
    JS_CFUNC_DEF("pos", 1, liba_polytraj3_pos),
    JS_CFUNC_DEF("vel", 1, liba_polytraj3_vel),
    JS_CFUNC_DEF("acc", 1, liba_polytraj3_acc),
};

int js_liba_polytraj3_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&liba_polytraj3_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_polytraj3_class_id, &liba_polytraj3_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_polytraj3_proto, A_LEN(liba_polytraj3_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_polytraj3_ctor, "polytraj3", 6, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_polytraj3_class_id, proto);

    return JS_SetModuleExport(ctx, m, "polytraj3", clazz);
}
