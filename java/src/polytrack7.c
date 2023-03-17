#include "polytrack7.h"
#include "liba_polytrack7.h"

j_polytrack7_s *j_polytrack7_new(JNIEnv *const jenv, jobject const jobj, j_polytrack7_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack7");
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
    jctx->j = (*jenv)->GetFieldID(jenv, jcls, "j", "[D");
    jctx->jj = (*jenv)->GetObjectField(jenv, jobj, jctx->j);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_polytrack7_get(j_polytrack7_s const *const jctx, a_polytrack7_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jt, 0, JCOUNTOF(ctx->t), ctx->t);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jq, 0, JCOUNTOF(ctx->q), ctx->q);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jv, 0, JCOUNTOF(ctx->v), ctx->v);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->ja, 0, JCOUNTOF(ctx->a), ctx->a);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jj, 0, JCOUNTOF(ctx->j), ctx->j);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack7_set(j_polytrack7_s const *const jctx, a_polytrack7_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jt, 0, JCOUNTOF(ctx->t), ctx->t);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jq, 0, JCOUNTOF(ctx->q), ctx->q);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jv, 0, JCOUNTOF(ctx->v), ctx->v);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->ja, 0, JCOUNTOF(ctx->a), ctx->a);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jj, 0, JCOUNTOF(ctx->j), ctx->j);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, JCOUNTOF(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init__DDDDDDDDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1, jdouble ja0, jdouble ja1, jdouble jj0, jdouble jj1)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init(ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1, jj0, jj1);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init__DDDDDDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1, jdouble ja0, jdouble ja1)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init(ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1, 0, 0);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init__DDDDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1, jdouble jv0, jdouble jv1)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init(ctx, jt0, jt1, jq0, jq1, jv0, jv1, 0, 0, 0, 0);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init__DDDD)(JNIEnv *jenv, jobject jobj, jdouble jt0, jdouble jt1, jdouble jq0, jdouble jq1)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init(ctx, jt0, jt1, jq0, jq1, 0, 0, 0, 0, 0, 0);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init___3D_3D_3D_3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jt, jdoubleArray jq, jdoubleArray jv, jdoubleArray ja, jdoubleArray jj)
{
    jdouble t[2] = {0}, q[2] = {0}, v[2] = {0}, a[2] = {0}, j[2] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jt, 0, GetArrayLengthN(jenv, jt, JCOUNTOF(t)), t);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, GetArrayLengthN(jenv, jq, JCOUNTOF(q)), q);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, GetArrayLengthN(jenv, jv, JCOUNTOF(v)), v);
    (*jenv)->GetDoubleArrayRegion(jenv, ja, 0, GetArrayLengthN(jenv, ja, JCOUNTOF(a)), a);
    (*jenv)->GetDoubleArrayRegion(jenv, jj, 0, GetArrayLengthN(jenv, jj, JCOUNTOF(j)), j);
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init1(ctx, t, q, v, a, j);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init___3D_3D_3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jt, jdoubleArray jq, jdoubleArray jv, jdoubleArray ja)
{
    jdouble t[2] = {0}, q[2] = {0}, v[2] = {0}, a[2] = {0}, j[2] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jt, 0, GetArrayLengthN(jenv, jt, JCOUNTOF(t)), t);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, GetArrayLengthN(jenv, jq, JCOUNTOF(q)), q);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, GetArrayLengthN(jenv, jv, JCOUNTOF(v)), v);
    (*jenv)->GetDoubleArrayRegion(jenv, ja, 0, GetArrayLengthN(jenv, ja, JCOUNTOF(a)), a);
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init1(ctx, t, q, v, a, j);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init___3D_3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jt, jdoubleArray jq, jdoubleArray jv)
{
    jdouble t[2] = {0}, q[2] = {0}, v[2] = {0}, a[2] = {0}, j[2] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jt, 0, GetArrayLengthN(jenv, jt, JCOUNTOF(t)), t);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, GetArrayLengthN(jenv, jq, JCOUNTOF(q)), q);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, GetArrayLengthN(jenv, jv, JCOUNTOF(v)), v);
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init1(ctx, t, q, v, a, j);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_init___3D_3D)(JNIEnv *jenv, jobject jobj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[5] = {0}, target[5] = {0};
    (*jenv)->GetDoubleArrayRegion(jenv, jsource, 0, GetArrayLengthN(jenv, jsource, JCOUNTOF(source)), source);
    (*jenv)->GetDoubleArrayRegion(jenv, jtarget, 0, GetArrayLengthN(jenv, jtarget, JCOUNTOF(target)), target);
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init2(ctx, source, target);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack7_out)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    jdouble out[4] = {0};
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    a_polytrack7_out(ctx, jts, out);
    jdoubleArray jresult = (*jenv)->NewDoubleArray(jenv, JCOUNTOF(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jresult, 0, JCOUNTOF(out), out);
    return jresult;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_pos)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_pos(ctx, jts);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_vec)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_vec(ctx, jts);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_acc)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_acc(ctx, jts);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_jer)(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_jer(ctx, jts);
}
