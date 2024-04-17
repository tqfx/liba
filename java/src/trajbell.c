#include "a.h"
#include "a/trajbell.h"
#include "liba_trajbell.h"

#undef L
#define L Java_liba_trajbell
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajbell_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_trajbell_init(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_trajbell));
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_gen(JNIEnv *Env, jobject Obj, jdouble jm, jdouble am, jdouble vm, jdouble p0, jdouble p1, jdouble vs, jdouble ve)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajbell_gen(ctx, jm, am, vm, p0, p1, vs, ve);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_t(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->t;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_tv(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->tv;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_ta(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->ta;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_td(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->td;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_taj(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->taj;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_tdj(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->tdj;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_p0(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->p0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_p1(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->p1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_v0(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->v0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_v1(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->v1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_vm(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->vm;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_jm(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->jm;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_am(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->am;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_dm(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->dm;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_pos(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajbell_pos(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_vel(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajbell_vel(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_acc(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajbell_acc(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_jer(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajbell_jer(ctx, x);
}
