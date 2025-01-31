#include "a.h"
#include "a/pid_neuro.h"

static JSClassID liba_pid_neuro_class_id;

static void liba_pid_neuro_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_pid_neuro_class_id));
}

static JSValue liba_pid_neuro_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_pid_neuro *const self = (a_pid_neuro *)js_mallocz(ctx, sizeof(a_pid_neuro));
    if (!self) { return JS_EXCEPTION; }
    self->pid.summax = +A_REAL_INF;
    self->pid.summin = -A_REAL_INF;
    self->pid.outmax = +A_REAL_INF;
    self->pid.outmin = -A_REAL_INF;
    self->k = self->pid.kp = 1;
    self->wp = A_REAL_C(0.1);
    self->wi = A_REAL_C(0.1);
    self->wd = A_REAL_C(0.1);
    a_pid_neuro_init(self);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_pid_neuro_class_id);
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

static JSValue liba_pid_neuro_set_kpid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int i;
    double arg[] = {0, 0, 0, 0};
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_pid_neuro_set_kpid(self, (a_real)arg[0], (a_real)arg[1], (a_real)arg[2], (a_real)arg[3]);
    (void)argc;
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuro_set_wpid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int i;
    double arg[] = {0, 0, 0};
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_pid_neuro_set_wpid(self, (a_real)arg[0], (a_real)arg[1], (a_real)arg[2]);
    (void)argc;
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuro_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_pid_neuro_zero(self);
    (void)argc;
    (void)argv;
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuro_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int i;
    double arg[] = {0, 0};
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)argc;
    return JS_NewFloat64(ctx, (double)a_pid_neuro_run(self, (a_real)arg[0], (a_real)arg[1]));
}

static JSValue liba_pid_neuro_inc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int i;
    double arg[] = {0, 0};
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)argc;
    return JS_NewFloat64(ctx, (double)a_pid_neuro_inc(self, (a_real)arg[0], (a_real)arg[1]));
}

enum
{
    self_k,
    self_kp,
    self_ki,
    self_kd,
    self_wp,
    self_wi,
    self_wd,
    self_outmax,
    self_outmin,
    self_out,
    self_fdb,
    self_err,
    self_ec
};

static JSValue liba_pid_neuro_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    double x;
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_k: x = (double)self->k; break;
    case self_kp: x = (double)self->pid.kp; break;
    case self_ki: x = (double)self->pid.ki; break;
    case self_kd: x = (double)self->pid.kd; break;
    case self_wp: x = (double)self->wp; break;
    case self_wi: x = (double)self->wi; break;
    case self_wd: x = (double)self->wd; break;
    case self_outmax: x = (double)self->pid.outmax; break;
    case self_outmin: x = (double)self->pid.outmin; break;
    case self_out: x = (double)self->pid.out; break;
    case self_fdb: x = (double)self->pid.fdb; break;
    case self_err: x = (double)self->pid.err; break;
    case self_ec: x = (double)self->ec; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_pid_neuro_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    double x;
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToFloat64(ctx, &x, val)) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_k: self->k = (a_real)x; break;
    case self_kp: self->pid.kp = (a_real)x; break;
    case self_ki: self->pid.ki = (a_real)x; break;
    case self_kd: self->pid.kd = (a_real)x; break;
    case self_wp: self->wp = (a_real)x; break;
    case self_wi: self->wi = (a_real)x; break;
    case self_wd: self->wd = (a_real)x; break;
    case self_outmax: self->pid.outmax = (a_real)x; break;
    case self_outmin: self->pid.outmin = (a_real)x; break;
    default: break;
    }
    return JS_UNDEFINED;
}

static JSClassDef liba_pid_neuro_class;
static JSCFunctionListEntry const liba_pid_neuro_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid.neuron", 0),
    JS_CGETSET_MAGIC_DEF("k", liba_pid_neuro_get, liba_pid_neuro_set, self_k),
    JS_CGETSET_MAGIC_DEF("kp", liba_pid_neuro_get, liba_pid_neuro_set, self_kp),
    JS_CGETSET_MAGIC_DEF("ki", liba_pid_neuro_get, liba_pid_neuro_set, self_ki),
    JS_CGETSET_MAGIC_DEF("kd", liba_pid_neuro_get, liba_pid_neuro_set, self_kd),
    JS_CGETSET_MAGIC_DEF("wp", liba_pid_neuro_get, liba_pid_neuro_set, self_wp),
    JS_CGETSET_MAGIC_DEF("wi", liba_pid_neuro_get, liba_pid_neuro_set, self_wi),
    JS_CGETSET_MAGIC_DEF("wd", liba_pid_neuro_get, liba_pid_neuro_set, self_wd),
    JS_CGETSET_MAGIC_DEF("outmax", liba_pid_neuro_get, liba_pid_neuro_set, self_outmax),
    JS_CGETSET_MAGIC_DEF("outmin", liba_pid_neuro_get, liba_pid_neuro_set, self_outmin),
    JS_CGETSET_MAGIC_DEF("out", liba_pid_neuro_get, NULL, self_out),
    JS_CGETSET_MAGIC_DEF("fdb", liba_pid_neuro_get, NULL, self_fdb),
    JS_CGETSET_MAGIC_DEF("err", liba_pid_neuro_get, NULL, self_err),
    JS_CGETSET_MAGIC_DEF("ec", liba_pid_neuro_get, NULL, self_ec),
    JS_CFUNC_DEF("set_kpid", 4, liba_pid_neuro_set_kpid),
    JS_CFUNC_DEF("set_wpid", 3, liba_pid_neuro_set_wpid),
    JS_CFUNC_DEF("zero", 0, liba_pid_neuro_zero),
    JS_CFUNC_DEF("run", 2, liba_pid_neuro_run),
    JS_CFUNC_DEF("inc", 2, liba_pid_neuro_inc),
};

int js_liba_pid_neuro_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_pid_neuro_class.class_name = "pid_neuro";
    liba_pid_neuro_class.finalizer = liba_pid_neuro_finalizer;

    JS_NewClassID(&liba_pid_neuro_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_pid_neuro_class_id, &liba_pid_neuro_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_pid_neuro_proto, A_LEN(liba_pid_neuro_proto));

    clazz = JS_NewCFunction2(ctx, liba_pid_neuro_ctor, "pid_neuro", 3, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_pid_neuro_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "pid_neuro", clazz);
}
