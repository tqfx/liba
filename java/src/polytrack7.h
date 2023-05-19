#ifndef J_POLYTRACK7_H
#define J_POLYTRACK7_H

#include "a.h"
#include "a/polytrack.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID k;
    jobject jk;
} j_polytrack7_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_polytrack7_s *j_polytrack7_new(JNIEnv *jenv, jobject jobj, j_polytrack7_s *jctx);
jobject j_polytrack7_set(j_polytrack7_s const *jctx, a_polytrack7_s const *ctx);
jobject j_polytrack7_get(j_polytrack7_s const *jctx, a_polytrack7_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytrack7.h */
