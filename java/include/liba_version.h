/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_version */

#ifndef _Included_liba_version
#define _Included_liba_version
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_version
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_version_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_version
 * Method:    init
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_liba_version_init__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     liba_version
 * Method:    init
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_liba_version_init__IIII
  (JNIEnv *, jobject, jint, jint, jint, jint);

/*
 * Class:     liba_version
 * Method:    check
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_liba_version_check
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     liba_version
 * Method:    toString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_liba_version_toString
  (JNIEnv *, jobject);

/*
 * Class:     liba_version
 * Method:    major
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_liba_version_major__
  (JNIEnv *, jobject);

/*
 * Class:     liba_version
 * Method:    major
 * Signature: (I)Lliba/version;
 */
JNIEXPORT jobject JNICALL Java_liba_version_major__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     liba_version
 * Method:    minor
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_liba_version_minor__
  (JNIEnv *, jobject);

/*
 * Class:     liba_version
 * Method:    minor
 * Signature: (I)Lliba/version;
 */
JNIEXPORT jobject JNICALL Java_liba_version_minor__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     liba_version
 * Method:    third
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_liba_version_third__
  (JNIEnv *, jobject);

/*
 * Class:     liba_version
 * Method:    third
 * Signature: (I)Lliba/version;
 */
JNIEXPORT jobject JNICALL Java_liba_version_third__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     liba_version
 * Method:    extra
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_liba_version_extra__
  (JNIEnv *, jobject);

/*
 * Class:     liba_version
 * Method:    extra
 * Signature: (I)Lliba/version;
 */
JNIEXPORT jobject JNICALL Java_liba_version_extra__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     liba_version
 * Method:    alpha
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_liba_version_alpha__
  (JNIEnv *, jobject);

/*
 * Class:     liba_version
 * Method:    alpha
 * Signature: (Ljava/lang/String;)Lliba/version;
 */
JNIEXPORT jobject JNICALL Java_liba_version_alpha__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     liba_version
 * Method:    parse
 * Signature: (Ljava/lang/String;)Lliba/version;
 */
JNIEXPORT jobject JNICALL Java_liba_version_parse
  (JNIEnv *, jobject, jstring);

/*
 * Class:     liba_version
 * Method:    lt
 * Signature: (Lliba/version;)Z
 */
JNIEXPORT jboolean JNICALL Java_liba_version_lt
  (JNIEnv *, jobject, jobject);

/*
 * Class:     liba_version
 * Method:    gt
 * Signature: (Lliba/version;)Z
 */
JNIEXPORT jboolean JNICALL Java_liba_version_gt
  (JNIEnv *, jobject, jobject);

/*
 * Class:     liba_version
 * Method:    le
 * Signature: (Lliba/version;)Z
 */
JNIEXPORT jboolean JNICALL Java_liba_version_le
  (JNIEnv *, jobject, jobject);

/*
 * Class:     liba_version
 * Method:    ge
 * Signature: (Lliba/version;)Z
 */
JNIEXPORT jboolean JNICALL Java_liba_version_ge
  (JNIEnv *, jobject, jobject);

/*
 * Class:     liba_version
 * Method:    eq
 * Signature: (Lliba/version;)Z
 */
JNIEXPORT jboolean JNICALL Java_liba_version_eq
  (JNIEnv *, jobject, jobject);

/*
 * Class:     liba_version
 * Method:    ne
 * Signature: (Lliba/version;)Z
 */
JNIEXPORT jboolean JNICALL Java_liba_version_ne
  (JNIEnv *, jobject, jobject);

/*
 * Class:     liba_version
 * Method:    cmp
 * Signature: (Lliba/version;)I
 */
JNIEXPORT jint JNICALL Java_liba_version_cmp
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif