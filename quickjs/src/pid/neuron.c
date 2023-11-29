#include "../a.h"
#include "a/pid/neuron.h"

static JSClassID liba_pid_neuron_class_id;

static void liba_pid_neuron_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_pid_neuron_class_id));
}

static JSClassDef liba_pid_neuron_class = {"pid_neuron", .finalizer = liba_pid_neuron_finalizer};

static JSValue liba_pid_neuron_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    JSValue clazz = JS_UNDEFINED;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)js_mallocz(ctx, sizeof(a_pid_neuron_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    self->pid.summax = +A_FLOAT_INF;
    self->pid.summin = -A_FLOAT_INF;
    self->pid.outmax = +A_FLOAT_INF;
    self->pid.outmin = -A_FLOAT_INF;
    self->k = 1;
    self->wp = A_FLOAT_C(0.1);
    self->wi = A_FLOAT_C(0.1);
    self->wd = A_FLOAT_C(0.1);
    a_pid_neuron_init(self);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_pid_neuron_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz))
    {
        goto fail;
    }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_pid_neuron_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, liba_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double x;
    switch (magic)
    {
    case 0:
        x = (double)self->k;
        break;
    case 1:
        x = (double)self->pid.kp;
        break;
    case 2:
        x = (double)self->pid.ki;
        break;
    case 3:
        x = (double)self->pid.kd;
        break;
    case 4:
        x = (double)self->wp;
        break;
    case 5:
        x = (double)self->wi;
        break;
    case 6:
        x = (double)self->wd;
        break;
    case 7:
        x = (double)self->pid.outmax;
        break;
    case 8:
        x = (double)self->pid.outmin;
        break;
    case 9:
        x = (double)self->pid.out;
        break;
    case 10:
        x = (double)self->pid.fdb;
        break;
    case 11:
        x = (double)self->pid.err;
        break;
    case 12:
        x = (double)self->ec;
        break;
    default:
        return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_pid_neuron_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, liba_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double x;
    if (JS_ToFloat64(ctx, &x, val))
    {
        return JS_EXCEPTION;
    }
    switch (magic)
    {
    case 0:
        self->k = (a_float_t)x;
        break;
    case 1:
        self->pid.kp = (a_float_t)x;
        break;
    case 2:
        self->pid.ki = (a_float_t)x;
        break;
    case 3:
        self->pid.kd = (a_float_t)x;
        break;
    case 4:
        self->wp = (a_float_t)x;
        break;
    case 5:
        self->wi = (a_float_t)x;
        break;
    case 6:
        self->wd = (a_float_t)x;
        break;
    case 7:
        self->pid.outmax = (a_float_t)x;
        break;
    case 8:
        self->pid.outmin = (a_float_t)x;
        break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuron_kpid(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, liba_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_pid_neuron_kpid(self, (a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3]);
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuron_wpid(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, liba_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_pid_neuron_wpid(self, (a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuron_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, liba_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_pid_neuron_zero(self);
    return JS_UNDEFINED;
}

static JSValue liba_pid_neuron_off(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, liba_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    return JS_NewFloat64(ctx, (double)a_pid_neuron_off(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSValue liba_pid_neuron_inc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, liba_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    return JS_NewFloat64(ctx, (double)a_pid_neuron_inc(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSCFunctionListEntry const liba_pid_neuron_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid.neuron", 0),
    JS_CGETSET_MAGIC_DEF("k", liba_pid_neuron_get, liba_pid_neuron_set, 0),
    JS_CGETSET_MAGIC_DEF("kp", liba_pid_neuron_get, liba_pid_neuron_set, 1),
    JS_CGETSET_MAGIC_DEF("ki", liba_pid_neuron_get, liba_pid_neuron_set, 2),
    JS_CGETSET_MAGIC_DEF("kd", liba_pid_neuron_get, liba_pid_neuron_set, 3),
    JS_CGETSET_MAGIC_DEF("wp", liba_pid_neuron_get, liba_pid_neuron_set, 4),
    JS_CGETSET_MAGIC_DEF("wi", liba_pid_neuron_get, liba_pid_neuron_set, 5),
    JS_CGETSET_MAGIC_DEF("wd", liba_pid_neuron_get, liba_pid_neuron_set, 6),
    JS_CGETSET_MAGIC_DEF("outmax", liba_pid_neuron_get, liba_pid_neuron_set, 7),
    JS_CGETSET_MAGIC_DEF("outmin", liba_pid_neuron_get, liba_pid_neuron_set, 8),
    JS_CGETSET_MAGIC_DEF("out", liba_pid_neuron_get, NULL, 9),
    JS_CGETSET_MAGIC_DEF("fdb", liba_pid_neuron_get, NULL, 10),
    JS_CGETSET_MAGIC_DEF("err", liba_pid_neuron_get, NULL, 11),
    JS_CGETSET_MAGIC_DEF("ec", liba_pid_neuron_get, NULL, 12),
    JS_CFUNC_DEF("kpid", 4, liba_pid_neuron_kpid),
    JS_CFUNC_DEF("wpid", 3, liba_pid_neuron_wpid),
    JS_CFUNC_DEF("zero", 0, liba_pid_neuron_zero),
    JS_CFUNC_DEF("off", 2, liba_pid_neuron_off),
    JS_CFUNC_DEF("inc", 2, liba_pid_neuron_inc),
};

int js_liba_pid_neuron_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&liba_pid_neuron_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_pid_neuron_class_id, &liba_pid_neuron_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_pid_neuron_proto, A_LEN(liba_pid_neuron_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_pid_neuron_ctor, "pid_neuron", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_pid_neuron_class_id, proto);

    return JS_SetModuleExport(ctx, m, "pid_neuron", clazz);
}
