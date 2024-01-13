#include "a.h"
#include "a/lpf.h"
#include "liba_lpf.h"

#undef L
#define L Java_liba_lpf
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_lpf_INIT(JNIEnv *jenv, jclass jcls)
{
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_lpf_init(JNIEnv *jenv, jobject jobj, jdouble fc, jdouble ts)
{
    a_lpf ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_lpf));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    a_lpf_init(&ctx, A_LPF_GEN(fc, ts));
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_alpha(JNIEnv *jenv, jobject jobj)
{
    a_lpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return ctx.alpha;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_output(JNIEnv *jenv, jobject jobj)
{
    a_lpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return ctx.output;
}

JNIEXPORT jobject JNICALL Java_liba_lpf_gen(JNIEnv *jenv, jobject jobj, jdouble fc, jdouble ts)
{
    a_lpf ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_lpf));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    ctx.alpha = A_LPF_GEN(fc, ts);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_lpf_iter(JNIEnv *jenv, jobject jobj, jdouble x)
{
    a_lpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    jdouble jres = a_lpf_iter(&ctx, x);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return jres;
}

JNIEXPORT jobject JNICALL Java_liba_lpf_zero(JNIEnv *jenv, jobject jobj)
{
    a_lpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    a_lpf_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_lpf), (jbyte *)&ctx);
    return jobj;
}
