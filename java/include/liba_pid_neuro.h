/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_pid_neuro */

#ifndef _Included_liba_pid_neuro
#define _Included_liba_pid_neuro
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_pid_neuro
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_pid_1neuro_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_pid_neuro
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_pid_1neuro_init
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    k
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_k__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    k
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_k__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    kp
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kp__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    kp
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kp__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    ki
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ki__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    ki
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_ki__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    kd
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_kd__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    kd
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kd__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    wp
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wp__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    wp
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wp__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    wi
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wi__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    wi
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wi__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    wd
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_wd__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    wd
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wd__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    outmax
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmax__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    outmax
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmax__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    outmin
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_outmin__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    outmin
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_outmin__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    out
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_out
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    fdb
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_fdb
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    err
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_err
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    ec
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_ec
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_neuro
 * Method:    kpid
 * Signature: (DDDD)Lliba/pid_neuro;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_kpid
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    wpid
 * Signature: (DDD)Lliba/pid_neuro;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_wpid
  (JNIEnv *, jobject, jdouble, jdouble, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    run
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_run
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    inc
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1neuro_inc
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid_neuro
 * Method:    zero
 * Signature: ()Lliba/pid_neuro;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1neuro_zero
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
