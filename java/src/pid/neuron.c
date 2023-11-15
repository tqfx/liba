#include "../a.h"
#include "a/pid/neuron.h"
#include "liba_pid_neuron.h"
#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

#undef L
#define L JPACKAGE(pid_1neuron)
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL JPACKAGE(pid_1neuron_INIT)(JNIEnv *jenv, jclass jcls)
{
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
}

JNIEXPORT void JNICALL JPACKAGE(pid_1neuron_init)(JNIEnv *jenv, jobject jobj, jdouble min, jdouble max, jdouble sum)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_pid_neuron_s));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    a_pid_neuron_kpid(&ctx, 0, 0, 0, 0);
    a_pid_neuron_wpid(&ctx, 0, 0, 0);
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
    a_pid_neuron_init(&ctx, 0);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_kpid)(JNIEnv *jenv, jobject jobj, jdouble k, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    a_pid_neuron_kpid(&ctx, k, kp, ki, kd);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_wpid)(JNIEnv *jenv, jobject jobj, jdouble wp, jdouble wi, jdouble wd)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    a_pid_neuron_wpid(&ctx, wp, wi, wd);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_iter)(JNIEnv *jenv, jobject jobj, jdouble jset, jdouble jfdb)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    jdouble jres = a_pid_neuron_outf(&ctx, jset, jfdb);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jres;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_zero)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    a_pid_neuron_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}
