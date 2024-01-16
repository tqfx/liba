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

JNIEXPORT void JNICALL Java_liba_pid_1neuro_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_pid_1neuro_init(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_pid_neuro));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.summax = +A_FLOAT_INF;
    ctx.pid.summin = -A_FLOAT_INF;
    ctx.pid.outmax = +A_FLOAT_INF;
    ctx.pid.outmin = -A_FLOAT_INF;
    ctx.k = 1;
    ctx.wp = A_FLOAT_C(0.1);
    ctx.wi = A_FLOAT_C(0.1);
    ctx.wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_k__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.k;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_k__D(JNIEnv *_env, jobject _obj, jdouble k)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.k = k;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kp__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kp__D(JNIEnv *_env, jobject _obj, jdouble kp)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.kp = kp;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ki__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_ki__D(JNIEnv *_env, jobject _obj, jdouble ki)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.ki = ki;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kd__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kd__D(JNIEnv *_env, jobject _obj, jdouble kd)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.kd = kd;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wp__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.wp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wp__D(JNIEnv *_env, jobject _obj, jdouble wp)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.wp = wp;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wi__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.wi;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wi__D(JNIEnv *_env, jobject _obj, jdouble wi)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.wi = wi;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wd__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.wd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wd__D(JNIEnv *_env, jobject _obj, jdouble wd)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.wd = wd;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmax__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmax__D(JNIEnv *_env, jobject _obj, jdouble outmax)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.outmax = outmax;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmin__(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmin__D(JNIEnv *_env, jobject _obj, jdouble outmin)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    ctx.pid.outmin = outmin;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_out(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_fdb(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_err(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.pid.err;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ec(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return ctx.ec;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kpid(JNIEnv *_env, jobject _obj, jdouble k, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    a_pid_neuro_kpid(&ctx, k, kp, ki, kd);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wpid(JNIEnv *_env, jobject _obj, jdouble wp, jdouble wi, jdouble wd)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    a_pid_neuro_wpid(&ctx, wp, wi, wd);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_run(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    jdouble res = a_pid_neuro_run(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return res;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_inc(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    jdouble res = a_pid_neuro_inc(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return res;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_zero(JNIEnv *_env, jobject _obj)
{
    a_pid_neuro ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    a_pid_neuro_zero(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_neuro), (jbyte *)&ctx);
    return _obj;
}
