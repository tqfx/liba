/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_trajpoly5 */

#ifndef _Included_liba_trajpoly5
#define _Included_liba_trajpoly5
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_trajpoly5
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_trajpoly5_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_trajpoly5
 * Method:    p
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly5_p
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly5
 * Method:    v
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly5_v
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly5
 * Method:    a
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly5_a
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly5
 * Method:    gen
 * Signature: (DDDDDDD)Lliba/trajpoly5;
 */
JNIEXPORT jobject JNICALL Java_liba_trajpoly5_gen
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble);

/*
 * Class:     liba_trajpoly5
 * Method:    pos
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_pos
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_trajpoly5
 * Method:    vel
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_vel
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_trajpoly5
 * Method:    acc
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly5_acc
  (JNIEnv *, jobject, jdouble);

#ifdef __cplusplus
}
#endif
#endif
