#include "a.h"
#include "a/crc.h"

struct CRC8
{
    a_u8 table[0x100];
};

static JSClassID liba_crc8_class_id;

static void liba_crc8_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_crc8_class_id));
}

static JSClassDef liba_crc8_class = {"crc8", .finalizer = liba_crc8_finalizer};

static JSValue liba_crc8_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    struct CRC8 *const self = (struct CRC8 *)js_mallocz(ctx, sizeof(struct CRC8));
    if (!self) { return JS_EXCEPTION; }
    a_u32 poly = 0;
    if (JS_ToUint32(ctx, &poly, argv[0])) { goto fail; }
    int reversed = 0;
    if (argc > 1)
    {
        reversed = JS_ToBool(ctx, argv[1]);
        if (reversed < 0) { goto fail; }
    }
    reversed
        ? a_crc8l_init(self->table, (a_u8)poly)
        : a_crc8m_init(self->table, (a_u8)poly);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_crc8_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_crc8_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    struct CRC8 *const self = (struct CRC8 *)JS_GetOpaque2(ctx, this_val, liba_crc8_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (magic == 0)
    {
        return js_array_u8_new(ctx, self->table, 0x100);
    }
    return JS_UNDEFINED;
}

static JSValue liba_crc8_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    struct CRC8 *const self = (struct CRC8 *)JS_GetOpaque2(ctx, this_val, liba_crc8_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u32 poly = 0;
    if (JS_ToUint32(ctx, &poly, argv[0])) { return JS_EXCEPTION; }
    int reversed = 0;
    if (argc > 1)
    {
        reversed = JS_ToBool(ctx, argv[1]);
        if (reversed < 0) { return JS_EXCEPTION; }
    }
    reversed
        ? a_crc8l_init(self->table, (a_u8)poly)
        : a_crc8m_init(self->table, (a_u8)poly);
    return JS_UNDEFINED;
}

static JSValue liba_crc8_eval(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    struct CRC8 *const self = (struct CRC8 *)JS_GetOpaque2(ctx, this_val, liba_crc8_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u8 value = 0;
    if (argc > 1)
    {
        a_u32 x = 0;
        if (JS_ToUint32(ctx, &x, argv[1])) { return JS_EXCEPTION; }
        value = (a_u8)x;
    }
    size_t n = 0;
    if (JS_IsArray(ctx, argv[0]))
    {
        a_byte *p = JS_GetArrayBuffer(ctx, &n, argv[0]);
        if (p) { value = a_crc8(self->table, p, n, value); }
    }
    else
    {
        char const *const p = JS_ToCStringLen(ctx, &n, argv[0]);
        value = a_crc8(self->table, p, n, value);
        JS_FreeCString(ctx, p);
    }
    return JS_NewUint32(ctx, value);
}

static JSValue liba_crc8_pack(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue val = JS_UNDEFINED;
    struct CRC8 *const self = (struct CRC8 *)JS_GetOpaque2(ctx, this_val, liba_crc8_class_id);
    if (!self) { return JS_EXCEPTION; }
    a_u8 value = 0;
    if (argc > 1)
    {
        a_u32 x = 0;
        if (JS_ToUint32(ctx, &x, argv[1])) { return JS_EXCEPTION; }
        value = (a_u8)x;
    }
    size_t n = 0;
    char const *const s = JS_ToCStringLen(ctx, &n, argv[0]);
    value = a_crc8(self->table, s, n, value);
    a_byte *p = (a_byte *)js_malloc(ctx, n + 1);
    if (p) { a_copy(p, s, n); }
    else { goto fail; }
    p[n] = value;
    val = js_array_u8_new(ctx, p, (uint32_t)n + 1);
fail:
    JS_FreeCString(ctx, s);
    js_free(ctx, p);
    return val;
}

static JSCFunctionListEntry const liba_crc8_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.crc8", 0),
    JS_CGETSET_MAGIC_DEF("table", liba_crc8_get, NULL, 0),
    JS_CFUNC_DEF("gen", 2, liba_crc8_gen),
    JS_CFUNC_DEF("eval", 2, liba_crc8_eval),
    JS_CFUNC_DEF("pack", 2, liba_crc8_pack),
};

int js_liba_crc8_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_crc8_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_crc8_class_id, &liba_crc8_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_crc8_proto, A_LEN(liba_crc8_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_crc8_ctor, "crc8", 2, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_crc8_class_id, proto);

    return JS_SetModuleExport(ctx, m, "crc8", clazz);
}
