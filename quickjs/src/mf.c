#include "mf.h"

JSValue liba_mf_gauss(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_gauss((a_float)arg[0], (a_float)arg[1], (a_float)arg[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_gauss2(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_gauss2((a_float)arg[0], (a_float)arg[1], (a_float)arg[2], (a_float)arg[3], (a_float)arg[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_gbell(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_gbell((a_float)arg[0], (a_float)arg[1], (a_float)arg[2], (a_float)arg[3]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_sig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_sig((a_float)arg[0], (a_float)arg[1], (a_float)arg[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_dsig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_dsig((a_float)arg[0], (a_float)arg[1], (a_float)arg[2], (a_float)arg[3], (a_float)arg[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_psig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_psig((a_float)arg[0], (a_float)arg[1], (a_float)arg[2], (a_float)arg[3], (a_float)arg[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_trap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_trap((a_float)arg[0], (a_float)arg[1], (a_float)arg[2], (a_float)arg[3], (a_float)arg[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_tri(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_tri((a_float)arg[0], (a_float)arg[1], (a_float)arg[2], (a_float)arg[3]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_lins(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_lins((a_float)arg[0], (a_float)arg[1], (a_float)arg[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_linz(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_linz((a_float)arg[0], (a_float)arg[1], (a_float)arg[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_s(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_s((a_float)arg[0], (a_float)arg[1], (a_float)arg[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_z(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_z((a_float)arg[0], (a_float)arg[1], (a_float)arg[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_pi(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_float x;
    unsigned int i;
    double arg[] = {0, 0, 0, 0, 0};
    for (i = 0; i < A_LEN(arg); ++i)
    {
        if (JS_ToFloat64(ctx, &arg[i], argv[i])) { return JS_EXCEPTION; }
    }
    (void)this_val;
    (void)argc;
    x = a_mf_pi((a_float)arg[0], (a_float)arg[1], (a_float)arg[2], (a_float)arg[3], (a_float)arg[4]);
    return JS_NewFloat64(ctx, (double)x);
}
