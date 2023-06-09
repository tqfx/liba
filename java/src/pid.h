#ifndef J_PID_H
#define J_PID_H

#include "a.h"
#include "a/pid.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID dt;
    jfieldID kp;
    jfieldID ki;
    jfieldID kd;
    jfieldID out;
    jfieldID fdb;
    jfieldID tmp;
    jfieldID err;
    jfieldID outmin;
    jfieldID outmax;
    jfieldID summax;
    jfieldID num;
    jfieldID reg;
} j_pid_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_pid_s *j_pid_new(JNIEnv *jenv, jobject jobj, j_pid_s *jctx);
jobject j_pid_set(j_pid_s const *jctx, a_pid_s const *ctx);
jobject j_pid_get(j_pid_s const *jctx, a_pid_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid.h */
