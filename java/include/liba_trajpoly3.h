/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_trajpoly3 */

#ifndef _Included_liba_trajpoly3
#define _Included_liba_trajpoly3
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_trajpoly3
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_trajpoly3_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_trajpoly3
 * Method:    c0
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly3_c0
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly3
 * Method:    c1
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly3_c1
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly3
 * Method:    c2
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_liba_trajpoly3_c2
  (JNIEnv *, jobject);

/*
 * Class:     liba_trajpoly3
 * Method:    gen
 * Signature: (DDDDD)Lliba/trajpoly3;
 */
JNIEXPORT jobject JNICALL Java_liba_trajpoly3_gen
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble, jdouble);

/*
 * Class:     liba_trajpoly3
 * Method:    pos
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly3_pos
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_trajpoly3
 * Method:    vel
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly3_vel
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_trajpoly3
 * Method:    acc
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_trajpoly3_acc
  (JNIEnv *, jobject, jdouble);

#ifdef __cplusplus
}
#endif
#endif
