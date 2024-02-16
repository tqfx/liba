#include "a.h"
#include "a/trajbell.h"
#include "liba_trajbell.h"

#undef L
#define L Java_liba_trajbell
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajbell_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_trajbell_init(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(a_trajbell));
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_gen(JNIEnv *_env, jobject _obj, jdouble jm, jdouble am, jdouble vm, jdouble p0, jdouble p1, jdouble vs, jdouble ve)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajbell_gen(ctx, jm, am, vm, p0, p1, vs, ve);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_t(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->t;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_tv(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->tv;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_ta(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->ta;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_td(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->td;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_taj(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->taj;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_tdj(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->tdj;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_p0(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->p0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_p1(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->p1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_v0(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->v0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_v1(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->v1;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_vm(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->vm;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_jm(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->jm;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_am(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->am;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_dm(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->dm;
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_pos(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajbell_pos(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_vel(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajbell_vel(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_acc(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajbell_acc(ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_trajbell_jer(JNIEnv *_env, jobject _obj, jdouble dt)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajbell *ctx = (a_trajbell *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajbell_jer(ctx, dt);
}
