#include "a.h"
#include "a/hpf.h"
#include "liba_hpf.h"

#undef L
#define L Java_liba_hpf
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_hpf_INIT(JNIEnv *jenv, jclass jcls)
{
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_hpf_init(JNIEnv *jenv, jobject jobj, jdouble fc, jdouble ts)
{
    a_hpf ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_hpf));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    a_hpf_init(&ctx, A_HPF_GEN(fc, ts));
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_alpha(JNIEnv *jenv, jobject jobj)
{
    a_hpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return ctx.alpha;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_output(JNIEnv *jenv, jobject jobj)
{
    a_hpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return ctx.output;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_input(JNIEnv *jenv, jobject jobj)
{
    a_hpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return ctx.input;
}

JNIEXPORT jobject JNICALL Java_liba_hpf_gen(JNIEnv *jenv, jobject jobj, jdouble fc, jdouble ts)
{
    a_hpf ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_hpf));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    ctx.alpha = A_HPF_GEN(fc, ts);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_hpf_iter(JNIEnv *jenv, jobject jobj, jdouble x)
{
    a_hpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    jdouble jres = a_hpf_iter(&ctx, x);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return jres;
}

JNIEXPORT jobject JNICALL Java_liba_hpf_zero(JNIEnv *jenv, jobject jobj)
{
    a_hpf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    a_hpf_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_hpf), (jbyte *)&ctx);
    return jobj;
}
