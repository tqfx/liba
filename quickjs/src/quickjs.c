#include "a.h"

int js_array_length(JSContext *ctx, JSValueConst val, a_u32 *plen)
{
    JSValue length = JS_GetPropertyStr(ctx, val, "length");
    if (JS_IsUndefined(length)) { return ~0; }
    JS_ToUint32(ctx, plen, length);
    JS_FreeValue(ctx, length);
    return 0;
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

int js_array_num_len(JSContext *ctx, JSValueConst val, unsigned int *num, int dim) // NOLINT(misc-no-recursion)
{
    a_u32 i = 0, n = 0;
    JSValueConst length = JS_GetPropertyStr(ctx, val, "length");
    if (JS_IsUndefined(length)) { return ~0; }
    JS_ToUint32(ctx, &n, length);
    JS_FreeValue(ctx, length);
    for (--dim; i < n; ++i)
    {
        JSValueConst v = JS_GetPropertyUint32(ctx, val, i);
        int tag = JS_VALUE_GET_TAG(v);
        if (tag == JS_TAG_FLOAT64 || tag == JS_TAG_INT ||
            tag <= JS_TAG_BIG_FLOAT) { ++*num; }
        else if (JS_IsArray(ctx, v) && dim > 0)
        {
            js_array_num_len(ctx, v, num, dim);
        }
        JS_FreeValue(ctx, v);
    }
    return 0;
}

a_float *js_array_num_ptr(JSContext *ctx, JSValueConst val, a_float *ptr, int dim) // NOLINT(misc-no-recursion)
{
    a_u32 i = 0, n = 0;
    JSValueConst length = JS_GetPropertyStr(ctx, val, "length");
    JS_ToUint32(ctx, &n, length);
    JS_FreeValue(ctx, length);
    for (--dim; i < n; ++i)
    {
        JSValueConst v = JS_GetPropertyUint32(ctx, val, i);
        int tag = JS_VALUE_GET_TAG(v);
        if (tag == JS_TAG_FLOAT64 || tag == JS_TAG_INT ||
            tag <= JS_TAG_BIG_FLOAT)
        {
            double x = 0;
            JS_ToFloat64(ctx, &x, v);
            *ptr++ = (a_float)x;
        }
        else if (JS_IsArray(ctx, v) && dim > 0)
        {
            ptr = js_array_num_ptr(ctx, v, ptr, dim);
        }
        JS_FreeValue(ctx, v);
    }
    return ptr;
}

a_float *js_array_num_get(JSContext *ctx, JSValueConst val, a_float *ptr, unsigned int *num, int dim)
{
    unsigned int n = 0, n_ = 0;
    int ret = js_array_num_len(ctx, val, &n, dim);
    if (ret == 0)
    {
        if (!num) { num = &n_; }
        if (n > *num)
        {
            ptr = (a_float *)js_realloc(ctx, ptr, sizeof(a_float) * n);
        }
        js_array_num_ptr(ctx, val, ptr, dim);
        *num = n;
        return ptr;
    }
    return NULL;
}
