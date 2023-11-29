#include "a.h"

static JSValue Concat(JSContext *const ctx, JSValueConst const val)
{
    JSValue this_val = JS_NewArray(ctx);
    JSValueConst argv[] = {this_val, val};
    JSValue concat = JS_GetPropertyStr(ctx, this_val, "concat");
    JSValue apply = JS_GetPropertyStr(ctx, concat, "apply");
    JSValue res = JS_Call(ctx, apply, this_val, A_LEN(argv), argv);
    JS_FreeValue(ctx, this_val);
    JS_FreeValue(ctx, concat);
    JS_FreeValue(ctx, apply);
    return res;
}

static int ArrayLength(JSContext *const ctx, JSValueConst const val, a_u32_t *const plen)
{
    JSValue len = JS_GetPropertyStr(ctx, val, "length");
    if (JS_IsException(len))
    {
        return ~0;
    }
    int ret = JS_ToUint32(ctx, plen, len);
    JS_FreeValue(ctx, len);
    return ret;
}

static int ArrayFloat(JSContext *const ctx, JSValueConst const val, a_float_t *const ptr, a_u32_t const len)
{
    for (unsigned int i = 0; i < len; ++i)
    {
        JSValue tmp = JS_GetPropertyUint32(ctx, val, i);
        if (JS_IsException(tmp))
        {
            return ~0;
        }
        double x;
        int ret = JS_ToFloat64(ctx, &x, tmp);
        JS_FreeValue(ctx, val);
        if (ret)
        {
            return ret;
        }
        ptr[i] = (a_float_t)x;
    }
    return 0;
}

static JSValue js_hash_bkdr(JSContext *const ctx, JSValueConst const this_val, int const argc, JSValueConst *const argv)
{
    (void)this_val;
    a_umax_t x = 0;
    for (int i = 0; i < argc; ++i)
    {
        char const *str = JS_ToCString(ctx, argv[i]);
        x = a_hash_bkdr(str, x);
        JS_FreeCString(ctx, str);
    }
    return JS_NewUint32(ctx, (a_u32_t)x);
}

#include "a/math.h"

static JSValue js_rsqrt(JSContext *const ctx, JSValueConst const this_val, int const argc, JSValueConst *const argv)
{
    (void)this_val;
    (void)argc;
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0]))
    {
        return JS_EXCEPTION;
    }
    return JS_NewFloat64(ctx, a_f64_rsqrt(x));
}

#include "a/mf.h"

