#include "../a.h"
#include "a/pid/fuzzy.h"
#include "liba_pid_fuzzy.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

#undef L
#define L JPACKAGE(pid_1fuzzy)
static struct
{
    jfieldID ctx;
    jfieldID me;
    jfieldID mec;
    jfieldID mkp;
    jfieldID mki;
    jfieldID mkd;
    jfieldID val;
    jfieldID idx;
} L = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL JPACKAGE(pid_1fuzzy_INIT)(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "EQU", "I"), A_PID_FUZZY_EQU);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CAP", "I"), A_PID_FUZZY_CAP);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CAP_ALGEBRA", "I"), A_PID_FUZZY_CAP_ALGEBRA);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CAP_BOUNDED", "I"), A_PID_FUZZY_CAP_BOUNDED);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CUP", "I"), A_PID_FUZZY_CUP);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CUP_ALGEBRA", "I"), A_PID_FUZZY_CUP_ALGEBRA);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "CUP_BOUNDED", "I"), A_PID_FUZZY_CUP_BOUNDED);
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
    L.me = (*jenv)->GetFieldID(jenv, jcls, "me", "[D");
    L.mec = (*jenv)->GetFieldID(jenv, jcls, "mec", "[D");
    L.mkp = (*jenv)->GetFieldID(jenv, jcls, "mkp", "[D");
    L.mki = (*jenv)->GetFieldID(jenv, jcls, "mki", "[D");
    L.mkd = (*jenv)->GetFieldID(jenv, jcls, "mkd", "[D");
    L.val = (*jenv)->GetFieldID(jenv, jcls, "val", "[D");
    L.idx = (*jenv)->GetFieldID(jenv, jcls, "idx", "[B");
}

JNIEXPORT jint JNICALL JPACKAGE(pid_1fuzzy_mode__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return (jint)ctx.pid.mode;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_mode__I)(JNIEnv *jenv, jobject jobj, jint mode)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.mode = (unsigned int)mode;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_kp__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.kp;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_kp__D)(JNIEnv *jenv, jobject jobj, jdouble kp)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.kp = kp;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_ki__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.ki;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_ki__D)(JNIEnv *jenv, jobject jobj, jdouble ki)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.ki = ki;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_kd__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.kd;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_kd__D)(JNIEnv *jenv, jobject jobj, jdouble kd)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.kd = kd;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_summax__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.summax;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_summax__D)(JNIEnv *jenv, jobject jobj, jdouble summax)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.summax = summax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_outmax__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.outmax;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_outmax__D)(JNIEnv *jenv, jobject jobj, jdouble outmax)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.outmax = outmax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_outmin__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.outmin;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_outmin__D)(JNIEnv *jenv, jobject jobj, jdouble outmin)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.pid.outmin = outmin;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_out)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.out.f;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_fdb)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.fdb.f;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_err)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return ctx.pid.err.f;
}

JNIEXPORT jint JNICALL JPACKAGE(pid_1fuzzy_col)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return (jint)ctx.col;
}

JNIEXPORT void JNICALL JPACKAGE(pid_1fuzzy_init)(JNIEnv *jenv, jobject jobj, jdouble min, jdouble max, jdouble sum)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_pid_fuzzy_s));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    a_pid_fuzzy_kpid(&ctx, 0, 0, 0);
    ctx.pid.outmin = min;
    ctx.pid.outmax = max;
    ctx.pid.summax = sum;
    if (ctx.pid.summax != 0)
    {
        ctx.pid.mode = A_PID_POS;
    }
    else
    {
        ctx.pid.mode = A_PID_INC;
    }
    ctx.me = A_NULL;
    ctx.mec = A_NULL;
    ctx.mkp = A_NULL;
    ctx.mki = A_NULL;
    ctx.mkd = A_NULL;
    ctx.idx = A_NULL;
    ctx.val = A_NULL;
    ctx.op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    ctx.kp = 0;
    ctx.ki = 0;
    ctx.kd = 0;
    ctx.col = 0;
    ctx.buf = 0;
    a_pid_fuzzy_init(&ctx, 0);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
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

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_rule)(JNIEnv *jenv, jobject jobj, jobjectArray me, jobjectArray mec,
                                                    jobjectArray mkp, jobjectArray mki, jobjectArray mkd)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.col = (unsigned int)(*jenv)->GetArrayLength(jenv, me);
    (*jenv)->SetObjectField(jenv, jobj, L.me, concat(jenv, me));
    (*jenv)->SetObjectField(jenv, jobj, L.mec, concat(jenv, mec));
    (*jenv)->SetObjectField(jenv, jobj, L.mkp, concat(jenv, mkp));
    (*jenv)->SetObjectField(jenv, jobj, L.mki, concat(jenv, mki));
    (*jenv)->SetObjectField(jenv, jobj, L.mkd, concat(jenv, mkd));
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_kpid)(JNIEnv *jenv, jobject jobj, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    a_pid_fuzzy_kpid(&ctx, kp, ki, kd);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jint JNICALL JPACKAGE(pid_1fuzzy_buff__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return (jint)ctx.buf;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_buff__I)(JNIEnv *jenv, jobject jobj, jint num)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.buf = (unsigned int)num;
    (*jenv)->SetObjectField(jenv, jobj, L.idx, (*jenv)->NewByteArray(jenv, (jsize)sizeof(unsigned int) * A_PID_FUZZY_IDX(num)));
    (*jenv)->SetObjectField(jenv, jobj, L.val, (*jenv)->NewDoubleArray(jenv, A_PID_FUZZY_VAL(num)));
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_op)(JNIEnv *jenv, jobject jobj, jint op)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    a_pid_fuzzy_set_op(&ctx, (unsigned int)op);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_iter)(JNIEnv *jenv, jobject jobj, jdouble set, jdouble fdb)
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
    jdoubleArray jval = (*jenv)->GetObjectField(jenv, jobj, L.val);
    jbyteArray jidx = (*jenv)->GetObjectField(jenv, jobj, L.idx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    ctx.me = (*jenv)->GetDoubleArrayElements(jenv, jme, NULL);
    ctx.mec = (*jenv)->GetDoubleArrayElements(jenv, jmec, NULL);
    ctx.mkp = (*jenv)->GetDoubleArrayElements(jenv, jmkp, NULL);
    ctx.mki = (*jenv)->GetDoubleArrayElements(jenv, jmki, NULL);
    ctx.mkd = (*jenv)->GetDoubleArrayElements(jenv, jmkd, NULL);
    ctx.val = (*jenv)->GetDoubleArrayElements(jenv, jval, NULL);
    ctx.idx = (unsigned int *)(void *)(*jenv)->GetByteArrayElements(jenv, jidx, NULL);
    jdouble jres = a_pid_fuzzy_outf(&ctx, set, fdb);
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
    (*jenv)->ReleaseDoubleArrayElements(jenv, jval, ctx.val, JNI_ABORT);
    (*jenv)->ReleaseByteArrayElements(jenv, jidx, (jbyte *)ctx.idx, JNI_ABORT);
    return jres;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_zero)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    a_pid_fuzzy_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_fuzzy_s), (jbyte *)&ctx);
    return jobj;
}
