#include "pid.h"
#include "liba_pid.h"

j_pid_s *j_pid_new(JNIEnv *const jenv, jobject const jobj, j_pid_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "pid");
    jctx->dt = (*jenv)->GetFieldID(jenv, jcls, "dt", "D");
    jctx->kp = (*jenv)->GetFieldID(jenv, jcls, "kp", "D");
    jctx->ki = (*jenv)->GetFieldID(jenv, jcls, "ki", "D");
    jctx->kd = (*jenv)->GetFieldID(jenv, jcls, "kd", "D");
    jctx->out = (*jenv)->GetFieldID(jenv, jcls, "out", "D");
    jctx->fdb = (*jenv)->GetFieldID(jenv, jcls, "fdb", "D");
    jctx->tmp = (*jenv)->GetFieldID(jenv, jcls, "tmp", "D");
    jctx->err = (*jenv)->GetFieldID(jenv, jcls, "err", "D");
    jctx->outmin = (*jenv)->GetFieldID(jenv, jcls, "outmin", "D");
    jctx->outmax = (*jenv)->GetFieldID(jenv, jcls, "outmax", "D");
    jctx->summax = (*jenv)->GetFieldID(jenv, jcls, "summax", "D");
    jctx->num = (*jenv)->GetFieldID(jenv, jcls, "num", "I");
    jctx->reg = (*jenv)->GetFieldID(jenv, jcls, "reg", "I");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_pid_get(j_pid_s const *const jctx, a_pid_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    ctx->dt = (*jenv)->GetDoubleField(jenv, jobj, jctx->dt);
    ctx->kp = (*jenv)->GetDoubleField(jenv, jobj, jctx->kp);
    ctx->ki = (*jenv)->GetDoubleField(jenv, jobj, jctx->ki);
    ctx->kd = (*jenv)->GetDoubleField(jenv, jobj, jctx->kd);
    ctx->out.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->out);
    ctx->fdb.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->fdb);
    ctx->tmp.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->tmp);
    ctx->err.f = (*jenv)->GetDoubleField(jenv, jobj, jctx->err);
    ctx->outmin = (*jenv)->GetDoubleField(jenv, jobj, jctx->outmin);
    ctx->outmax = (*jenv)->GetDoubleField(jenv, jobj, jctx->outmax);
    ctx->summax = (*jenv)->GetDoubleField(jenv, jobj, jctx->summax);
    ctx->num = (unsigned int)(*jenv)->GetIntField(jenv, jobj, jctx->num);
    ctx->reg = (unsigned int)(*jenv)->GetIntField(jenv, jobj, jctx->reg);
    return jctx->jobj;
}

jobject j_pid_set(j_pid_s const *const jctx, a_pid_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    (*jenv)->SetDoubleField(jenv, jobj, jctx->dt, ctx->dt);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kp, ctx->kp);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ki, ctx->ki);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kd, ctx->kd);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->out, ctx->out.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->fdb, ctx->fdb.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->tmp, ctx->tmp.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->err, ctx->err.f);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->outmin, ctx->outmin);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->outmax, ctx->outmax);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->summax, ctx->summax);
    (*jenv)->SetIntField(jenv, jobj, jctx->num, (jint)ctx->num);
    (*jenv)->SetIntField(jenv, jobj, jctx->reg, (jint)ctx->reg);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_off)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    a_pid_off(&ctx);
    return j_pid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_inc)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    a_pid_inc(&ctx);
    return j_pid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_pos)(JNIEnv *jenv, jobject jobj, jdouble jmax)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    a_pid_pos(&ctx, jmax);
    return j_pid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_mode)(JNIEnv *jenv, jobject jobj, jint jmode)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    a_pid_set_mode(&ctx, (unsigned int)jmode);
    return j_pid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_time)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    a_pid_set_dt(&ctx, jdt);
    return j_pid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_kpid)(JNIEnv *jenv, jobject jobj, jdouble jkp, jdouble jki, jdouble jkd)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    a_pid_kpid(&ctx, jkp, jki, jkd);
    return j_pid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_init)(JNIEnv *jenv, jobject jobj, jdouble jdt, jdouble jmin, jdouble jmax)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_new(jenv, jobj, &jctx);
    a_pid_init(&ctx, jdt, jmin, jmax);
    return j_pid_set(&jctx, &ctx);
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_iter)(JNIEnv *jenv, jobject jobj, jdouble jset, jdouble jfdb)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    jdouble jres = a_pid_outf(&ctx, jset, jfdb);
    j_pid_set(&jctx, &ctx);
    return jres;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_zero)(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx;
    j_pid_s jctx;
    j_pid_get(j_pid_new(jenv, jobj, &jctx), &ctx);
    a_pid_zero(&ctx);
    return j_pid_set(&jctx, &ctx);
}
