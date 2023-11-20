#include "a.h"
#include "a/math.h"
#include "a/version.h"
#include "liba.h"

JNIEXPORT void JNICALL JPACKAGE(INIT)(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticObjectField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "VERSION", "Ljava/lang/String;"), (*jenv)->NewStringUTF(jenv, A_VERSION));
}

JNIEXPORT jfloat JNICALL JPACKAGE(f32_1rsqrt)(JNIEnv *jenv, jclass jcls, jfloat x)
{
    return (void)(jenv), (void)(jcls), a_f32_rsqrt(x);
}

JNIEXPORT jdouble JNICALL JPACKAGE(f64_1rsqrt)(JNIEnv *jenv, jclass jcls, jdouble x)
{
    return (void)(jenv), (void)(jcls), a_f64_rsqrt(x);
}
