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
    jfieldID block;
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
    L.block = (*Env)->GetFieldID(Env, Cls, "block", "Ljava/nio/ByteBuffer;");
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
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->kp = ctx->pid.kp = 1;
    ctx->opr = a_fuzzy_equ;
    a_pid_fuzzy_init(ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kp__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kp__D(JNIEnv *Env, jobject Obj, jdouble kp)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.kp = ctx->kp = kp;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_ki__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_ki__D(JNIEnv *Env, jobject Obj, jdouble ki)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.ki = ctx->ki = ki;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kd__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kd__D(JNIEnv *Env, jobject Obj, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.kd = ctx->kd = kd;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summax__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summax__D(JNIEnv *Env, jobject Obj, jdouble summax)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.summax = summax;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summin__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summin__D(JNIEnv *Env, jobject Obj, jdouble summin)
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

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmax__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmax__D(JNIEnv *Env, jobject Obj, jdouble outmax)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->pid.outmax = outmax;
    return Obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmin__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return ctx->pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmin__D(JNIEnv *Env, jobject Obj, jdouble outmin)
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

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_order(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->order;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_opr(JNIEnv *Env, jobject Obj, jint opr)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_fuzzy_set_opr(ctx, (unsigned int)opr);
    return Obj;
}

static jobject concat(JNIEnv *Env, jobject Obj, jobjectArray val, jdouble const **out)
{
    jsize length = 0;
    jsize order = (*Env)->GetArrayLength(Env, val);
    for (jsize idx = 0; idx != order; ++idx)
    {
        jobject o = (*Env)->GetObjectArrayElement(Env, val, idx);
        length += (*Env)->GetArrayLength(Env, o);
        (*Env)->DeleteLocalRef(Env, o);
    }
    jobject obj = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)length * 8);
    jdouble *ptr = (jdouble *)(*Env)->GetDirectBufferAddress(Env, obj);
    *out = ptr;
    for (jsize idx = 0, num = 0; idx != order; ++idx, ptr += num)
    {
        jobject o = (*Env)->GetObjectArrayElement(Env, val, idx);
        num = (*Env)->GetArrayLength(Env, o);
        (*Env)->GetDoubleArrayRegion(Env, o, 0, num, ptr);
        (*Env)->DeleteLocalRef(Env, o);
    }
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_rule(JNIEnv *Env, jobject Obj, jobjectArray me, jobjectArray mec,
                                                    jobjectArray mkp, jobjectArray mki, jobjectArray mkd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->order = (unsigned int)(*Env)->GetArrayLength(Env, me);
    jobject Me = concat(Env, Obj, me, &ctx->me);
    jobject Mec = concat(Env, Obj, mec, &ctx->mec);
    jobject Mkp = concat(Env, Obj, mkp, &ctx->mkp);
    jobject Mki = concat(Env, Obj, mki, &ctx->mki);
    jobject Mkd = concat(Env, Obj, mkd, &ctx->mkd);
    (*Env)->SetObjectField(Env, Obj, L.me, Me);
    (*Env)->SetObjectField(Env, Obj, L.mec, Mec);
    (*Env)->SetObjectField(Env, Obj, L.mkp, Mkp);
    (*Env)->SetObjectField(Env, Obj, L.mki, Mki);
    (*Env)->SetObjectField(Env, Obj, L.mkd, Mkd);
    return Obj;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_block__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->block;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_block__I(JNIEnv *Env, jobject Obj, jint num)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    if (num > (jint)ctx->block)
    {
        jobject Block = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)A_PID_FUZZY_BLOCK((unsigned int)num));
        a_pid_fuzzy_set_block(ctx, (*Env)->GetDirectBufferAddress(Env, Block), (a_size)num);
        (*Env)->SetObjectField(Env, Obj, L.block, Block);
    }
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kpid(JNIEnv *Env, jobject Obj, jdouble kp, jdouble ki, jdouble kd)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_pid_fuzzy_kpid(ctx, kp, ki, kd);
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
