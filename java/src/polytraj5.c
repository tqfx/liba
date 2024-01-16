#include "a.h"
#include "a/polytraj5.h"
#include "liba_polytraj5.h"

#undef L
#define L Java_liba_polytraj5
static struct
{
    jfieldID q;
    jfieldID v;
    jfieldID a;
} L = {NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_polytraj5_INIT(JNIEnv *_env, jclass _cls)
{
    L.q = (*_env)->GetFieldID(_env, _cls, "q", "[D");
    L.v = (*_env)->GetFieldID(_env, _cls, "v", "[D");
    L.a = (*_env)->GetFieldID(_env, _cls, "a", "[D");
}

JNIEXPORT jobject JNICALL Java_liba_polytraj5_gen(JNIEnv *_env, jobject _obj, jdouble t0, jdouble t1, jdouble q0, jdouble q1, jdouble v0, jdouble v1, jdouble a0, jdouble a1)
{
    a_polytraj5 ctx;
    jdoubleArray _q = (*_env)->GetObjectField(_env, _obj, L.q);
    jdoubleArray _v = (*_env)->GetObjectField(_env, _obj, L.v);
    jdoubleArray _a = (*_env)->GetObjectField(_env, _obj, L.a);
    (*_env)->GetDoubleArrayRegion(_env, _q, 0, A_LEN(ctx.q), ctx.q);
    (*_env)->GetDoubleArrayRegion(_env, _v, 0, A_LEN(ctx.v), ctx.v);
    (*_env)->GetDoubleArrayRegion(_env, _a, 0, A_LEN(ctx.a), ctx.a);
    a_polytraj5_gen(&ctx, t0, t1, q0, q1, v0, v1, a0, a1);
    (*_env)->SetDoubleArrayRegion(_env, _q, 0, A_LEN(ctx.q), ctx.q);
    (*_env)->SetDoubleArrayRegion(_env, _v, 0, A_LEN(ctx.v), ctx.v);
    (*_env)->SetDoubleArrayRegion(_env, _a, 0, A_LEN(ctx.a), ctx.a);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj5_pos(JNIEnv *_env, jobject _obj, jdouble dt)
{
    a_polytraj5 ctx;
    jdoubleArray _q = (*_env)->GetObjectField(_env, _obj, L.q);
    (*_env)->GetDoubleArrayRegion(_env, _q, 0, A_LEN(ctx.q), ctx.q);
    return a_polytraj5_pos(&ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj5_vel(JNIEnv *_env, jobject _obj, jdouble dt)
{
    a_polytraj5 ctx;
    jdoubleArray _v = (*_env)->GetObjectField(_env, _obj, L.v);
    (*_env)->GetDoubleArrayRegion(_env, _v, 0, A_LEN(ctx.v), ctx.v);
    return a_polytraj5_vel(&ctx, dt);
}

JNIEXPORT jdouble JNICALL Java_liba_polytraj5_acc(JNIEnv *_env, jobject _obj, jdouble dt)
{
    a_polytraj5 ctx;
    jdoubleArray _a = (*_env)->GetObjectField(_env, _obj, L.a);
    (*_env)->GetDoubleArrayRegion(_env, _a, 0, A_LEN(ctx.a), ctx.a);
    return a_polytraj5_acc(&ctx, dt);
}
