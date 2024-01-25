#include "a.h"
#include "a/crc.h"

struct CRC64
{
    a_u64 table[0x100];
    a_u64 (*eval)(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value);
};

static JSClassID liba_crc64_class_id;

static void liba_crc64_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_crc64_class_id));
}

static JSClassDef liba_crc64_class = {"crc64", .finalizer = liba_crc64_finalizer};

static JSValue liba_crc64_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    struct CRC64 *const self = (struct CRC64 *)js_mallocz(ctx, sizeof(struct CRC64));
    if (!self) { return JS_EXCEPTION; }
    a_i64 poly = 0;
    if (JS_ToInt64Ext(ctx, &poly, argv[0])) { goto fail; }
    int reversed = 0;
    if (argc > 1)
    {
        reversed = JS_ToBool(ctx, argv[1]);
        if (reversed < 0) { goto fail; }
    }
    if (reversed)
    {
        a_crc64l_init(self->table, (a_u64)poly);
        self->eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(self->table, (a_u64)poly);
        self->eval = a_crc64m;
    }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_crc64_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_crc64_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    struct CRC64 *const self = (struct CRC64 *)JS_GetOpaque2(ctx, this_val, liba_crc64_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (magic == 0)
    {
        return js_array_u64_new(ctx, self->table, 0x100);
    }
    return JS_UNDEFINED;
}

static JSValue liba_crc64_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    struct CRC64 *const self = (struct CRC64 *)JS_GetOpaque2(ctx, this_val, liba_crc64_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_i64 poly = 0;
    if (JS_ToInt64Ext(ctx, &poly, argv[0])) { return JS_EXCEPTION; }
    int reversed = 0;
    if (argc > 1)
    {
        reversed = JS_ToBool(ctx, argv[1]);
        if (reversed < 0) { return JS_EXCEPTION; }
    }
    if (reversed)
    {
        a_crc64l_init(self->table, (a_u64)poly);
        self->eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(self->table, (a_u64)poly);
        self->eval = a_crc64m;
    }
    return JS_UNDEFINED;
}

static JSValue liba_crc64_eval(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    struct CRC64 *const self = (struct CRC64 *)JS_GetOpaque2(ctx, this_val, liba_crc64_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u64 value = 0;
    if (argc > 1)
    {
        a_i64 x = 0;
        if (JS_ToInt64Ext(ctx, &x, argv[1])) { return JS_EXCEPTION; }
        value = (a_u64)x;
    }
    size_t n = 0;
    if (JS_IsArray(ctx, argv[0]))
    {
        a_byte *p = JS_GetArrayBuffer(ctx, &n, argv[0]);
        if (p) { value = self->eval(self->table, p, n, value); }
    }
    else
    {
        char const *const p = JS_ToCStringLen(ctx, &n, argv[0]);
        value = self->eval(self->table, p, n, value);
        JS_FreeCString(ctx, p);
    }
    return JS_NewBigUint64(ctx, value);
}

static JSValue liba_crc64_pack(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue val = JS_UNDEFINED;
    struct CRC64 *const self = (struct CRC64 *)JS_GetOpaque2(ctx, this_val, liba_crc64_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u64 value = 0;
    if (argc > 1)
    {
        a_i64 x = 0;
        if (JS_ToInt64Ext(ctx, &x, argv[1])) { return JS_EXCEPTION; }
        value = (a_u64)x;
    }
    size_t n = 0;
    char const *const s = JS_ToCStringLen(ctx, &n, argv[0]);
    value = self->eval(self->table, s, n, value);
    a_byte *p = (a_byte *)js_malloc(ctx, n + 8);
    if (p) { a_copy(p, s, n); }
    else { goto fail; }
    self->eval == a_crc64m
        ? a_u64_setb(p + n, value)
        : a_u64_setl(p + n, value);
    val = js_array_u8_new(ctx, p, (uint32_t)n + 8);
fail:
    JS_FreeCString(ctx, s);
    js_free(ctx, p);
    return val;
}

static JSCFunctionListEntry const liba_crc64_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.crc64", 0),
    JS_CGETSET_MAGIC_DEF("table", liba_crc64_get, NULL, 0),
    JS_CFUNC_DEF("gen", 2, liba_crc64_gen),
    JS_CFUNC_DEF("eval", 2, liba_crc64_eval),
    JS_CFUNC_DEF("pack", 2, liba_crc64_pack),
};

int js_liba_crc64_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_crc64_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_crc64_class_id, &liba_crc64_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_crc64_proto, A_LEN(liba_crc64_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_crc64_ctor, "crc64", 2, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_crc64_class_id, proto);

    return JS_SetModuleExport(ctx, m, "crc64", clazz);
}
