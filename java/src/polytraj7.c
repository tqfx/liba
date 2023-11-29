#include "a.h"
#include "a/polytraj.h"
#include "liba_polytraj7.h"

#undef L
#define L JPACKAGE(polytraj7)
static struct
{
    jfieldID k;
} L = {NULL};

JNIEXPORT void JNICALL JPACKAGE(polytraj7_INIT)(JNIEnv *jenv, jclass jcls)
{
    L.k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
}

JNIEXPORT jobject JNICALL JPACKAGE(polytraj7_gen)(JNIEnv *jenv, jobject jobj, jdouble t0, jdouble t1, jdouble q0, jdouble q1, jdouble v0, jdouble v1, jdouble a0, jdouble a1, jdouble j0, jdouble j1)
{
    a_polytraj7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytraj7_gen(&ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    (*jenv)->SetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return jobj;
}

JNIEXPORT jdoubleArray JNICALL JPACKAGE(polytraj7_out)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    jdouble out[4] = {0};
    a_polytraj7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    a_polytraj7_out(&ctx, dt, out);
    jdoubleArray jres = (*jenv)->NewDoubleArray(jenv, A_LEN(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jres, 0, A_LEN(out), out);
    return jres;
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytraj7_pos)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytraj7_pos(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytraj7_vel)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytraj7_vel(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytraj7_acc)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytraj7_acc(&ctx, dt);
}

JNIEXPORT jdouble JNICALL JPACKAGE(polytraj7_jer)(JNIEnv *jenv, jobject jobj, jdouble dt)
{
    a_polytraj7_s ctx;
    jdoubleArray jk = (*jenv)->GetObjectField(jenv, jobj, L.k);
    (*jenv)->GetDoubleArrayRegion(jenv, jk, 0, A_LEN(ctx.k), ctx.k);
    return a_polytraj7_jer(&ctx, dt);
}
