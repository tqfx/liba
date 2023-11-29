#include "../a.h"
#include "a/pid/fuzzy.h"
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

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_INIT(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CAP", "I"), A_PID_FUZZY_CAP);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CAP_ALGEBRA", "I"), A_PID_FUZZY_CAP_ALGEBRA);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CAP_BOUNDED", "I"), A_PID_FUZZY_CAP_BOUNDED);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CUP", "I"), A_PID_FUZZY_CUP);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CUP_ALGEBRA", "I"), A_PID_FUZZY_CUP_ALGEBRA);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CUP_BOUNDED", "I"), A_PID_FUZZY_CUP_BOUNDED);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "EQU", "I"), A_PID_FUZZY_EQU);
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
    L.me = (*jenv)->GetFieldID(jenv, jcls, "me", "[D");
    L.mec = (*jenv)->GetFieldID(jenv, jcls, "mec", "[D");
    L.mkp = (*jenv)->GetFieldID(jenv, jcls, "mkp", "[D");
    L.mki = (*jenv)->GetFieldID(jenv, jcls, "mki", "[D");
    L.mkd = (*jenv)->GetFieldID(jenv, jcls, "mkd", "[D");
    L.joint = (*jenv)->GetFieldID(jenv, jcls, "joint", "[B");
}

JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_init(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_pid_fuzzy_s));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.kp = 1;
    ctx.pid.summax = +A_FLOAT_INF;
    ctx.pid.summin = -A_FLOAT_INF;
    ctx.pid.outmax = +A_FLOAT_INF;
    ctx.pid.outmin = -A_FLOAT_INF;
    ctx.kp = 1;
    ctx.op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    a_pid_fuzzy_init(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kp__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.kp;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kp__D(JNIEnv *jenv, jobject jobj, jdouble kp)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.kp = ctx.kp = kp;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_ki__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.ki;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_ki__D(JNIEnv *jenv, jobject jobj, jdouble ki)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.ki = ctx.ki = ki;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kd__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.kd;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kd__D(JNIEnv *jenv, jobject jobj, jdouble kd)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.kd = ctx.kd = kd;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summax__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.summax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summax__D(JNIEnv *jenv, jobject jobj, jdouble summax)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.summax = summax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summin__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.summin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summin__D(JNIEnv *jenv, jobject jobj, jdouble summin)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.summin = summin;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmax__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.outmax;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmax__D(JNIEnv *jenv, jobject jobj, jdouble outmax)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.outmax = outmax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmin__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.outmin;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmin__D(JNIEnv *jenv, jobject jobj, jdouble outmin)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.outmin = outmin;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_out(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.out;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_fdb(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.fdb;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_err(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.err;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_order(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return (jint)ctx.order;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_op(JNIEnv *jenv, jobject jobj, jint op)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    a_pid_fuzzy_set_op(&ctx, (unsigned int)op);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

static jobject concat(JNIEnv *jenv, jobjectArray jval)
{
    jsize length = 0;
    jsize num = (*jenv)->GetArrayLength(jenv, jval);
    for (jsize idx = 0; idx != num; ++idx)
    {
        jobject o = (*jenv)->GetObjectArrayElement(jenv, jval, idx);
        length += (*jenv)->GetArrayLength(jenv, o);
        (*jenv)->DeleteLocalRef(jenv, o);
    }
    jobject obj = (*jenv)->NewDoubleArray(jenv, length);
    jdouble *val = (*jenv)->GetDoubleArrayElements(jenv, obj, NULL), *jptr = val;
    for (jsize idx = 0, jnum = 0; idx != num; ++idx, jptr += jnum)
    {
        jobject o = (*jenv)->GetObjectArrayElement(jenv, jval, idx);
        jnum = (*jenv)->GetArrayLength(jenv, o);
        (*jenv)->GetDoubleArrayRegion(jenv, o, 0, jnum, jptr);
        (*jenv)->DeleteLocalRef(jenv, o);
    }
    (*jenv)->ReleaseDoubleArrayElements(jenv, obj, val, 0);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_rule(JNIEnv *jenv, jobject jobj, jobjectArray me, jobjectArray mec,
                                                    jobjectArray mkp, jobjectArray mki, jobjectArray mkd)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.order = (unsigned int)(*jenv)->GetArrayLength(jenv, me);
    (*jenv)->SetObjectField(jenv, jobj, L.me, concat(jenv, me));
    (*jenv)->SetObjectField(jenv, jobj, L.mec, concat(jenv, mec));
    (*jenv)->SetObjectField(jenv, jobj, L.mkp, concat(jenv, mkp));
    (*jenv)->SetObjectField(jenv, jobj, L.mki, concat(jenv, mki));
    (*jenv)->SetObjectField(jenv, jobj, L.mkd, concat(jenv, mkd));
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_joint__(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return (jint)ctx.joint;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_joint__I(JNIEnv *jenv, jobject jobj, jint num)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    if (ctx.joint != (unsigned int)num)
    {
        ctx.joint = (unsigned int)num;
        (*jenv)->SetObjectField(jenv, jobj, L.joint, (*jenv)->NewByteArray(jenv, (jsize)A_PID_FUZZY_JOINT(ctx.joint)));
    }
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kpid(JNIEnv *jenv, jobject jobj, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    a_pid_fuzzy_kpid(&ctx, kp, ki, kd);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_off(JNIEnv *jenv, jobject jobj, jdouble set, jdouble fdb)
{
    union
    {
        a_float_t const *p;
        a_float_t *o;
    } u;
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jdoubleArray jme = (*jenv)->GetObjectField(jenv, jobj, L.me);
    jdoubleArray jmec = (*jenv)->GetObjectField(jenv, jobj, L.mec);
    jdoubleArray jmkp = (*jenv)->GetObjectField(jenv, jobj, L.mkp);
    jdoubleArray jmki = (*jenv)->GetObjectField(jenv, jobj, L.mki);
    jdoubleArray jmkd = (*jenv)->GetObjectField(jenv, jobj, L.mkd);
    jdoubleArray jjoint = (*jenv)->GetObjectField(jenv, jobj, L.joint);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.me = (*jenv)->GetDoubleArrayElements(jenv, jme, NULL);
    ctx.mec = (*jenv)->GetDoubleArrayElements(jenv, jmec, NULL);
    ctx.mkp = (*jenv)->GetDoubleArrayElements(jenv, jmkp, NULL);
    ctx.mki = (*jenv)->GetDoubleArrayElements(jenv, jmki, NULL);
    ctx.mkd = (*jenv)->GetDoubleArrayElements(jenv, jmkd, NULL);
    jbyte *joint = (*jenv)->GetByteArrayElements(jenv, jjoint, NULL);
    a_pid_fuzzy_set_joint(&ctx, joint, ctx.joint);
    jdouble jres = a_pid_fuzzy_off(&ctx, set, fdb);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    u.p = ctx.me;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jme, u.o, JNI_ABORT);
    u.p = ctx.mec;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmec, u.o, JNI_ABORT);
    u.p = ctx.mkp;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmkp, u.o, JNI_ABORT);
    u.p = ctx.mki;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmki, u.o, JNI_ABORT);
    u.p = ctx.mkd;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmkd, u.o, JNI_ABORT);
    (*jenv)->ReleaseByteArrayElements(jenv, jjoint, joint, JNI_ABORT);
    return jres;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_pos(JNIEnv *jenv, jobject jobj, jdouble set, jdouble fdb)
{
    union
    {
        a_float_t const *p;
        a_float_t *o;
    } u;
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jdoubleArray jme = (*jenv)->GetObjectField(jenv, jobj, L.me);
    jdoubleArray jmec = (*jenv)->GetObjectField(jenv, jobj, L.mec);
    jdoubleArray jmkp = (*jenv)->GetObjectField(jenv, jobj, L.mkp);
    jdoubleArray jmki = (*jenv)->GetObjectField(jenv, jobj, L.mki);
    jdoubleArray jmkd = (*jenv)->GetObjectField(jenv, jobj, L.mkd);
    jdoubleArray jjoint = (*jenv)->GetObjectField(jenv, jobj, L.joint);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.me = (*jenv)->GetDoubleArrayElements(jenv, jme, NULL);
    ctx.mec = (*jenv)->GetDoubleArrayElements(jenv, jmec, NULL);
    ctx.mkp = (*jenv)->GetDoubleArrayElements(jenv, jmkp, NULL);
    ctx.mki = (*jenv)->GetDoubleArrayElements(jenv, jmki, NULL);
    ctx.mkd = (*jenv)->GetDoubleArrayElements(jenv, jmkd, NULL);
    jbyte *joint = (*jenv)->GetByteArrayElements(jenv, jjoint, NULL);
    a_pid_fuzzy_set_joint(&ctx, joint, ctx.joint);
    jdouble jres = a_pid_fuzzy_pos(&ctx, set, fdb);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    u.p = ctx.me;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jme, u.o, JNI_ABORT);
    u.p = ctx.mec;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmec, u.o, JNI_ABORT);
    u.p = ctx.mkp;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmkp, u.o, JNI_ABORT);
    u.p = ctx.mki;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmki, u.o, JNI_ABORT);
    u.p = ctx.mkd;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmkd, u.o, JNI_ABORT);
    (*jenv)->ReleaseByteArrayElements(jenv, jjoint, joint, JNI_ABORT);
    return jres;
}

JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_inc(JNIEnv *jenv, jobject jobj, jdouble set, jdouble fdb)
{
    union
    {
        a_float_t const *p;
        a_float_t *o;
    } u;
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jdoubleArray jme = (*jenv)->GetObjectField(jenv, jobj, L.me);
    jdoubleArray jmec = (*jenv)->GetObjectField(jenv, jobj, L.mec);
    jdoubleArray jmkp = (*jenv)->GetObjectField(jenv, jobj, L.mkp);
    jdoubleArray jmki = (*jenv)->GetObjectField(jenv, jobj, L.mki);
    jdoubleArray jmkd = (*jenv)->GetObjectField(jenv, jobj, L.mkd);
    jdoubleArray jjoint = (*jenv)->GetObjectField(jenv, jobj, L.joint);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.me = (*jenv)->GetDoubleArrayElements(jenv, jme, NULL);
    ctx.mec = (*jenv)->GetDoubleArrayElements(jenv, jmec, NULL);
    ctx.mkp = (*jenv)->GetDoubleArrayElements(jenv, jmkp, NULL);
    ctx.mki = (*jenv)->GetDoubleArrayElements(jenv, jmki, NULL);
    ctx.mkd = (*jenv)->GetDoubleArrayElements(jenv, jmkd, NULL);
    jbyte *joint = (*jenv)->GetByteArrayElements(jenv, jjoint, NULL);
    a_pid_fuzzy_set_joint(&ctx, joint, ctx.joint);
    jdouble jres = a_pid_fuzzy_inc(&ctx, set, fdb);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    u.p = ctx.me;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jme, u.o, JNI_ABORT);
    u.p = ctx.mec;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmec, u.o, JNI_ABORT);
    u.p = ctx.mkp;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmkp, u.o, JNI_ABORT);
    u.p = ctx.mki;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmki, u.o, JNI_ABORT);
    u.p = ctx.mkd;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jmkd, u.o, JNI_ABORT);
    (*jenv)->ReleaseByteArrayElements(jenv, jjoint, joint, JNI_ABORT);
    return jres;
}

JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_zero(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    a_pid_fuzzy_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}
