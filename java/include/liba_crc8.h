/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_crc8 */

#ifndef _Included_liba_crc8
#define _Included_liba_crc8
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_crc8
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_crc8_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_crc8
 * Method:    init
 * Signature: (BZ)V
 */
JNIEXPORT void JNICALL Java_liba_crc8_init
  (JNIEnv *, jobject, jbyte, jboolean);

/*
 * Class:     liba_crc8
 * Method:    table
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_liba_crc8_table
  (JNIEnv *, jobject);

/*
 * Class:     liba_crc8
 * Method:    gen
 * Signature: (BZ)Lliba/crc8;
 */
JNIEXPORT jobject JNICALL Java_liba_crc8_gen
  (JNIEnv *, jobject, jbyte, jboolean);

/*
 * Class:     liba_crc8
 * Method:    eval
 * Signature: ([BB)B
 */
JNIEXPORT jbyte JNICALL Java_liba_crc8_eval
  (JNIEnv *, jobject, jbyteArray, jbyte);

/*
 * Class:     liba_crc8
 * Method:    pack
 * Signature: ([BB)[B
 */
JNIEXPORT jbyteArray JNICALL Java_liba_crc8_pack
  (JNIEnv *, jobject, jbyteArray, jbyte);

#ifdef __cplusplus
}
#endif
#endif
