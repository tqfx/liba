#include "a.h"
#include "a/math.h"
#include "a/version.h"
#include "liba.h"

JNIEXPORT void JNICALL JPACKAGE(INIT)(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticLongField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "VERSION_TWEAK", "J"), (jlong)A_VERSION_TWEAK);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "VERSION_PATCH", "I"), A_VERSION_PATCH);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "VERSION_MINOR", "I"), A_VERSION_MINOR);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "VERSION_MAJOR", "I"), A_VERSION_MAJOR);
    (*jenv)->SetStaticObjectField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "VERSION", "Ljava/lang/String;"), (*jenv)->NewStringUTF(jenv, A_VERSION));
}

JNIEXPORT jint JNICALL JPACKAGE(version_1check)(JNIEnv *jenv, jclass jcls, jint major, jint minor, jint patch)
{
#undef a_version_check
    return (void)(jenv), (void)(jcls), a_version_check((unsigned int)major, (unsigned int)minor, (unsigned int)patch);
}

JNIEXPORT jfloat JNICALL JPACKAGE(f32_1rsqrt)(JNIEnv *jenv, jclass jcls, jfloat jx)
{
    return (void)(jenv), (void)(jcls), a_f32_rsqrt(jx);
}

JNIEXPORT jdouble JNICALL JPACKAGE(f64_1rsqrt)(JNIEnv *jenv, jclass jcls, jdouble jx)
{
    return (void)(jenv), (void)(jcls), a_f64_rsqrt(jx);
}
