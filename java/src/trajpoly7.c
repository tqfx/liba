#include "a.h"
#include "a/trajpoly7.h"
#include "liba_trajpoly7.h"

#undef L
#define L Java_liba_trajpoly7
static struct
{
    jmethodID _new;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajpoly7_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _nbb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L._new = (*_env)->GetStaticMethodID(_env, _nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_gen(JNIEnv *_env, jobject _obj, jdouble ts, jdouble p0, jdouble p1, jdouble v0, jdouble v1, jdouble a0, jdouble a1, jdouble j0, jdouble j1)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)sizeof(a_trajpoly7));
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    a_trajpoly7_gen(ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_p(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject p = (*_env)->NewDoubleArray(_env, A_LEN(ctx->p));
    (*_env)->SetDoubleArrayRegion(_env, p, 0, A_LEN(ctx->p), ctx->p);
    return p;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_v(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject v = (*_env)->NewDoubleArray(_env, A_LEN(ctx->v));
    (*_env)->SetDoubleArrayRegion(_env, v, 0, A_LEN(ctx->v), ctx->v);
    return v;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_a(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject a = (*_env)->NewDoubleArray(_env, A_LEN(ctx->a));
    (*_env)->SetDoubleArrayRegion(_env, a, 0, A_LEN(ctx->a), ctx->a);
    return a;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly7_j(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject j = (*_env)->NewDoubleArray(_env, A_LEN(ctx->j));
    (*_env)->SetDoubleArrayRegion(_env, j, 0, A_LEN(ctx->j), ctx->j);
    return j;
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_pos(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajpoly7_pos(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_vel(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajpoly7_vel(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_acc(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajpoly7_acc(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_jer(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly7 *ctx = (a_trajpoly7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajpoly7_jer(ctx, dt);
}
