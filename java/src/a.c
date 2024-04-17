#include "a.h"
#include "a/math.h"
#if !defined A_VERSION
#include "a/version.h"
#endif /* A_VERSION */
#include "liba.h"

JNIEXPORT void JNICALL Java_liba_clinit(JNIEnv *Env, jclass Cls)
{
    (*Env)->SetStaticObjectField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "VERSION", "Ljava/lang/String;"), (*Env)->NewStringUTF(Env, A_VERSION));
}

JNIEXPORT jint JNICALL Java_liba_isqrt__I(JNIEnv *Env, jclass Cls, jint x)
{
    return (void)Env, (void)Cls, (jint)a_u32_sqrt((a_u32)x);
}

JNIEXPORT jint JNICALL Java_liba_isqrt__J(JNIEnv *Env, jclass Cls, jlong x)
{
    return (void)Env, (void)Cls, (jint)a_u64_sqrt((a_u64)x);
}

JNIEXPORT jfloat JNICALL Java_liba_rsqrt__F(JNIEnv *Env, jclass Cls, jfloat x)
{
    return (void)Env, (void)Cls, a_f32_rsqrt(x);
}

JNIEXPORT jdouble JNICALL Java_liba_rsqrt__D(JNIEnv *Env, jclass Cls, jdouble x)
{
    return (void)Env, (void)Cls, a_f64_rsqrt(x);
}

JNIEXPORT jint JNICALL Java_liba_hash_1bkdr(JNIEnv *Env, jclass Cls, jbyteArray block, jint value)
{
    jsize nbyte = (*Env)->GetArrayLength(Env, block);
    jbyte *pdata = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jint)a_hash_bkdr_(pdata, (a_size)nbyte, (a_u32)value);
    (*Env)->ReleaseByteArrayElements(Env, block, pdata, JNI_ABORT);
    return (void)Cls, value & 0x7FFFFFFF;
}

JNIEXPORT jint JNICALL Java_liba_hash_1sdbm(JNIEnv *Env, jclass Cls, jbyteArray block, jint value)
{
    jsize nbyte = (*Env)->GetArrayLength(Env, block);
    jbyte *pdata = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jint)a_hash_sdbm_(pdata, (a_size)nbyte, (a_u32)value);
    (*Env)->ReleaseByteArrayElements(Env, block, pdata, JNI_ABORT);
    return (void)Cls, value & 0x7FFFFFFF;
}
