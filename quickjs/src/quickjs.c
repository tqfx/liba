#include "a.h"

JSValue js_concat(JSContext *ctx, JSValueConst val)
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

int js_array_length(JSContext *ctx, JSValueConst val, a_u32 *plen)
{
    JSValue length = JS_GetPropertyStr(ctx, val, "length");
    if (JS_IsException(length)) { return ~0; }
    int ret = JS_ToUint32(ctx, plen, length);
    JS_FreeValue(ctx, length);
    return ret;
}

JSValue js_array_u8_new(JSContext *ctx, a_u8 const *ptr, a_u32 len)
{
    JSValue val = JS_NewArray(ctx);
    if (JS_IsException(val)) { return val; }
    for (unsigned int i = 0; i < len; ++i)
    {
        JS_SetPropertyUint32(ctx, val, i, JS_NewInt32(ctx, (a_u8)ptr[i]));
    }
    return val;
}

JSValue js_array_u16_new(JSContext *ctx, a_u16 const *ptr, a_u32 len)
{
    JSValue val = JS_NewArray(ctx);
    if (JS_IsException(val)) { return val; }
    for (unsigned int i = 0; i < len; ++i)
    {
        JS_SetPropertyUint32(ctx, val, i, JS_NewInt32(ctx, (a_u8)ptr[i]));
    }
    return val;
}

JSValue js_array_u32_new(JSContext *ctx, a_u32 const *ptr, a_u32 len)
{
    JSValue val = JS_NewArray(ctx);
    if (JS_IsException(val)) { return val; }
    for (unsigned int i = 0; i < len; ++i)
    {
        JS_SetPropertyUint32(ctx, val, i, JS_NewUint32(ctx, ptr[i]));
    }
    return val;
}

JSValue js_array_u64_new(JSContext *ctx, a_u64 const *ptr, a_u32 len)
{
    JSValue val = JS_NewArray(ctx);
    if (JS_IsException(val)) { return val; }
    for (unsigned int i = 0; i < len; ++i)
    {
        JS_SetPropertyUint32(ctx, val, i, JS_NewBigUint64(ctx, ptr[i]));
    }
    return val;
}

JSValue js_array_num_new(JSContext *ctx, a_float const *ptr, a_u32 len)
{
    JSValue val = JS_NewArray(ctx);
    if (JS_IsException(val)) { return val; }
    for (unsigned int i = 0; i < len; ++i)
    {
        JS_SetPropertyUint32(ctx, val, i, JS_NewFloat64(ctx, (double)ptr[i]));
    }
    return val;
}

int js_array_num_get(JSContext *ctx, JSValueConst val, a_float *ptr, a_u32 len)
{
    for (unsigned int i = 0; i < len; ++i)
    {
        JSValue x_ = JS_GetPropertyUint32(ctx, val, i);
        if (JS_IsException(x_)) { return ~0; }
        double x;
        int r = JS_ToFloat64(ctx, &x, x_);
        JS_FreeValue(ctx, x_);
        if (r) { return r; }
        ptr[i] = (a_float)x;
    }
    return 0;
}
