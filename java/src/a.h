#ifndef J_A_H
#define J_A_H

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC system_header
#endif /* __GNUC__ */
#include "a/a.h"
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* -Wreserved-id-macro */
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#include <jni.h>

#define CLASSPATH "liba/"
#define JPACKAGE(F) Java_liba_##F

A_INTERN jsize GetArrayLengthN(JNIEnv *jenv, jarray jobj, jsize jmax)
{
    jsize length = (*jenv)->GetArrayLength(jenv, jobj);
    return length < jmax ? length : jmax;
}

#endif /* a.h */
