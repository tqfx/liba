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
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_pid_1neuro_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_pid_1neuro_init(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_pid_neuro));
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->k = ctx->pid.kp = 1;
    ctx->wp = A_FLOAT_C(0.1);
    ctx->wi = A_FLOAT_C(0.1);
    ctx->wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_k__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->k;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_k__D(JNIEnv *Env, jobject Obj, jdouble k)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->k = k;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kp__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kp__D(JNIEnv *Env, jobject Obj, jdouble kp)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.kp = kp;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ki__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_ki__D(JNIEnv *Env, jobject Obj, jdouble ki)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.ki = ki;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kd__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kd__D(JNIEnv *Env, jobject Obj, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.kd = kd;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wp__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->wp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wp__D(JNIEnv *Env, jobject Obj, jdouble wp)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->wp = wp;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wi__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->wi;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wi__D(JNIEnv *Env, jobject Obj, jdouble wi)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->wi = wi;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wd__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->wd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wd__D(JNIEnv *Env, jobject Obj, jdouble wd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->wd = wd;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmax__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmax__D(JNIEnv *Env, jobject Obj, jdouble outmax)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.outmax = outmax;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmin__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmin__D(JNIEnv *Env, jobject Obj, jdouble outmin)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.outmin = outmin;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_out(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_fdb(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_err(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.err;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ec(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->ec;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kpid(JNIEnv *Env, jobject Obj, jdouble k, jdouble kp, jdouble ki, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_neuro_kpid(ctx, k, kp, ki, kd);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wpid(JNIEnv *Env, jobject Obj, jdouble wp, jdouble wi, jdouble wd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_neuro_wpid(ctx, wp, wi, wd);
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_run(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_neuro_run(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_inc(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_neuro_inc(ctx, set, fdb);
}

JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_neuro *ctx = (a_pid_neuro *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_neuro_zero(ctx);
    return Obj;
}