static JSValue js_mf_gauss(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_gauss((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_gauss2(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_gauss2((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3], (a_float_t)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_gbell(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_gbell((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_sig(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_sig((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_dsig(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_dsig((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3], (a_float_t)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_psig(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_psig((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3], (a_float_t)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_trap(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_trap((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3], (a_float_t)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_tri(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_tri((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_lins(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_lins((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_linz(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_linz((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_s(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_s((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_z(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_z((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_pi(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_pi((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3], (a_float_t)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSCFunctionListEntry const js_liba_mf_funcs[] = {
    JS_PROP_INT32_DEF("NUL", A_MF_NUL, 0),
    JS_PROP_INT32_DEF("GAUSS", A_MF_GAUSS, 0),
    JS_PROP_INT32_DEF("GAUSS2", A_MF_GAUSS2, 0),
    JS_PROP_INT32_DEF("GBELL", A_MF_GBELL, 0),
    JS_PROP_INT32_DEF("SIG", A_MF_SIG, 0),
    JS_PROP_INT32_DEF("DSIG", A_MF_DSIG, 0),
    JS_PROP_INT32_DEF("PSIG", A_MF_PSIG, 0),
    JS_PROP_INT32_DEF("TRAP", A_MF_TRAP, 0),
    JS_PROP_INT32_DEF("TRI", A_MF_TRI, 0),
    JS_PROP_INT32_DEF("LINS", A_MF_LINS, 0),
    JS_PROP_INT32_DEF("LINZ", A_MF_LINZ, 0),
    JS_PROP_INT32_DEF("S", A_MF_S, 0),
    JS_PROP_INT32_DEF("Z", A_MF_Z, 0),
    JS_PROP_INT32_DEF("PI", A_MF_PI, 0),
    JS_CFUNC_DEF("gauss", 3, js_mf_gauss),
    JS_CFUNC_DEF("gauss2", 5, js_mf_gauss2),
    JS_CFUNC_DEF("gbell", 4, js_mf_gbell),
    JS_CFUNC_DEF("sig", 3, js_mf_sig),
    JS_CFUNC_DEF("dsig", 5, js_mf_dsig),
    JS_CFUNC_DEF("psig", 5, js_mf_psig),
    JS_CFUNC_DEF("trap", 5, js_mf_trap),
    JS_CFUNC_DEF("tri", 4, js_mf_tri),
    JS_CFUNC_DEF("lins", 3, js_mf_lins),
    JS_CFUNC_DEF("linz", 3, js_mf_linz),
    JS_CFUNC_DEF("s", 3, js_mf_s),
    JS_CFUNC_DEF("z", 3, js_mf_z),
    JS_CFUNC_DEF("pi", 5, js_mf_pi),
};

#include "a/pid.h"

static JSClassID js_pid_class_id;

static void js_pid_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, js_pid_class_id));
}

static JSClassDef js_pid_class = {"pid", .finalizer = js_pid_finalizer};

static JSValue js_pid_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
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
    clazz = JS_NewObjectProtoClass(ctx, proto, js_pid_class_id);
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

static JSValue js_pid_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, js_pid_class_id);
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

static JSValue js_pid_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, js_pid_class_id);
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

static JSValue js_pid_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, js_pid_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_pid_zero(self);
    return JS_UNDEFINED;
}

static JSValue js_pid_kpid(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, js_pid_class_id);
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

static JSValue js_pid_off(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, js_pid_class_id);
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
    return JS_NewFloat64(ctx, (double)a_pid_off(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSValue js_pid_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, js_pid_class_id);
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

static JSValue js_pid_inc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_s *const self = (a_pid_s *)JS_GetOpaque2(ctx, this_val, js_pid_class_id);
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

static JSCFunctionListEntry const js_pid_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid", 0),
    JS_CGETSET_MAGIC_DEF("kp", js_pid_get, js_pid_set, 0),
    JS_CGETSET_MAGIC_DEF("ki", js_pid_get, js_pid_set, 1),
    JS_CGETSET_MAGIC_DEF("kd", js_pid_get, js_pid_set, 2),
    JS_CGETSET_MAGIC_DEF("summax", js_pid_get, js_pid_set, 3),
    JS_CGETSET_MAGIC_DEF("summin", js_pid_get, js_pid_set, 4),
    JS_CGETSET_MAGIC_DEF("outmax", js_pid_get, js_pid_set, 5),
    JS_CGETSET_MAGIC_DEF("outmin", js_pid_get, js_pid_set, 6),
    JS_CGETSET_MAGIC_DEF("out", js_pid_get, NULL, 7),
    JS_CGETSET_MAGIC_DEF("fdb", js_pid_get, NULL, 8),
    JS_CGETSET_MAGIC_DEF("err", js_pid_get, NULL, 9),
    JS_CFUNC_DEF("kpid", 3, js_pid_kpid),
    JS_CFUNC_DEF("zero", 0, js_pid_zero),
    JS_CFUNC_DEF("off", 2, js_pid_off),
    JS_CFUNC_DEF("pos", 2, js_pid_pos),
    JS_CFUNC_DEF("inc", 2, js_pid_inc),
};

static A_INLINE int js_liba_pid_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_pid_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_pid_class_id, &js_pid_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_pid_proto, A_LEN(js_pid_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_pid_ctor, "pid", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_pid_class_id, proto);

    JS_DefinePropertyValueStr(ctx, clazz, "OFF", JS_NewUint32(ctx, A_PID_OFF), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "POS", JS_NewUint32(ctx, A_PID_POS), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "INC", JS_NewUint32(ctx, A_PID_INC), 0);

    JS_SetModuleExport(ctx, m, "pid", clazz);
    return 0;
}

#include "a/pid/fuzzy.h"

static JSClassID js_pid_fuzzy_class_id;

static void js_pid_fuzzy_finalizer(JSRuntime *const rt, JSValue const val)
{
    a_pid_fuzzy_s *self = (a_pid_fuzzy_s *)JS_GetOpaque(val, js_pid_fuzzy_class_id);
    union
    {
        a_float_t const *p;
        a_float_t *o;
    } u;
    js_free_rt(rt, ((void)(u.p = self->me), u.o));
    js_free_rt(rt, ((void)(u.p = self->mec), u.o));
    js_free_rt(rt, ((void)(u.p = self->mkp), u.o));
    js_free_rt(rt, ((void)(u.p = self->mki), u.o));
    js_free_rt(rt, ((void)(u.p = self->mkd), u.o));
    js_free_rt(rt, a_pid_fuzzy_joint(self));
    js_free_rt(rt, self);
}

static JSClassDef js_pid_fuzzy_class = {"pid_fuzzy", .finalizer = js_pid_fuzzy_finalizer};

static JSValue js_pid_fuzzy_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    JSValue clazz = JS_UNDEFINED;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)js_mallocz(ctx, sizeof(a_pid_fuzzy_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    self->pid.kp = 1;
    self->pid.summax = +A_FLOAT_INF;
    self->pid.summin = -A_FLOAT_INF;
    self->pid.outmax = +A_FLOAT_INF;
    self->pid.outmin = -A_FLOAT_INF;
    self->kp = 1;
    self->op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    a_pid_fuzzy_init(self);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, js_pid_fuzzy_class_id);
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

static JSValue js_pid_fuzzy_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double x;
    switch (magic)
    {
    case 0:
        return JS_NewUint32(ctx, self->joint);
    case 1:
        x = (double)self->kp;
        break;
    case 2:
        x = (double)self->ki;
        break;
    case 3:
        x = (double)self->kd;
        break;
    case 4:
        x = (double)self->pid.summax;
        break;
    case 5:
        x = (double)self->pid.summin;
        break;
    case 6:
        x = (double)self->pid.outmax;
        break;
    case 7:
        x = (double)self->pid.outmin;
        break;
    case 8:
        x = (double)self->pid.out;
        break;
    case 9:
        x = (double)self->pid.fdb;
        break;
    case 10:
        x = (double)self->pid.err;
        break;
    case 11:
        return JS_NewUint32(ctx, self->order);
    default:
        return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static int js_pid_fuzzy_joint_(JSContext *const ctx, a_pid_fuzzy_s *const self, unsigned int joint)
{
    void *ptr = a_pid_fuzzy_joint(self);
    if (joint > self->joint)
    {
        ptr = js_realloc(ctx, ptr, A_PID_FUZZY_JOINT(joint));
        if (!ptr)
        {
            return ~0;
        }
    }
    a_pid_fuzzy_set_joint(self, ptr, joint);
    return 0;
}

static JSValue js_pid_fuzzy_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_u32_t u;
    if (magic == 0)
    {
        if (JS_ToUint32(ctx, &u, val))
        {
            return JS_EXCEPTION;
        }
        if (js_pid_fuzzy_joint_(ctx, self, (unsigned int)u))
        {
            return JS_EXCEPTION;
        }
        return JS_UNDEFINED;
    }
    double x;
    if (JS_ToFloat64(ctx, &x, val))
    {
        return JS_EXCEPTION;
    }
    switch (magic)
    {
    case 1:
        self->pid.kp = self->kp = (a_float_t)x;
        break;
    case 2:
        self->pid.ki = self->ki = (a_float_t)x;
        break;
    case 3:
        self->pid.kd = self->kd = (a_float_t)x;
        break;
    case 4:
        self->pid.summax = (a_float_t)x;
        break;
    case 5:
        self->pid.summin = (a_float_t)x;
        break;
    case 6:
        self->pid.outmax = (a_float_t)x;
        break;
    case 7:
        self->pid.outmin = (a_float_t)x;
        break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSValue js_pid_fuzzy_op(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_u32_t op;
    if (JS_ToUint32(ctx, &op, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_pid_fuzzy_set_op(self, (unsigned int)op);
    return JS_UNDEFINED;
}

static JSValue js_pid_fuzzy_rule(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    union
    {
        a_float_t const *p;
        a_float_t *o;
    } u;
    a_u32_t row;
    a_u32_t len = 0;
    a_u32_t order = 0;
    JSValue res = JS_UNDEFINED;
    if (JS_IsArray(ctx, argv[0]))
    {
        if (ArrayLength(ctx, argv[0], &order))
        {
            goto fail;
        }
        res = Concat(ctx, argv[0]);
        if (ArrayLength(ctx, res, &len))
        {
            goto fail;
        }
        if (len)
        {
            a_float_t *const me = (a_float_t *)js_realloc(ctx, ((void)(u.p = self->me), u.o), sizeof(a_float_t) * len);
            if (!me)
            {
                goto fail;
            }
            self->me = me;
            if (ArrayFloat(ctx, res, me, len))
            {
                goto fail;
            }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[1]))
    {
        if (ArrayLength(ctx, argv[1], &row) || row != order)
        {
            goto fail;
        }
        res = Concat(ctx, argv[1]);
        if (ArrayLength(ctx, res, &len))
        {
            goto fail;
        }
        if (len)
        {
            a_float_t *const mec = (a_float_t *)js_realloc(ctx, ((void)(u.p = self->mec), u.o), sizeof(a_float_t) * len);
            if (!mec)
            {
                goto fail;
            }
            self->mec = mec;
            if (ArrayFloat(ctx, res, mec, len))
            {
                goto fail;
            }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[2]))
    {
        if (ArrayLength(ctx, argv[2], &row) || row != order)
        {
            goto fail;
        }
        res = Concat(ctx, argv[2]);
        if (ArrayLength(ctx, res, &len))
        {
            goto fail;
        }
        if (len)
        {
            a_float_t *const mkp = (a_float_t *)js_realloc(ctx, ((void)(u.p = self->mkp), u.o), sizeof(a_float_t) * len);
            if (!mkp)
            {
                goto fail;
            }
            self->mkp = mkp;
            if (ArrayFloat(ctx, res, mkp, len))
            {
                goto fail;
            }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[3]))
    {
        if (ArrayLength(ctx, argv[3], &row) || row != order)
        {
            goto fail;
        }
        res = Concat(ctx, argv[3]);
        if (ArrayLength(ctx, res, &len))
        {
            goto fail;
        }
        if (len)
        {
            a_float_t *const mki = (a_float_t *)js_realloc(ctx, ((void)(u.p = self->mki), u.o), sizeof(a_float_t) * len);
            if (!mki)
            {
                goto fail;
            }
            self->mki = mki;
            if (ArrayFloat(ctx, res, mki, len))
            {
                goto fail;
            }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[4]))
    {
        if (ArrayLength(ctx, argv[4], &row) || row != order)
        {
            goto fail;
        }
        res = Concat(ctx, argv[4]);
        if (ArrayLength(ctx, res, &len))
        {
            goto fail;
        }
        if (len)
        {
            a_float_t *const mkd = (a_float_t *)js_realloc(ctx, ((void)(u.p = self->mkd), u.o), sizeof(a_float_t) * len);
            if (!mkd)
            {
                goto fail;
            }
            self->mkd = mkd;
            if (ArrayFloat(ctx, res, mkd, len))
            {
                goto fail;
            }
        }
        JS_FreeValue(ctx, res);
    }
    self->order = order;
    return JS_UNDEFINED;
fail:
    JS_FreeValue(ctx, res);
    return JS_UNDEFINED;
}

static JSValue js_pid_fuzzy_joint(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_u32_t joint;
    if (JS_ToUint32(ctx, &joint, argv[0]))
    {
        return JS_EXCEPTION;
    }
    if (js_pid_fuzzy_joint_(ctx, self, joint))
    {
        return JS_EXCEPTION;
    }
    return JS_UNDEFINED;
}

static JSValue js_pid_fuzzy_kpid(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
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
    a_pid_fuzzy_kpid(self, (a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_UNDEFINED;
}

static JSValue js_pid_fuzzy_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_pid_fuzzy_zero(self);
    return JS_UNDEFINED;
}

static JSValue js_pid_fuzzy_off(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
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
    return JS_NewFloat64(ctx, (double)a_pid_fuzzy_off(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSValue js_pid_fuzzy_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
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
    return JS_NewFloat64(ctx, (double)a_pid_fuzzy_pos(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSValue js_pid_fuzzy_inc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_fuzzy_s *const self = (a_pid_fuzzy_s *)JS_GetOpaque2(ctx, this_val, js_pid_fuzzy_class_id);
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
    return JS_NewFloat64(ctx, (double)a_pid_fuzzy_inc(self, (a_float_t)args[0], (a_float_t)args[1]));
}

static JSCFunctionListEntry const js_pid_fuzzy_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid.fuzzy", 0),
    JS_CGETSET_MAGIC_DEF("joint", js_pid_fuzzy_get, js_pid_fuzzy_set, 0),
    JS_CGETSET_MAGIC_DEF("kp", js_pid_fuzzy_get, js_pid_fuzzy_set, 1),
    JS_CGETSET_MAGIC_DEF("ki", js_pid_fuzzy_get, js_pid_fuzzy_set, 2),
    JS_CGETSET_MAGIC_DEF("kd", js_pid_fuzzy_get, js_pid_fuzzy_set, 3),
    JS_CGETSET_MAGIC_DEF("summax", js_pid_fuzzy_get, js_pid_fuzzy_set, 4),
    JS_CGETSET_MAGIC_DEF("summin", js_pid_fuzzy_get, js_pid_fuzzy_set, 5),
    JS_CGETSET_MAGIC_DEF("outmax", js_pid_fuzzy_get, js_pid_fuzzy_set, 6),
    JS_CGETSET_MAGIC_DEF("outmin", js_pid_fuzzy_get, js_pid_fuzzy_set, 7),
    JS_CGETSET_MAGIC_DEF("out", js_pid_fuzzy_get, NULL, 8),
    JS_CGETSET_MAGIC_DEF("fdb", js_pid_fuzzy_get, NULL, 9),
    JS_CGETSET_MAGIC_DEF("err", js_pid_fuzzy_get, NULL, 10),
    JS_CGETSET_MAGIC_DEF("order", js_pid_fuzzy_get, NULL, 11),
    JS_CFUNC_DEF("op", 1, js_pid_fuzzy_op),
    JS_CFUNC_DEF("rule", 5, js_pid_fuzzy_rule),
    JS_CFUNC_DEF("set_joint", 1, js_pid_fuzzy_joint),
    JS_CFUNC_DEF("kpid", 3, js_pid_fuzzy_kpid),
    JS_CFUNC_DEF("zero", 0, js_pid_fuzzy_zero),
    JS_CFUNC_DEF("off", 2, js_pid_fuzzy_off),
    JS_CFUNC_DEF("pos", 2, js_pid_fuzzy_pos),
    JS_CFUNC_DEF("inc", 2, js_pid_fuzzy_inc),
};

static A_INLINE int js_liba_pid_fuzzy_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_pid_fuzzy_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_pid_fuzzy_class_id, &js_pid_fuzzy_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_pid_fuzzy_proto, A_LEN(js_pid_fuzzy_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_pid_fuzzy_ctor, "pid_fuzzy", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_pid_fuzzy_class_id, proto);

    JS_DefinePropertyValueStr(ctx, clazz, "CAP", JS_NewUint32(ctx, A_PID_FUZZY_CAP), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CAP_ALGEBRA", JS_NewUint32(ctx, A_PID_FUZZY_CAP_ALGEBRA), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CAP_BOUNDED", JS_NewUint32(ctx, A_PID_FUZZY_CAP_BOUNDED), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CUP", JS_NewUint32(ctx, A_PID_FUZZY_CUP), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CUP_ALGEBRA", JS_NewUint32(ctx, A_PID_FUZZY_CUP_ALGEBRA), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CUP_BOUNDED", JS_NewUint32(ctx, A_PID_FUZZY_CUP_BOUNDED), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "EQU", JS_NewUint32(ctx, A_PID_FUZZY_EQU), 0);

    JS_SetModuleExport(ctx, m, "pid_fuzzy", clazz);
    return 0;
}

#include "a/pid/neuron.h"

static JSClassID js_pid_neuron_class_id;

static void js_pid_neuron_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, js_pid_neuron_class_id));
}

static JSClassDef js_pid_neuron_class = {"pid_neuron", .finalizer = js_pid_neuron_finalizer};

static JSValue js_pid_neuron_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
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
    clazz = JS_NewObjectProtoClass(ctx, proto, js_pid_neuron_class_id);
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

static JSValue js_pid_neuron_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, js_pid_neuron_class_id);
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

static JSValue js_pid_neuron_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, js_pid_neuron_class_id);
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

static JSValue js_pid_neuron_kpid(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, js_pid_neuron_class_id);
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

static JSValue js_pid_neuron_wpid(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, js_pid_neuron_class_id);
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

static JSValue js_pid_neuron_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, js_pid_neuron_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_pid_neuron_zero(self);
    return JS_UNDEFINED;
}

static JSValue js_pid_neuron_off(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, js_pid_neuron_class_id);
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

static JSValue js_pid_neuron_inc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_pid_neuron_s *const self = (a_pid_neuron_s *)JS_GetOpaque2(ctx, this_val, js_pid_neuron_class_id);
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

static JSCFunctionListEntry const js_pid_neuron_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid.neuron", 0),
    JS_CGETSET_MAGIC_DEF("k", js_pid_neuron_get, js_pid_neuron_set, 0),
    JS_CGETSET_MAGIC_DEF("kp", js_pid_neuron_get, js_pid_neuron_set, 1),
    JS_CGETSET_MAGIC_DEF("ki", js_pid_neuron_get, js_pid_neuron_set, 2),
    JS_CGETSET_MAGIC_DEF("kd", js_pid_neuron_get, js_pid_neuron_set, 3),
    JS_CGETSET_MAGIC_DEF("wp", js_pid_neuron_get, js_pid_neuron_set, 4),
    JS_CGETSET_MAGIC_DEF("wi", js_pid_neuron_get, js_pid_neuron_set, 5),
    JS_CGETSET_MAGIC_DEF("wd", js_pid_neuron_get, js_pid_neuron_set, 6),
    JS_CGETSET_MAGIC_DEF("outmax", js_pid_neuron_get, js_pid_neuron_set, 7),
    JS_CGETSET_MAGIC_DEF("outmin", js_pid_neuron_get, js_pid_neuron_set, 8),
    JS_CGETSET_MAGIC_DEF("out", js_pid_neuron_get, NULL, 9),
    JS_CGETSET_MAGIC_DEF("fdb", js_pid_neuron_get, NULL, 10),
    JS_CGETSET_MAGIC_DEF("err", js_pid_neuron_get, NULL, 11),
    JS_CGETSET_MAGIC_DEF("ec", js_pid_neuron_get, NULL, 12),
    JS_CFUNC_DEF("kpid", 4, js_pid_neuron_kpid),
    JS_CFUNC_DEF("wpid", 3, js_pid_neuron_wpid),
    JS_CFUNC_DEF("zero", 0, js_pid_neuron_zero),
    JS_CFUNC_DEF("off", 2, js_pid_neuron_off),
    JS_CFUNC_DEF("inc", 2, js_pid_neuron_inc),
};

static A_INLINE int js_liba_pid_neuron_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_pid_neuron_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_pid_neuron_class_id, &js_pid_neuron_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_pid_neuron_proto, A_LEN(js_pid_neuron_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_pid_neuron_ctor, "pid_neuron", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_pid_neuron_class_id, proto);

    JS_SetModuleExport(ctx, m, "pid_neuron", clazz);
    return 0;
}

#include "a/polytraj.h"

static JSClassID js_polytraj3_class_id;

static void js_polytraj3_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, js_polytraj3_class_id));
}

static JSClassDef js_polytraj3_class = {"polytraj3", .finalizer = js_polytraj3_finalizer};

static JSValue js_polytraj3_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue clazz = JS_UNDEFINED;
    a_polytraj3_s *const self = (a_polytraj3_s *)js_mallocz(ctx, sizeof(a_polytraj3_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            goto fail;
        }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            goto fail;
        }
    }
    a_polytraj3_gen(self,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5]);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, js_polytraj3_class_id);
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

static JSValue js_polytraj3_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_polytraj3_s *const self = (a_polytraj3_s *)JS_GetOpaque2(ctx, this_val, js_polytraj3_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_polytraj3_gen(self,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5]);
    return JS_UNDEFINED;
}

static JSValue js_polytraj3_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj3_s *const self = (a_polytraj3_s *)JS_GetOpaque2(ctx, this_val, js_polytraj3_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t pos = a_polytraj3_pos(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue js_polytraj3_vel(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj3_s *const self = (a_polytraj3_s *)JS_GetOpaque2(ctx, this_val, js_polytraj3_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t vel = a_polytraj3_vel(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue js_polytraj3_acc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj3_s *const self = (a_polytraj3_s *)JS_GetOpaque2(ctx, this_val, js_polytraj3_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t acc = a_polytraj3_acc(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const js_polytraj3_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.polytraj3", 0),
    JS_CFUNC_DEF("gen", 6, js_polytraj3_gen),
    JS_CFUNC_DEF("pos", 1, js_polytraj3_pos),
    JS_CFUNC_DEF("vel", 1, js_polytraj3_vel),
    JS_CFUNC_DEF("acc", 1, js_polytraj3_acc),
};

static A_INLINE int js_liba_polytraj3_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_polytraj3_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_polytraj3_class_id, &js_polytraj3_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_polytraj3_proto, A_LEN(js_polytraj3_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_polytraj3_ctor, "polytraj3", 6, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_polytraj3_class_id, proto);

    JS_SetModuleExport(ctx, m, "polytraj3", clazz);
    return 0;
}

static JSClassID js_polytraj5_class_id;

static void js_polytraj5_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, js_polytraj5_class_id));
}

static JSClassDef js_polytraj5_class = {"polytraj5", .finalizer = js_polytraj5_finalizer};

static JSValue js_polytraj5_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue clazz = JS_UNDEFINED;
    a_polytraj5_s *const self = (a_polytraj5_s *)js_mallocz(ctx, sizeof(a_polytraj5_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            goto fail;
        }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            goto fail;
        }
    }
    a_polytraj5_gen(self,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5],
                     (a_float_t)args[6], (a_float_t)args[7]);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, js_polytraj5_class_id);
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

static JSValue js_polytraj5_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_polytraj5_s *const self = (a_polytraj5_s *)JS_GetOpaque2(ctx, this_val, js_polytraj5_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_polytraj5_gen(self,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5],
                     (a_float_t)args[6], (a_float_t)args[7]);
    return JS_UNDEFINED;
}

static JSValue js_polytraj5_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj5_s *const self = (a_polytraj5_s *)JS_GetOpaque2(ctx, this_val, js_polytraj5_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t pos = a_polytraj5_pos(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue js_polytraj5_vel(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj5_s *const self = (a_polytraj5_s *)JS_GetOpaque2(ctx, this_val, js_polytraj5_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t vel = a_polytraj5_vel(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue js_polytraj5_acc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj5_s *const self = (a_polytraj5_s *)JS_GetOpaque2(ctx, this_val, js_polytraj5_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t acc = a_polytraj5_acc(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const js_polytraj5_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.polytraj5", 0),
    JS_CFUNC_DEF("gen", 8, js_polytraj5_gen),
    JS_CFUNC_DEF("pos", 1, js_polytraj5_pos),
    JS_CFUNC_DEF("vel", 1, js_polytraj5_vel),
    JS_CFUNC_DEF("acc", 1, js_polytraj5_acc),
};

static A_INLINE int js_liba_polytraj5_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_polytraj5_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_polytraj5_class_id, &js_polytraj5_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_polytraj5_proto, A_LEN(js_polytraj5_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_polytraj5_ctor, "polytraj5", 8, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_polytraj5_class_id, proto);

    JS_SetModuleExport(ctx, m, "polytraj5", clazz);
    return 0;
}

static JSClassID js_polytraj7_class_id;

static void js_polytraj7_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, js_polytraj7_class_id));
}

static JSClassDef js_polytraj7_class = {"polytraj7", .finalizer = js_polytraj7_finalizer};

static JSValue js_polytraj7_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue clazz = JS_UNDEFINED;
    a_polytraj7_s *const self = (a_polytraj7_s *)js_mallocz(ctx, sizeof(a_polytraj7_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            goto fail;
        }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            goto fail;
        }
    }
    a_polytraj7_gen(self,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5],
                     (a_float_t)args[6], (a_float_t)args[7],
                     (a_float_t)args[8], (a_float_t)args[9]);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, js_polytraj7_class_id);
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

static JSValue js_polytraj7_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_polytraj7_s *const self = (a_polytraj7_s *)JS_GetOpaque2(ctx, this_val, js_polytraj7_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < 4; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    for (int i = 4; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_polytraj7_gen(self,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5],
                     (a_float_t)args[6], (a_float_t)args[7],
                     (a_float_t)args[8], (a_float_t)args[9]);
    return JS_UNDEFINED;
}

static JSValue js_polytraj7_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj7_s *const self = (a_polytraj7_s *)JS_GetOpaque2(ctx, this_val, js_polytraj7_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t pos = a_polytraj7_pos(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue js_polytraj7_vel(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj7_s *const self = (a_polytraj7_s *)JS_GetOpaque2(ctx, this_val, js_polytraj7_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t vel = a_polytraj7_vel(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue js_polytraj7_acc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj7_s *const self = (a_polytraj7_s *)JS_GetOpaque2(ctx, this_val, js_polytraj7_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t acc = a_polytraj7_acc(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSValue js_polytraj7_jer(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytraj7_s *const self = (a_polytraj7_s *)JS_GetOpaque2(ctx, this_val, js_polytraj7_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t jer = a_polytraj7_jer(self, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)jer);
}

static JSCFunctionListEntry const js_polytraj7_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.polytraj7", 0),
    JS_CFUNC_DEF("gen", 10, js_polytraj7_gen),
    JS_CFUNC_DEF("pos", 1, js_polytraj7_pos),
    JS_CFUNC_DEF("vel", 1, js_polytraj7_vel),
    JS_CFUNC_DEF("acc", 1, js_polytraj7_acc),
    JS_CFUNC_DEF("jer", 1, js_polytraj7_jer),
};

static A_INLINE int js_liba_polytraj7_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_polytraj7_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_polytraj7_class_id, &js_polytraj7_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_polytraj7_proto, A_LEN(js_polytraj7_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_polytraj7_ctor, "polytraj7", 10, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_polytraj7_class_id, proto);

    JS_SetModuleExport(ctx, m, "polytraj7", clazz);
    return 0;
}

#include "a/tf.h"

static JSClassID js_tf_class_id;

static void js_tf_finalizer(JSRuntime *const rt, JSValue const val)
{
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque(val, js_tf_class_id);
    js_free_rt(rt, self->output);
    js_free_rt(rt, self->input);
    js_free_rt(rt, self);
}

static JSClassDef js_tf_class = {"tf", .finalizer = js_tf_finalizer};

static int js_tf_set_num(JSContext *const ctx, a_tf_s *const self, JSValueConst num)
{
    a_u32_t num_n = 0;
    a_float_t *num_p = self->input;
    int ret = ArrayLength(ctx, num, &num_n);
    if (ret)
    {
        return ret;
    }
    if (num_n > self->num_n)
    {
        num_p = (a_float_t *)js_realloc(ctx, num_p, sizeof(a_float_t) * num_n * 2);
        if (!num_p)
        {
            return ~0;
        }
        self->input = num_p;
        num_p += num_n;
        self->num_p = num_p;
    }
    else
    {
        num_p += self->num_n;
    }
    self->num_n = (unsigned int)num_n;
    a_zero(self->input, sizeof(a_float_t) * num_n);
    return ArrayFloat(ctx, num, num_p, num_n);
}

static int js_tf_set_den(JSContext *const ctx, a_tf_s *const self, JSValueConst den)
{
    a_u32_t den_n = 0;
    a_float_t *den_p = self->output;
    int ret = ArrayLength(ctx, den, &den_n);
    if (ret)
    {
        return ret;
    }
    if (den_n > self->den_n)
    {
        den_p = (a_float_t *)js_realloc(ctx, den_p, sizeof(a_float_t) * den_n * 2);
        if (!den_p)
        {
            return ~0;
        }
        self->output = den_p;
        den_p += den_n;
        self->den_p = den_p;
    }
    else
    {
        den_p += self->den_n;
    }
    self->den_n = (unsigned int)den_n;
    a_zero(self->output, sizeof(a_float_t) * den_n);
    return ArrayFloat(ctx, den, den_p, den_n);
}

static JSValue js_tf_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    (void)argc;
    JSValue clazz = JS_UNDEFINED;
    a_tf_s *const self = (a_tf_s *)js_mallocz(ctx, sizeof(a_tf_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    if (JS_IsObject(argv[0]) && js_tf_set_num(ctx, self, argv[0]))
    {
        goto fail;
    }
    if (JS_IsObject(argv[1]) && js_tf_set_den(ctx, self, argv[1]))
    {
        goto fail;
    }
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, js_tf_class_id);
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
    return JS_UNDEFINED;
}

static JSValue js_tf_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, js_tf_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    JSValue val = JS_NewArray(ctx);
    if (JS_IsException(val))
    {
        return val;
    }
    a_float_t const *val_p;
    a_size_t val_n;
    switch (magic)
    {
    case 0:
        val_p = self->num_p;
        val_n = self->num_n;
        break;
    case 1:
        val_p = self->den_p;
        val_n = self->den_n;
        break;
    case 2:
        val_p = self->input;
        val_n = self->num_n;
        break;
    case 3:
        val_p = self->output;
        val_n = self->den_n;
        break;
    default:
        return JS_UNDEFINED;
    }
    for (unsigned int i = 0; i < val_n; ++i)
    {
        JSValue x = JS_NewFloat64(ctx, (double)val_p[i]);
        JS_SetPropertyUint32(ctx, val, i, x);
    }
    return val;
}

static JSValue js_tf_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, js_tf_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    switch (magic)
    {
    case 0:
        if (JS_IsObject(val))
        {
            js_tf_set_num(ctx, self, val);
        }
        break;
    case 1:
        if (JS_IsObject(val))
        {
            js_tf_set_den(ctx, self, val);
        }
        break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSValue js_tf_iter(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, js_tf_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    double x;
    if (JS_ToFloat64(ctx, &x, argv[0]))
    {
        return JS_EXCEPTION;
    }
    return JS_NewFloat64(ctx, (double)a_tf_iter(self, (a_float_t)x));
}

static JSValue js_tf_zero(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)argv;
    a_tf_s *const self = (a_tf_s *)JS_GetOpaque2(ctx, this_val, js_tf_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_tf_zero(self);
    return JS_UNDEFINED;
}

static JSCFunctionListEntry const js_tf_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.tf", 0),
    JS_CGETSET_MAGIC_DEF("num", js_tf_get, js_tf_set, 0),
    JS_CGETSET_MAGIC_DEF("den", js_tf_get, js_tf_set, 1),
    JS_CGETSET_MAGIC_DEF("input", js_tf_get, js_tf_set, 2),
    JS_CGETSET_MAGIC_DEF("output", js_tf_get, js_tf_set, 3),
    JS_CFUNC_DEF("iter", 1, js_tf_iter),
    JS_CFUNC_DEF("zero", 0, js_tf_zero),
};

static A_INLINE int js_liba_tf_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_tf_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_tf_class_id, &js_tf_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_tf_proto, A_LEN(js_tf_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_tf_ctor, "tf", 2, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_tf_class_id, proto);

    JS_SetModuleExport(ctx, m, "tf", clazz);
    return 0;
}

#include "a/version.h"

static JSClassID js_version_class_id;

static void js_version_finalizer(JSRuntime *const rt, JSValue const val)
{
    js_free_rt(rt, JS_GetOpaque(val, js_version_class_id));
}

static JSClassDef js_version_class = {"version", .finalizer = js_version_finalizer};

static JSValue js_version_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue clazz = JS_UNDEFINED;
    a_version_s *const self = (a_version_s *)js_mallocz(ctx, sizeof(a_version_s));
    if (!self)
    {
        return JS_EXCEPTION;
    }
    char const *ver = NULL;
    a_u32_t args[] = {0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToUint32(ctx, &args[i], argv[i]))
        {
            if (!i && ((void)(ver = JS_ToCString(ctx, argv[0])), ver))
            {
                break;
            }
            goto fail;
        }
    }
    if (ver)
    {
        a_version_parse(self, ver);
        JS_FreeCString(ctx, ver);
    }
    else
    {
        self->major = (unsigned int)args[0];
        self->minor = (unsigned int)args[1];
        self->patch = (unsigned int)args[2];
    }
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    clazz = JS_NewObjectProtoClass(ctx, proto, js_version_class_id);
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

static JSValue js_version_get(JSContext *const ctx, JSValueConst const this_val, int magic)
{
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_u32_t ver;
    switch (magic)
    {
    case 0:
        ver = self->major;
        break;
    case 1:
        ver = self->minor;
        break;
    case 2:
        ver = self->patch;
        break;
    default:
        return JS_UNDEFINED;
    }
    return JS_NewUint32(ctx, ver);
}

static JSValue js_version_set(JSContext *const ctx, JSValueConst const this_val, JSValueConst const val, int magic)
{
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_u32_t ver;
    if (JS_ToUint32(ctx, &ver, val))
    {
        return JS_EXCEPTION;
    }
    switch (magic)
    {
    case 0:
        self->major = (unsigned int)ver;
        break;
    case 1:
        self->minor = (unsigned int)ver;
        break;
    case 2:
        self->patch = (unsigned int)ver;
        break;
    default:
        break;
    }
    return JS_UNDEFINED;
}

static JSValue js_version_check(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)this_val;
    a_u32_t args[] = {0, 0, 0};
    if (argc > (int)A_LEN(args))
    {
        argc = (int)A_LEN(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToUint32(ctx, &args[i], argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
#undef a_version_check
    return JS_NewInt32(ctx, a_version_check((unsigned int)args[0], (unsigned int)args[1], (unsigned int)args[2]));
}

static JSValue js_version_parse(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    char const *ver = JS_ToCString(ctx, argv[0]);
    if (!ver)
    {
        return JS_EXCEPTION;
    }
    a_version_parse(self, ver);
    JS_FreeCString(ctx, ver);
    return JS_UNDEFINED;
}

static JSValue js_version_cmp(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_version_s *const other = (a_version_s *)JS_GetOpaque2(ctx, argv[0], js_version_class_id);
    if (!other)
    {
        return JS_EXCEPTION;
    }
    return JS_NewInt32(ctx, a_version_cmp(self, other));
}

static JSValue js_version_lt(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_version_s *const other = (a_version_s *)JS_GetOpaque2(ctx, argv[0], js_version_class_id);
    if (!other)
    {
        return JS_EXCEPTION;
    }
    return JS_NewBool(ctx, a_version_lt(self, other));
}

static JSValue js_version_gt(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_version_s *const other = (a_version_s *)JS_GetOpaque2(ctx, argv[0], js_version_class_id);
    if (!other)
    {
        return JS_EXCEPTION;
    }
    return JS_NewBool(ctx, a_version_gt(self, other));
}

static JSValue js_version_le(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_version_s *const other = (a_version_s *)JS_GetOpaque2(ctx, argv[0], js_version_class_id);
    if (!other)
    {
        return JS_EXCEPTION;
    }
    return JS_NewBool(ctx, a_version_le(self, other));
}

static JSValue js_version_ge(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_version_s *const other = (a_version_s *)JS_GetOpaque2(ctx, argv[0], js_version_class_id);
    if (!other)
    {
        return JS_EXCEPTION;
    }
    return JS_NewBool(ctx, a_version_ge(self, other));
}

static JSValue js_version_eq(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_version_s *const other = (a_version_s *)JS_GetOpaque2(ctx, argv[0], js_version_class_id);
    if (!other)
    {
        return JS_EXCEPTION;
    }
    return JS_NewBool(ctx, a_version_eq(self, other));
}

static JSValue js_version_ne(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_version_s *const self = (a_version_s *)JS_GetOpaque2(ctx, this_val, js_version_class_id);
    if (!self)
    {
        return JS_EXCEPTION;
    }
    a_version_s *const other = (a_version_s *)JS_GetOpaque2(ctx, argv[0], js_version_class_id);
    if (!other)
    {
        return JS_EXCEPTION;
    }
    return JS_NewBool(ctx, a_version_ne(self, other));
}

static JSCFunctionListEntry const js_version_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.version", 0),
    JS_CGETSET_MAGIC_DEF("major", js_version_get, js_version_set, 0),
    JS_CGETSET_MAGIC_DEF("minor", js_version_get, js_version_set, 1),
    JS_CGETSET_MAGIC_DEF("patch", js_version_get, js_version_set, 2),
    JS_CFUNC_DEF("parse", 1, js_version_parse),
    JS_CFUNC_DEF("cmp", 1, js_version_cmp),
    JS_CFUNC_DEF("lt", 1, js_version_lt),
    JS_CFUNC_DEF("gt", 1, js_version_gt),
    JS_CFUNC_DEF("le", 1, js_version_le),
    JS_CFUNC_DEF("ge", 1, js_version_ge),
    JS_CFUNC_DEF("eq", 1, js_version_eq),
    JS_CFUNC_DEF("ne", 1, js_version_ne),
};

static A_INLINE int js_liba_version_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_version_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_version_class_id, &js_version_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_version_proto, A_LEN(js_version_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, js_version_ctor, "version", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, js_version_class_id, proto);

    JS_DefinePropertyValueStr(ctx, clazz, "MAJOR", JS_NewUint32(ctx, A_VERSION_MAJOR), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "MINOR", JS_NewUint32(ctx, A_VERSION_MINOR), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "PATCH", JS_NewUint32(ctx, A_VERSION_PATCH), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "TWEAK", JS_NewUint32(ctx, A_VERSION_TWEAK), 0);
    JSValue const version_check = JS_NewCFunction2(ctx, js_version_check, "check", 3, JS_CFUNC_generic, 0);
    JS_DefinePropertyValueStr(ctx, clazz, "check", version_check, 0);

    JS_SetModuleExport(ctx, m, "version", clazz);
    return 0;
}

static JSCFunctionListEntry const js_liba_funcs[] = {
    JS_OBJECT_DEF("mf", js_liba_mf_funcs, A_LEN(js_liba_mf_funcs), 0),
    JS_PROP_STRING_DEF("VERSION", A_VERSION, 0),
    JS_CFUNC_DEF("hash_bkdr", 1, js_hash_bkdr),
    JS_CFUNC_DEF("rsqrt", 1, js_rsqrt),
};

static int js_liba_init(JSContext *const ctx, JSModuleDef *const m)
{
    js_liba_pid_init(ctx, m);
    js_liba_pid_fuzzy_init(ctx, m);
    js_liba_pid_neuron_init(ctx, m);
    js_liba_polytraj3_init(ctx, m);
    js_liba_polytraj5_init(ctx, m);
    js_liba_polytraj7_init(ctx, m);
    js_liba_tf_init(ctx, m);
    js_liba_version_init(ctx, m);
    return JS_SetModuleExportList(ctx, m, js_liba_funcs, A_LEN(js_liba_funcs));
}

JSModuleDef *js_init_module(JSContext *const ctx, char const *const module_name)
{
    JSModuleDef *m = JS_NewCModule(ctx, module_name, js_liba_init);
    if (m)
    {
        JS_AddModuleExport(ctx, m, "pid");
        JS_AddModuleExport(ctx, m, "pid_fuzzy");
        JS_AddModuleExport(ctx, m, "pid_neuron");
        JS_AddModuleExport(ctx, m, "polytraj3");
        JS_AddModuleExport(ctx, m, "polytraj5");
        JS_AddModuleExport(ctx, m, "polytraj7");
        JS_AddModuleExport(ctx, m, "tf");
        JS_AddModuleExport(ctx, m, "version");
        JS_AddModuleExportList(ctx, m, js_liba_funcs, A_LEN(js_liba_funcs));
    }
    return m;
}
