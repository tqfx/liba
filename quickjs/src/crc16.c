#include "a.h"
#include "a/crc.h"

struct crc16
{
    a_u16 table[0x100];
    a_u16 (*eval)(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value);
};

static JSClassID liba_crc16_class_id;

static void liba_crc16_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_crc16_class_id));
}

static JSValue liba_crc16_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    a_u32 poly = 0;
    int reversed = 0;
    JSValue proto, clazz = JS_UNDEFINED;
    struct crc16 *const self = (struct crc16 *)js_mallocz(ctx, sizeof(struct crc16));
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToUint32(ctx, &poly, argv[0])) { goto fail; }
    if (argc > 1)
    {
        reversed = JS_ToBool(ctx, argv[1]);
        if (reversed < 0) { goto fail; }
    }
    if (reversed)
    {
        a_crc16l_init(self->table, (a_u16)poly);
        self->eval = a_crc16l;
    }
    else
    {
        a_crc16m_init(self->table, (a_u16)poly);
        self->eval = a_crc16m;
    }
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_crc16_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_UNDEFINED;
}

static JSValue liba_crc16_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_u32 poly = 0;
    int reversed = 0;
    struct crc16 *const self = (struct crc16 *)JS_GetOpaque2(ctx, this_val, liba_crc16_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (JS_ToUint32(ctx, &poly, argv[0])) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        reversed = JS_ToBool(ctx, argv[1]);
        if (reversed < 0) { return JS_EXCEPTION; }
    }
    if (reversed)
    {
        a_crc16l_init(self->table, (a_u16)poly);
        self->eval = a_crc16l;
    }
    else
    {
        a_crc16m_init(self->table, (a_u16)poly);
        self->eval = a_crc16m;
    }
    return JS_UNDEFINED;
}

static JSValue liba_crc16_eval(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    size_t n = 0;
    a_u16 value = 0;
    struct crc16 *const self = (struct crc16 *)JS_GetOpaque2(ctx, this_val, liba_crc16_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        a_u32 x = 0;
        if (JS_ToUint32(ctx, &x, argv[1])) { return JS_EXCEPTION; }
        value = (a_u16)x;
    }
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
    return JS_NewUint32(ctx, value);
}

static JSValue liba_crc16_pack(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue val = JS_UNDEFINED;
    a_u16 value = 0;
    size_t n = 0;
    char const *s;
    a_byte *p;
    struct crc16 *const self = (struct crc16 *)JS_GetOpaque2(ctx, this_val, liba_crc16_class_id);
    if (!self) { return JS_EXCEPTION; }
    if (argc > 1)
    {
        a_u32 x = 0;
        if (JS_ToUint32(ctx, &x, argv[1])) { return JS_EXCEPTION; }
        value = (a_u16)x;
    }
    s = JS_ToCStringLen(ctx, &n, argv[0]);
    value = self->eval(self->table, s, n, value);
    p = (a_byte *)js_malloc(ctx, n + 2);
    if (p) { a_copy(p, s, n); }
    else { goto fail; }
    self->eval == a_crc16m
        ? a_u16_setb(p + n, value)
        : a_u16_setl(p + n, value);
    val = js_array_u8_new(ctx, p, (uint32_t)n + 2);
fail:
    JS_FreeCString(ctx, s);
    js_free(ctx, p);
    return val;
}

static JSValue liba_crc16_get(JSContext *ctx, JSValueConst this_val)
{
    struct crc16 *const self = (struct crc16 *)JS_GetOpaque2(ctx, this_val, liba_crc16_class_id);
    if (!self) { return JS_EXCEPTION; }
    return js_array_u16_new(ctx, self->table, 0x100);
}

static JSClassDef liba_crc16_class;
static JSCFunctionListEntry const liba_crc16_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.crc16", 0),
    JS_CGETSET_DEF("table", liba_crc16_get, NULL),
    JS_CFUNC_DEF("gen", 2, liba_crc16_gen),
    JS_CFUNC_DEF("eval", 2, liba_crc16_eval),
    JS_CFUNC_DEF("pack", 2, liba_crc16_pack),
};

int js_liba_crc16_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, clazz;
    liba_crc16_class.class_name = "crc16";
    liba_crc16_class.finalizer = liba_crc16_finalizer;

    JS_NewClassID(&liba_crc16_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_crc16_class_id, &liba_crc16_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_crc16_proto, A_LEN(liba_crc16_proto));

    clazz = JS_NewCFunction2(ctx, liba_crc16_ctor, "crc16", 2, JS_CFUNC_constructor, 0);
    JS_SetClassProto(ctx, liba_crc16_class_id, proto);
    JS_SetConstructor(ctx, clazz, proto);

    return JS_SetModuleExport(ctx, m, "crc16", clazz);
}
