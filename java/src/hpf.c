#include "a.h"
#include "a/hpf.h"
#include "liba_hpf.h"

#undef L
#define L Java_liba_hpf
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_hpf_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_hpf_init(JNIEnv *_env, jobject _obj, jdouble fc, jdouble ts)
{
    a_hpf ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_hpf));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    a_hpf_init(&ctx, A_HPF_GEN(fc, ts));
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_alpha(JNIEnv *_env, jobject _obj)
{
    a_hpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return ctx.alpha;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_output(JNIEnv *_env, jobject _obj)
{
    a_hpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return ctx.output;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_input(JNIEnv *_env, jobject _obj)
{
    a_hpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return ctx.input;
}

JNIEXPORT jobject JNICALL Java_liba_hpf_gen(JNIEnv *_env, jobject _obj, jdouble fc, jdouble ts)
{
    a_hpf ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_hpf));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    ctx.alpha = A_HPF_GEN(fc, ts);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_iter(JNIEnv *_env, jobject _obj, jdouble x)
{
    a_hpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    jdouble res = a_hpf_iter(&ctx, x);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return res;
}

JNIEXPORT jobject JNICALL Java_liba_hpf_zero(JNIEnv *_env, jobject _obj)
{
    a_hpf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    a_hpf_zero(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return _obj;
}
