#ifndef J_TF_H
#define J_TF_H

#include "a.h"
#include "a/tf.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID num;
    jobject jnum;
    jfieldID den;
    jobject jden;
    jfieldID input;
    jobject jinput;
    jfieldID output;
    jobject joutput;
} j_tf_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_tf_s *j_tf_new(JNIEnv *jenv, jobject jobj, j_tf_s *jctx);
jobject j_tf_set(j_tf_s const *jctx, a_tf_s const *ctx);
jobject j_tf_get(j_tf_s const *jctx, a_tf_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* tf.h */
