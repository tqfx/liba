#include "a.h"
#include "a/traptraj.h"

static JSClassID liba_traptraj_class_id;

static void liba_traptraj_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_traptraj_class_id));
}

static JSClassDef liba_traptraj_class = {"traptraj", .finalizer = liba_traptraj_finalizer};

static JSValue liba_traptraj_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_traptraj *const self = (a_traptraj *)js_mallocz(ctx, sizeof(a_traptraj));
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
    args[0] = (double)a_traptraj_gen(self, (a_float)args[0], (a_float)args[1], (a_float)args[2],
                                     (a_float)args[3], (a_float)args[4], (a_float)args[5]);
    if (args[0] <= 0) { goto fail; }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_traptraj_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_traptraj_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_traptraj *const self = (a_traptraj *)JS_GetOpaque2(ctx, this_val, liba_traptraj_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case 0: x = (double)self->ac; break;
    case 1: x = (double)self->de; break;
    case 2: x = (double)self->ta; break;
    case 3: x = (double)self->qa; break;
    case 4: x = (double)self->tc; break;
    case 5: x = (double)self->qc; break;
    case 6: x = (double)self->td; break;
    case 7: x = (double)self->qd; break;
    case 8: x = (double)self->vs; break;
    case 9: x = (double)self->vc; break;
    case 10: x = (double)self->ve; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_traptraj_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_traptraj *const self = (a_traptraj *)JS_GetOpaque2(ctx, this_val, liba_traptraj_class_id);
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
    args[0] = (double)a_traptraj_gen(self, (a_float)args[0], (a_float)args[1], (a_float)args[2],
                                     (a_float)args[3], (a_float)args[4], (a_float)args[5]);
    return JS_NewFloat64(ctx, args[0]);
}

static JSValue liba_traptraj_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_traptraj *const self = (a_traptraj *)JS_GetOpaque2(ctx, this_val, liba_traptraj_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float pos = a_traptraj_pos(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_traptraj_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_traptraj *const self = (a_traptraj *)JS_GetOpaque2(ctx, this_val, liba_traptraj_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float vel = a_traptraj_vel(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_traptraj_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_traptraj *const self = (a_traptraj *)JS_GetOpaque2(ctx, this_val, liba_traptraj_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float acc = a_traptraj_acc(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const liba_traptraj_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.traptraj", 0),
    JS_CGETSET_MAGIC_DEF("ac", liba_traptraj_get, NULL, 0),
    JS_CGETSET_MAGIC_DEF("de", liba_traptraj_get, NULL, 1),
    JS_CGETSET_MAGIC_DEF("ta", liba_traptraj_get, NULL, 2),
    JS_CGETSET_MAGIC_DEF("qa", liba_traptraj_get, NULL, 3),
    JS_CGETSET_MAGIC_DEF("tc", liba_traptraj_get, NULL, 4),
    JS_CGETSET_MAGIC_DEF("qc", liba_traptraj_get, NULL, 5),
    JS_CGETSET_MAGIC_DEF("td", liba_traptraj_get, NULL, 6),
    JS_CGETSET_MAGIC_DEF("qd", liba_traptraj_get, NULL, 7),
    JS_CGETSET_MAGIC_DEF("vs", liba_traptraj_get, NULL, 8),
    JS_CGETSET_MAGIC_DEF("vc", liba_traptraj_get, NULL, 9),
    JS_CGETSET_MAGIC_DEF("ve", liba_traptraj_get, NULL, 10),
    JS_CFUNC_DEF("gen", 6, liba_traptraj_gen),
    JS_CFUNC_DEF("pos", 1, liba_traptraj_pos),
    JS_CFUNC_DEF("vel", 1, liba_traptraj_vel),
    JS_CFUNC_DEF("acc", 1, liba_traptraj_acc),
};

int js_liba_traptraj_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_traptraj_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_traptraj_class_id, &liba_traptraj_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_traptraj_proto, A_LEN(liba_traptraj_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_traptraj_ctor, "traptraj", 6, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_traptraj_class_id, proto);

    return JS_SetModuleExport(ctx, m, "traptraj", clazz);
}
