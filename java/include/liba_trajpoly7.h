/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_trajpoly7 */

#ifndef _Included_liba_trajpoly7
#define _Included_liba_trajpoly7
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_trajpoly7
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_trajpoly7_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_trajpoly7
 * Method:    p
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly7_p
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly7
 * Method:    v
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly7_v
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly7
 * Method:    a
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly7_a
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly7
 * Method:    j
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly7_j
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly7
 * Method:    gen
 * Signature: (DDDDDDDDD)Lliba/trajpoly7;
 */
JNIEXPORT jobject JNICALL Java_liba_trajpoly7_gen
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble);

/*
 * Class:     liba_trajpoly7
 * Method:    pos
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_pos
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_trajpoly7
 * Method:    vel
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_vel
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_trajpoly7
 * Method:    acc
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_acc
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_trajpoly7
 * Method:    jer
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly7_jer
  (JNIEnv *, jobject, jdouble);

#ifdef __cplusplus
}
#endif
#endif
