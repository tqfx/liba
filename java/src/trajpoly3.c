#include "a.h"
#include "a/trajpoly3.h"
#include "liba_trajpoly3.h"

#undef L
#define L Java_liba_trajpoly3
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajpoly3_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly3_gen(JNIEnv *Env, jobject Obj, jdouble ts, jdouble p0, jdouble p1, jdouble v0, jdouble v1)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_trajpoly3));
    a_trajpoly3 *ctx = (a_trajpoly3 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    a_trajpoly3_gen(ctx, ts, p0, p1, v0, v1);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly3_c0(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly3 *ctx = (a_trajpoly3 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject p = (*Env)->NewDoubleArray(Env, A_LEN(ctx->c));
    (*Env)->SetDoubleArrayRegion(Env, p, 0, A_LEN(ctx->c), ctx->c);
    return p;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly3_c1(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly3 *ctx = (a_trajpoly3 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble c[A_LEN(ctx->c) - 1];
    jobject v = (*Env)->NewDoubleArray(Env, A_LEN(c));
    a_trajpoly3_c1(ctx, c);
    (*Env)->SetDoubleArrayRegion(Env, v, 0, A_LEN(c), c);
    return v;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly3_c2(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly3 *ctx = (a_trajpoly3 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jdouble c[A_LEN(ctx->c) - 2];
    jobject a = (*Env)->NewDoubleArray(Env, A_LEN(c));
    a_trajpoly3_c2(ctx, c);
    (*Env)->SetDoubleArrayRegion(Env, a, 0, A_LEN(c), c);
    return a;
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly3_pos(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly3 *ctx = (a_trajpoly3 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly3_pos(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly3_vel(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly3 *ctx = (a_trajpoly3 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly3_vel(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly3_acc(JNIEnv *Env, jobject Obj, jdouble x)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_trajpoly3 *ctx = (a_trajpoly3 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_trajpoly3_acc(ctx, x);
}
