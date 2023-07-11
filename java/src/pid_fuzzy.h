#ifndef J_PID_FUZZY_H
#define J_PID_FUZZY_H

#include "pid.h"
#include "a/pid_fuzzy.h"

typedef struct
{
    j_pid_s pid;
    JNIEnv *jenv;
    jobject jobj;
    jclass jcls;
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
    jfieldID col;
    jfieldID buf;
} j_pid_fuzzy_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_pid_fuzzy_s *j_pid_fuzzy_new(JNIEnv *jenv, jobject jobj, j_pid_fuzzy_s *jctx);
jobject j_pid_fuzzy_set(j_pid_fuzzy_s const *jctx, a_pid_fuzzy_s const *ctx);
jobject j_pid_fuzzy_get(j_pid_fuzzy_s const *jctx, a_pid_fuzzy_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid_fuzzy.h */
