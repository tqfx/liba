#include "a.h"
#include "a/trajbell.h"

static JSClassID liba_trajbell_class_id;

static void liba_trajbell_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_trajbell_class_id));
}

static JSValue liba_trajbell_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
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
    (void)argc;
    (void)argv;
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_trajbell_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg[] = {0, 0, 0, 0, 0, 0, 0};
    int i = (int)A_LEN(arg);
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
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
    arg[0] = (double)a_trajbell_gen(self, (a_float)arg[0], (a_float)arg[1], (a_float)arg[2],
                                    (a_float)arg[3], (a_float)arg[4], (a_float)arg[5], (a_float)arg[6]);
    return JS_NewFloat64(ctx, arg[0]);
}

static JSValue liba_trajbell_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_float pos;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    pos = a_trajbell_pos(self, (a_float)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_trajbell_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_float vel;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    vel = a_trajbell_vel(self, (a_float)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_trajbell_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_float acc;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    acc = a_trajbell_acc(self, (a_float)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)acc);
}

static JSValue liba_trajbell_jer(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double x;
    a_float acc;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, argv[0])) { return JS_EXCEPTION; }
    acc = a_trajbell_jer(self, (a_float)x);
    (void)argc;
    return JS_NewFloat64(ctx, (double)acc);
}

enum
{
    self_t,
    self_tv,
    self_ta,
    self_td,
    self_taj,
    self_tdj,
    self_p0,
    self_p1,
    self_v0,
    self_v1,
    self_vm,
    self_jm,
    self_am,
    self_dm
};

static JSValue liba_trajbell_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    double x;
    a_trajbell *const self = (a_trajbell *)JS_GetOpaque2(ctx, this_val, liba_trajbell_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_t: x = (double)self->t; break;
    case self_tv: x = (double)self->tv; break;
    case self_ta: x = (double)self->ta; break;
    case self_td: x = (double)self->td; break;
    case self_taj: x = (double)self->taj; break;
    case self_tdj: x = (double)self->tdj; break;
    case self_p0: x = (double)self->p0; break;
    case self_p1: x = (double)self->p1; break;
    case self_v0: x = (double)self->v0; break;
    case self_v1: x = (double)self->v1; break;
    case self_vm: x = (double)self->vm; break;
    case self_jm: x = (double)self->jm; break;
    case self_am: x = (double)self->am; break;
    case self_dm: x = (double)self->dm; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSClassDef liba_trajbell_class;
static JSCFunctionListEntry const liba_trajbell_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.trajbell", 0),
    JS_CGETSET_MAGIC_DEF("t", liba_trajbell_get, NULL, self_t),
    JS_CGETSET_MAGIC_DEF("tv", liba_trajbell_get, NULL, self_tv),
    JS_CGETSET_MAGIC_DEF("ta", liba_trajbell_get, NULL, self_ta),
    JS_CGETSET_MAGIC_DEF("td", liba_trajbell_get, NULL, self_td),
    JS_CGETSET_MAGIC_DEF("taj", liba_trajbell_get, NULL, self_taj),
    JS_CGETSET_MAGIC_DEF("tdj", liba_trajbell_get, NULL, self_tdj),
    JS_CGETSET_MAGIC_DEF("p0", liba_trajbell_get, NULL, self_p0),
    JS_CGETSET_MAGIC_DEF("p1", liba_trajbell_get, NULL, self_p1),
    JS_CGETSET_MAGIC_DEF("v0", liba_trajbell_get, NULL, self_v0),
    JS_CGETSET_MAGIC_DEF("v1", liba_trajbell_get, NULL, self_v1),
    JS_CGETSET_MAGIC_DEF("vm", liba_trajbell_get, NULL, self_vm),
    JS_CGETSET_MAGIC_DEF("jm", liba_trajbell_get, NULL, self_jm),
    JS_CGETSET_MAGIC_DEF("am", liba_trajbell_get, NULL, self_am),
    JS_CGETSET_MAGIC_DEF("dm", liba_trajbell_get, NULL, self_dm),
    JS_CFUNC_DEF("gen", 7, liba_trajbell_gen),
    JS_CFUNC_DEF("pos", 1, liba_trajbell_pos),
    JS_CFUNC_DEF("vel", 1, liba_trajbell_vel),
    JS_CFUNC_DEF("acc", 1, liba_trajbell_acc),
    JS_CFUNC_DEF("jer", 1, liba_trajbell_jer),
};

int js_liba_trajbell_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_trajbell_class.class_name = "trajbell";
    liba_trajbell_class.finalizer = liba_trajbell_finalizer;

    JS_NewClassID(&liba_trajbell_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_trajbell_class_id, &liba_trajbell_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_trajbell_proto, A_LEN(liba_trajbell_proto));

    clazz = JS_NewCFunction2(ctx, liba_trajbell_ctor, "trajbell", 0, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_trajbell_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "trajbell", clazz);
}
