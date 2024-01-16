#include "a.h"
#include "a/lpf.h"
#include "liba_lpf.h"

#undef L
#define L Java_liba_lpf
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_lpf_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_lpf_init(JNIEnv *_env, jobject _obj, jdouble fc, jdouble ts)
{
    a_lpf ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_lpf));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    a_lpf_init(&ctx, A_LPF_GEN(fc, ts));
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_alpha(JNIEnv *_env, jobject _obj)
{
    a_lpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return ctx.alpha;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_output(JNIEnv *_env, jobject _obj)
{
    a_lpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return ctx.output;
}

JNIEXPORT jobject JNICALL Java_liba_lpf_gen(JNIEnv *_env, jobject _obj, jdouble fc, jdouble ts)
{
    a_lpf ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_lpf));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    ctx.alpha = A_LPF_GEN(fc, ts);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_iter(JNIEnv *_env, jobject _obj, jdouble x)
{
    a_lpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    jdouble res = a_lpf_iter(&ctx, x);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return res;
}

JNIEXPORT jobject JNICALL Java_liba_lpf_zero(JNIEnv *_env, jobject _obj)
{
    a_lpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    a_lpf_zero(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return _obj;
}
