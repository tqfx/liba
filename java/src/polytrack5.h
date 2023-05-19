#ifndef J_POLYTRACK5_H
#define J_POLYTRACK5_H

#include "a.h"
#include "a/polytrack.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID k;
    jobject jk;
} j_polytrack5_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_polytrack5_s *j_polytrack5_new(JNIEnv *jenv, jobject jobj, j_polytrack5_s *jctx);
jobject j_polytrack5_set(j_polytrack5_s const *jctx, a_polytrack5_s const *ctx);
jobject j_polytrack5_get(j_polytrack5_s const *jctx, a_polytrack5_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytrack5.h */
