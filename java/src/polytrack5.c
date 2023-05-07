#include "polytrack5.h"
#include "liba_polytrack5.h"

j_polytrack5_s *j_polytrack5_new(JNIEnv *const jenv, jobject const jobj, j_polytrack5_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack5");
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    jctx->t = (*jenv)->GetFieldID(jenv, jcls, "t", "[D");
    jctx->jt = (*jenv)->GetObjectField(jenv, jobj, jctx->t);
    jctx->q = (*jenv)->GetFieldID(jenv, jcls, "q", "[D");
    jctx->jq = (*jenv)->GetObjectField(jenv, jobj, jctx->q);
    jctx->v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    jctx->jv = (*jenv)->GetObjectField(jenv, jobj, jctx->v);
    jctx->a = (*jenv)->GetFieldID(jenv, jcls, "a", "[D");
    jctx->ja = (*jenv)->GetObjectField(jenv, jobj, jctx->a);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_polytrack5_get(j_polytrack5_s const *const jctx, a_polytrack5_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jt, 0, JCOUNTOF(ctx->t), ctx->t);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jq, 0, JCOUNTOF(ctx->q), ctx->q);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jv, 0, JCOUNTOF(ctx->v), ctx->v);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->ja, 0, JCOUNTOF(ctx->a), ctx->a);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack5_set(j_polytrack5_s const *const jctx, a_polytrack5_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jt, 0, JCOUNTOF(ctx->t), ctx->t);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jq, 0, JCOUNTOF(ctx->q), ctx->q);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jv, 0, JCOUNTOF(ctx->v), ctx->v);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->ja, 0, JCOUNTOF(ctx->a), ctx->a);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_init__DDDDDDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1, jdouble ja0, jdouble ja1)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_new(jenv, jobj, &jctx);
    a_polytrack5_init(&ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1);
    return j_polytrack5_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_init__DDDDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_new(jenv, jobj, &jctx);
    a_polytrack5_init(&ctx, jt0, jt1, jq0, jq1, jv0, jv1, 0, 0);
    return j_polytrack5_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_init__DDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_new(jenv, jobj, &jctx);
    a_polytrack5_init(&ctx, jt0, jt1, jq0, jq1, 0, 0, 0, 0);
    return j_polytrack5_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_init___3D_3D_3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jt, jdoubleArray jq, jdoubleArray jv, jdoubleArray ja)
{
    jdouble t[2] = {0}, q[2] = {0}, v[2] = {0}, a[2] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jt, 0, GetArrayLengthN(jenv, jt, JCOUNTOF(t)), t);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, GetArrayLengthN(jenv, jq, JCOUNTOF(q)), q);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, GetArrayLengthN(jenv, jv, JCOUNTOF(v)), v);
    (*jenv)->GetDoubleArrayRegion(jenv, ja, 0, GetArrayLengthN(jenv, ja, JCOUNTOF(a)), a);
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_new(jenv, jobj, &jctx);
    a_polytrack5_init1(&ctx, t, q, v, a);
    return j_polytrack5_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_init___3D_3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jt, jdoubleArray jq, jdoubleArray jv)
{
    jdouble t[2] = {0}, q[2] = {0}, v[2] = {0}, a[2] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jt, 0, GetArrayLengthN(jenv, jt, JCOUNTOF(t)), t);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, GetArrayLengthN(jenv, jq, JCOUNTOF(q)), q);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, GetArrayLengthN(jenv, jv, JCOUNTOF(v)), v);
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_new(jenv, jobj, &jctx);
    a_polytrack5_init1(&ctx, t, q, v, a);
    return j_polytrack5_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_init___3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[4] = {0}, target[4] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jsource, 0, GetArrayLengthN(jenv, jsource, JCOUNTOF(source)), source);
    (*jenv)->GetDoubleArrayRegion(jenv, jtarget, 0, GetArrayLengthN(jenv, jtarget, JCOUNTOF(target)), target);
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_new(jenv, jobj, &jctx);
    a_polytrack5_init2(&ctx, source, target);
    return j_polytrack5_set(&jctx, &ctx);
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack5_out)(JNIEnv *jenv, jobject jobj, jdouble ts)
{
    jdouble out[3] = {0};
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    a_polytrack5_out(&ctx, ts, out);
    jdoubleArray jresult = (*jenv)->NewDoubleArray(jenv, JCOUNTOF(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jresult, 0, JCOUNTOF(out), out);
    return jresult;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_pos)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack5_pos(&ctx, jts);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_vec)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack5_vec(&ctx, jts);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_acc)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack5_s ctx;
    j_polytrack5_s jctx;
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, &jctx), &ctx);
    return a_polytrack5_acc(&ctx, jts);
}
