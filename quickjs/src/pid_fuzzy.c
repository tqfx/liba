#include "a.h"
#include "a/pid_fuzzy.h"

static JSClassID liba_pid_fuzzy_class_id;

static void liba_pid_fuzzy_finalizer(JSRuntime *rt, JSValue val)
{
    a_pid_fuzzy *self = (a_pid_fuzzy *)JS_GetOpaque(val, liba_pid_fuzzy_class_id);
    union
    {
        a_float const *p;
        a_float *o;
    } u;
    js_free_rt(rt, ((void)(u.p = self->me), u.o));
    js_free_rt(rt, ((void)(u.p = self->mec), u.o));
    js_free_rt(rt, ((void)(u.p = self->mkp), u.o));
    js_free_rt(rt, ((void)(u.p = self->mki), u.o));
    js_free_rt(rt, ((void)(u.p = self->mkd), u.o));
    js_free_rt(rt, a_pid_fuzzy_block(self));
    js_free_rt(rt, self);
}

static JSClassDef liba_pid_fuzzy_class = {"pid_fuzzy", .finalizer = liba_pid_fuzzy_finalizer};

static JSValue liba_pid_fuzzy_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    JSValue proto, clazz = JS_UNDEFINED;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)js_mallocz(ctx, sizeof(a_pid_fuzzy));
    if (!self) { return JS_EXCEPTION; }
    self->pid.summax = +A_FLOAT_INF;
    self->pid.summin = -A_FLOAT_INF;
    self->pid.outmax = +A_FLOAT_INF;
    self->pid.outmin = -A_FLOAT_INF;
    self->kp = self->pid.kp = 1;
    self->op = a_fuzzy_equ;
    a_pid_fuzzy_init(self);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_pid_fuzzy_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_pid_fuzzy_op(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u32 op;
    if (JS_ToUint32(ctx, &op, argv[0])) { return JS_EXCEPTION; }
    a_pid_fuzzy_set_op(self, (unsigned int)op);
    return JS_UNDEFINED;
}

static JSValue liba_pid_fuzzy_rule(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    union
    {
        a_float const *p;
        a_float *o;
    } u;
    a_u32 row;
    a_u32 len = 0;
    a_u32 order = 0;
    JSValue res = JS_UNDEFINED;
    if (JS_IsArray(ctx, argv[0]))
    {
        if (js_array_length(ctx, argv[0], &order)) { goto fail; }
        res = js_concat(ctx, argv[0]);
        if (js_array_length(ctx, res, &len)) { goto fail; }
        if (len)
        {
            a_float *const me = (a_float *)js_realloc(ctx, ((void)(u.p = self->me), u.o), sizeof(a_float) * len);
            if (!me) { goto fail; }
            self->me = me;
            if (js_array_num_get(ctx, res, me, len)) { goto fail; }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[1]))
    {
        if (js_array_length(ctx, argv[1], &row) || row != order) { goto fail; }
        res = js_concat(ctx, argv[1]);
        if (js_array_length(ctx, res, &len)) { goto fail; }
        if (len)
        {
            a_float *const mec = (a_float *)js_realloc(ctx, ((void)(u.p = self->mec), u.o), sizeof(a_float) * len);
            if (!mec) { goto fail; }
            self->mec = mec;
            if (js_array_num_get(ctx, res, mec, len)) { goto fail; }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[2]))
    {
        if (js_array_length(ctx, argv[2], &row) || row != order) { goto fail; }
        res = js_concat(ctx, argv[2]);
        if (js_array_length(ctx, res, &len)) { goto fail; }
        if (len)
        {
            a_float *const mkp = (a_float *)js_realloc(ctx, ((void)(u.p = self->mkp), u.o), sizeof(a_float) * len);
            if (!mkp) { goto fail; }
            self->mkp = mkp;
            if (js_array_num_get(ctx, res, mkp, len)) { goto fail; }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[3]))
    {
        if (js_array_length(ctx, argv[3], &row) || row != order) { goto fail; }
        res = js_concat(ctx, argv[3]);
        if (js_array_length(ctx, res, &len)) { goto fail; }
        if (len)
        {
            a_float *const mki = (a_float *)js_realloc(ctx, ((void)(u.p = self->mki), u.o), sizeof(a_float) * len);
            if (!mki) { goto fail; }
            self->mki = mki;
            if (js_array_num_get(ctx, res, mki, len)) { goto fail; }
        }
        JS_FreeValue(ctx, res);
        res = JS_UNDEFINED;
    }
    if (JS_IsArray(ctx, argv[4]))
    {
        if (js_array_length(ctx, argv[4], &row) || row != order) { goto fail; }
        res = js_concat(ctx, argv[4]);
        if (js_array_length(ctx, res, &len)) { goto fail; }
        if (len)
        {
            a_float *const mkd = (a_float *)js_realloc(ctx, ((void)(u.p = self->mkd), u.o), sizeof(a_float) * len);
            if (!mkd) { goto fail; }
            self->mkd = mkd;
            if (js_array_num_get(ctx, res, mkd, len)) { goto fail; }
        }
        JS_FreeValue(ctx, res);
    }
    self->order = order;
    return JS_UNDEFINED;
fail:
    JS_FreeValue(ctx, res);
    return JS_UNDEFINED;
}

