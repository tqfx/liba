#include "a.h"
#include "a/trajpoly7.h"
#include "liba_trajpoly7.h"

#undef L
#define L Java_liba_trajpoly7
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajpoly7_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_gen(JNIEnv *Env, jobject Obj, jdouble ts, jdouble p0, jdouble p1, jdouble v0, jdouble v1, jdouble a0, jdouble a1, jdouble j0, jdouble j1)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_trajpoly7));
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    a_trajpoly7_gen(ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_p(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject p = (*Env)->NewDoubleArray(Env, A_LEN(ctx->p));
    (*Env)->SetDoubleArrayRegion(Env, p, 0, A_LEN(ctx->p), ctx->p);
    return p;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_v(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject v = (*Env)->NewDoubleArray(Env, A_LEN(ctx->v));
    (*Env)->SetDoubleArrayRegion(Env, v, 0, A_LEN(ctx->v), ctx->v);
    return v;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_a(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject a = (*Env)->NewDoubleArray(Env, A_LEN(ctx->a));
    (*Env)->SetDoubleArrayRegion(Env, a, 0, A_LEN(ctx->a), ctx->a);
    return a;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_j(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject j = (*Env)->NewDoubleArray(Env, A_LEN(ctx->j));
    (*Env)->SetDoubleArrayRegion(Env, j, 0, A_LEN(ctx->j), ctx->j);
    return j;
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_pos(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly7_pos(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_vel(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly7_vel(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_acc(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly7_acc(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_jer(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly7_jer(ctx, x);
}
