#include "a.h"
#include "a/trajpoly5.h"
#include "liba_trajpoly5.h"

#undef L
#define L Java_liba_trajpoly5
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajpoly5_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_gen(JNIEnv *Env, jobject Obj, jdouble ts, jdouble p0, jdouble p1, jdouble v0, jdouble v1, jdouble a0, jdouble a1)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_trajpoly5));
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    a_trajpoly5_gen(ctx, ts, p0, p1, v0, v1, a0, a1);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_p(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject p = (*Env)->NewDoubleArray(Env, A_LEN(ctx->p));
    (*Env)->SetDoubleArrayRegion(Env, p, 0, A_LEN(ctx->p), ctx->p);
    return p;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_v(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject v = (*Env)->NewDoubleArray(Env, A_LEN(ctx->v));
    (*Env)->SetDoubleArrayRegion(Env, v, 0, A_LEN(ctx->v), ctx->v);
    return v;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_a(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject a = (*Env)->NewDoubleArray(Env, A_LEN(ctx->a));
    (*Env)->SetDoubleArrayRegion(Env, a, 0, A_LEN(ctx->a), ctx->a);
    return a;
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_pos(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly5_pos(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_vel(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly5_vel(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_acc(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly5_acc(ctx, x);
}