static int liba_pid_fuzzy_block_(JSContext *ctx, a_pid_fuzzy *self, unsigned int num)
{
    void *ptr = a_pid_fuzzy_block(self);
    if (num > self->block)
    {
        ptr = js_realloc(ctx, ptr, A_PID_FUZZY_BLOCK(num));
        if (!ptr) { return ~0; }
    }
    a_pid_fuzzy_set_block(self, ptr, num);
    return 0;
}

static JSValue liba_pid_fuzzy_block(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u32 num;
    if (JS_ToUint32(ctx, &num, argv[0])) { return JS_EXCEPTION; }
    if (liba_pid_fuzzy_block_(ctx, self, num)) { return JS_EXCEPTION; }
    return JS_UNDEFINED;
}

static JSValue liba_pid_fuzzy_kpid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_pid_fuzzy_kpid(self, (a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_UNDEFINED;
}

static JSValue liba_pid_fuzzy_zero(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    (void)argv;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_pid_fuzzy_zero(self);
    return JS_UNDEFINED;
}

static JSValue liba_pid_fuzzy_run(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_fuzzy_run(self, (a_float)args[0], (a_float)args[1]));
}

static JSValue liba_pid_fuzzy_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_fuzzy_pos(self, (a_float)args[0], (a_float)args[1]));
}

static JSValue liba_pid_fuzzy_inc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    return JS_NewFloat64(ctx, (double)a_pid_fuzzy_inc(self, (a_float)args[0], (a_float)args[1]));
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
    self_order_,
    self_block_,
};

static JSValue liba_pid_fuzzy_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    double x;
    switch (magic)
    {
    case self_kp_: x = (double)self->kp; break;
    case self_ki_: x = (double)self->ki; break;
    case self_kd_: x = (double)self->kd; break;
    case self_summax_: x = (double)self->pid.summax; break;
    case self_summin_: x = (double)self->pid.summin; break;
    case self_sum_: x = (double)self->pid.sum; break;
    case self_outmax_: x = (double)self->pid.outmax; break;
    case self_outmin_: x = (double)self->pid.outmin; break;
    case self_out_: x = (double)self->pid.out; break;
    case self_fdb_: x = (double)self->pid.fdb; break;
    case self_err_: x = (double)self->pid.err; break;
    case self_order_: return JS_NewUint32(ctx, self->order);
    case self_block_: return JS_NewUint32(ctx, self->block);
    default: return JS_UNDEFINED;
    }
    return JS_NewFloat64(ctx, x);
}

