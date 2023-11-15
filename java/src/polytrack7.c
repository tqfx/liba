#include "a.h"
#include "a/polytrack.h"
#include "liba_polytrack7.h"

#undef L
#define L JPACKAGE(polytrack7)
static struct
{
    jfieldID k;
} L = {NULL};

JNIEXPORT void JNICALL JPACKAGE(polytrack7_INIT)(JNIEnv *jenv, jclass jcls)
{
    L.k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
}

JNIEXPORT jobject JNICALL JPACKAGE(polytrack7_gen)(JNIEnv *jenv, jobject jobj, jdouble t0, jdouble t1, jdouble q0, jdouble q1, jdouble v0, jdouble v1, jdouble a0, jdouble a1, jdouble j0, jdouble j1)
{
    a_polytrack7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytrack7_gen(&ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    (*jenv)->SetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return jobj;
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytrack7_out)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    jdouble out[4] = {0};
    a_polytrack7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytrack7_out(&ctx, dt, out);
    jdoubleArray jres = (*jenv)->NewDoubleArray(jenv, A_LEN(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jres, 0, A_LEN(out), out);
    return jres;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_pos)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack7_pos(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_vel)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack7_vel(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_acc)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack7_acc(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytrack7_jer)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytrack7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytrack7_jer(&ctx, dt);
}
