#include "tf.h"
#include "liba_tf.h"

j_tf_s *j_tf_new(JNIEnv *const jenv, jobject const jobj, j_tf_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "tf");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    jctx->jcls = jcls;
    jctx->num = (*jenv)->GetFieldID(jenv, jcls, "num", "[D");
    jctx->jnum = (*jenv)->GetObjectField(jenv, jobj, jctx->num);
    jctx->den = (*jenv)->GetFieldID(jenv, jcls, "den", "[D");
    jctx->jden = (*jenv)->GetObjectField(jenv, jobj, jctx->den);
    jctx->input = (*jenv)->GetFieldID(jenv, jcls, "input", "[D");
    jctx->jinput = (*jenv)->GetObjectField(jenv, jobj, jctx->input);
    jctx->output = (*jenv)->GetFieldID(jenv, jcls, "output", "[D");
    jctx->joutput = (*jenv)->GetObjectField(jenv, jobj, jctx->output);
    return jctx;
}

jobject j_tf_get(j_tf_s const *const jctx, a_tf_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    ctx->num_p = NULL;
    ctx->num_n = 0;
    if (jctx->jnum)
    {
        ctx->num_p = (*jenv)->GetDoubleArrayElements(jenv, jctx->jnum, NULL);
        ctx->num_n = (unsigned int)(*jenv)->GetArrayLength(jenv, jctx->jnum);
    }
    ctx->den_p = NULL;
    ctx->den_n = 0;
    if (jctx->jden)
    {
        ctx->den_p = (*jenv)->GetDoubleArrayElements(jenv, jctx->jden, NULL);
        ctx->den_n = (unsigned int)(*jenv)->GetArrayLength(jenv, jctx->jden);
    }
    ctx->input = NULL;
    if (jctx->jinput)
    {
        ctx->input = (*jenv)->GetDoubleArrayElements(jenv, jctx->jinput, NULL);
    }
    ctx->output = NULL;
    if (jctx->joutput)
    {
        ctx->output = (*jenv)->GetDoubleArrayElements(jenv, jctx->joutput, NULL);
    }
    return jctx->jobj;
}

jobject j_tf_set(j_tf_s const *const jctx, a_tf_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    if (ctx->num_p)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jnum, (jdouble *)(intptr_t)ctx->num_p, 0);
    }
    if (ctx->den_p)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jden, (jdouble *)(intptr_t)ctx->den_p, 0);
    }
    if (ctx->input)
    {
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jinput, ctx->input, 0);
    }
    if (ctx->output)
    {
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->joutput, ctx->output, 0);
    }
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(tf_init)(JNIEnv *jenv, jobject jobj, jdoubleArray jnum, jdoubleArray jden)
{
    j_tf_s jctx;
    j_tf_new(jenv, jobj, &jctx);
    (*jenv)->SetObjectField(jenv, jobj, jctx.num, jnum);
    (*jenv)->SetObjectField(jenv, jobj, jctx.den, jden);
    (*jenv)->SetObjectField(jenv, jobj, jctx.input, (*jenv)->NewDoubleArray(jenv, (*jenv)->GetArrayLength(jenv, jnum)));
    (*jenv)->SetObjectField(jenv, jobj, jctx.output, (*jenv)->NewDoubleArray(jenv, (*jenv)->GetArrayLength(jenv, jnum)));
    return jobj;
}

JNIEXPORT jdouble JNICALL JPACKAGE(tf_iter)(JNIEnv *jenv, jobject jobj, jdouble jx)
{
    a_tf_s ctx;
    j_tf_s jctx;
    j_tf_get(j_tf_new(jenv, jobj, &jctx), &ctx);
    jdouble jres = a_tf_iter(&ctx, jx);
    j_tf_set(&jctx, &ctx);
    return jres;
}

JNIEXPORT jobject JNICALL JPACKAGE(tf_zero)(JNIEnv *jenv, jobject jobj)
{
    a_tf_s ctx;
    j_tf_s jctx;
    j_tf_get(j_tf_new(jenv, jobj, &jctx), &ctx);
    a_tf_zero(&ctx);
    return j_tf_set(&jctx, &ctx);
}
