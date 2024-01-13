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

JNIEXPORT void JNICALL Java_liba_tf_INIT(JNIEnv *jenv, jclass jcls)
{
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
    L.num = (*jenv)->GetFieldID(jenv, jcls, "num", "[D");
    L.den = (*jenv)->GetFieldID(jenv, jcls, "den", "[D");
    L.input = (*jenv)->GetFieldID(jenv, jcls, "input", "[D");
    L.output = (*jenv)->GetFieldID(jenv, jcls, "output", "[D");
}

JNIEXPORT void JNICALL Java_liba_tf_init(JNIEnv *jenv, jobject jobj, jdoubleArray num, jdoubleArray den)
{
    a_tf ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_tf));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    ctx.num_n = (unsigned int)(*jenv)->GetArrayLength(jenv, num);
    ctx.den_n = (unsigned int)(*jenv)->GetArrayLength(jenv, den);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
    (*jenv)->SetObjectField(jenv, jobj, L.num, num);
    (*jenv)->SetObjectField(jenv, jobj, L.den, den);
    (*jenv)->SetObjectField(jenv, jobj, L.input, (*jenv)->NewDoubleArray(jenv, (jsize)ctx.num_n));
    (*jenv)->SetObjectField(jenv, jobj, L.output, (*jenv)->NewDoubleArray(jenv, (jsize)ctx.den_n));
}

JNIEXPORT jobject JNICALL Java_liba_tf_num(JNIEnv *jenv, jobject jobj, jdoubleArray num)
{
    a_tf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.num, num);
    jsize num_n = (*jenv)->GetArrayLength(jenv, num);
    if (ctx.num_n != (unsigned int)num_n)
    {
        ctx.num_n = (unsigned int)num_n;
        (*jenv)->SetObjectField(jenv, jobj, L.input, (*jenv)->NewDoubleArray(jenv, num_n));
    }
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL Java_liba_tf_den(JNIEnv *jenv, jobject jobj, jdoubleArray den)
{
    a_tf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.den, den);
    jsize den_n = (*jenv)->GetArrayLength(jenv, den);
    if (ctx.den_n != (unsigned int)den_n)
    {
        ctx.den_n = (unsigned int)den_n;
        (*jenv)->SetObjectField(jenv, jobj, L.output, (*jenv)->NewDoubleArray(jenv, den_n));
    }
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jdouble JNICALL Java_liba_tf_iter(JNIEnv *jenv, jobject jobj, jdouble x)
{
    union
    {
        a_float const *p;
        a_float *o;
    } u;
    a_tf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jnum = (*jenv)->GetObjectField(jenv, jobj, L.num);
    jbyteArray jden = (*jenv)->GetObjectField(jenv, jobj, L.den);
    jbyteArray jinput = (*jenv)->GetObjectField(jenv, jobj, L.input);
    jbyteArray joutput = (*jenv)->GetObjectField(jenv, jobj, L.output);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    ctx.num_p = (*jenv)->GetDoubleArrayElements(jenv, jnum, NULL);
    ctx.den_p = (*jenv)->GetDoubleArrayElements(jenv, jden, NULL);
    ctx.input = (*jenv)->GetDoubleArrayElements(jenv, jinput, NULL);
    ctx.output = (*jenv)->GetDoubleArrayElements(jenv, joutput, NULL);
    jdouble jres = a_tf_iter(&ctx, x);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    u.p = ctx.num_p;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jnum, u.o, JNI_ABORT);
    u.p = ctx.den_p;
    (*jenv)->ReleaseDoubleArrayElements(jenv, jden, u.o, JNI_ABORT);
    (*jenv)->ReleaseDoubleArrayElements(jenv, jinput, ctx.input, 0);
    (*jenv)->ReleaseDoubleArrayElements(jenv, joutput, ctx.output, 0);
    return jres;
}

JNIEXPORT jobject JNICALL Java_liba_tf_zero(JNIEnv *jenv, jobject jobj)
{
    a_tf ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jinput = (*jenv)->GetObjectField(jenv, jobj, L.input);
    jbyteArray joutput = (*jenv)->GetObjectField(jenv, jobj, L.output);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    ctx.input = (*jenv)->GetDoubleArrayElements(jenv, jinput, NULL);
    ctx.output = (*jenv)->GetDoubleArrayElements(jenv, joutput, NULL);
    a_tf_zero(&ctx);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_tf), (jbyte *)&ctx);
    (*jenv)->ReleaseDoubleArrayElements(jenv, jinput, ctx.input, 0);
    (*jenv)->ReleaseDoubleArrayElements(jenv, joutput, ctx.output, 0);
    return jobj;
}
