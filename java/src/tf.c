#include "a.h"
#include "a/tf.h"
#include "liba_tf.h"

#undef L
#define L Java_liba_tf
static struct
{
    jmethodID alloc;
    jfieldID ctx;
    jfieldID num;
    jfieldID den;
    jfieldID input;
    jfieldID output;
} L = {NULL, NULL, NULL, NULL, NULL, NULL};

JNIEXPORT void JNICALL Java_liba_tf_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.num = (*_env)->GetFieldID(_env, _cls, "num", "Ljava/nio/ByteBuffer;");
    L.den = (*_env)->GetFieldID(_env, _cls, "den", "Ljava/nio/ByteBuffer;");
    L.input = (*_env)->GetFieldID(_env, _cls, "input", "Ljava/nio/ByteBuffer;");
    L.output = (*_env)->GetFieldID(_env, _cls, "output", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_tf_init(JNIEnv *_env, jobject _obj, jdoubleArray num, jdoubleArray den)
{
    jsize num_n = (*_env)->GetArrayLength(_env, num);
    jsize den_n = (*_env)->GetArrayLength(_env, den);

    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(a_tf));
    jobject _num = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)num_n * 8);
    jobject _den = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)den_n * 8);
    jobject _input = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)num_n * 8);
    jobject _output = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)den_n * 8);

    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    double *num_p = (double *)(*_env)->GetDirectBufferAddress(_env, _num);
    double *den_p = (double *)(*_env)->GetDirectBufferAddress(_env, _den);
    double *input = (double *)(*_env)->GetDirectBufferAddress(_env, _input);
    double *output = (double *)(*_env)->GetDirectBufferAddress(_env, _output);

    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.num, _num);
    (*_env)->SetObjectField(_env, _obj, L.den, _den);
    (*_env)->SetObjectField(_env, _obj, L.input, _input);
    (*_env)->SetObjectField(_env, _obj, L.output, _output);
    (*_env)->GetDoubleArrayRegion(_env, num, 0, num_n, num_p);
    (*_env)->GetDoubleArrayRegion(_env, den, 0, den_n, den_p);

    ctx->num_p = num_p;
    ctx->den_p = den_p;
    ctx->input = input;
    ctx->output = output;
    ctx->num_n = (unsigned int)num_n;
    ctx->den_n = (unsigned int)den_n;
}

JNIEXPORT jobject JNICALL Java_liba_tf_num__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject num = (*_env)->NewDoubleArray(_env, (jsize)ctx->num_n);
    (*_env)->SetDoubleArrayRegion(_env, num, 0, (jsize)ctx->num_n, ctx->num_p);
    return num;
}

JNIEXPORT jobject JNICALL Java_liba_tf_num___3D(JNIEnv *_env, jobject _obj, jdoubleArray num)
{
    union
    {
        double *p;
        double const *q;
    } u;
    jsize num_n = (*_env)->GetArrayLength(_env, num);
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    if (num_n > (jsize)ctx->num_n)
    {
        jobject _num = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)num_n * 8);
        jobject _input = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)num_n * 8);
        double *num_p = (double *)(*_env)->GetDirectBufferAddress(_env, _num);
        double *input = (double *)(*_env)->GetDirectBufferAddress(_env, _input);
        (*_env)->SetObjectField(_env, _obj, L.num, _num);
        (*_env)->SetObjectField(_env, _obj, L.input, _input);
        ctx->num_n = (unsigned int)num_n;
        ctx->num_p = num_p;
        ctx->input = input;
    }
    u.q = ctx->num_p;
    (*_env)->GetDoubleArrayRegion(_env, num, 0, num_n, u.p);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_tf_input(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject input = (*_env)->NewDoubleArray(_env, (jsize)ctx->num_n);
    (*_env)->SetDoubleArrayRegion(_env, input, 0, (jsize)ctx->num_n, ctx->input);
    return input;
}

JNIEXPORT jobject JNICALL Java_liba_tf_den__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject den = (*_env)->NewDoubleArray(_env, (jsize)ctx->den_n);
    (*_env)->SetDoubleArrayRegion(_env, den, 0, (jsize)ctx->den_n, ctx->den_p);
    return den;
}

JNIEXPORT jobject JNICALL Java_liba_tf_den___3D(JNIEnv *_env, jobject _obj, jdoubleArray den)
{
    union
    {
        double *p;
        double const *q;
    } u;
    jsize den_n = (*_env)->GetArrayLength(_env, den);
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    if (den_n > (jsize)ctx->den_n)
    {
        jobject _den = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)den_n * 8);
        jobject _output = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)den_n * 8);
        double *den_p = (double *)(*_env)->GetDirectBufferAddress(_env, _den);
        double *output = (double *)(*_env)->GetDirectBufferAddress(_env, _output);
        (*_env)->SetObjectField(_env, _obj, L.den, _den);
        (*_env)->SetObjectField(_env, _obj, L.output, _output);
        ctx->den_n = (unsigned int)den_n;
        ctx->den_p = den_p;
        ctx->output = output;
    }
    u.q = ctx->den_p;
    (*_env)->GetDoubleArrayRegion(_env, den, 0, den_n, u.p);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_tf_output(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jobject output = (*_env)->NewDoubleArray(_env, (jsize)ctx->num_n);
    (*_env)->SetDoubleArrayRegion(_env, output, 0, (jsize)ctx->num_n, ctx->output);
    return output;
}

JNIEXPORT jdouble JNICALL Java_liba_tf_iter(JNIEnv *_env, jobject _obj, jdouble x)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return a_tf_iter(ctx, x);
}

JNIEXPORT jobject JNICALL Java_liba_tf_zero(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_tf *ctx = (a_tf *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_tf_zero(ctx);
    return _obj;
}
