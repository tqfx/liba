#include "a.h"
#include "a/trajpoly5.h"
#include "liba_trajpoly5.h"

#undef L
#define L Java_liba_trajpoly5
static struct
{
    jmethodID _new;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajpoly5_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _nbb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L._new = (*_env)->GetStaticMethodID(_env, _nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_gen(JNIEnv *_env, jobject _obj, jdouble ts, jdouble p0, jdouble p1, jdouble v0, jdouble v1, jdouble a0, jdouble a1)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)sizeof(a_trajpoly5));
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    a_trajpoly5_gen(ctx, ts, p0, p1, v0, v1, a0, a1);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_p(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject p = (*_env)->NewDoubleArray(_env, A_LEN(ctx->p));
    (*_env)->SetDoubleArrayRegion(_env, p, 0, A_LEN(ctx->p), ctx->p);
    return p;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_v(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject v = (*_env)->NewDoubleArray(_env, A_LEN(ctx->v));
    (*_env)->SetDoubleArrayRegion(_env, v, 0, A_LEN(ctx->v), ctx->v);
    return v;
}

JNIEXPORT jobject JNICALL Java_liba_trajpoly5_a(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject a = (*_env)->NewDoubleArray(_env, A_LEN(ctx->a));
    (*_env)->SetDoubleArrayRegion(_env, a, 0, A_LEN(ctx->a), ctx->a);
    return a;
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_pos(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajpoly5_pos(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_vel(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajpoly5_vel(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_acc(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajpoly5 *ctx = (a_trajpoly5 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajpoly5_acc(ctx, dt);
}
