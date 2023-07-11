#include "polytrack5.h"
#include "liba_polytrack5.h"

j_polytrack5_s *j_polytrack5_new(JNIEnv *const jenv, jobject const jobj, j_polytrack5_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack5");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    jctx->jcls = jcls;
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    return jctx;
}

jobject j_polytrack5_get(j_polytrack5_s const *const jctx, a_polytrack5_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack5_set(j_polytrack5_s const *const jctx, a_polytrack5_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_gen)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1, jdouble ja0, jdouble ja1)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_new(jenv, jobj, &jctx);
    a_polytrack5_gen(&ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1);
    return j_polytrack5_set(&jctx, &ctx);
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack5_out)(JNIEnv *jenv, jobject jobj, jdouble ts)
{
    jdouble out[3] = {0};
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    a_polytrack5_out(&ctx, ts, out);
    jdoubleArray jres = (*jenv)->NewDoubleArray(jenv, JCOUNTOF(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jres, 0, JCOUNTOF(out), out);
    return jres;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_pos)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack5_pos(&ctx, jdt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_vel)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack5_vel(&ctx, jdt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_acc)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack5_acc(&ctx, jdt);
}
