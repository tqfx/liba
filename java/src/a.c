#include "a.h"
#include "a/math.h"
#if !defined A_VERSION
#include "a/version.h"
#endif /* A_VERSION */
#include "liba.h"

JNIEXPORT void JNICALL Java_liba_INIT(JNIEnv *_env, jclass _cls)
{
    (*_env)->SetStaticObjectField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "VERSION", "Ljava/lang/String;"), (*_env)->NewStringUTF(_env, A_VERSION));
}

JNIEXPORT jint JNICALL Java_liba_isqrt__I(JNIEnv *_env, jclass _cls, jint x)
{
    return (void)(_env), (void)(_cls), (jint)a_u32_sqrt((a_u32)x);
}

JNIEXPORT jint JNICALL Java_liba_isqrt__J(JNIEnv *_env, jclass _cls, jlong x)
{
    return (void)(_env), (void)(_cls), (jint)a_u64_sqrt((a_u64)x);
}

JNIEXPORT jfloat JNICALL Java_liba_rsqrt__F(JNIEnv *_env, jclass _cls, jfloat x)
{
    return (void)(_env), (void)(_cls), a_f32_rsqrt(x);
}

JNIEXPORT jdouble JNICALL Java_liba_rsqrt__D(JNIEnv *_env, jclass _cls, jdouble x)
{
    return (void)(_env), (void)(_cls), a_f64_rsqrt(x);
}

JNIEXPORT jint JNICALL Java_liba_hash_1bkdr(JNIEnv *_env, jclass _cls, jbyteArray block, jint value)
{
    jsize nbyte = (*_env)->GetArrayLength(_env, block);
    jbyte *pdata = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jint)a_hash_bkdr_(pdata, (a_size)nbyte, (a_u32)value);
    (*_env)->ReleaseByteArrayElements(_env, block, pdata, JNI_ABORT);
    return (void)(_cls), value & 0x7FFFFFFF;
}

JNIEXPORT jint JNICALL Java_liba_hash_1sdbm(JNIEnv *_env, jclass _cls, jbyteArray block, jint value)
{
    jsize nbyte = (*_env)->GetArrayLength(_env, block);
    jbyte *pdata = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jint)a_hash_sdbm_(pdata, (a_size)nbyte, (a_u32)value);
    (*_env)->ReleaseByteArrayElements(_env, block, pdata, JNI_ABORT);
    return (void)(_cls), value & 0x7FFFFFFF;
}
