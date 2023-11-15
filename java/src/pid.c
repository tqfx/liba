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

JNIEXPORT void JNICALL JPACKAGE(pid_init)(JNIEnv *jenv, jobject jobj, jdouble kp, jdouble ki, jdouble kd, jdouble min, jdouble max, jdouble sum)
{
    a_pid_s ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_pid_s));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    a_pid_kpid(&ctx, kp, ki, kd);
    ctx.outmin = min;
    ctx.outmax = max;
    ctx.summax = sum;
    if (ctx.summax != 0)
    {
        ctx.mode = A_PID_POS;
    }
    else
    {
        ctx.mode = A_PID_INC;
    }
    a_pid_init(&ctx, 0);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_pid_s), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
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
