#include "a.h"
#include "a/polytrack.h"
#include "liba_polytrack5.h"

#undef L
#define L JPACKAGE(polytrack5)
static struct
{
    jfieldID k;
} L = {NULL};

JNIEXPORT void JNICALL JPACKAGE(polytrack5_INIT)(JNIEnv *jenv, jclass jcls)
{
    L.k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack5_gen)(JNIEnv *jenv, jobject jobj, jdouble t0, jdouble t1, jdouble q0, jdouble q1, jdouble v0, jdouble v1, jdouble a0, jdouble a1)
{
    a_polytrack5_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytrack5_gen(&ctx, t0, t1, q0, q1, v0, v1, a0, a1);
    (*jenv)->SetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return jobj;
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack5_out)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    jdouble out[3] = {0};
    a_polytrack5_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytrack5_out(&ctx, dt, out);
    jdoubleArray jres = (*jenv)->NewDoubleArray(jenv, A_LEN(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jres, 0, A_LEN(out), out);
    return jres;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_pos)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack5_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack5_pos(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_vel)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack5_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack5_vel(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack5_acc)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack5_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack5_acc(&ctx, dt);
}
