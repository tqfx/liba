#ifndef J_VERSION_H
#define J_VERSION_H

#include "a.h"
#include "a/version.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jclass jcls;
    jfieldID major;
    jfieldID minor;
    jfieldID patch;
} j_version_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_version_s *j_version_new(JNIEnv *jenv, jobject jobj, j_version_s *jctx);
jobject j_version_set(j_version_s const *jctx, a_version_s const *ctx);
jobject j_version_get(j_version_s const *jctx, a_version_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* version.h */
