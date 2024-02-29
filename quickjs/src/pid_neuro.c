#include "a.h"
#include "a/pid_neuro.h"

static JSClassID liba_pid_neuro_class_id;

static void liba_pid_neuro_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_pid_neuro_class_id));
}

static JSClassDef liba_pid_neuro_class = {"pid_neuro", .finalizer = liba_pid_neuro_finalizer};

static JSValue liba_pid_neuro_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    JSValue proto, clazz = JS_UNDEFINED;
    a_pid_neuro *const self = (a_pid_neuro *)js_mallocz(ctx, sizeof(a_pid_neuro));
    if (!self) { return JS_EXCEPTION; }
    self->pid.summax = +A_FLOAT_INF;
    self->pid.summin = -A_FLOAT_INF;
    self->pid.outmax = +A_FLOAT_INF;
    self->pid.outmin = -A_FLOAT_INF;
    self->k = self->pid.kp = 1;
    self->wp = A_FLOAT_C(0.1);
    self->wi = A_FLOAT_C(0.1);
    self->wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(self);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_pid_neuro_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_pid_neuro_kpid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_pid_neuro_kpid(self, (a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3]);
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuro_wpid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_pid_neuro_wpid(self, (a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuro_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_pid_neuro_zero(self);
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuro_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_neuro_run(self, (a_float)args[0], (a_float)args[1]));
}

static JSValue liba_pid_neuro_inc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_neuro_inc(self, (a_float)args[0], (a_float)args[1]));
}

enum
{
    self_k_,
    self_kp_,
    self_ki_,
    self_kd_,
    self_wp_,
    self_wi_,
    self_wd_,
    self_outmax_,
    self_outmin_,
    self_out_,
    self_fdb_,
    self_err_,
    self_ec_,
};

static JSValue liba_pid_neuro_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case self_k_: x = (double)self->k; break;
    case self_kp_: x = (double)self->pid.kp; break;
    case self_ki_: x = (double)self->pid.ki; break;
    case self_kd_: x = (double)self->pid.kd; break;
    case self_wp_: x = (double)self->wp; break;
    case self_wi_: x = (double)self->wi; break;
    case self_wd_: x = (double)self->wd; break;
    case self_outmax_: x = (double)self->pid.outmax; break;
    case self_outmin_: x = (double)self->pid.outmin; break;
    case self_out_: x = (double)self->pid.out; break;
    case self_fdb_: x = (double)self->pid.fdb; break;
    case self_err_: x = (double)self->pid.err; break;
    case self_ec_: x = (double)self->ec; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_pid_neuro_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    a_pid_neuro *const self = (a_pid_neuro *)JS_GetOpaque2(ctx, this_val, liba_pid_neuro_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, val)) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_k_: self->k = (a_float)x; break;
    case self_kp_: self->pid.kp = (a_float)x; break;
    case self_ki_: self->pid.ki = (a_float)x; break;
    case self_kd_: self->pid.kd = (a_float)x; break;
    case self_wp_: self->wp = (a_float)x; break;
    case self_wi_: self->wi = (a_float)x; break;
    case self_wd_: self->wd = (a_float)x; break;
    case self_outmax_: self->pid.outmax = (a_float)x; break;
    case self_outmin_: self->pid.outmin = (a_float)x; break;
    default: break;
    }
    return JS_UNDEFINED;
}

static JSCFunctionListEntry const liba_pid_neuro_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid.neuron", 0),
    JS_CGETSET_MAGIC_DEF("k", liba_pid_neuro_get, liba_pid_neuro_set, self_k_),
    JS_CGETSET_MAGIC_DEF("kp", liba_pid_neuro_get, liba_pid_neuro_set, self_kp_),
    JS_CGETSET_MAGIC_DEF("ki", liba_pid_neuro_get, liba_pid_neuro_set, self_ki_),
    JS_CGETSET_MAGIC_DEF("kd", liba_pid_neuro_get, liba_pid_neuro_set, self_kd_),
    JS_CGETSET_MAGIC_DEF("wp", liba_pid_neuro_get, liba_pid_neuro_set, self_wp_),
    JS_CGETSET_MAGIC_DEF("wi", liba_pid_neuro_get, liba_pid_neuro_set, self_wi_),
    JS_CGETSET_MAGIC_DEF("wd", liba_pid_neuro_get, liba_pid_neuro_set, self_wd_),
    JS_CGETSET_MAGIC_DEF("outmax", liba_pid_neuro_get, liba_pid_neuro_set, self_outmax_),
    JS_CGETSET_MAGIC_DEF("outmin", liba_pid_neuro_get, liba_pid_neuro_set, self_outmin_),
    JS_CGETSET_MAGIC_DEF("out", liba_pid_neuro_get, NULL, self_out_),
    JS_CGETSET_MAGIC_DEF("fdb", liba_pid_neuro_get, NULL, self_fdb_),
    JS_CGETSET_MAGIC_DEF("err", liba_pid_neuro_get, NULL, self_err_),
    JS_CGETSET_MAGIC_DEF("ec", liba_pid_neuro_get, NULL, self_ec_),
    JS_CFUNC_DEF("kpid", 4, liba_pid_neuro_kpid),
    JS_CFUNC_DEF("wpid", 3, liba_pid_neuro_wpid),
    JS_CFUNC_DEF("zero", 0, liba_pid_neuro_zero),
    JS_CFUNC_DEF("run", 2, liba_pid_neuro_run),
    JS_CFUNC_DEF("inc", 2, liba_pid_neuro_inc),
};

int js_liba_pid_neuro_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_pid_neuro_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_pid_neuro_class_id, &liba_pid_neuro_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_pid_neuro_proto, A_LEN(liba_pid_neuro_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_pid_neuro_ctor, "pid_neuro", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_pid_neuro_class_id, proto);

    return JS_SetModuleExport(ctx, m, "pid_neuro", clazz);
}
