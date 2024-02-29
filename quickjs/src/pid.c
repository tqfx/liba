#include "a.h"
#include "a/pid.h"

static JSClassID liba_pid_class_id;

static void liba_pid_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_pid_class_id));
}

static JSClassDef liba_pid_class = {"pid", .finalizer = liba_pid_finalizer};

static JSValue liba_pid_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    JSValue proto, clazz = JS_UNDEFINED;
    a_pid *const self = (a_pid *)js_mallocz(ctx, sizeof(a_pid));
    if (!self) { return JS_EXCEPTION; }
    self->kp = 1;
    self->summax = +A_FLOAT_INF;
    self->summin = -A_FLOAT_INF;
    self->outmax = +A_FLOAT_INF;
    self->outmin = -A_FLOAT_INF;
    a_pid_init(self);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_pid_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_pid_kpid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid *const self = (a_pid *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_pid_kpid(self, (a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_UNDEFINED;
}

static JSValue liba_pid_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    a_pid *const self = (a_pid *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_pid_zero(self);
    return JS_UNDEFINED;
}

static JSValue liba_pid_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid *const self = (a_pid *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_run(self, (a_float)args[0], (a_float)args[1]));
}

static JSValue liba_pid_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid *const self = (a_pid *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_pos(self, (a_float)args[0], (a_float)args[1]));
}

static JSValue liba_pid_inc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid *const self = (a_pid *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_inc(self, (a_float)args[0], (a_float)args[1]));
}

enum
{
    self_kp_,
    self_ki_,
    self_kd_,
    self_summax_,
    self_summin_,
    self_sum_,
    self_outmax_,
    self_outmin_,
    self_out_,
    self_fdb_,
    self_err_,
};

static JSValue liba_pid_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_pid *const self = (a_pid *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case self_kp_: x = (double)self->kp; break;
    case self_ki_: x = (double)self->ki; break;
    case self_kd_: x = (double)self->kd; break;
    case self_summax_: x = (double)self->summax; break;
    case self_summin_: x = (double)self->summin; break;
    case self_sum_: x = (double)self->sum; break;
    case self_outmax_: x = (double)self->outmax; break;
    case self_outmin_: x = (double)self->outmin; break;
    case self_out_: x = (double)self->out; break;
    case self_fdb_: x = (double)self->fdb; break;
    case self_err_: x = (double)self->err; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_pid_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    a_pid *const self = (a_pid *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    if (JS_ToFloat64(ctx, &x, val)) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_kp_: self->kp = (a_float)x; break;
    case self_ki_: self->ki = (a_float)x; break;
    case self_kd_: self->kd = (a_float)x; break;
    case self_summax_: self->summax = (a_float)x; break;
    case self_summin_: self->summin = (a_float)x; break;
    case self_outmax_: self->outmax = (a_float)x; break;
    case self_outmin_: self->outmin = (a_float)x; break;
    default: break;
    }
    return JS_UNDEFINED;
}

static JSCFunctionListEntry const liba_pid_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid", 0),
    JS_CGETSET_MAGIC_DEF("kp", liba_pid_get, liba_pid_set, self_kp_),
    JS_CGETSET_MAGIC_DEF("ki", liba_pid_get, liba_pid_set, self_ki_),
    JS_CGETSET_MAGIC_DEF("kd", liba_pid_get, liba_pid_set, self_kd_),
    JS_CGETSET_MAGIC_DEF("summax", liba_pid_get, liba_pid_set, self_summax_),
    JS_CGETSET_MAGIC_DEF("summin", liba_pid_get, liba_pid_set, self_summin_),
    JS_CGETSET_MAGIC_DEF("sum", liba_pid_get, NULL, self_sum_),
    JS_CGETSET_MAGIC_DEF("outmax", liba_pid_get, liba_pid_set, self_outmax_),
    JS_CGETSET_MAGIC_DEF("outmin", liba_pid_get, liba_pid_set, self_outmin_),
    JS_CGETSET_MAGIC_DEF("out", liba_pid_get, NULL, self_out_),
    JS_CGETSET_MAGIC_DEF("fdb", liba_pid_get, NULL, self_fdb_),
    JS_CGETSET_MAGIC_DEF("err", liba_pid_get, NULL, self_err_),
    JS_CFUNC_DEF("kpid", 3, liba_pid_kpid),
    JS_CFUNC_DEF("zero", 0, liba_pid_zero),
    JS_CFUNC_DEF("run", 2, liba_pid_run),
    JS_CFUNC_DEF("pos", 2, liba_pid_pos),
    JS_CFUNC_DEF("inc", 2, liba_pid_inc),
};

int js_liba_pid_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_pid_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_pid_class_id, &liba_pid_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_pid_proto, A_LEN(liba_pid_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_pid_ctor, "pid", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_pid_class_id, proto);

    return JS_SetModuleExport(ctx, m, "pid", clazz);
}
