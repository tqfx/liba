#ifndef J_A_H
#define J_A_H

#include "a/a.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Wpadded")
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* -Wpadded */
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* -Wreserved-id-macro */
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#endif /* diagnostic */
#if A_PREREQ_GNUC(6, 1) || __has_warning("-Wignored-attributes")
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif /* -Wignored-attributes */
#if __has_warning("-Wlanguage-extension-token")
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
#endif /* -Wlanguage-extension-token */
#include <jni.h>
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */

#define JCOUNTOF(A) (sizeof(A) / sizeof(*(A)))
#define JPACKAGE(F) Java_liba_##F
#define CLASSPATH "liba/"

A_INTERN jsize GetArrayLengthN(JNIEnv *jenv, jarray jobj, jsize jmax)
{
    jsize length = (*jenv)->GetArrayLength(jenv, jobj);
    return length < jmax ? length : jmax;
}

#endif /* a.h */
