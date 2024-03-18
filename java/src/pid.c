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
    jmethodID _new;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_pid_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _nbb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L._new = (*_env)->GetStaticMethodID(_env, _nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_pid_init(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)sizeof(a_pid));
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    ctx->kp = 1;
    ctx->summax = +A_FLOAT_INF;
    ctx->summin = -A_FLOAT_INF;
    ctx->outmax = +A_FLOAT_INF;
    ctx->outmin = -A_FLOAT_INF;
    a_pid_init(ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_kp__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_kp__D(JNIEnv *_env, jobject _obj, jdouble kp)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->kp = kp;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_ki__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_ki__D(JNIEnv *_env, jobject _obj, jdouble ki)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->ki = ki;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_kd__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_kd__D(JNIEnv *_env, jobject _obj, jdouble kd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->kd = kd;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_summax__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_summax__D(JNIEnv *_env, jobject _obj, jdouble summax)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->summax = summax;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_summin__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_summin__D(JNIEnv *_env, jobject _obj, jdouble summin)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->summin = summin;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_sum(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->sum;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_outmax__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_outmax__D(JNIEnv *_env, jobject _obj, jdouble outmax)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->outmax = outmax;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_outmin__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_outmin__D(JNIEnv *_env, jobject _obj, jdouble outmin)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->outmin = outmin;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_out(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_fdb(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_err(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->err;
}

JNIEXPORT jobject JNICALL Java_liba_pid_kpid(JNIEnv *_env, jobject _obj, jdouble kp, jdouble ki, jdouble kd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_kpid(ctx, kp, ki, kd);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_run(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_run(ctx, set, fdb);
}
JNIEXPORT jdouble JNICALL Java_liba_pid_pos(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_pos(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_inc(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_inc(ctx, set, fdb);
}

JNIEXPORT jobject JNICALL Java_liba_pid_zero(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid *ctx = (a_pid *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_zero(ctx);
    return _obj;
}
