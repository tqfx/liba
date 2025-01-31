#include "a.h"
#include "a/pid_fuzzy.h"
#include "liba_pid_fuzzy.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

#undef L
#define L Java_liba_pid_1fuzzy
static struct
{
    jmethodID New;
    jfieldID ctx;
    jfieldID me;
    jfieldID mec;
    jfieldID mkp;
    jfieldID mki;
    jfieldID mkd;
    jfieldID bfuzz;
} L = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.me = (*Env)->GetFieldID(Env, Cls, "me", "Ljava/nio/ByteBuffer;");
    L.mec = (*Env)->GetFieldID(Env, Cls, "mec", "Ljava/nio/ByteBuffer;");
    L.mkp = (*Env)->GetFieldID(Env, Cls, "mkp", "Ljava/nio/ByteBuffer;");
    L.mki = (*Env)->GetFieldID(Env, Cls, "mki", "Ljava/nio/ByteBuffer;");
    L.mkd = (*Env)->GetFieldID(Env, Cls, "mkd", "Ljava/nio/ByteBuffer;");
    L.bfuzz = (*Env)->GetFieldID(Env, Cls, "bfuzz", "Ljava/nio/ByteBuffer;");
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "CAP", "I"), A_PID_FUZZY_CAP);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "CAP_ALGEBRA", "I"), A_PID_FUZZY_CAP_ALGEBRA);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "CAP_BOUNDED", "I"), A_PID_FUZZY_CAP_BOUNDED);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "CUP", "I"), A_PID_FUZZY_CUP);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "CUP_ALGEBRA", "I"), A_PID_FUZZY_CUP_ALGEBRA);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "CUP_BOUNDED", "I"), A_PID_FUZZY_CUP_BOUNDED);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "EQU", "I"), A_PID_FUZZY_EQU);
}

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_init(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_pid_fuzzy));
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    ctx->pid.summax = +A_REAL_INF;
    ctx->pid.summin = -A_REAL_INF;
    ctx->pid.outmax = +A_REAL_INF;
    ctx->pid.outmin = -A_REAL_INF;
    ctx->kp = ctx->pid.kp = 1;
    ctx->opr = a_fuzzy_equ;
    a_pid_fuzzy_init(ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kp(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1kp(JNIEnv *Env, jobject Obj, jdouble kp)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.kp = ctx->kp = kp;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_ki(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1ki(JNIEnv *Env, jobject Obj, jdouble ki)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.ki = ctx->ki = ki;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kd(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1kd(JNIEnv *Env, jobject Obj, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.kd = ctx->kd = kd;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summax(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1summax(JNIEnv *Env, jobject Obj, jdouble summax)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.summax = summax;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summin(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1summin(JNIEnv *Env, jobject Obj, jdouble summin)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.summin = summin;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_sum(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.sum;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmax(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1outmax(JNIEnv *Env, jobject Obj, jdouble outmax)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.outmax = outmax;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmin(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1outmin(JNIEnv *Env, jobject Obj, jdouble outmin)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.outmin = outmin;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_out(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_fdb(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_err(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.err;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_nrule(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->nrule;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_opr(JNIEnv *Env, jobject Obj, jint opr)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_fuzzy_set_opr(ctx, (unsigned int)opr);
    return Obj;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_nfuzz(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->nfuzz;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1nfuzz(JNIEnv *Env, jobject Obj, jint num)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    if (num > (jint)ctx->nfuzz)
    {
        jobject Bfuzz = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)A_PID_FUZZY_BFUZZ((unsigned int)num));
        a_pid_fuzzy_set_bfuzz(ctx, (*Env)->GetDirectBufferAddress(Env, Bfuzz), (a_size)num);
        (*Env)->SetObjectField(Env, Obj, L.bfuzz, Bfuzz);
    }
    return Obj;
}

static jobject concat(JNIEnv *Env, jobject Obj, jobjectArray val, jdouble const **out)
{
    jobject obj;
    jdouble *ptr;
    jsize idx, num, length = 0;
    jsize n = (*Env)->GetArrayLength(Env, val);
    for (idx = 0; idx != n; ++idx)
    {
        jobject o = (*Env)->GetObjectArrayElement(Env, val, idx);
        length += (*Env)->GetArrayLength(Env, o);
        (*Env)->DeleteLocalRef(Env, o);
    }
    obj = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)length * 8);
    ptr = (jdouble *)(*Env)->GetDirectBufferAddress(Env, obj);
    *out = ptr;
    for (idx = 0; idx != n; ++idx, ptr += num)
    {
        jobject o = (*Env)->GetObjectArrayElement(Env, val, idx);
        num = (*Env)->GetArrayLength(Env, o);
        (*Env)->GetDoubleArrayRegion(Env, o, 0, num, ptr);
        (*Env)->DeleteLocalRef(Env, o);
    }
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1rule(JNIEnv *Env, jobject Obj, jobjectArray me, jobjectArray mec,
                                                         jobjectArray mkp, jobjectArray mki, jobjectArray mkd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jobject Me = concat(Env, Obj, me, &ctx->me);
    jobject Mec = concat(Env, Obj, mec, &ctx->mec);
    jobject Mkp = concat(Env, Obj, mkp, &ctx->mkp);
    jobject Mki = concat(Env, Obj, mki, &ctx->mki);
    jobject Mkd = concat(Env, Obj, mkd, &ctx->mkd);
    ctx->nrule = (unsigned int)(*Env)->GetArrayLength(Env, me);
    (*Env)->SetObjectField(Env, Obj, L.me, Me);
    (*Env)->SetObjectField(Env, Obj, L.mec, Mec);
    (*Env)->SetObjectField(Env, Obj, L.mkp, Mkp);
    (*Env)->SetObjectField(Env, Obj, L.mki, Mki);
    (*Env)->SetObjectField(Env, Obj, L.mkd, Mkd);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_set_1kpid(JNIEnv *Env, jobject Obj, jdouble kp, jdouble ki, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_fuzzy_set_kpid(ctx, kp, ki, kd);
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_run(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_fuzzy_run(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_pos(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_fuzzy_pos(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_inc(JNIEnv *Env, jobject Obj, jdouble set, jdouble fdb)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return a_pid_fuzzy_inc(ctx, set, fdb);
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_zero(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_fuzzy_zero(ctx);
    return Obj;
}
