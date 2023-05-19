#include "polytrack3.h"
#include "liba_polytrack3.h"

j_polytrack3_s *j_polytrack3_new(JNIEnv *const jenv, jobject const jobj, j_polytrack3_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack3");
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_polytrack3_get(j_polytrack3_s const *const jctx, a_polytrack3_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack3_set(j_polytrack3_s const *const jctx, a_polytrack3_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack3_gen)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1)
{
    a_polytrack3_s ctx;
    j_polytrack3_s jctx;
    j_polytrack3_new(jenv, jobj, &jctx);
    a_polytrack3_gen(&ctx, jt0, jt1, jq0, jq1, jv0, jv1);
    return j_polytrack3_set(&jctx, &ctx);
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack3_out)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    jdouble out[3] = {0};
    a_polytrack3_s ctx;
    j_polytrack3_s jctx;
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, &jctx), &ctx);
    a_polytrack3_out(&ctx, jdt, out);
    jdoubleArray jres = (*jenv)->NewDoubleArray(jenv, JCOUNTOF(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jres, 0, JCOUNTOF(out), out);
    return jres;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_pos)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack3_s ctx;
    j_polytrack3_s jctx;
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack3_pos(&ctx, jdt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_vec)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack3_s ctx;
    j_polytrack3_s jctx;
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack3_vec(&ctx, jdt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_acc)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack3_s ctx;
    j_polytrack3_s jctx;
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack3_acc(&ctx, jdt);
}
