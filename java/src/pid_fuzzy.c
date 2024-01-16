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
    jfieldID ctx;
    jfieldID me;
    jfieldID mec;
    jfieldID mkp;
    jfieldID mki;
    jfieldID mkd;
    jfieldID joint;
} L = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_INIT(JNIEnv *_env, jclass _cls)
{
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CAP", "I"), A_PID_FUZZY_CAP);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CAP_ALGEBRA", "I"), A_PID_FUZZY_CAP_ALGEBRA);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CAP_BOUNDED", "I"), A_PID_FUZZY_CAP_BOUNDED);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CUP", "I"), A_PID_FUZZY_CUP);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CUP_ALGEBRA", "I"), A_PID_FUZZY_CUP_ALGEBRA);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "CUP_BOUNDED", "I"), A_PID_FUZZY_CUP_BOUNDED);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "EQU", "I"), A_PID_FUZZY_EQU);
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
    L.me = (*_env)->GetFieldID(_env, _cls, "me", "[D");
    L.mec = (*_env)->GetFieldID(_env, _cls, "mec", "[D");
    L.mkp = (*_env)->GetFieldID(_env, _cls, "mkp", "[D");
    L.mki = (*_env)->GetFieldID(_env, _cls, "mki", "[D");
    L.mkd = (*_env)->GetFieldID(_env, _cls, "mkd", "[D");
    L.joint = (*_env)->GetFieldID(_env, _cls, "joint", "[B");
}

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_init(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_pid_fuzzy));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.kp = 1;
    ctx.pid.summax = +A_FLOAT_INF;
    ctx.pid.summin = -A_FLOAT_INF;
    ctx.pid.outmax = +A_FLOAT_INF;
    ctx.pid.outmin = -A_FLOAT_INF;
    ctx.kp = 1;
    ctx.op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    a_pid_fuzzy_init(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kp__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kp__D(JNIEnv *_env, jobject _obj, jdouble kp)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.kp = ctx.kp = kp;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_ki__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_ki__D(JNIEnv *_env, jobject _obj, jdouble ki)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.ki = ctx.ki = ki;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kd__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kd__D(JNIEnv *_env, jobject _obj, jdouble kd)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.kd = ctx.kd = kd;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summax__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.pid.summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summax__D(JNIEnv *_env, jobject _obj, jdouble summax)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.summax = summax;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summin__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.pid.summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summin__D(JNIEnv *_env, jobject _obj, jdouble summin)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.summin = summin;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmax__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmax__D(JNIEnv *_env, jobject _obj, jdouble outmax)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.outmax = outmax;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmin__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmin__D(JNIEnv *_env, jobject _obj, jdouble outmin)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.pid.outmin = outmin;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_out(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_fdb(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_err(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return ctx.pid.err;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_order(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return (jint)ctx.order;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_op(JNIEnv *_env, jobject _obj, jint op)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    a_pid_fuzzy_set_op(&ctx, (unsigned int)op);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

static jobject concat(JNIEnv *_env, jobjectArray _val)
{
    jsize length = 0;
    jsize num = (*_env)->GetArrayLength(_env, _val);
    for (jsize idx = 0; idx != num; ++idx)
    {
        jobject o = (*_env)->GetObjectArrayElement(_env, _val, idx);
        length += (*_env)->GetArrayLength(_env, o);
        (*_env)->DeleteLocalRef(_env, o);
    }
    jobject obj = (*_env)->NewDoubleArray(_env, length);
    jdouble *val = (*_env)->GetDoubleArrayElements(_env, obj, NULL), *_ptr = val;
    for (jsize idx = 0, _num = 0; idx != num; ++idx, _ptr += _num)
    {
        jobject o = (*_env)->GetObjectArrayElement(_env, _val, idx);
        _num = (*_env)->GetArrayLength(_env, o);
        (*_env)->GetDoubleArrayRegion(_env, o, 0, _num, _ptr);
        (*_env)->DeleteLocalRef(_env, o);
    }
    (*_env)->ReleaseDoubleArrayElements(_env, obj, val, 0);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_rule(JNIEnv *_env, jobject _obj, jobjectArray me, jobjectArray mec,
                                                    jobjectArray mkp, jobjectArray mki, jobjectArray mkd)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.order = (unsigned int)(*_env)->GetArrayLength(_env, me);
    (*_env)->SetObjectField(_env, _obj, L.me, concat(_env, me));
    (*_env)->SetObjectField(_env, _obj, L.mec, concat(_env, mec));
    (*_env)->SetObjectField(_env, _obj, L.mkp, concat(_env, mkp));
    (*_env)->SetObjectField(_env, _obj, L.mki, concat(_env, mki));
    (*_env)->SetObjectField(_env, _obj, L.mkd, concat(_env, mkd));
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_joint__(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return (jint)ctx.joint;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_joint__I(JNIEnv *_env, jobject _obj, jint num)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    if (ctx.joint != (unsigned int)num)
    {
        ctx.joint = (unsigned int)num;
        (*_env)->SetObjectField(_env, _obj, L.joint, (*_env)->NewByteArray(_env, (jsize)A_PID_FUZZY_JOINT(ctx.joint)));
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kpid(JNIEnv *_env, jobject _obj, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    a_pid_fuzzy_kpid(&ctx, kp, ki, kd);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_run(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    union
    {
        a_float const *p;
        a_float *o;
    } u;
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jdoubleArray _me = (*_env)->GetObjectField(_env, _obj, L.me);
    jdoubleArray _mec = (*_env)->GetObjectField(_env, _obj, L.mec);
    jdoubleArray _mkp = (*_env)->GetObjectField(_env, _obj, L.mkp);
    jdoubleArray _mki = (*_env)->GetObjectField(_env, _obj, L.mki);
    jdoubleArray _mkd = (*_env)->GetObjectField(_env, _obj, L.mkd);
    jdoubleArray _joint = (*_env)->GetObjectField(_env, _obj, L.joint);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.me = (*_env)->GetDoubleArrayElements(_env, _me, NULL);
    ctx.mec = (*_env)->GetDoubleArrayElements(_env, _mec, NULL);
    ctx.mkp = (*_env)->GetDoubleArrayElements(_env, _mkp, NULL);
    ctx.mki = (*_env)->GetDoubleArrayElements(_env, _mki, NULL);
    ctx.mkd = (*_env)->GetDoubleArrayElements(_env, _mkd, NULL);
    jbyte *joint = (*_env)->GetByteArrayElements(_env, _joint, NULL);
    a_pid_fuzzy_set_joint(&ctx, joint, ctx.joint);
    jdouble res = a_pid_fuzzy_run(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    u.p = ctx.me;
    (*_env)->ReleaseDoubleArrayElements(_env, _me, u.o, JNI_ABORT);
    u.p = ctx.mec;
    (*_env)->ReleaseDoubleArrayElements(_env, _mec, u.o, JNI_ABORT);
    u.p = ctx.mkp;
    (*_env)->ReleaseDoubleArrayElements(_env, _mkp, u.o, JNI_ABORT);
    u.p = ctx.mki;
    (*_env)->ReleaseDoubleArrayElements(_env, _mki, u.o, JNI_ABORT);
    u.p = ctx.mkd;
    (*_env)->ReleaseDoubleArrayElements(_env, _mkd, u.o, JNI_ABORT);
    (*_env)->ReleaseByteArrayElements(_env, _joint, joint, JNI_ABORT);
    return res;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_pos(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    union
    {
        a_float const *p;
        a_float *o;
    } u;
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jdoubleArray _me = (*_env)->GetObjectField(_env, _obj, L.me);
    jdoubleArray _mec = (*_env)->GetObjectField(_env, _obj, L.mec);
    jdoubleArray _mkp = (*_env)->GetObjectField(_env, _obj, L.mkp);
    jdoubleArray _mki = (*_env)->GetObjectField(_env, _obj, L.mki);
    jdoubleArray _mkd = (*_env)->GetObjectField(_env, _obj, L.mkd);
    jdoubleArray _joint = (*_env)->GetObjectField(_env, _obj, L.joint);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.me = (*_env)->GetDoubleArrayElements(_env, _me, NULL);
    ctx.mec = (*_env)->GetDoubleArrayElements(_env, _mec, NULL);
    ctx.mkp = (*_env)->GetDoubleArrayElements(_env, _mkp, NULL);
    ctx.mki = (*_env)->GetDoubleArrayElements(_env, _mki, NULL);
    ctx.mkd = (*_env)->GetDoubleArrayElements(_env, _mkd, NULL);
    jbyte *joint = (*_env)->GetByteArrayElements(_env, _joint, NULL);
    a_pid_fuzzy_set_joint(&ctx, joint, ctx.joint);
    jdouble res = a_pid_fuzzy_pos(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    u.p = ctx.me;
    (*_env)->ReleaseDoubleArrayElements(_env, _me, u.o, JNI_ABORT);
    u.p = ctx.mec;
    (*_env)->ReleaseDoubleArrayElements(_env, _mec, u.o, JNI_ABORT);
    u.p = ctx.mkp;
    (*_env)->ReleaseDoubleArrayElements(_env, _mkp, u.o, JNI_ABORT);
    u.p = ctx.mki;
    (*_env)->ReleaseDoubleArrayElements(_env, _mki, u.o, JNI_ABORT);
    u.p = ctx.mkd;
    (*_env)->ReleaseDoubleArrayElements(_env, _mkd, u.o, JNI_ABORT);
    (*_env)->ReleaseByteArrayElements(_env, _joint, joint, JNI_ABORT);
    return res;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_inc(JNIEnv *_env, jobject _obj, jdouble set, jdouble fdb)
{
    union
    {
        a_float const *p;
        a_float *o;
    } u;
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jdoubleArray _me = (*_env)->GetObjectField(_env, _obj, L.me);
    jdoubleArray _mec = (*_env)->GetObjectField(_env, _obj, L.mec);
    jdoubleArray _mkp = (*_env)->GetObjectField(_env, _obj, L.mkp);
    jdoubleArray _mki = (*_env)->GetObjectField(_env, _obj, L.mki);
    jdoubleArray _mkd = (*_env)->GetObjectField(_env, _obj, L.mkd);
    jdoubleArray _joint = (*_env)->GetObjectField(_env, _obj, L.joint);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    ctx.me = (*_env)->GetDoubleArrayElements(_env, _me, NULL);
    ctx.mec = (*_env)->GetDoubleArrayElements(_env, _mec, NULL);
    ctx.mkp = (*_env)->GetDoubleArrayElements(_env, _mkp, NULL);
    ctx.mki = (*_env)->GetDoubleArrayElements(_env, _mki, NULL);
    ctx.mkd = (*_env)->GetDoubleArrayElements(_env, _mkd, NULL);
    jbyte *joint = (*_env)->GetByteArrayElements(_env, _joint, NULL);
    a_pid_fuzzy_set_joint(&ctx, joint, ctx.joint);
    jdouble res = a_pid_fuzzy_inc(&ctx, set, fdb);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    u.p = ctx.me;
    (*_env)->ReleaseDoubleArrayElements(_env, _me, u.o, JNI_ABORT);
    u.p = ctx.mec;
    (*_env)->ReleaseDoubleArrayElements(_env, _mec, u.o, JNI_ABORT);
    u.p = ctx.mkp;
    (*_env)->ReleaseDoubleArrayElements(_env, _mkp, u.o, JNI_ABORT);
    u.p = ctx.mki;
    (*_env)->ReleaseDoubleArrayElements(_env, _mki, u.o, JNI_ABORT);
    u.p = ctx.mkd;
    (*_env)->ReleaseDoubleArrayElements(_env, _mkd, u.o, JNI_ABORT);
    (*_env)->ReleaseByteArrayElements(_env, _joint, joint, JNI_ABORT);
    return res;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_zero(JNIEnv *_env, jobject _obj)
{
    a_pid_fuzzy ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    a_pid_fuzzy_zero(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_pid_fuzzy), (jbyte *)&ctx);
    return _obj;
}
