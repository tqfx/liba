#include "a.h"
#include "a/trajtrap.h"
#include "liba_trajtrap.h"

#undef L
#define L Java_liba_trajtrap
static struct
{
    jmethodID _new;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_trajtrap_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _nbb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L._new = (*_env)->GetStaticMethodID(_env, _nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_trajtrap_init(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)sizeof(a_trajtrap));
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_gen(JNIEnv *_env, jobject _obj, jdouble vm, jdouble ac, jdouble de, jdouble p0, jdouble p1, jdouble vs, jdouble ve)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajtrap_gen(ctx, vm, ac, de, p0, p1, vs, ve);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_t(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->t;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_p0(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->p0;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_p1(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->p1;
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

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_pa(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pa;
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_pd(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pd;
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

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_pos(JNIEnv *_env, jobject _obj, jdouble x)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajtrap_pos(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_vel(JNIEnv *_env, jobject _obj, jdouble x)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajtrap_vel(ctx, x);
}

JNIEXPORT jdouble JNICALL Java_liba_trajtrap_acc(JNIEnv *_env, jobject _obj, jdouble x)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_trajtrap *ctx = (a_trajtrap *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_trajtrap_acc(ctx, x);
}
