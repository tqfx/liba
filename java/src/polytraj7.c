#include "a.h"
#include "a/polytraj7.h"
#include "liba_polytraj7.h"

#undef L
#define L Java_liba_polytraj7
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_polytraj7_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

JNIEXPORT jobject JNICALL Java_liba_polytraj7_gen(JNIEnv *_env, jobject _obj, jdouble ts, jdouble q0, jdouble q1, jdouble v0, jdouble v1, jdouble a0, jdouble a1, jdouble j0, jdouble j1)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(a_polytraj7));
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    a_polytraj7_gen(ctx, ts, q0, q1, v0, v1, a0, a1, j0, j1);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_polytraj7_q(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject q = (*_env)->NewDoubleArray(_env, A_LEN(ctx->q));
    (*_env)->SetDoubleArrayRegion(_env, q, 0, A_LEN(ctx->q), ctx->q);
    return q;
}

JNIEXPORT jobject JNICALL Java_liba_polytraj7_v(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject v = (*_env)->NewDoubleArray(_env, A_LEN(ctx->v));
    (*_env)->SetDoubleArrayRegion(_env, v, 0, A_LEN(ctx->v), ctx->v);
    return v;
}

JNIEXPORT jobject JNICALL Java_liba_polytraj7_a(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject a = (*_env)->NewDoubleArray(_env, A_LEN(ctx->a));
    (*_env)->SetDoubleArrayRegion(_env, a, 0, A_LEN(ctx->a), ctx->a);
    return a;
}

JNIEXPORT jobject JNICALL Java_liba_polytraj7_j(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject j = (*_env)->NewDoubleArray(_env, A_LEN(ctx->j));
    (*_env)->SetDoubleArrayRegion(_env, j, 0, A_LEN(ctx->j), ctx->j);
    return j;
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_pos(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_polytraj7_pos(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_vel(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_polytraj7_vel(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_acc(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_polytraj7_acc(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_jer(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_polytraj7 *ctx = (a_polytraj7 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_polytraj7_jer(ctx, dt);
}
