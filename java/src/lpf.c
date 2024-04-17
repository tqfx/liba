#include "a.h"
#include "a/lpf.h"
#include "liba_lpf.h"

#undef L
#define L Java_liba_lpf
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_lpf_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_lpf_init(JNIEnv *Env, jobject Obj, jdouble fc, jdouble ts)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_lpf));
    a_lpf *ctx = (a_lpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    a_lpf_init(ctx, A_LPF_GEN(fc, ts));
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_alpha(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->alpha;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_output(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->output;
}

JNIEXPORT jobject JNICALL Java_liba_lpf_gen(JNIEnv *Env, jobject Obj, jdouble fc, jdouble ts)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->alpha = A_LPF_GEN(fc, ts);
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_iter(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_lpf_iter(ctx, x);
}

JNIEXPORT jobject JNICALL Java_liba_lpf_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_lpf_zero(ctx);
    return Obj;
}
