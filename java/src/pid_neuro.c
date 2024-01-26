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
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_pid_1neuro_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_pid_1neuro_init(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(a_pid_neuro));
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->k = 1;
    ctx->wp = A_FLOAT_C(0.1);
    ctx->wi = A_FLOAT_C(0.1);
    ctx->wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_k__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->k;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_k__D(JNIEnv *_env, jobject _obj, jdouble k)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->k = k;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kp__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kp__D(JNIEnv *_env, jobject _obj, jdouble kp)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.kp = kp;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ki__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_ki__D(JNIEnv *_env, jobject _obj, jdouble ki)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.ki = ki;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kd__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kd__D(JNIEnv *_env, jobject _obj, jdouble kd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.kd = kd;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wp__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->wp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wp__D(JNIEnv *_env, jobject _obj, jdouble wp)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->wp = wp;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wi__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->wi;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wi__D(JNIEnv *_env, jobject _obj, jdouble wi)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->wi = wi;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wd__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->wd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wd__D(JNIEnv *_env, jobject _obj, jdouble wd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->wd = wd;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmax__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmax__D(JNIEnv *_env, jobject _obj, jdouble outmax)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.outmax = outmax;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmin__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmin__D(JNIEnv *_env, jobject _obj, jdouble outmin)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.outmin = outmin;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_out(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_fdb(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_err(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.err;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ec(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->ec;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kpid(JNIEnv *_env, jobject _obj, jdouble k, jdouble kp, jdouble ki, jdouble kd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_neuro_kpid(ctx, k, kp, ki, kd);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wpid(JNIEnv *_env, jobject _obj, jdouble wp, jdouble wi, jdouble wd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_neuro_wpid(ctx, wp, wi, wd);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_run(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_neuro_run(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_inc(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_neuro_inc(ctx, set, fdb);
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_zero(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_neuro_zero(ctx);
    return _obj;
}
