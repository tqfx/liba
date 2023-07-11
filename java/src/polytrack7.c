#include "polytrack7.h"
#include "liba_polytrack7.h"

j_polytrack7_s *j_polytrack7_new(JNIEnv *const jenv, jobject const jobj, j_polytrack7_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack7");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    jctx->jcls = jcls;
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    return jctx;
}

jobject j_polytrack7_get(j_polytrack7_s const *const jctx, a_polytrack7_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack7_set(j_polytrack7_s const *const jctx, a_polytrack7_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_gen)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1, jdouble ja0, jdouble ja1, jdouble jj0, jdouble jj1)
{
    a_polytrack7_s ctx;
    j_polytrack7_s jctx;
    j_polytrack7_new(jenv, jobj, &jctx);
    a_polytrack7_gen(&ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1, jj0, jj1);
    return j_polytrack7_set(&jctx, &ctx);
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack7_out)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    jdouble out[4] = {0};
    a_polytrack7_s ctx;
    j_polytrack7_s jctx;
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, &jctx), &ctx);
    a_polytrack7_out(&ctx, jdt, out);
    jdoubleArray jres = (*jenv)->NewDoubleArray(jenv, JCOUNTOF(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jres, 0, JCOUNTOF(out), out);
    return jres;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_pos)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack7_s ctx;
    j_polytrack7_s jctx;
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack7_pos(&ctx, jdt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_vel)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack7_s ctx;
    j_polytrack7_s jctx;
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack7_vel(&ctx, jdt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_acc)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack7_s ctx;
    j_polytrack7_s jctx;
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack7_acc(&ctx, jdt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_jer)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_polytrack7_s ctx;
    j_polytrack7_s jctx;
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack7_jer(&ctx, jdt);
}
