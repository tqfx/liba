#include "polytrack3.h"
#include "liba_polytrack3.h"

j_polytrack3_s *j_polytrack3_new(JNIEnv *const jenv, jobject const jobj, j_polytrack3_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack3");
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    jctx->t = (*jenv)->GetFieldID(jenv, jcls, "t", "[D");
    jctx->jt = (*jenv)->GetObjectField(jenv, jobj, jctx->t);
    jctx->q = (*jenv)->GetFieldID(jenv, jcls, "q", "[D");
    jctx->jq = (*jenv)->GetObjectField(jenv, jobj, jctx->q);
    jctx->v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    jctx->jv = (*jenv)->GetObjectField(jenv, jobj, jctx->v);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_polytrack3_get(j_polytrack3_s const *const jctx, a_polytrack3_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jt, 0, JCOUNTOF(ctx->t), ctx->t);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jq, 0, JCOUNTOF(ctx->q), ctx->q);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jv, 0, JCOUNTOF(ctx->v), ctx->v);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack3_set(j_polytrack3_s const *const jctx, a_polytrack3_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jt, 0, JCOUNTOF(ctx->t), ctx->t);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jq, 0, JCOUNTOF(ctx->q), ctx->q);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jv, 0, JCOUNTOF(ctx->v), ctx->v);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack3_init__DDDDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_new(jenv, jobj, jctx);
    a_polytrack3_init(ctx, jt0, jt1, jq0, jq1, jv0, jv1);
    return j_polytrack3_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack3_init__DDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_new(jenv, jobj, jctx);
    a_polytrack3_init(ctx, jt0, jt1, jq0, jq1, 0, 0);
    return j_polytrack3_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack3_init___3D_3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jt, jdoubleArray jq, jdoubleArray jv)
{
    jdouble t[2] = {0}, q[2] = {0}, v[2] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jt, 0, GetArrayLengthN(jenv, jt, JCOUNTOF(t)), t);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, GetArrayLengthN(jenv, jq, JCOUNTOF(q)), q);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, GetArrayLengthN(jenv, jv, JCOUNTOF(v)), v);
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_new(jenv, jobj, jctx);
    a_polytrack3_init1(ctx, t, q, v);
    return j_polytrack3_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack3_init___3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[3] = {0}, target[3] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jsource, 0, GetArrayLengthN(jenv, jsource, JCOUNTOF(source)), source);
    (*jenv)->GetDoubleArrayRegion(jenv, jtarget, 0, GetArrayLengthN(jenv, jtarget, JCOUNTOF(target)), target);
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_new(jenv, jobj, jctx);
    a_polytrack3_init2(ctx, source, target);
    return j_polytrack3_set(jctx, ctx);
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack3_out)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    jdouble out[3] = {0};
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    a_polytrack3_out(ctx, jts, out);
    jdoubleArray jresult = (*jenv)->NewDoubleArray(jenv, JCOUNTOF(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jresult, 0, JCOUNTOF(out), out);
    return jresult;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_pos)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    return a_polytrack3_pos(ctx, jts);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_vec)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    return a_polytrack3_vec(ctx, jts);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_acc)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    return a_polytrack3_acc(ctx, jts);
}
