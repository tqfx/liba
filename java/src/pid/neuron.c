#include "neuron.h"
#include "liba_pid_neuron.h"

j_pid_neuron_s *j_pid_neuron_new(JNIEnv *const jenv, jobject const jobj, j_pid_neuron_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "pid_neuron");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    jctx->jcls = jcls;
    jfieldID pid = (*jenv)->GetFieldID(jenv, jcls, "pid", "L" CLASSPATH "pid;");
    j_pid_new(jenv, (*jenv)->GetObjectField(jenv, jobj, pid), &jctx->pid);
    jctx->ec = (*jenv)->GetFieldID(jenv, jcls, "ec", "D");
    jctx->wp = (*jenv)->GetFieldID(jenv, jcls, "wp", "D");
    jctx->wi = (*jenv)->GetFieldID(jenv, jcls, "wi", "D");
    jctx->wd = (*jenv)->GetFieldID(jenv, jcls, "wd", "D");
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "D");
    return jctx;
}

jobject j_pid_neuron_get(j_pid_neuron_s const *const jctx, a_pid_neuron_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    j_pid_get(&jctx->pid, &ctx->pid);
    ctx->ec.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->ec);
    ctx->wp.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->wp);
    ctx->wi.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->wi);
    ctx->wd.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->wd);
    ctx->k = (*jenv)->GetDoubleField(jenv, jobj, jctx->k);
    return jctx->jobj;
}

jobject j_pid_neuron_set(j_pid_neuron_s const *const jctx, a_pid_neuron_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    j_pid_set(&jctx->pid, &ctx->pid);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ec, ctx->ec.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->wp, ctx->wp.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->wi, ctx->wi.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->wd, ctx->wd.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->k, ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_init)(JNIEnv *jenv, jobject jobj, jdouble jmin, jdouble jmax, jdouble jsum)
{
    a_pid_neuron_s ctx;
    j_pid_neuron_s jctx;
    j_pid_neuron_new(jenv, jobj, &jctx);
    jmethodID init = (*jenv)->GetMethodID(jenv, jctx.pid.jcls, "init", "(DDD)L" CLASSPATH "pid;");
    (*jenv)->CallObjectMethod(jenv, jctx.pid.jobj, init, jmin, jmax, jsum);
    ctx.wp.f = 0;
    ctx.wi.f = 0;
    ctx.wd.f = 0;
    ctx.k = 0;
    a_pid_neuron_init(&ctx, 0);
    return j_pid_neuron_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_kpid)(JNIEnv *jenv, jobject jobj, jdouble jk, jdouble jkp, jdouble jki, jdouble jkd)
{
    a_pid_neuron_s ctx;
    j_pid_neuron_s jctx;
    j_pid_neuron_get(j_pid_neuron_new(jenv, jobj, &jctx), &ctx);
    a_pid_neuron_kpid(&ctx, jk, jkp, jki, jkd);
    return j_pid_neuron_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_wpid)(JNIEnv *jenv, jobject jobj, jdouble jkp, jdouble jki, jdouble jkd)
{
    a_pid_neuron_s ctx;
    j_pid_neuron_s jctx;
    j_pid_neuron_get(j_pid_neuron_new(jenv, jobj, &jctx), &ctx);
    a_pid_neuron_wpid(&ctx, jkp, jki, jkd);
    return j_pid_neuron_set(&jctx, &ctx);
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1neuron_iter)(JNIEnv *jenv, jobject jobj, jdouble jset, jdouble jfdb)
{
    a_pid_neuron_s ctx;
    j_pid_neuron_s jctx;
    j_pid_neuron_get(j_pid_neuron_new(jenv, jobj, &jctx), &ctx);
    jdouble jres = a_pid_neuron_outf(&ctx, jset, jfdb);
    j_pid_neuron_set(&jctx, &ctx);
    return jres;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1neuron_zero)(JNIEnv *jenv, jobject jobj)
{
    a_pid_neuron_s ctx;
    j_pid_neuron_s jctx;
    j_pid_neuron_get(j_pid_neuron_new(jenv, jobj, &jctx), &ctx);
    a_pid_neuron_zero(&ctx);
    return j_pid_neuron_set(&jctx, &ctx);
}
