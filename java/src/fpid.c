#include "fpid.h"
#include "liba_fpid.h"

j_fpid_s *j_fpid_new(JNIEnv *const jenv, jobject const jobj, j_fpid_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "fpid");
    jfieldID pid = (*jenv)->GetFieldID(jenv, jcls, "pid", "L" CLASSPATH "pid;");
    j_pid_new(jenv, (*jenv)->GetObjectField(jenv, jobj, pid), &jctx->pid);
    jctx->mmp = (*jenv)->GetFieldID(jenv, jcls, "mmp", "[D");
    jctx->jmmp = (*jenv)->GetObjectField(jenv, jobj, jctx->mmp);
    jctx->mkp = (*jenv)->GetFieldID(jenv, jcls, "mkp", "[D");
    jctx->jmkp = (*jenv)->GetObjectField(jenv, jobj, jctx->mkp);
    jctx->mki = (*jenv)->GetFieldID(jenv, jcls, "mki", "[D");
    jctx->jmki = (*jenv)->GetObjectField(jenv, jobj, jctx->mki);
    jctx->mkd = (*jenv)->GetFieldID(jenv, jcls, "mkd", "[D");
    jctx->jmkd = (*jenv)->GetObjectField(jenv, jobj, jctx->mkd);
    jctx->mat = (*jenv)->GetFieldID(jenv, jcls, "mat", "[D");
    jctx->jmat = (*jenv)->GetObjectField(jenv, jobj, jctx->mat);
    jctx->mms = (*jenv)->GetFieldID(jenv, jcls, "mms", "[D");
    jctx->jmms = (*jenv)->GetObjectField(jenv, jobj, jctx->mms);
    jctx->idx = (*jenv)->GetFieldID(jenv, jcls, "idx", "[I");
    jctx->jidx = (*jenv)->GetObjectField(jenv, jobj, jctx->idx);
    jctx->sigma = (*jenv)->GetFieldID(jenv, jcls, "sigma", "D");
    jctx->alpha = (*jenv)->GetFieldID(jenv, jcls, "alpha", "D");
    jctx->kp = (*jenv)->GetFieldID(jenv, jcls, "kp", "D");
    jctx->ki = (*jenv)->GetFieldID(jenv, jcls, "ki", "D");
    jctx->kd = (*jenv)->GetFieldID(jenv, jcls, "kd", "D");
    jctx->op = (*jenv)->GetFieldID(jenv, jcls, "op", "J");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_fpid_get(j_fpid_s const *const jctx, a_fpid_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    j_pid_get(&jctx->pid, &ctx->pid);
    ctx->mmp = NULL;
    if (jctx->jmmp)
    {
        ctx->mmp = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmmp, NULL);
    }
    ctx->mkp = NULL;
    if (jctx->jmkp)
    {
        ctx->mkp = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmkp, NULL);
    }
    ctx->mki = NULL;
    if (jctx->jmki)
    {
        ctx->mki = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmki, NULL);
    }
    ctx->mkd = NULL;
    if (jctx->jmkd)
    {
        ctx->mkd = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmkd, NULL);
    }
    ctx->mat = NULL;
    if (jctx->jmat)
    {
        ctx->mat = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmat, NULL);
    }
    ctx->mms = NULL;
    if (jctx->jmms)
    {
        ctx->mms = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmms, NULL);
    }
    ctx->idx = NULL;
    if (jctx->jidx)
    {
        ctx->idx = (a_uint_t *)(*jenv)->GetIntArrayElements(jenv, jctx->jidx, NULL);
    }
    ctx->sigma = (*jenv)->GetDoubleField(jenv, jobj, jctx->sigma);
    ctx->alpha = (*jenv)->GetDoubleField(jenv, jobj, jctx->alpha);
    ctx->kp = (*jenv)->GetDoubleField(jenv, jobj, jctx->kp);
    ctx->ki = (*jenv)->GetDoubleField(jenv, jobj, jctx->ki);
    ctx->kd = (*jenv)->GetDoubleField(jenv, jobj, jctx->kd);
    jlong op = (*jenv)->GetLongField(jenv, jobj, jctx->op);
    ctx->op = (a_real_t(*)(a_real_t, a_real_t))(intptr_t)op; // NOLINT(performance-no-int-to-ptr)
    return jctx->jobj;
}

