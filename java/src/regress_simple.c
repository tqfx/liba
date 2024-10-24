#include "a.h"
#include "a/regress_simple.h"
#include "liba_regress_simple.h"

#undef L
#define L Java_liba_regress_simple
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_regress_1simple_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_regress_1simple_init(JNIEnv *Env, jobject Obj, jdouble coef, jdouble bias)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_regress_simple));
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    a_regress_simple_init(ctx, coef, bias);
}

JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_coef(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->coef;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1simple_set_1coef(JNIEnv *Env, jobject Obj, jdouble coef)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->coef = coef;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_bias(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->bias;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1simple_set_1bias(JNIEnv *Env, jobject Obj, jdouble bias)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->bias = bias;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_eval(JNIEnv *Env, jobject Obj, jdouble val)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_regress_simple_eval(ctx, val);
}

JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_evar(JNIEnv *Env, jobject Obj, jdouble val)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_regress_simple_evar(ctx, val);
}

JNIEXPORT jobject JNICALL Java_liba_regress_1simple_ols(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size x_n = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size y_n = (a_size)(*Env)->GetArrayLength(Env, Y);
    a_regress_simple_ols(ctx, A_MIN(x_n, y_n), x, y);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1simple_ols_1(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y, jdouble x_mean, jdouble y_mean)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size x_n = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size y_n = (a_size)(*Env)->GetArrayLength(Env, Y);
    a_regress_simple_ols_(ctx, A_MIN(x_n, y_n), x, y, x_mean, y_mean);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1simple_olsx(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y, jdouble x_mean)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size x_n = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size y_n = (a_size)(*Env)->GetArrayLength(Env, Y);
    a_regress_simple_olsx(ctx, A_MIN(x_n, y_n), x, y, x_mean);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1simple_olsy(JNIEnv *Env, jobject Obj, jdoubleArray X, jdoubleArray Y, jdouble y_mean)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble *x = (*Env)->GetDoubleArrayElements(Env, X, NULL);
    jdouble *y = (*Env)->GetDoubleArrayElements(Env, Y, NULL);
    a_size x_n = (a_size)(*Env)->GetArrayLength(Env, X);
    a_size y_n = (a_size)(*Env)->GetArrayLength(Env, Y);
    a_regress_simple_olsy(ctx, A_MIN(x_n, y_n), x, y, y_mean);
    (*Env)->ReleaseDoubleArrayElements(Env, Y, y, JNI_ABORT);
    (*Env)->ReleaseDoubleArrayElements(Env, X, x, JNI_ABORT);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_regress_1simple_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_regress_simple *ctx = (a_regress_simple *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_regress_simple_zero(ctx);
    return Obj;
}
