#ifndef J_PID_NEURON_H
#define J_PID_NEURON_H

#include "../pid.h"
#include "a/pid/neuron.h"

typedef struct
{
    j_pid_s pid;
    JNIEnv *jenv;
    jobject jobj;
    jclass jcls;
    jfieldID ec;
    jfieldID wp;
    jfieldID wi;
    jfieldID wd;
    jfieldID k;
} j_pid_neuron_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_pid_neuron_s *j_pid_neuron_new(JNIEnv *jenv, jobject jobj, j_pid_neuron_s *jctx);
jobject j_pid_neuron_set(j_pid_neuron_s const *jctx, a_pid_neuron_s const *ctx);
jobject j_pid_neuron_get(j_pid_neuron_s const *jctx, a_pid_neuron_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid/neuron.h */
