#include "a.h"
#include "a/polytraj7.h"
#include "liba_polytraj7.h"

#undef L
#define L Java_liba_polytraj7
static struct
{
    jfieldID q;
    jfieldID v;
    jfieldID a;
    jfieldID j;
} L = {NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_polytraj7_INIT(JNIEnv *jenv, jclass jcls)
{
    L.q = (*jenv)->GetFieldID(jenv, jcls, "q", "[D");
    L.v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    L.a = (*jenv)->GetFieldID(jenv, jcls, "a", "[D");
    L.j = (*jenv)->GetFieldID(jenv, jcls, "j", "[D");
}

JNIEXPORT jobject JNICALL Java_liba_polytraj7_gen(JNIEnv *jenv, jobject jobj, jdouble t0, jdouble t1, jdouble q0, jdouble q1, jdouble v0, jdouble v1, jdouble a0, jdouble a1, jdouble j0, jdouble j1)
{
    a_polytraj7_s ctx;
    jdoubleArray jq = (*jenv)->GetObjectField(jenv, jobj, L.q);
    jdoubleArray jv = (*jenv)->GetObjectField(jenv, jobj, L.v);
    jdoubleArray ja = (*jenv)->GetObjectField(jenv, jobj, L.a);
    jdoubleArray jj = (*jenv)->GetObjectField(jenv, jobj, L.j);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, A_LEN(ctx.q), ctx.q);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, A_LEN(ctx.v), ctx.v);
    (*jenv)->GetDoubleArrayRegion(jenv, ja, 0, A_LEN(ctx.a), ctx.a);
    (*jenv)->GetDoubleArrayRegion(jenv, jj, 0, A_LEN(ctx.j), ctx.j);
    a_polytraj7_gen(&ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    (*jenv)->SetDoubleArrayRegion(jenv, jq, 0, A_LEN(ctx.q), ctx.q);
    (*jenv)->SetDoubleArrayRegion(jenv, jv, 0, A_LEN(ctx.v), ctx.v);
    (*jenv)->SetDoubleArrayRegion(jenv, ja, 0, A_LEN(ctx.a), ctx.a);
    (*jenv)->SetDoubleArrayRegion(jenv, jj, 0, A_LEN(ctx.j), ctx.j);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_pos(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray jq = (*jenv)->GetObjectField(jenv, jobj, L.q);
    (*jenv)->GetDoubleArrayRegion(jenv, jq, 0, A_LEN(ctx.q), ctx.q);
    return a_polytraj7_pos(&ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_vel(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray jv = (*jenv)->GetObjectField(jenv, jobj, L.v);
    (*jenv)->GetDoubleArrayRegion(jenv, jv, 0, A_LEN(ctx.v), ctx.v);
    return a_polytraj7_vel(&ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_acc(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray ja = (*jenv)->GetObjectField(jenv, jobj, L.a);
    (*jenv)->GetDoubleArrayRegion(jenv, ja, 0, A_LEN(ctx.a), ctx.a);
    return a_polytraj7_acc(&ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj7_jer(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray jj = (*jenv)->GetObjectField(jenv, jobj, L.j);
    (*jenv)->GetDoubleArrayRegion(jenv, jj, 0, A_LEN(ctx.j), ctx.j);
    return a_polytraj7_jer(&ctx, dt);
}
