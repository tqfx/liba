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
    jmethodID _new;
    jfieldID ctx;
    jfieldID me;
    jfieldID mec;
    jfieldID mkp;
    jfieldID mki;
    jfieldID mkd;
    jfieldID block;
} L = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _nbb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L._new = (*_env)->GetStaticMethodID(_env, _nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.me = (*_env)->GetFieldID(_env, _cls, "me", "Ljava/nio/ByteBuffer;");
    L.mec = (*_env)->GetFieldID(_env, _cls, "mec", "Ljava/nio/ByteBuffer;");
    L.mkp = (*_env)->GetFieldID(_env, _cls, "mkp", "Ljava/nio/ByteBuffer;");
    L.mki = (*_env)->GetFieldID(_env, _cls, "mki", "Ljava/nio/ByteBuffer;");
    L.mkd = (*_env)->GetFieldID(_env, _cls, "mkd", "Ljava/nio/ByteBuffer;");
    L.block = (*_env)->GetFieldID(_env, _cls, "block", "Ljava/nio/ByteBuffer;");
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CAP", "I"), A_PID_FUZZY_CAP);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CAP_ALGEBRA", "I"), A_PID_FUZZY_CAP_ALGEBRA);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CAP_BOUNDED", "I"), A_PID_FUZZY_CAP_BOUNDED);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CUP", "I"), A_PID_FUZZY_CUP);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CUP_ALGEBRA", "I"), A_PID_FUZZY_CUP_ALGEBRA);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CUP_BOUNDED", "I"), A_PID_FUZZY_CUP_BOUNDED);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "EQU", "I"), A_PID_FUZZY_EQU);
}

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_init(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)sizeof(a_pid_fuzzy));
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->kp = ctx->pid.kp = 1;
    ctx->op = a_fuzzy_equ;
    a_pid_fuzzy_init(ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kp__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kp__D(JNIEnv *_env, jobject _obj, jdouble kp)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.kp = ctx->kp = kp;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_ki__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_ki__D(JNIEnv *_env, jobject _obj, jdouble ki)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.ki = ctx->ki = ki;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kd__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kd__D(JNIEnv *_env, jobject _obj, jdouble kd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.kd = ctx->kd = kd;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summax__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summax__D(JNIEnv *_env, jobject _obj, jdouble summax)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.summax = summax;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summin__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summin__D(JNIEnv *_env, jobject _obj, jdouble summin)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.summin = summin;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_sum(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.sum;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmax__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmax__D(JNIEnv *_env, jobject _obj, jdouble outmax)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.outmax = outmax;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmin__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmin__D(JNIEnv *_env, jobject _obj, jdouble outmin)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->pid.outmin = outmin;
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_out(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_fdb(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_err(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return ctx->pid.err;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_order(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return (jint)ctx->order;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_op(JNIEnv *_env, jobject _obj, jint op)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_fuzzy_set_op(ctx, (unsigned int)op);
    return _obj;
}

static jobject concat(JNIEnv *_env, jobject _obj, jobjectArray _val, jdouble const **out)
{
    jsize length = 0;
    jsize order = (*_env)->GetArrayLength(_env, _val);
    for (jsize idx = 0; idx != order; ++idx)
    {
        jobject o = (*_env)->GetObjectArrayElement(_env, _val, idx);
        length += (*_env)->GetArrayLength(_env, o);
        (*_env)->DeleteLocalRef(_env, o);
    }
    jobject obj = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)length * 8);
    jdouble *ptr = (jdouble *)(*_env)->GetDirectBufferAddress(_env, obj);
    *out = ptr;
    for (jsize idx = 0, num = 0; idx != order; ++idx, ptr += num)
    {
        jobject o = (*_env)->GetObjectArrayElement(_env, _val, idx);
        num = (*_env)->GetArrayLength(_env, o);
        (*_env)->GetDoubleArrayRegion(_env, o, 0, num, ptr);
        (*_env)->DeleteLocalRef(_env, o);
    }
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_rule(JNIEnv *_env, jobject _obj, jobjectArray me, jobjectArray mec,
                                                    jobjectArray mkp, jobjectArray mki, jobjectArray mkd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->order = (unsigned int)(*_env)->GetArrayLength(_env, me);
    jobject _me = concat(_env, _obj, me, &ctx->me);
    jobject _mec = concat(_env, _obj, mec, &ctx->mec);
    jobject _mkp = concat(_env, _obj, mkp, &ctx->mkp);
    jobject _mki = concat(_env, _obj, mki, &ctx->mki);
    jobject _mkd = concat(_env, _obj, mkd, &ctx->mkd);
    (*_env)->SetObjectField(_env, _obj, L.me, _me);
    (*_env)->SetObjectField(_env, _obj, L.mec, _mec);
    (*_env)->SetObjectField(_env, _obj, L.mkp, _mkp);
    (*_env)->SetObjectField(_env, _obj, L.mki, _mki);
    (*_env)->SetObjectField(_env, _obj, L.mkd, _mkd);
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_block__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return (jint)ctx->block;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_block__I(JNIEnv *_env, jobject _obj, jint num)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    if (num > (jint)ctx->block)
    {
        jobject _block = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)A_PID_FUZZY_BLOCK((unsigned int)num));
        a_pid_fuzzy_set_block(ctx, (*_env)->GetDirectBufferAddress(_env, _block), (a_size)num);
        (*_env)->SetObjectField(_env, _obj, L.block, _block);
    }
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kpid(JNIEnv *_env, jobject _obj, jdouble kp, jdouble ki, jdouble kd)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_fuzzy_kpid(ctx, kp, ki, kd);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_run(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_fuzzy_run(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_pos(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_fuzzy_pos(ctx, set, fdb);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_inc(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_pid_fuzzy_inc(ctx, set, fdb);
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_zero(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_pid_fuzzy *ctx = (a_pid_fuzzy *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_pid_fuzzy_zero(ctx);
    return _obj;
}
