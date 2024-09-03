/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_pid */

#ifndef _Included_liba_pid
#define _Included_liba_pid
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_pid
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_pid_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_pid
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_pid_init
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    kp
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_kp__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    kp
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_kp__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid
 * Method:    ki
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_ki__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    ki
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_ki__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid
 * Method:    kd
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_kd__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    kd
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_kd__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid
 * Method:    summax
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_summax__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    summax
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_summax__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid
 * Method:    summin
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_summin__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    summin
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_summin__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid
 * Method:    sum
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_sum
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    outmax
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_outmax__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    outmax
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_outmax__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid
 * Method:    outmin
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_outmin__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    outmin
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_outmin__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid
 * Method:    out
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_out
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    fdb
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_fdb
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    err
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_err
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid
 * Method:    set_kpid
 * Signature: (DDD)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_set_1kpid
  (JNIEnv *, jobject, jdouble, jdouble, jdouble);

/*
 * Class:     liba_pid
 * Method:    run
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_run
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid
 * Method:    pos
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_pos
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid
 * Method:    inc
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_inc
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid
 * Method:    zero
 * Signature: ()Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_zero
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
