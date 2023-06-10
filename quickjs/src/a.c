#include "a.h"

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
    (void)(this_val);
    (void)(argc);
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
    (void)(this_val);
    double args[] = {0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_gauss((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_gbell(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)(this_val);
    double args[] = {0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_gbell((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_sig(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)(this_val);
    double args[] = {0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_sig((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_trap(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)(this_val);
    double args[] = {0, 0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_trap((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[3], (a_float_t)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_tri(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)(this_val);
    double args[] = {0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_tri((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSValue js_mf_z(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)(this_val);
    double args[] = {0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_float_t x = a_mf_z((a_float_t)args[0], (a_float_t)args[1], (a_float_t)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

static JSCFunctionListEntry const js_liba_mf_funcs[] = {
    JS_PROP_INT32_DEF("NUL", A_MF_NUL, 0),
    JS_PROP_INT32_DEF("GAUSS", A_MF_GAUSS, 0),
    JS_PROP_INT32_DEF("GBELL", A_MF_GBELL, 0),
    JS_PROP_INT32_DEF("SIG", A_MF_SIG, 0),
    JS_PROP_INT32_DEF("TRAP", A_MF_TRAP, 0),
    JS_PROP_INT32_DEF("TRI", A_MF_TRI, 0),
    JS_PROP_INT32_DEF("Z", A_MF_Z, 0),
    JS_CFUNC_DEF("gauss", 3, js_mf_gauss),
    JS_CFUNC_DEF("gbell", 4, js_mf_gbell),
    JS_CFUNC_DEF("sig", 3, js_mf_sig),
    JS_CFUNC_DEF("trap", 5, js_mf_trap),
    JS_CFUNC_DEF("tri", 4, js_mf_tri),
    JS_CFUNC_DEF("z", 3, js_mf_z),
};

#include "a/version.h"

static JSCFunctionListEntry const js_liba_funcs[] = {
    JS_OBJECT_DEF("mf", js_liba_mf_funcs, countof(js_liba_mf_funcs), 0),
    JS_PROP_STRING_DEF("VERSION", A_VERSION, 0),
    JS_CFUNC_DEF("hash_bkdr", 1, js_hash_bkdr),
    JS_CFUNC_DEF("rsqrt", 1, js_rsqrt),
};

#include "a/polytrack.h"

static JSClassID js_polytrack3_class_id;

static void js_polytrack3_finalizer(JSRuntime *const rt, JSValue const val)
{
    void *const ctx = JS_GetOpaque(val, js_polytrack3_class_id);
    js_free_rt(rt, ctx);
}

static JSClassDef js_polytrack3_class = {"polytrack3", .finalizer = js_polytrack3_finalizer};

static JSValue js_polytrack3_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue obj = JS_UNDEFINED;
    a_polytrack3_s *const polytrack3 = (a_polytrack3_s *)js_mallocz(ctx, sizeof(a_polytrack3_s));
    if (!polytrack3)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            goto fail;
        }
    }
    a_polytrack3_gen(polytrack3,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5]);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    obj = JS_NewObjectProtoClass(ctx, proto, js_polytrack3_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
    {
        goto fail;
    }
    JS_SetOpaque(obj, polytrack3);
    return obj;
fail:
    js_free(ctx, polytrack3);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSValue js_polytrack3_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_polytrack3_s *const polytrack3 = (a_polytrack3_s *)JS_GetOpaque2(ctx, this_val, js_polytrack3_class_id);
    if (!polytrack3)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_polytrack3_gen(polytrack3,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5]);
    return JS_UNDEFINED;
}

static JSValue js_polytrack3_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack3_s *const polytrack3 = (a_polytrack3_s *)JS_GetOpaque2(ctx, this_val, js_polytrack3_class_id);
    if (!polytrack3)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t pos = a_polytrack3_pos(polytrack3, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue js_polytrack3_vel(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack3_s *const polytrack3 = (a_polytrack3_s *)JS_GetOpaque2(ctx, this_val, js_polytrack3_class_id);
    if (!polytrack3)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t vel = a_polytrack3_vel(polytrack3, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue js_polytrack3_acc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack3_s *const polytrack3 = (a_polytrack3_s *)JS_GetOpaque2(ctx, this_val, js_polytrack3_class_id);
    if (!polytrack3)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t acc = a_polytrack3_acc(polytrack3, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const js_polytrack3_proto_funcs[] = {
    JS_CFUNC_DEF("gen", 6, js_polytrack3_gen),
    JS_CFUNC_DEF("pos", 1, js_polytrack3_pos),
    JS_CFUNC_DEF("vel", 1, js_polytrack3_vel),
    JS_CFUNC_DEF("acc", 1, js_polytrack3_acc),
};

static A_INLINE int js_liba_polytrack3_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_polytrack3_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_polytrack3_class_id, &js_polytrack3_class);

    JSValue const polytrack3_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, polytrack3_proto, js_polytrack3_proto_funcs, countof(js_polytrack3_proto_funcs));

    JSValue const polytrack3_class = JS_NewCFunction2(ctx, js_polytrack3_ctor, "polytrack3", 6, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, polytrack3_class, polytrack3_proto);
    JS_SetClassProto(ctx, js_polytrack3_class_id, polytrack3_proto);

    JS_SetModuleExport(ctx, m, "polytrack3", polytrack3_class);
    return 0;
}

static JSClassID js_polytrack5_class_id;

static void js_polytrack5_finalizer(JSRuntime *const rt, JSValue const val)
{
    void *const ctx = JS_GetOpaque(val, js_polytrack5_class_id);
    js_free_rt(rt, ctx);
}

static JSClassDef js_polytrack5_class = {"polytrack5", .finalizer = js_polytrack5_finalizer};

static JSValue js_polytrack5_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue obj = JS_UNDEFINED;
    a_polytrack5_s *const polytrack5 = (a_polytrack5_s *)js_mallocz(ctx, sizeof(a_polytrack5_s));
    if (!polytrack5)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            goto fail;
        }
    }
    a_polytrack5_gen(polytrack5,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5],
                     (a_float_t)args[6], (a_float_t)args[7]);
    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
    {
        goto fail;
    }
    obj = JS_NewObjectProtoClass(ctx, proto, js_polytrack5_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
    {
        goto fail;
    }
    JS_SetOpaque(obj, polytrack5);
    return obj;
fail:
    js_free(ctx, polytrack5);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSValue js_polytrack5_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_polytrack5_s *const polytrack5 = (a_polytrack5_s *)JS_GetOpaque2(ctx, this_val, js_polytrack5_class_id);
    if (!polytrack5)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_polytrack5_gen(polytrack5,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5],
                     (a_float_t)args[6], (a_float_t)args[7]);
    return JS_UNDEFINED;
}

static JSValue js_polytrack5_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack5_s *const polytrack5 = (a_polytrack5_s *)JS_GetOpaque2(ctx, this_val, js_polytrack5_class_id);
    if (!polytrack5)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t pos = a_polytrack5_pos(polytrack5, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue js_polytrack5_vel(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack5_s *const polytrack5 = (a_polytrack5_s *)JS_GetOpaque2(ctx, this_val, js_polytrack5_class_id);
    if (!polytrack5)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t vel = a_polytrack5_vel(polytrack5, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue js_polytrack5_acc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack5_s *const polytrack5 = (a_polytrack5_s *)JS_GetOpaque2(ctx, this_val, js_polytrack5_class_id);
    if (!polytrack5)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t acc = a_polytrack5_acc(polytrack5, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const js_polytrack5_proto_funcs[] = {
    JS_CFUNC_DEF("gen", 8, js_polytrack5_gen),
    JS_CFUNC_DEF("pos", 1, js_polytrack5_pos),
    JS_CFUNC_DEF("vel", 1, js_polytrack5_vel),
    JS_CFUNC_DEF("acc", 1, js_polytrack5_acc),
};

static A_INLINE int js_liba_polytrack5_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_polytrack5_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_polytrack5_class_id, &js_polytrack5_class);

    JSValue const polytrack5_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, polytrack5_proto, js_polytrack5_proto_funcs, countof(js_polytrack5_proto_funcs));

    JSValue const polytrack5_class = JS_NewCFunction2(ctx, js_polytrack5_ctor, "polytrack5", 8, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, polytrack5_class, polytrack5_proto);
    JS_SetClassProto(ctx, js_polytrack5_class_id, polytrack5_proto);

    JS_SetModuleExport(ctx, m, "polytrack5", polytrack5_class);
    return 0;
}

static JSClassID js_polytrack7_class_id;

static void js_polytrack7_finalizer(JSRuntime *const rt, JSValue const val)
{
    void *const ctx = JS_GetOpaque(val, js_polytrack7_class_id);
    js_free_rt(rt, ctx);
}

static JSClassDef js_polytrack7_class = {"polytrack7", .finalizer = js_polytrack7_finalizer};

static JSValue js_polytrack7_ctor(JSContext *const ctx, JSValueConst const new_target, int argc, JSValueConst *const argv)
{
    JSValue obj = JS_UNDEFINED;
    a_polytrack7_s *const polytrack7 = (a_polytrack7_s *)js_mallocz(ctx, sizeof(a_polytrack7_s));
    if (!polytrack7)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            goto fail;
        }
    }
    a_polytrack7_gen(polytrack7,
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
    obj = JS_NewObjectProtoClass(ctx, proto, js_polytrack7_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
    {
        goto fail;
    }
    JS_SetOpaque(obj, polytrack7);
    return obj;
fail:
    js_free(ctx, polytrack7);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSValue js_polytrack7_gen(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    a_polytrack7_s *const polytrack7 = (a_polytrack7_s *)JS_GetOpaque2(ctx, this_val, js_polytrack7_class_id);
    if (!polytrack7)
    {
        return JS_EXCEPTION;
    }
    double args[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)countof(args))
    {
        argc = (int)countof(args);
    }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, args + i, argv[i]))
        {
            return JS_EXCEPTION;
        }
    }
    a_polytrack7_gen(polytrack7,
                     (a_float_t)args[0], (a_float_t)args[1],
                     (a_float_t)args[2], (a_float_t)args[3],
                     (a_float_t)args[4], (a_float_t)args[5],
                     (a_float_t)args[6], (a_float_t)args[7],
                     (a_float_t)args[8], (a_float_t)args[9]);
    return JS_UNDEFINED;
}

static JSValue js_polytrack7_pos(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack7_s *const polytrack7 = (a_polytrack7_s *)JS_GetOpaque2(ctx, this_val, js_polytrack7_class_id);
    if (!polytrack7)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t pos = a_polytrack7_pos(polytrack7, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue js_polytrack7_vel(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack7_s *const polytrack7 = (a_polytrack7_s *)JS_GetOpaque2(ctx, this_val, js_polytrack7_class_id);
    if (!polytrack7)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t vel = a_polytrack7_vel(polytrack7, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue js_polytrack7_acc(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack7_s *const polytrack7 = (a_polytrack7_s *)JS_GetOpaque2(ctx, this_val, js_polytrack7_class_id);
    if (!polytrack7)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t acc = a_polytrack7_acc(polytrack7, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSValue js_polytrack7_jer(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    a_polytrack7_s *const polytrack7 = (a_polytrack7_s *)JS_GetOpaque2(ctx, this_val, js_polytrack7_class_id);
    if (!polytrack7)
    {
        return JS_EXCEPTION;
    }
    double dt = 0;
    if (JS_ToFloat64(ctx, &dt, argv[0]))
    {
        return JS_EXCEPTION;
    }
    a_float_t jer = a_polytrack7_jer(polytrack7, (a_float_t)dt);
    return JS_NewFloat64(ctx, (double)jer);
}

static JSCFunctionListEntry const js_polytrack7_proto_funcs[] = {
    JS_CFUNC_DEF("gen", 10, js_polytrack7_gen),
    JS_CFUNC_DEF("pos", 1, js_polytrack7_pos),
    JS_CFUNC_DEF("vel", 1, js_polytrack7_vel),
    JS_CFUNC_DEF("acc", 1, js_polytrack7_acc),
    JS_CFUNC_DEF("jer", 1, js_polytrack7_jer),
};

static A_INLINE int js_liba_polytrack7_init(JSContext *const ctx, JSModuleDef *const m)
{
    JS_NewClassID(&js_polytrack7_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_polytrack7_class_id, &js_polytrack7_class);

    JSValue const polytrack7_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, polytrack7_proto, js_polytrack7_proto_funcs, countof(js_polytrack7_proto_funcs));

    JSValue const polytrack7_class = JS_NewCFunction2(ctx, js_polytrack7_ctor, "polytrack7", 10, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, polytrack7_class, polytrack7_proto);
    JS_SetClassProto(ctx, js_polytrack7_class_id, polytrack7_proto);

    JS_SetModuleExport(ctx, m, "polytrack7", polytrack7_class);
    return 0;
}

static int js_liba_init(JSContext *const ctx, JSModuleDef *const m)
{
    js_liba_polytrack3_init(ctx, m);
    js_liba_polytrack5_init(ctx, m);
    js_liba_polytrack7_init(ctx, m);
    return JS_SetModuleExportList(ctx, m, js_liba_funcs, countof(js_liba_funcs));
}

JSModuleDef *js_init_module(JSContext *const ctx, char const *const module_name)
{
    JSModuleDef *m = JS_NewCModule(ctx, module_name, js_liba_init);
    if (m)
    {
        JS_AddModuleExport(ctx, m, "polytrack3");
        JS_AddModuleExport(ctx, m, "polytrack5");
        JS_AddModuleExport(ctx, m, "polytrack7");
        JS_AddModuleExportList(ctx, m, js_liba_funcs, countof(js_liba_funcs));
    }
    return m;
}
