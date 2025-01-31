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
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_pid_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_pid_init(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_pid));
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    ctx->kp = 1;
    ctx->summax = +A_REAL_INF;
    ctx->summin = -A_REAL_INF;
    ctx->outmax = +A_REAL_INF;
    ctx->outmin = -A_REAL_INF;
    a_pid_init(ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_kp(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1kp(JNIEnv *Env, jobject Obj, jdouble kp)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->kp = kp;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_ki(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1ki(JNIEnv *Env, jobject Obj, jdouble ki)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->ki = ki;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_kd(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1kd(JNIEnv *Env, jobject Obj, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->kd = kd;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_summax(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1summax(JNIEnv *Env, jobject Obj, jdouble summax)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->summax = summax;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_summin(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1summin(JNIEnv *Env, jobject Obj, jdouble summin)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->summin = summin;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_sum(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->sum;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_outmax(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1outmax(JNIEnv *Env, jobject Obj, jdouble outmax)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->outmax = outmax;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_outmin(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1outmin(JNIEnv *Env, jobject Obj, jdouble outmin)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->outmin = outmin;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_out(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_fdb(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_err(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->err;
}

JNIEXPORT jobject JNICALL Java_liba_pid_set_1kpid(JNIEnv *Env, jobject Obj, jdouble kp, jdouble ki, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_set_kpid(ctx, kp, ki, kd);
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_run(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_run(ctx, set, fdb);
}
JNIEXPORT jdouble JNICALL Java_liba_pid_pos(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_pos(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_inc(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_inc(ctx, set, fdb);
}

JNIEXPORT jobject JNICALL Java_liba_pid_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid *ctx = (a_pid *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_zero(ctx);
    return Obj;
}
