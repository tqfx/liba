#include "a.h"
#include "a/tf.h"
#include "liba_tf.h"

#undef L
#define L Java_liba_tf
static struct
{
    jmethodID New;
    jfieldID ctx;
    jfieldID num;
    jfieldID den;
    jfieldID input;
    jfieldID output;
} L = {NULL, NULL, NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_tf_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.num = (*Env)->GetFieldID(Env, Cls, "num", "Ljava/nio/ByteBuffer;");
    L.den = (*Env)->GetFieldID(Env, Cls, "den", "Ljava/nio/ByteBuffer;");
    L.input = (*Env)->GetFieldID(Env, Cls, "input", "Ljava/nio/ByteBuffer;");
    L.output = (*Env)->GetFieldID(Env, Cls, "output", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_tf_init(JNIEnv *Env, jobject Obj, jdoubleArray num, jdoubleArray den)
{
    jsize num_n = (*Env)->GetArrayLength(Env, num);
    jsize den_n = (*Env)->GetArrayLength(Env, den);

    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_tf));
    jobject Num = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)num_n * 8);
    jobject Den = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)den_n * 8);
    jobject Input = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)num_n * 8);
    jobject Output = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)den_n * 8);

    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    double *num_p = (double *)(*Env)->GetDirectBufferAddress(Env, Num);
    double *den_p = (double *)(*Env)->GetDirectBufferAddress(Env, Den);
    double *input = (double *)(*Env)->GetDirectBufferAddress(Env, Input);
    double *output = (double *)(*Env)->GetDirectBufferAddress(Env, Output);

    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.num, Num);
    (*Env)->SetObjectField(Env, Obj, L.den, Den);
    (*Env)->SetObjectField(Env, Obj, L.input, Input);
    (*Env)->SetObjectField(Env, Obj, L.output, Output);
    (*Env)->GetDoubleArrayRegion(Env, num, 0, num_n, num_p);
    (*Env)->GetDoubleArrayRegion(Env, den, 0, den_n, den_p);

    ctx->num_p = num_p;
    ctx->den_p = den_p;
    ctx->input = input;
    ctx->output = output;
    ctx->num_n = (unsigned int)num_n;
    ctx->den_n = (unsigned int)den_n;
}

JNIEXPORT jobject JNICALL Java_liba_tf_num(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject num = (*Env)->NewDoubleArray(Env, (jsize)ctx->num_n);
    (*Env)->SetDoubleArrayRegion(Env, num, 0, (jsize)ctx->num_n, ctx->num_p);
    return num;
}

JNIEXPORT jobject JNICALL Java_liba_tf_set_1num(JNIEnv *Env, jobject Obj, jdoubleArray num)
{
    union
    {
        double *p;
        double const *q;
    } u;
    jsize num_n = (*Env)->GetArrayLength(Env, num);
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    if (num_n > (jsize)ctx->num_n)
    {
        jobject Num = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)num_n * 8);
        jobject Input = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)num_n * 8);
        double *num_p = (double *)(*Env)->GetDirectBufferAddress(Env, Num);
        double *input = (double *)(*Env)->GetDirectBufferAddress(Env, Input);
        (*Env)->SetObjectField(Env, Obj, L.num, Num);
        (*Env)->SetObjectField(Env, Obj, L.input, Input);
        ctx->num_n = (unsigned int)num_n;
        ctx->num_p = num_p;
        ctx->input = input;
    }
    u.q = ctx->num_p;
    (*Env)->GetDoubleArrayRegion(Env, num, 0, num_n, u.p);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_tf_input(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject input = (*Env)->NewDoubleArray(Env, (jsize)ctx->num_n);
    (*Env)->SetDoubleArrayRegion(Env, input, 0, (jsize)ctx->num_n, ctx->input);
    return input;
}

JNIEXPORT jobject JNICALL Java_liba_tf_den(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject den = (*Env)->NewDoubleArray(Env, (jsize)ctx->den_n);
    (*Env)->SetDoubleArrayRegion(Env, den, 0, (jsize)ctx->den_n, ctx->den_p);
    return den;
}

JNIEXPORT jobject JNICALL Java_liba_tf_set_1den(JNIEnv *Env, jobject Obj, jdoubleArray den)
{
    union
    {
        double *p;
        double const *q;
    } u;
    jsize den_n = (*Env)->GetArrayLength(Env, den);
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    if (den_n > (jsize)ctx->den_n)
    {
        jobject Den = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)den_n * 8);
        jobject Output = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)den_n * 8);
        double *den_p = (double *)(*Env)->GetDirectBufferAddress(Env, Den);
        double *output = (double *)(*Env)->GetDirectBufferAddress(Env, Output);
        (*Env)->SetObjectField(Env, Obj, L.den, Den);
        (*Env)->SetObjectField(Env, Obj, L.output, Output);
        ctx->den_n = (unsigned int)den_n;
        ctx->den_p = den_p;
        ctx->output = output;
    }
    u.q = ctx->den_p;
    (*Env)->GetDoubleArrayRegion(Env, den, 0, den_n, u.p);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_tf_output(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject output = (*Env)->NewDoubleArray(Env, (jsize)ctx->num_n);
    (*Env)->SetDoubleArrayRegion(Env, output, 0, (jsize)ctx->num_n, ctx->output);
    return output;
}

JNIEXPORT jdouble JNICALL Java_liba_tf_iter(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_tf_iter(ctx, x);
}

JNIEXPORT jobject JNICALL Java_liba_tf_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_tf *ctx = (a_tf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_tf_zero(ctx);
    return Obj;
}
