#include "a.h"
#include "a/hpf.h"
#include "liba_hpf.h"

#undef L
#define L Java_liba_hpf
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_hpf_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_hpf_init(JNIEnv *Env, jobject Obj, jdouble fc, jdouble ts)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_hpf));
    a_hpf *ctx = (a_hpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    a_hpf_init(ctx, A_HPF_GEN(fc, ts));
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_alpha(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_hpf *ctx = (a_hpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->alpha;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_output(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_hpf *ctx = (a_hpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->output;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_input(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_hpf *ctx = (a_hpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->input;
}

JNIEXPORT jobject JNICALL Java_liba_hpf_gen(JNIEnv *Env, jobject Obj, jdouble fc, jdouble ts)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_hpf *ctx = (a_hpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->alpha = A_HPF_GEN(fc, ts);
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_iter(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_hpf *ctx = (a_hpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_hpf_iter(ctx, x);
}

JNIEXPORT jobject JNICALL Java_liba_hpf_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_hpf *ctx = (a_hpf *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_hpf_zero(ctx);
    return Obj;
}
