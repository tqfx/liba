#include "a.h"
#include "a/polytrack.h"
#include "liba_polytrack3.h"

#undef L
#define L JPACKAGE(polytrack3)
static struct
{
    jfieldID k;
} L = {NULL};

JNIEXPORT void JNICALL JPACKAGE(polytrack3_INIT)(JNIEnv *jenv, jclass jcls)
{
    L.k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack3_gen)(JNIEnv *jenv, jobject jobj, jdouble t0, jdouble t1, jdouble q0, jdouble q1, jdouble v0, jdouble v1)
{
    a_polytrack3_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytrack3_gen(&ctx, t0, t1, q0, q1, v0, v1);
    (*jenv)->SetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return jobj;
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack3_out)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    jdouble out[3] = {0};
    a_polytrack3_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytrack3_out(&ctx, dt, out);
    jdoubleArray jres = (*jenv)->NewDoubleArray(jenv, A_LEN(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jres, 0, A_LEN(out), out);
    return jres;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_pos)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack3_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack3_pos(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_vel)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack3_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack3_vel(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack3_acc)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack3_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack3_acc(&ctx, dt);
}
