#include "a.h"
#include "a/pid.h"
#include "liba_pid.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

#undef L
#define L Java_liba_pid
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_pid_INIT(JNIEnv *_env, jclass _cls)
{
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "RUN", "I"), A_PID_RUN);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "POS", "I"), A_PID_POS);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "INC", "I"), A_PID_INC);
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_pid_init(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_pid));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.kp = 1;
    ctx.summax = +A_FLOAT_INF;
    ctx.summin = -A_FLOAT_INF;
    ctx.outmax = +A_FLOAT_INF;
    ctx.outmin = -A_FLOAT_INF;
    a_pid_init(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_kp__(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_kp__D(JNIEnv *_env, jobject _obj, jdouble kp)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.kp = kp;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_ki__(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_ki__D(JNIEnv *_env, jobject _obj, jdouble ki)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.ki = ki;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_kd__(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_kd__D(JNIEnv *_env, jobject _obj, jdouble kd)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.kd = kd;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_summax__(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_summax__D(JNIEnv *_env, jobject _obj, jdouble summax)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.summax = summax;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_summin__(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_summin__D(JNIEnv *_env, jobject _obj, jdouble summin)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.summin = summin;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_outmax__(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_outmax__D(JNIEnv *_env, jobject _obj, jdouble outmax)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.outmax = outmax;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_outmin__(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_outmin__D(JNIEnv *_env, jobject _obj, jdouble outmin)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    ctx.outmin = outmin;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_out(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_fdb(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_err(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return ctx.err;
}

JNIEXPORT jobject JNICALL Java_liba_pid_kpid(JNIEnv *_env, jobject _obj, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    a_pid_kpid(&ctx, kp, ki, kd);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_run(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    jdouble res = a_pid_run(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return res;
}
JNIEXPORT jdouble JNICALL Java_liba_pid_pos(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    jdouble res = a_pid_pos(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return res;
}
JNIEXPORT jdouble JNICALL Java_liba_pid_inc(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    jdouble res = a_pid_inc(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return res;
}

JNIEXPORT jobject JNICALL Java_liba_pid_zero(JNIEnv *_env, jobject _obj)
{
    a_pid ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    a_pid_zero(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid), (jbyte *)&ctx);
    return _obj;
}
