#include "a.h"
#include "a/trajtrap.h"

static JSClassID liba_trajtrap_class_id;

static void liba_trajtrap_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajtrap_class_id));
}

static JSValue liba_trajtrap_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
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
    (void)argc;
    (void)argv;
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_trajtrap_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (argc > i) { argc = i; }
    for (i = 0; i < 5; ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    for (i = 5; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    arg[0] = (double)a_trajtrap_gen(self, (a_float)arg[0], (a_float)arg[1], (a_float)arg[2],
                                    (a_float)arg[3], (a_float)arg[4], (a_float)arg[5], (a_float)arg[6]);
    return JS_NewFloat64(ctx, arg[0]);
}

static JSValue liba_trajtrap_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_float pos;
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    pos = a_trajtrap_pos(self, (a_float)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajtrap_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_float vel;
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    vel = a_trajtrap_vel(self, (a_float)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajtrap_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_float acc;
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    acc = a_trajtrap_acc(self, (a_float)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)acc);
}

enum
{
    self_t,
    self_p0,
    self_p1,
    self_v0,
    self_v1,
    self_vc,
    self_ta,
    self_td,
    self_pa,
    self_pd,
    self_ac,
    self_de
};

static JSValue liba_trajtrap_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    double x;
    a_trajtrap *const self = (a_trajtrap *)JS_GetOpaque2(ctx, this_val, liba_trajtrap_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_t: x = (double)self->t; break;
    case self_p0: x = (double)self->p0; break;
    case self_p1: x = (double)self->p1; break;
    case self_v0: x = (double)self->v0; break;
    case self_v1: x = (double)self->v1; break;
    case self_vc: x = (double)self->vc; break;
    case self_ta: x = (double)self->ta; break;
    case self_td: x = (double)self->td; break;
    case self_pa: x = (double)self->pa; break;
    case self_pd: x = (double)self->pd; break;
    case self_ac: x = (double)self->ac; break;
    case self_de: x = (double)self->de; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSClassDef liba_trajtrap_class;
static JSCFunctionListEntry const liba_trajtrap_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajtrap", 0),
    JS_CGETSET_MAGIC_DEF("t", liba_trajtrap_get, NULL, self_t),
    JS_CGETSET_MAGIC_DEF("p0", liba_trajtrap_get, NULL, self_p0),
    JS_CGETSET_MAGIC_DEF("p1", liba_trajtrap_get, NULL, self_p1),
    JS_CGETSET_MAGIC_DEF("v0", liba_trajtrap_get, NULL, self_v0),
    JS_CGETSET_MAGIC_DEF("v1", liba_trajtrap_get, NULL, self_v1),
    JS_CGETSET_MAGIC_DEF("vc", liba_trajtrap_get, NULL, self_vc),
    JS_CGETSET_MAGIC_DEF("ta", liba_trajtrap_get, NULL, self_ta),
    JS_CGETSET_MAGIC_DEF("td", liba_trajtrap_get, NULL, self_td),
    JS_CGETSET_MAGIC_DEF("pa", liba_trajtrap_get, NULL, self_pa),
    JS_CGETSET_MAGIC_DEF("pd", liba_trajtrap_get, NULL, self_pd),
    JS_CGETSET_MAGIC_DEF("ac", liba_trajtrap_get, NULL, self_ac),
    JS_CGETSET_MAGIC_DEF("de", liba_trajtrap_get, NULL, self_de),
    JS_CFUNC_DEF("gen", 7, liba_trajtrap_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajtrap_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajtrap_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajtrap_acc),
};

int js_liba_trajtrap_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_trajtrap_class.class_name = "trajtrap";
    liba_trajtrap_class.finalizer = liba_trajtrap_finalizer;

    JS_NewClassID(&liba_trajtrap_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajtrap_class_id, &liba_trajtrap_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajtrap_proto, A_LEN(liba_trajtrap_proto));

    clazz = JS_NewCFunction2(ctx, liba_trajtrap_ctor, "trajtrap", 0, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_trajtrap_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "trajtrap", clazz);
}
