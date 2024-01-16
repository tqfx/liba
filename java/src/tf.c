#include "a.h"
#include "a/tf.h"
#include "liba_tf.h"

#undef L
#define L Java_liba_tf
static struct
{
    jfieldID ctx;
    jfieldID num;
    jfieldID den;
    jfieldID input;
    jfieldID output;
} L = {NULL, NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_tf_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
    L.num = (*_env)->GetFieldID(_env, _cls, "num", "[D");
    L.den = (*_env)->GetFieldID(_env, _cls, "den", "[D");
    L.input = (*_env)->GetFieldID(_env, _cls, "input", "[D");
    L.output = (*_env)->GetFieldID(_env, _cls, "output", "[D");
}

JNIEXPORT void JNICALL Java_liba_tf_init(JNIEnv *_env, jobject _obj, jdoubleArray num, jdoubleArray den)
{
    a_tf ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_tf));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    ctx.num_n = (unsigned int)(*_env)->GetArrayLength(_env, num);
    ctx.den_n = (unsigned int)(*_env)->GetArrayLength(_env, den);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.num, num);
    (*_env)->SetObjectField(_env, _obj, L.den, den);
    (*_env)->SetObjectField(_env, _obj, L.input, (*_env)->NewDoubleArray(_env, (jsize)ctx.num_n));
    (*_env)->SetObjectField(_env, _obj, L.output, (*_env)->NewDoubleArray(_env, (jsize)ctx.den_n));
}

JNIEXPORT jobject JNICALL Java_liba_tf_num(JNIEnv *_env, jobject _obj, jdoubleArray num)
{
    a_tf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.num, num);
    jsize num_n = (*_env)->GetArrayLength(_env, num);
    if (ctx.num_n != (unsigned int)num_n)
    {
        ctx.num_n = (unsigned int)num_n;
        (*_env)->SetObjectField(_env, _obj, L.input, (*_env)->NewDoubleArray(_env, num_n));
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_tf_den(JNIEnv *_env, jobject _obj, jdoubleArray den)
{
    a_tf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.den, den);
    jsize den_n = (*_env)->GetArrayLength(_env, den);
    if (ctx.den_n != (unsigned int)den_n)
    {
        ctx.den_n = (unsigned int)den_n;
        (*_env)->SetObjectField(_env, _obj, L.output, (*_env)->NewDoubleArray(_env, den_n));
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jdouble JNICALL Java_liba_tf_iter(JNIEnv *_env, jobject _obj, jdouble x)
{
    union
    {
        a_float const *p;
        a_float *o;
    } u;
    a_tf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _num = (*_env)->GetObjectField(_env, _obj, L.num);
    jbyteArray _den = (*_env)->GetObjectField(_env, _obj, L.den);
    jbyteArray _input = (*_env)->GetObjectField(_env, _obj, L.input);
    jbyteArray _output = (*_env)->GetObjectField(_env, _obj, L.output);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    ctx.num_p = (*_env)->GetDoubleArrayElements(_env, _num, NULL);
    ctx.den_p = (*_env)->GetDoubleArrayElements(_env, _den, NULL);
    ctx.input = (*_env)->GetDoubleArrayElements(_env, _input, NULL);
    ctx.output = (*_env)->GetDoubleArrayElements(_env, _output, NULL);
    jdouble res = a_tf_iter(&ctx, x);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    u.p = ctx.num_p;
    (*_env)->ReleaseDoubleArrayElements(_env, _num, u.o, JNI_ABORT);
    u.p = ctx.den_p;
    (*_env)->ReleaseDoubleArrayElements(_env, _den, u.o, JNI_ABORT);
    (*_env)->ReleaseDoubleArrayElements(_env, _input, ctx.input, 0);
    (*_env)->ReleaseDoubleArrayElements(_env, _output, ctx.output, 0);
    return res;
}

JNIEXPORT jobject JNICALL Java_liba_tf_zero(JNIEnv *_env, jobject _obj)
{
    a_tf ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _input = (*_env)->GetObjectField(_env, _obj, L.input);
    jbyteArray _output = (*_env)->GetObjectField(_env, _obj, L.output);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    ctx.input = (*_env)->GetDoubleArrayElements(_env, _input, NULL);
    ctx.output = (*_env)->GetDoubleArrayElements(_env, _output, NULL);
    a_tf_zero(&ctx);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*_env)->ReleaseDoubleArrayElements(_env, _input, ctx.input, 0);
    (*_env)->ReleaseDoubleArrayElements(_env, _output, ctx.output, 0);
    return _obj;
}
