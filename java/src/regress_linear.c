#include "a.h"
#include "a/regress_linear.h"
#include "liba_regress_linear.h"

#undef L
#define L Java_liba_regress_linear
static struct
{
    jmethodID New;
    jfieldID ctx;
    jfieldID coef;
} L = {NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_regress_1linear_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.coef = (*Env)->GetFieldID(Env, Cls, "coef", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_regress_1linear_init(JNIEnv *Env, jobject Obj, jdoubleArray coef, jdouble bias)
{
    jsize n = (*Env)->GetArrayLength(Env, coef);

    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_regress_linear));
    jobject Coef = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)n * 8);

    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *p = (jdouble *)(*Env)->GetDirectBufferAddress(Env, Coef);

    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.coef, Coef);

    (*Env)->GetDoubleArrayRegion(Env, coef, 0, n, p);
    a_regress_linear_init(ctx, p, (a_size)n, bias);
}

JNIEXPORT jdoubleArray JNICALL Java_liba_regress_1linear_coef(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject coef = (*Env)->NewDoubleArray(Env, (jsize)ctx->coef_n);
    (*Env)->SetDoubleArrayRegion(Env, coef, 0, (jsize)ctx->coef_n, ctx->coef_p);
    return coef;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1linear_set_1coef(JNIEnv *Env, jobject Obj, jdoubleArray coef)
{
    jsize n = (*Env)->GetArrayLength(Env, coef);
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    if (n > (jsize)ctx->coef_n)
    {
        jobject Coef = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)n * 8);
        ctx->coef_p = (a_float *)(*Env)->GetDirectBufferAddress(Env, Coef);
        (*Env)->SetObjectField(Env, Obj, L.coef, Coef);
    }
    ctx->coef_n = (a_size)n;
    (*Env)->GetDoubleArrayRegion(Env, coef, 0, n, ctx->coef_p);
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_regress_1linear_bias(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->bias;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1linear_set_1bias(JNIEnv *Env, jobject Obj, jdouble bias)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->bias = bias;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_regress_1linear_eval(JNIEnv *Env, jobject Obj, jdoubleArray Val)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *val = (*Env)->GetDoubleArrayElements(Env, Val, NULL);
    jdouble r = a_regress_linear_eval(ctx, val);
    (*Env)->ReleaseDoubleArrayElements(Env, Val, val, JNI_ABORT);
    return r;
}

JNIEXPORT jdoubleArray JNICALL Java_liba_regress_1linear_err(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size m = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size n = (a_size)(*Env)->GetArrayLength(Env, Y);
    m /= (a_size)ctx->coef_n;
    if (m < n) { n = m; }
    a_regress_linear_err(ctx, n, x, y, y);
    jdoubleArray r = (*Env)->NewDoubleArray(Env, (jsize)n);
    (*Env)->SetDoubleArrayRegion(Env, r, 0, (jsize)n, y);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    return r;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1linear_gd(JNIEnv *Env, jobject Obj, jdoubleArray Input, jdouble error, jdouble alpha)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *input = (*Env)->GetDoubleArrayElements(Env, Input, NULL);
    a_regress_linear_gd(ctx, input, error, alpha);
    (*Env)->ReleaseDoubleArrayElements(Env, Input, input, JNI_ABORT);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1linear_sgd(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y, jdouble alpha)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size m = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size n = (a_size)(*Env)->GetArrayLength(Env, Y);
    m /= (a_size)ctx->coef_n;
    if (m < n) { n = m; }
    a_regress_linear_sgd(ctx, n, x, y, alpha);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1linear_bgd(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y, jdouble alpha)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size m = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size n = (a_size)(*Env)->GetArrayLength(Env, Y);
    m /= (a_size)ctx->coef_n;
    if (m < n) { n = m; }
    a_regress_linear_err(ctx, n, x, y, y);
    a_regress_linear_bgd(ctx, n, x, y, alpha);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_regress_1linear_mgd(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y, jdouble delta, jdouble lrmax, jdouble lrmin, jint lrtim, jint epoch, jint batch)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size m = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size n = (a_size)(*Env)->GetArrayLength(Env, Y);
    m /= (a_size)ctx->coef_n;
    if (m < n) { n = m; }
    a_float *err = (a_float *)a_alloc(0, sizeof(a_float) * n);
    jdouble r = a_regress_linear_mgd(ctx, n, x, y, err, delta, lrmax, lrmin, (a_size)lrtim, (a_size)epoch, (a_size)batch);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    a_alloc(err, 0);
    return r;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1linear_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_linear *ctx = (a_regress_linear *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_regress_linear_zero(ctx);
    return Obj;
}
