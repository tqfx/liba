#include "mf.h"

JSValue liba_mf_gauss(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_gauss((a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_gauss2(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_gauss2((a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3], (a_float)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_gbell(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_gbell((a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_sig(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_sig((a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_dsig(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_dsig((a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3], (a_float)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_psig(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_psig((a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3], (a_float)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_trap(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_trap((a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3], (a_float)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_tri(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_tri((a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_lins(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_lins((a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_linz(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_linz((a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_s(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_s((a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_z(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_z((a_float)args[0], (a_float)args[1], (a_float)args[2]);
    return JS_NewFloat64(ctx, (double)x);
}

JSValue liba_mf_pi(JSContext *const ctx, JSValueConst const this_val, int argc, JSValueConst *const argv)
{
    (void)argc;
    (void)this_val;
    double args[] = {0, 0, 0, 0, 0};
    for (unsigned int i = 0; i < A_LEN(args); ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_float x = a_mf_pi((a_float)args[0], (a_float)args[1], (a_float)args[2], (a_float)args[3], (a_float)args[4]);
    return JS_NewFloat64(ctx, (double)x);
}
