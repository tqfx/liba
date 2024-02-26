#include "a.h"
#include "a/trajtrap.h"

static JSClassID liba_trajtrap_class_id;

static void liba_trajtrap_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajtrap_class_id));
}

static JSClassDef liba_trajtrap_class = {"trajtrap", .finalizer = liba_trajtrap_finalizer};

static JSValue liba_trajtrap_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    JSValue proto, clazz = JS_UNDEFINED;
    a_trajtrap *const self = (a_trajtrap *)js_mallocz(ctx, sizeof(a_trajtrap));
    if (!self) { return JS_EXCEPTION; }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_trajtrap_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

enum
{
    self_t_,
    self_p0_,
    self_p1_,
    self_v0_,
    self_v1_,
    self_vc_,
    self_ta_,
    self_td_,
    self_pa_,
    self_pd_,
    self_ac_,
    self_de_,
};

static JSValue liba_trajtrap_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case self_t_: x = (double)self->t; break;
    case self_p0_: x = (double)self->p0; break;
    case self_p1_: x = (double)self->p1; break;
    case self_v0_: x = (double)self->v0; break;
    case self_v1_: x = (double)self->v1; break;
    case self_vc_: x = (double)self->vc; break;
    case self_ta_: x = (double)self->ta; break;
    case self_td_: x = (double)self->td; break;
    case self_pa_: x = (double)self->pa; break;
    case self_pd_: x = (double)self->pd; break;
    case self_ac_: x = (double)self->ac; break;
    case self_de_: x = (double)self->de; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_trajtrap_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < 5; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    for (int i = 5; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    args[0] = (double)a_trajtrap_gen(self, (a_float)args[0], (a_float)args[1], (a_float)args[2],
                                     (a_float)args[3], (a_float)args[4], (a_float)args[5], (a_float)args[6]);
    return JS_NewFloat64(ctx, args[0]);
}

static JSValue liba_trajtrap_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float pos = a_trajtrap_pos(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajtrap_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float vel = a_trajtrap_vel(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajtrap_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float acc = a_trajtrap_acc(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const liba_trajtrap_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajtrap", 0),
    JS_CGETSET_MAGIC_DEF("t", liba_trajtrap_get, NULL, self_t_),
    JS_CGETSET_MAGIC_DEF("p0", liba_trajtrap_get, NULL, self_p0_),
    JS_CGETSET_MAGIC_DEF("p1", liba_trajtrap_get, NULL, self_p1_),
    JS_CGETSET_MAGIC_DEF("v0", liba_trajtrap_get, NULL, self_v0_),
    JS_CGETSET_MAGIC_DEF("v1", liba_trajtrap_get, NULL, self_v1_),
    JS_CGETSET_MAGIC_DEF("vc", liba_trajtrap_get, NULL, self_vc_),
    JS_CGETSET_MAGIC_DEF("ta", liba_trajtrap_get, NULL, self_ta_),
    JS_CGETSET_MAGIC_DEF("td", liba_trajtrap_get, NULL, self_td_),
    JS_CGETSET_MAGIC_DEF("pa", liba_trajtrap_get, NULL, self_pa_),
    JS_CGETSET_MAGIC_DEF("pd", liba_trajtrap_get, NULL, self_pd_),
    JS_CGETSET_MAGIC_DEF("ac", liba_trajtrap_get, NULL, self_ac_),
    JS_CGETSET_MAGIC_DEF("de", liba_trajtrap_get, NULL, self_de_),
    JS_CFUNC_DEF("gen", 7, liba_trajtrap_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajtrap_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajtrap_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajtrap_acc),
};

int js_liba_trajtrap_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_trajtrap_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajtrap_class_id, &liba_trajtrap_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajtrap_proto, A_LEN(liba_trajtrap_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_trajtrap_ctor, "trajtrap", 0, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_trajtrap_class_id, proto);

    return JS_SetModuleExport(ctx, m, "trajtrap", clazz);
}
