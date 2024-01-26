#include "a.h"
#include "a/lpf.h"
#include "liba_lpf.h"

#undef L
#define L Java_liba_lpf
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_lpf_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_lpf_init(JNIEnv *_env, jobject _obj, jdouble fc, jdouble ts)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(a_lpf));
    a_lpf *ctx = (a_lpf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    a_lpf_init(ctx, A_LPF_GEN(fc, ts));
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_alpha(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->alpha;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_output(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->output;
}

JNIEXPORT jobject JNICALL Java_liba_lpf_gen(JNIEnv *_env, jobject _obj, jdouble fc, jdouble ts)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->alpha = A_LPF_GEN(fc, ts);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_iter(JNIEnv *_env, jobject _obj, jdouble x)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_lpf_iter(ctx, x);
}

JNIEXPORT jobject JNICALL Java_liba_lpf_zero(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_lpf *ctx = (a_lpf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_lpf_zero(ctx);
    return _obj;
}
