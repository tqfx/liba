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
    ctx.pid.outmin = min;
    ctx.pid.outmax = max;
    if (sum != 0)
    {
        ctx.pid.summax = sum;
        ctx.pid.mode = A_PID_POS;
    }
    else
    {
        ctx.pid.summax = A_FLOAT_INF;
        ctx.pid.mode = A_PID_INC;
    }
    ctx.k = 1;
    ctx.wp.f = A_FLOAT_C(0.1);
    ctx.wi.f = A_FLOAT_C(0.1);
    ctx.wd.f = A_FLOAT_C(0.1);
    a_pid_neuron_init(&ctx, 0);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jint JNICALL JPACKAGE(pid_1neuron_mode__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return (jint)ctx.pid.mode;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_mode__I)(JNIEnv *jenv, jobject jobj, jint mode)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.pid.mode = (unsigned int)mode;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_k__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.k;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_k__D)(JNIEnv *jenv, jobject jobj, jdouble k)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.k = k;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_kp__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.kp;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_kp__D)(JNIEnv *jenv, jobject jobj, jdouble kp)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.pid.kp = kp;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_ki__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.ki;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_ki__D)(JNIEnv *jenv, jobject jobj, jdouble ki)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.pid.ki = ki;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_kd__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.kd;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_kd__D)(JNIEnv *jenv, jobject jobj, jdouble kd)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.pid.kd = kd;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_wp__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.wp.f;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_wp__D)(JNIEnv *jenv, jobject jobj, jdouble wp)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.wp.f = wp;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_wi__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.wi.f;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_wi__D)(JNIEnv *jenv, jobject jobj, jdouble wi)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.wi.f = wi;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_wd__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.wd.f;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_wd__D)(JNIEnv *jenv, jobject jobj, jdouble wd)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.wd.f = wd;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_summax__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.summax;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_summax__D)(JNIEnv *jenv, jobject jobj, jdouble summax)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.pid.summax = summax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_outmax__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.outmax;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_outmax__D)(JNIEnv *jenv, jobject jobj, jdouble outmax)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.pid.outmax = outmax;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_outmin__)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.outmin;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_outmin__D)(JNIEnv *jenv, jobject jobj, jdouble outmin)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    ctx.pid.outmin = outmin;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_out)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.out.f;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_fdb)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.fdb.f;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_err)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.pid.err.f;
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_ec)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_neuron_s), (jbyte *)&ctx);
    return ctx.ec.f;
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
