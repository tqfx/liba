#include "a.h"
#include "a/trajbell.h"

static JSClassID liba_trajbell_class_id;

static void liba_trajbell_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajbell_class_id));
}

static JSClassDef liba_trajbell_class = {"trajbell", .finalizer = liba_trajbell_finalizer};

static JSValue liba_trajbell_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    JSValue proto, clazz = JS_UNDEFINED;
    a_trajbell *const self = (a_trajbell *)js_mallocz(ctx, sizeof(a_trajbell));
    if (!self) { return JS_EXCEPTION; }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_trajbell_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_trajbell_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
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
    args[0] = (double)a_trajbell_gen(self, (a_float)args[0], (a_float)args[1], (a_float)args[2],
                                     (a_float)args[3], (a_float)args[4], (a_float)args[5], (a_float)args[6]);
    return JS_NewFloat64(ctx, args[0]);
}

static JSValue liba_trajbell_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float pos = a_trajbell_pos(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajbell_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float vel = a_trajbell_vel(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajbell_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float acc = a_trajbell_acc(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSValue liba_trajbell_jer(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float acc = a_trajbell_jer(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

enum
{
    self_t_,
    self_tv_,
    self_ta_,
    self_td_,
    self_taj_,
    self_tdj_,
    self_p0_,
    self_p1_,
    self_v0_,
    self_v1_,
    self_vm_,
    self_jm_,
    self_am_,
    self_dm_,
};

static JSValue liba_trajbell_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case self_t_: x = (double)self->t; break;
    case self_tv_: x = (double)self->tv; break;
    case self_ta_: x = (double)self->ta; break;
    case self_td_: x = (double)self->td; break;
    case self_taj_: x = (double)self->taj; break;
    case self_tdj_: x = (double)self->tdj; break;
    case self_p0_: x = (double)self->p0; break;
    case self_p1_: x = (double)self->p1; break;
    case self_v0_: x = (double)self->v0; break;
    case self_v1_: x = (double)self->v1; break;
    case self_vm_: x = (double)self->vm; break;
    case self_jm_: x = (double)self->jm; break;
    case self_am_: x = (double)self->am; break;
    case self_dm_: x = (double)self->dm; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSCFunctionListEntry const liba_trajbell_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajbell", 0),
    JS_CGETSET_MAGIC_DEF("t", liba_trajbell_get, NULL, self_t_),
    JS_CGETSET_MAGIC_DEF("tv", liba_trajbell_get, NULL, self_tv_),
    JS_CGETSET_MAGIC_DEF("ta", liba_trajbell_get, NULL, self_ta_),
    JS_CGETSET_MAGIC_DEF("td", liba_trajbell_get, NULL, self_td_),
    JS_CGETSET_MAGIC_DEF("taj", liba_trajbell_get, NULL, self_taj_),
    JS_CGETSET_MAGIC_DEF("tdj", liba_trajbell_get, NULL, self_tdj_),
    JS_CGETSET_MAGIC_DEF("p0", liba_trajbell_get, NULL, self_p0_),
    JS_CGETSET_MAGIC_DEF("p1", liba_trajbell_get, NULL, self_p1_),
    JS_CGETSET_MAGIC_DEF("v0", liba_trajbell_get, NULL, self_v0_),
    JS_CGETSET_MAGIC_DEF("v1", liba_trajbell_get, NULL, self_v1_),
    JS_CGETSET_MAGIC_DEF("vm", liba_trajbell_get, NULL, self_vm_),
    JS_CGETSET_MAGIC_DEF("jm", liba_trajbell_get, NULL, self_jm_),
    JS_CGETSET_MAGIC_DEF("am", liba_trajbell_get, NULL, self_am_),
    JS_CGETSET_MAGIC_DEF("dm", liba_trajbell_get, NULL, self_dm_),
    JS_CFUNC_DEF("gen", 7, liba_trajbell_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajbell_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajbell_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajbell_acc),
    JS_CFUNC_DEF("jer", 1, liba_trajbell_jer),
};

int js_liba_trajbell_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_trajbell_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajbell_class_id, &liba_trajbell_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajbell_proto, A_LEN(liba_trajbell_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_trajbell_ctor, "trajbell", 0, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_trajbell_class_id, proto);

    return JS_SetModuleExport(ctx, m, "trajbell", clazz);
}
