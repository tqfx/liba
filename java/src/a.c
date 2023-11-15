#include "a.h"
#include "a/math.h"
#include "a/version.h"
#include "liba.h"

JNIEXPORT jstring JNICALL JPACKAGE(version)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jcls), (*jenv)->NewStringUTF(jenv, a_version());
}

JNIEXPORT jint JNICALL JPACKAGE(version_1major)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_major();
}

JNIEXPORT jint JNICALL JPACKAGE(version_1minor)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_minor();
}

JNIEXPORT jint JNICALL JPACKAGE(version_1patch)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_patch();
}

JNIEXPORT jlong JNICALL JPACKAGE(version_1tweak)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jlong)a_version_tweak();
}

JNIEXPORT jfloat JNICALL JPACKAGE(f32_1rsqrt)(JNIEnv *jenv, jclass jcls, jfloat jx)
{
    return (void)(jenv), (void)(jcls), a_f32_rsqrt(jx);
}

JNIEXPORT jdouble JNICALL JPACKAGE(f64_1rsqrt)(JNIEnv *jenv, jclass jcls, jdouble jx)
{
    return (void)(jenv), (void)(jcls), a_f64_rsqrt(jx);
}
