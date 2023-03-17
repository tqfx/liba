#include "a.h"
#include "a/math.h"
#include "a/version.h"
#include "liba_a.h"

JNIEXPORT jstring JNICALL JPACKAGE(a_version)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jcls), (*jenv)->NewStringUTF(jenv, a_version());
}

JNIEXPORT jint JNICALL JPACKAGE(a_version_1major)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_major();
}

JNIEXPORT jint JNICALL JPACKAGE(a_version_1minor)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_minor();
}

JNIEXPORT jint JNICALL JPACKAGE(a_version_1patch)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_patch();
}

JNIEXPORT jfloat JNICALL JPACKAGE(a_f32_1rsqrt)(JNIEnv *jenv, jclass jcls, jfloat jx)
{
    return (void)(jenv), (void)(jcls), a_f32_rsqrt(jx);
}

JNIEXPORT jdouble JNICALL JPACKAGE(a_f64_1rsqrt)(JNIEnv *jenv, jclass jcls, jdouble jx)
{
    return (void)(jenv), (void)(jcls), a_f64_rsqrt(jx);
}
