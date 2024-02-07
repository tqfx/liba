#include "a.h"
#include "a/trajtrap.h"
#include "liba_trajtrap.h"

#undef L
#define L Java_liba_trajtrap
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajtrap_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_gen(JNIEnv *_env, jobject _obj, jdouble vm, jdouble ac, jdouble de, jdouble q0, jdouble q1, jdouble vs, jdouble ve)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(a_trajtrap));
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    return a_trajtrap_gen(ctx, vm, ac, de, q0, q1, vs, ve);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_t(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->t;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_q0(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->q0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_q1(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->q1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_v0(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->v0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_v1(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->v1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_vc(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->vc;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_ta(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->ta;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_td(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->td;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_qa(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->qa;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_qd(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->qd;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_ac(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->ac;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_de(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->de;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_pos(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajtrap_pos(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_vel(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajtrap_vel(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_acc(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajtrap_acc(ctx, dt);
}
