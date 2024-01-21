#include "a.h"
#include "a/version.h"

static JSClassID liba_version_class_id;

static void liba_version_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_version_class_id));
}

static JSClassDef liba_version_class = {"version", .finalizer = liba_version_finalizer};

static JSValue liba_version_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_version *const self = (a_version *)js_mallocz(ctx, sizeof(a_version));
    if (!self) { return JS_EXCEPTION; }
    char const *ver = NULL;
    a_u32 args[] = {0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToUint32(ctx, &args[i], argv[i]))
        {
            if (!i)
            {
                ver = JS_ToCString(ctx, argv[0]);
                if (ver) { break; }
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
        self->third = (unsigned int)args[2];
    }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_version_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_version_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u32 ver;
    switch (magic)
    {
    case 0: ver = self->major; break;
    case 1: ver = self->minor; break;
    case 2: ver = self->third; break;
    case 3: ver = self->extra; break;
    default: return JS_UNDEFINED;
    }
    return JS_NewUint32(ctx, ver);
}

static JSValue liba_version_set(JSContext *ctx, JSValueConst this_val, JSValueConst val, int magic)
{
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u32 ver;
    if (JS_ToUint32(ctx, &ver, val)) { return JS_EXCEPTION; }
    switch (magic)
    {
    case 0: self->major = (unsigned int)ver; break;
    case 1: self->minor = (unsigned int)ver; break;
    case 2: self->third = (unsigned int)ver; break;
    case 3: self->extra = (unsigned int)ver; break;
    default: break;
    }
    return JS_UNDEFINED;
}

static JSValue liba_version_check(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)this_val;
    a_u32 args[] = {0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < argc; ++i)
    {
        if (JS_ToUint32(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
#undef a_version_check
    return JS_NewInt32(ctx, a_version_check((unsigned int)args[0], (unsigned int)args[1], (unsigned int)args[2]));
}

static JSValue liba_version_parse(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    char const *ver = JS_ToCString(ctx, argv[0]);
    if (!ver) { return JS_EXCEPTION; }
    a_version_parse(self, ver);
    JS_FreeCString(ctx, ver);
    return JS_UNDEFINED;
}

static JSValue liba_version_cmp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_version *const other = (a_version *)JS_GetOpaque2(ctx, argv[0], liba_version_class_id);
    if (!other) { return JS_EXCEPTION; }
    return JS_NewInt32(ctx, a_version_cmp(self, other));
}

static JSValue liba_version_lt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_version *const other = (a_version *)JS_GetOpaque2(ctx, argv[0], liba_version_class_id);
    if (!other) { return JS_EXCEPTION; }
    return JS_NewBool(ctx, a_version_lt(self, other));
}

static JSValue liba_version_gt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_version *const other = (a_version *)JS_GetOpaque2(ctx, argv[0], liba_version_class_id);
    if (!other) { return JS_EXCEPTION; }
    return JS_NewBool(ctx, a_version_gt(self, other));
}

static JSValue liba_version_le(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_version *const other = (a_version *)JS_GetOpaque2(ctx, argv[0], liba_version_class_id);
    if (!other) { return JS_EXCEPTION; }
    return JS_NewBool(ctx, a_version_le(self, other));
}

static JSValue liba_version_ge(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_version *const other = (a_version *)JS_GetOpaque2(ctx, argv[0], liba_version_class_id);
    if (!other) { return JS_EXCEPTION; }
    return JS_NewBool(ctx, a_version_ge(self, other));
}

static JSValue liba_version_eq(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_version *const other = (a_version *)JS_GetOpaque2(ctx, argv[0], liba_version_class_id);
    if (!other) { return JS_EXCEPTION; }
    return JS_NewBool(ctx, a_version_eq(self, other));
}

static JSValue liba_version_ne(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_version *const self = (a_version *)JS_GetOpaque2(ctx, this_val, liba_version_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_version *const other = (a_version *)JS_GetOpaque2(ctx, argv[0], liba_version_class_id);
    if (!other) { return JS_EXCEPTION; }
    return JS_NewBool(ctx, a_version_ne(self, other));
}

static JSCFunctionListEntry const liba_version_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.version", 0),
    JS_CGETSET_MAGIC_DEF("major", liba_version_get, liba_version_set, 0),
    JS_CGETSET_MAGIC_DEF("minor", liba_version_get, liba_version_set, 1),
    JS_CGETSET_MAGIC_DEF("third", liba_version_get, liba_version_set, 2),
    JS_CGETSET_MAGIC_DEF("extra", liba_version_get, liba_version_set, 3),
    JS_CFUNC_DEF("parse", 1, liba_version_parse),
    JS_CFUNC_DEF("cmp", 1, liba_version_cmp),
    JS_CFUNC_DEF("lt", 1, liba_version_lt),
    JS_CFUNC_DEF("gt", 1, liba_version_gt),
    JS_CFUNC_DEF("le", 1, liba_version_le),
    JS_CFUNC_DEF("ge", 1, liba_version_ge),
    JS_CFUNC_DEF("eq", 1, liba_version_eq),
    JS_CFUNC_DEF("ne", 1, liba_version_ne),
};

int js_liba_version_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_version_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_version_class_id, &liba_version_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_version_proto, A_LEN(liba_version_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_version_ctor, "version", 3, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_version_class_id, proto);

    JSValue const version_check = JS_NewCFunction2(ctx, liba_version_check, "check", 3, JS_CFUNC_generic, 0);
    JS_DefinePropertyValueStr(ctx, clazz, "MAJOR", JS_NewUint32(ctx, A_VERSION_MAJOR), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "MINOR", JS_NewUint32(ctx, A_VERSION_MINOR), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "PATCH", JS_NewUint32(ctx, A_VERSION_PATCH), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "TWEAK", JS_NewUint32(ctx, A_VERSION_TWEAK), 0);
    JS_DefinePropertyValueStr(ctx, clazz, "check", version_check, 0);

    return JS_SetModuleExport(ctx, m, "version", clazz);
}
