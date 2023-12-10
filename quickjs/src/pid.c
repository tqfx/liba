#include "a.h"
#include "a/pid.h"

static JSClassID liba_pid_class_id;

static void liba_pid_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_pid_class_id));
}

static JSClassDef liba_pid_class = {"pid", .finalizer = liba_pid_finalizer};

static JSValue liba_pid_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    JSValue clazz = JS_UNDEFINED;
    a_pid_s *const self = (a_pid_s *)js_mallocz(ctx, sizeof(a_pid_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    self->kp = 1;
    self->summax = +A_FLOAT_INF;
    self->summin = -A_FLOAT_INF;
    self->outmax = +A_FLOAT_INF;
    self->outmin = -A_FLOAT_INF;
    a_pid_init(self);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_pid_class_id);
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

static JSValue liba_pid_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double x;
    switch (magic)
    {
    case 0:
        x = (double)self->kp;
        break;
    case 1:
        x = (double)self->ki;
        break;
    case 2:
        x = (double)self->kd;
        break;
    case 3:
        x = (double)self->summax;
        break;
    case 4:
        x = (double)self->summin;
        break;
    case 5:
        x = (double)self->outmax;
        break;
    case 6:
        x = (double)self->outmin;
        break;
    case 7:
        x = (double)self->out;
        break;
    case 8:
        x = (double)self->fdb;
        break;
    case 9:
        x = (double)self->err;
        break;
    default:
        return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_pid_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
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
        self->kp = (a_float_t)x;
        break;
    case 1:
        self->ki = (a_float_t)x;
        break;
    case 2:
        self->kd = (a_float_t)x;
        break;
    case 3:
        self->summax = (a_float_t)x;
        break;
    case 4:
        self->summin = (a_float_t)x;
        break;
    case 5:
        self->outmax = (a_float_t)x;
        break;
    case 6:
        self->outmin = (a_float_t)x;
        break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSValue liba_pid_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_pid_zero(self);
    return JS_UNDEFINED;
}

static JSValue liba_pid_kpid(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
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
    a_pid_kpid(self, (a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_UNDEFINED;
}

static JSValue liba_pid_run(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
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
    return JS_NewFloat64(ctx, (double)a_pid_run(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSValue liba_pid_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
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
    return JS_NewFloat64(ctx, (double)a_pid_pos(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSValue liba_pid_inc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, liba_pid_class_id);
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
    return JS_NewFloat64(ctx, (double)a_pid_inc(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSCFunctionListEntry const liba_pid_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid", 0),
    JS_CGETSET_MAGIC_DEF("kp", liba_pid_get, liba_pid_set, 0),
    JS_CGETSET_MAGIC_DEF("ki", liba_pid_get, liba_pid_set, 1),
    JS_CGETSET_MAGIC_DEF("kd", liba_pid_get, liba_pid_set, 2),
    JS_CGETSET_MAGIC_DEF("summax", liba_pid_get, liba_pid_set, 3),
    JS_CGETSET_MAGIC_DEF("summin", liba_pid_get, liba_pid_set, 4),
    JS_CGETSET_MAGIC_DEF("outmax", liba_pid_get, liba_pid_set, 5),
    JS_CGETSET_MAGIC_DEF("outmin", liba_pid_get, liba_pid_set, 6),
    JS_CGETSET_MAGIC_DEF("out", liba_pid_get, NULL, 7),
    JS_CGETSET_MAGIC_DEF("fdb", liba_pid_get, NULL, 8),
    JS_CGETSET_MAGIC_DEF("err", liba_pid_get, NULL, 9),
    JS_CFUNC_DEF("kpid", 3, liba_pid_kpid),
    JS_CFUNC_DEF("zero", 0, liba_pid_zero),
    JS_CFUNC_DEF("run", 2, liba_pid_run),
    JS_CFUNC_DEF("pos", 2, liba_pid_pos),
    JS_CFUNC_DEF("inc", 2, liba_pid_inc),
};

int js_liba_pid_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&liba_pid_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_pid_class_id, &liba_pid_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_pid_proto, A_LEN(liba_pid_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_pid_ctor, "pid", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_pid_class_id, proto);

    JS_DefinePropertyValueStr(ctx, clazz, "RUN", JS_NewUint32(ctx, A_PID_RUN), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "POS", JS_NewUint32(ctx, A_PID_POS), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "INC", JS_NewUint32(ctx, A_PID_INC), 0);

    return JS_SetModuleExport(ctx, m, "pid", clazz);
}