jobject j_fpid_set(j_fpid_s const *const jctx, a_fpid_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    j_pid_set(&jctx->pid, &ctx->pid);
    if (ctx->mmp)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mmp = (jdouble *)(intptr_t)ctx->mmp;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmmp, mmp, JNI_ABORT);
    }
    if (ctx->mkp)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mkp = (jdouble *)(intptr_t)ctx->mkp;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmkp, mkp, JNI_ABORT);
    }
    if (ctx->mki)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mki = (jdouble *)(intptr_t)ctx->mki;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmki, mki, JNI_ABORT);
    }
    if (ctx->mkd)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mkd = (jdouble *)(intptr_t)ctx->mkd;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmkd, mkd, JNI_ABORT);
    }
    if (ctx->mat)
    {
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmat, ctx->mat, JNI_ABORT);
    }
    if (ctx->mms)
    {
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmms, ctx->mms, JNI_ABORT);
    }
    if (ctx->idx)
    {
        (*jenv)->ReleaseIntArrayElements(jenv, jctx->jidx, (jint *)ctx->idx, JNI_ABORT);
    }
    (*jenv)->SetDoubleField(jenv, jobj, jctx->sigma, ctx->sigma);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->alpha, ctx->alpha);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kp, ctx->kp);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ki, ctx->ki);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kd, ctx->kd);
    (*jenv)->SetLongField(jenv, jobj, jctx->op, (intptr_t)ctx->op);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_inc)(JNIEnv *jenv, jobject jobj)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_fpid_inc(&ctx);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_off)(JNIEnv *jenv, jobject jobj)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_fpid_off(&ctx);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_pos)(JNIEnv *jenv, jobject jobj, jdouble jmax)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_fpid_pos(&ctx, jmax);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_mode)(JNIEnv *jenv, jobject jobj, jint jmode)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_pid_set_mode(&ctx.pid, (a_uint_t)jmode);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_time)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_pid_set_dt(&ctx.pid, jdt);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_ilim)(JNIEnv *jenv, jobject jobj, jdouble jmin, jdouble jmax)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_fpid_ilim(&ctx, jmin, jmax);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_olim)(JNIEnv *jenv, jobject jobj, jdouble jmin, jdouble jmax)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_fpid_olim(&ctx, jmin, jmax);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_kpid)(JNIEnv *jenv, jobject jobj, jdouble jkp, jdouble jki, jdouble jkd)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_fpid_kpid(&ctx, jkp, jki, jkd);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_buff)(JNIEnv *jenv, jobject jobj, jint jnum)
{
    j_fpid_s jctx;
    j_fpid_new(jenv, jobj, &jctx);
    (*jenv)->SetObjectField(jenv, jobj, jctx.mat, (*jenv)->NewDoubleArray(jenv, jnum * jnum));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mmp, (*jenv)->NewDoubleArray(jenv, jnum << 1));
    (*jenv)->SetObjectField(jenv, jobj, jctx.idx, (*jenv)->NewIntArray(jenv, jnum << 1));
    return jobj;
}

static jobject concat(j_fpid_s const *jctx, jobjectArray jmat)
{
    jsize length = 0;
    JNIEnv *jenv = jctx->jenv;
    jsize num = (*jenv)->GetArrayLength(jenv, jmat);
    for (jsize idx = 0; idx != num; ++idx)
    {
        length += (*jenv)->GetArrayLength(jenv, (*jenv)->GetObjectArrayElement(jenv, jmat, idx));
    }
    jobject obj = (*jenv)->NewDoubleArray(jenv, length);
    jdouble *mat = (*jenv)->GetDoubleArrayElements(jenv, obj, NULL), *jptr = mat;
    for (jsize idx = 0, jnum = 0; idx != num; ++idx, jptr += jnum)
    {
        jobject jobj = (*jenv)->GetObjectArrayElement(jenv, jmat, idx);
        jnum = (*jenv)->GetArrayLength(jenv, jobj);
        (*jenv)->GetDoubleArrayRegion(jenv, jobj, 0, jnum, jptr);
    }
    (*jenv)->ReleaseDoubleArrayElements(jenv, obj, mat, 0);
    return obj;
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_base)(JNIEnv *jenv, jobject jobj, jobjectArray jmmp,
                                              jobjectArray jmkp, jobjectArray jmki, jobjectArray jmkd)
{
    j_fpid_s jctx;
    j_fpid_new(jenv, jobj, &jctx);
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkp, concat(&jctx, jmkp));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mki, concat(&jctx, jmki));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkd, concat(&jctx, jmkd));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mmp, concat(&jctx, jmmp));
    return jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_init)(JNIEnv *jenv, jobject jobj, jdouble jdt, jobjectArray jmmp,
                                              jobjectArray jmkp, jobjectArray jmki, jobjectArray jmkd,
                                              jdouble jimin, jdouble jimax, jdouble jomin, jdouble jomax)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    a_uint_t num = (a_uint_t)(*jenv)->GetArrayLength(jenv, jmkp);
    j_fpid_new(jenv, jobj, &jctx);
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkp, concat(&jctx, jmkp));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mki, concat(&jctx, jmki));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkd, concat(&jctx, jmkd));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mmp, concat(&jctx, jmmp));
    a_fpid_init(&ctx, jdt, num, 0, 0, 0, 0, jimin, jimax, jomin, jomax);
    return j_fpid_set(&jctx, &ctx);
}

JNIEXPORT jdouble JNICALL JPACKAGE(fpid_proc)(JNIEnv *jenv, jobject jobj, jdouble jset, jdouble jfdb)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    jdouble jresult = a_fpid_outv(&ctx, jset, jfdb);
    j_fpid_set(&jctx, &ctx);
    return jresult;
}

JNIEXPORT jobject JNICALL JPACKAGE(fpid_zero)(JNIEnv *jenv, jobject jobj)
{
    a_fpid_s ctx;
    j_fpid_s jctx;
    j_fpid_get(j_fpid_new(jenv, jobj, &jctx), &ctx);
    a_fpid_zero(&ctx);
    return j_fpid_set(&jctx, &ctx);
}