static JSValue liba_pid_fuzzy_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    a_pid_fuzzy *const self = (a_pid_fuzzy *)JS_GetOpaque2(ctx, this_val, liba_pid_fuzzy_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u32 u;
    if (magic == self_block_)
    {
        if (JS_ToUint32(ctx, &u, val)) { return JS_EXCEPTION; }
        if (liba_pid_fuzzy_block_(ctx, self, (unsigned int)u)) { return JS_EXCEPTION; }
        return JS_UNDEFINED;
    }
    double x;
    if (JS_ToFloat64(ctx, &x, val)) { return JS_EXCEPTION; }
    switch (magic)
    {
    case self_kp_: self->pid.kp = self->kp = (a_float)x; break;
    case self_ki_: self->pid.ki = self->ki = (a_float)x; break;
    case self_kd_: self->pid.kd = self->kd = (a_float)x; break;
    case self_summax_: self->pid.summax = (a_float)x; break;
    case self_summin_: self->pid.summin = (a_float)x; break;
    case self_outmax_: self->pid.outmax = (a_float)x; break;
    case self_outmin_: self->pid.outmin = (a_float)x; break;
    default: break;
    }
    return JS_UNDEFINED;
}

static JSCFunctionListEntry const liba_pid_fuzzy_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.pid.fuzzy", 0),
    JS_CGETSET_MAGIC_DEF("kp", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_kp_),
    JS_CGETSET_MAGIC_DEF("ki", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_ki_),
    JS_CGETSET_MAGIC_DEF("kd", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_kd_),
    JS_CGETSET_MAGIC_DEF("summax", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_summax_),
    JS_CGETSET_MAGIC_DEF("summin", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_summin_),
    JS_CGETSET_MAGIC_DEF("sum", liba_pid_fuzzy_get, NULL, self_sum_),
    JS_CGETSET_MAGIC_DEF("outmax", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_outmax_),
    JS_CGETSET_MAGIC_DEF("outmin", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_outmin_),
    JS_CGETSET_MAGIC_DEF("out", liba_pid_fuzzy_get, NULL, self_out_),
    JS_CGETSET_MAGIC_DEF("fdb", liba_pid_fuzzy_get, NULL, self_fdb_),
    JS_CGETSET_MAGIC_DEF("err", liba_pid_fuzzy_get, NULL, self_err_),
    JS_CGETSET_MAGIC_DEF("order", liba_pid_fuzzy_get, NULL, self_order_),
    JS_CGETSET_MAGIC_DEF("block", liba_pid_fuzzy_get, liba_pid_fuzzy_set, self_block_),
    JS_CFUNC_DEF("op", 1, liba_pid_fuzzy_op),
    JS_CFUNC_DEF("rule", 5, liba_pid_fuzzy_rule),
    JS_CFUNC_DEF("set_block", 1, liba_pid_fuzzy_block),
    JS_CFUNC_DEF("kpid", 3, liba_pid_fuzzy_kpid),
    JS_CFUNC_DEF("zero", 0, liba_pid_fuzzy_zero),
    JS_CFUNC_DEF("run", 2, liba_pid_fuzzy_run),
    JS_CFUNC_DEF("pos", 2, liba_pid_fuzzy_pos),
    JS_CFUNC_DEF("inc", 2, liba_pid_fuzzy_inc),
};

int js_liba_pid_fuzzy_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_pid_fuzzy_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_pid_fuzzy_class_id, &liba_pid_fuzzy_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_pid_fuzzy_proto, A_LEN(liba_pid_fuzzy_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_pid_fuzzy_ctor, "pid_fuzzy", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_pid_fuzzy_class_id, proto);

    JS_DefinePropertyValueStr(ctx, clazz, "CAP", JS_NewUint32(ctx, A_PID_FUZZY_CAP), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CAP_ALGEBRA", JS_NewUint32(ctx, A_PID_FUZZY_CAP_ALGEBRA), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CAP_BOUNDED", JS_NewUint32(ctx, A_PID_FUZZY_CAP_BOUNDED), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CUP", JS_NewUint32(ctx, A_PID_FUZZY_CUP), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CUP_ALGEBRA", JS_NewUint32(ctx, A_PID_FUZZY_CUP_ALGEBRA), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "CUP_BOUNDED", JS_NewUint32(ctx, A_PID_FUZZY_CUP_BOUNDED), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "EQU", JS_NewUint32(ctx, A_PID_FUZZY_EQU), 0);

    return JS_SetModuleExport(ctx, m, "pid_fuzzy", clazz);
}
