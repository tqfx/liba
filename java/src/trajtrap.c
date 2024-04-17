#include "a.h"
#include "a/trajtrap.h"
#include "liba_trajtrap.h"

#undef L
#define L Java_liba_trajtrap
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajtrap_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_trajtrap_init(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_trajtrap));
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_gen(JNIEnv *Env, jobject Obj, jdouble vm, jdouble ac, jdouble de, jdouble p0, jdouble p1, jdouble vs, jdouble ve)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajtrap_gen(ctx, vm, ac, de, p0, p1, vs, ve);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_t(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->t;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_p0(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->p0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_p1(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->p1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_v0(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->v0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_v1(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->v1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_vc(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->vc;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_ta(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->ta;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_td(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->td;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_pa(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pa;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_pd(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pd;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_ac(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->ac;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_de(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->de;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_pos(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajtrap_pos(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_vel(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajtrap_vel(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_acc(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajtrap_acc(ctx, x);
}
