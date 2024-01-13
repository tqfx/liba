#include "a.h"
#include "a/pid_neuro.h"
#include "liba_pid_neuro.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

#undef L
#define L Java_liba_pid_1neuro
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_pid_1neuro_INIT(JNIEnv *jenv, jclass jcls)
{
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_pid_1neuro_init(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_pid_neuro));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.summax = +A_FLOAT_INF;
    ctx.pid.summin = -A_FLOAT_INF;
    ctx.pid.outmax = +A_FLOAT_INF;
    ctx.pid.outmin = -A_FLOAT_INF;
    ctx.k = 1;
    ctx.wp = A_FLOAT_C(0.1);
    ctx.wi = A_FLOAT_C(0.1);
    ctx.wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_k__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.k;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_k__D(JNIEnv *jenv, jobject jobj, jdouble k)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.k = k;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kp__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kp__D(JNIEnv *jenv, jobject jobj, jdouble kp)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.kp = kp;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ki__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_ki__D(JNIEnv *jenv, jobject jobj, jdouble ki)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.ki = ki;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kd__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kd__D(JNIEnv *jenv, jobject jobj, jdouble kd)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.kd = kd;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wp__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.wp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wp__D(JNIEnv *jenv, jobject jobj, jdouble wp)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.wp = wp;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wi__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.wi;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wi__D(JNIEnv *jenv, jobject jobj, jdouble wi)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.wi = wi;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wd__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.wd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wd__D(JNIEnv *jenv, jobject jobj, jdouble wd)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.wd = wd;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmax__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmax__D(JNIEnv *jenv, jobject jobj, jdouble outmax)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.outmax = outmax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmin__(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmin__D(JNIEnv *jenv, jobject jobj, jdouble outmin)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.outmin = outmin;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_out(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_fdb(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_err(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.err;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ec(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.ec;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kpid(JNIEnv *jenv, jobject jobj, jdouble k, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    a_pid_neuro_kpid(&ctx, k, kp, ki, kd);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wpid(JNIEnv *jenv, jobject jobj, jdouble wp, jdouble wi, jdouble wd)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    a_pid_neuro_wpid(&ctx, wp, wi, wd);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_run(JNIEnv *jenv, jobject jobj, jdouble set, jdouble fdb)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    jdouble jres = a_pid_neuro_run(&ctx, set, fdb);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jres;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_inc(JNIEnv *jenv, jobject jobj, jdouble set, jdouble fdb)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    jdouble jres = a_pid_neuro_inc(&ctx, set, fdb);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jres;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_zero(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuro ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    a_pid_neuro_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return jobj;
}
