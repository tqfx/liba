#include "a.h"
#include "a/math.h"
#if !defined A_VERSION
#include "a/version.h"
#endif /* A_VERSION */
#include "liba.h"

JNIEXPORT void JNICALL Java_liba_INIT(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticObjectField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "VERSION", "Ljava/lang/String;"), (*jenv)->NewStringUTF(jenv, A_VERSION));
}

JNIEXPORT jint JNICALL Java_liba_isqrt__I(JNIEnv *jenv, jclass jcls, jint x)
{
    return (void)(jenv), (void)(jcls), (jint)a_u32_sqrt((a_u32_t)x);
}

JNIEXPORT jint JNICALL Java_liba_isqrt__J(JNIEnv *jenv, jclass jcls, jlong x)
{
    return (void)(jenv), (void)(jcls), (jint)a_u64_sqrt((a_u64_t)x);
}

JNIEXPORT jfloat JNICALL Java_liba_rsqrt__F(JNIEnv *jenv, jclass jcls, jfloat x)
{
    return (void)(jenv), (void)(jcls), a_f32_rsqrt(x);
}

JNIEXPORT jdouble JNICALL Java_liba_rsqrt__D(JNIEnv *jenv, jclass jcls, jdouble x)
{
    return (void)(jenv), (void)(jcls), a_f64_rsqrt(x);
}
