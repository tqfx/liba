#include "a.h"
#include "a/pid.h"
#include "liba_pid.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

#undef L
#define L JPACKAGE(pid)
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL JPACKAGE(pid_INIT)(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "OFF", "I"), A_PID_OFF);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "POS", "I"), A_PID_POS);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "INC", "I"), A_PID_INC);
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
}

JNIEXPORT void JNICALL JPACKAGE(pid_init)(JNIEnv *jenv, jobject jobj, jdouble min, jdouble max, jdouble sum)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_pid_s));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.kp = 1;
    ctx.outmin = min;
    ctx.outmax = max;
    if (sum != 0)
    {
        ctx.summax = sum;
        ctx.mode = A_PID_POS;
    }
    else
    {
        ctx.summax = A_FLOAT_INF;
        ctx.mode = A_PID_INC;
    }
    a_pid_init(&ctx, 0);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jint JNICALL JPACKAGE(pid_mode__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return (jint)ctx.mode;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_mode__I)(JNIEnv *jenv, jobject jobj, jint mode)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.mode = (unsigned int)mode;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_kp__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.kp;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_kp__D)(JNIEnv *jenv, jobject jobj, jdouble kp)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.kp = kp;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_ki__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.ki;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_ki__D)(JNIEnv *jenv, jobject jobj, jdouble ki)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.ki = ki;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_kd__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.kd;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_kd__D)(JNIEnv *jenv, jobject jobj, jdouble kd)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.kd = kd;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_summax__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.summax;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_summax__D)(JNIEnv *jenv, jobject jobj, jdouble summax)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.summax = summax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_outmax__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.outmax;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_outmax__D)(JNIEnv *jenv, jobject jobj, jdouble outmax)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.outmax = outmax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_outmin__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.outmin;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_outmin__D)(JNIEnv *jenv, jobject jobj, jdouble outmin)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    ctx.outmin = outmin;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_out)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.out.f;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_fdb)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.fdb.f;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_err)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return ctx.err.f;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_kpid)(JNIEnv *jenv, jobject jobj, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    a_pid_kpid(&ctx, kp, ki, kd);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_iter)(JNIEnv *jenv, jobject jobj, jdouble set, jdouble fdb)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    jdouble jres = a_pid_outf(&ctx, set, fdb);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jres;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_zero)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    a_pid_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    return jobj;
}
