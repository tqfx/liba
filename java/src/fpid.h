#ifndef J_FPID_H
#define J_FPID_H

#include "pid.h"
#include "a/fpid.h"

typedef struct
{
    j_pid_s pid;
    JNIEnv *jenv;
    jobject jobj;
    jfieldID me;
    jobject jme;
    jfieldID mec;
    jobject jmec;
    jfieldID mkp;
    jobject jmkp;
    jfieldID mki;
    jobject jmki;
    jfieldID mkd;
    jobject jmkd;
    jfieldID idx;
    jobject jidx;
    jfieldID val;
    jobject jval;
    jfieldID op;
    jfieldID kp;
    jfieldID ki;
    jfieldID kd;
} j_fpid_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_fpid_s *j_fpid_new(JNIEnv *jenv, jobject jobj, j_fpid_s *jctx);
jobject j_fpid_set(j_fpid_s const *jctx, a_fpid_s const *ctx);
jobject j_fpid_get(j_fpid_s const *jctx, a_fpid_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* fpid.h */
