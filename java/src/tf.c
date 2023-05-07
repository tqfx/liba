#include "tf.h"
#include "liba_tf.h"

j_tf_s *j_tf_new(JNIEnv *const jenv, jobject const jobj, j_tf_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "tf");
    jctx->u = (*jenv)->GetFieldID(jenv, jcls, "u", "[D");
    jctx->ju = (*jenv)->GetObjectField(jenv, jobj, jctx->u);
    jctx->v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    jctx->jv = (*jenv)->GetObjectField(jenv, jobj, jctx->v);
    jctx->num = (*jenv)->GetFieldID(jenv, jcls, "num", "[D");
    jctx->jnum = (*jenv)->GetObjectField(jenv, jobj, jctx->num);
    jctx->den = (*jenv)->GetFieldID(jenv, jcls, "den", "[D");
    jctx->jden = (*jenv)->GetObjectField(jenv, jobj, jctx->den);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_tf_get(j_tf_s const *const jctx, a_tf_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    if (jctx->ju)
    {
        ctx->u = (*jenv)->GetDoubleArrayElements(jenv, jctx->ju, NULL);
    }
    if (jctx->jv)
    {
        ctx->v = (*jenv)->GetDoubleArrayElements(jenv, jctx->jv, NULL);
    }
    if (jctx->jnum)
    {
        ctx->num = (*jenv)->GetDoubleArrayElements(jenv, jctx->jnum, NULL);
        ctx->m = (a_uint_t)(*jenv)->GetArrayLength(jenv, jctx->jnum);
    }
    if (jctx->jden)
    {
        ctx->den = (*jenv)->GetDoubleArrayElements(jenv, jctx->jden, NULL);
        ctx->n = (a_uint_t)(*jenv)->GetArrayLength(jenv, jctx->jden);
    }
    return jctx->jobj;
}

jobject j_tf_set(j_tf_s const *const jctx, a_tf_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    if (ctx->u)
    {
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->ju, ctx->u, 0);
    }
    if (ctx->v)
    {
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jv, ctx->v, 0);
    }
    if (ctx->num)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *num = (jdouble *)(intptr_t)ctx->num;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jnum, num, 0);
    }
    if (ctx->den)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *den = (jdouble *)(intptr_t)ctx->den;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jden, den, 0);
    }
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(tf_init)(JNIEnv *jenv, jobject jobj, jdoubleArray jnum, jdoubleArray jden)
{
    j_tf_s jctx;
    jsize m = (*jenv)->GetArrayLength(jenv, jnum);
    jobject ju = (*jenv)->NewDoubleArray(jenv, m);
    jsize n = (*jenv)->GetArrayLength(jenv, jden);
    jobject jv = (*jenv)->NewDoubleArray(jenv, n);
    j_tf_new(jenv, jobj, &jctx);
    (*jenv)->SetObjectField(jenv, jobj, jctx.u, ju);
    (*jenv)->SetObjectField(jenv, jobj, jctx.v, jv);
    (*jenv)->SetObjectField(jenv, jobj, jctx.num, jnum);
    (*jenv)->SetObjectField(jenv, jobj, jctx.den, jden);
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(tf_proc)(JNIEnv *jenv, jobject jobj, jdouble jx)
{
    a_tf_s ctx;
    j_tf_s jctx;
    j_tf_get(j_tf_new(jenv, jobj, &jctx), &ctx);
    jdouble jresult = a_tf_proc(&ctx, jx);
    j_tf_set(&jctx, &ctx);
    return jresult;
}

JNIEXPORT jobject JNICALL JPACKAGE(tf_zero)(JNIEnv *jenv, jobject jobj)
{
    a_tf_s ctx;
    j_tf_s jctx;
    j_tf_get(j_tf_new(jenv, jobj, &jctx), &ctx);
    a_tf_zero(&ctx);
    return j_tf_set(&jctx, &ctx);
}
