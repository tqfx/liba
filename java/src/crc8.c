#include "a.h"
#include "a/crc.h"
#include "liba_crc8.h"

#undef L
#define L Java_liba_crc8
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_crc8_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

struct CRC8
{
    a_u8 table[0x100];
};

JNIEXPORT void JNICALL Java_liba_crc8_init(JNIEnv *_env, jobject _obj, jbyte poly, jboolean reversed)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(struct CRC8));
    struct CRC8 *ctx = (struct CRC8 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    reversed ? a_crc8l_init(ctx->table, (a_u8)poly)
             : a_crc8m_init(ctx->table, (a_u8)poly);
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc8_table(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct CRC8 *ctx = (struct CRC8 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jbyteArray table = (*_env)->NewByteArray(_env, A_LEN(ctx->table));
    (*_env)->SetByteArrayRegion(_env, table, 0, A_LEN(ctx->table), (jbyte *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc8_gen(JNIEnv *_env, jobject _obj, jbyte poly, jboolean reversed)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct CRC8 *ctx = (struct CRC8 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    reversed ? a_crc8l_init(ctx->table, (a_u8)poly)
             : a_crc8m_init(ctx->table, (a_u8)poly);
    return _obj;
}

JNIEXPORT jbyte JNICALL Java_liba_crc8_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jbyte value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct CRC8 *ctx = (struct CRC8 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jbyte)a_crc8(ctx->table, p, (a_size)n, (a_u8)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc8_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jbyte value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct CRC8 *ctx = (struct CRC8 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 1);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jbyte)a_crc8(ctx->table, block_p, (a_size)block_n, (a_u8)value);
    (*_env)->SetByteArrayRegion(_env, res, 0, block_n, block_p);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    (*_env)->SetByteArrayRegion(_env, res, block_n, 1, &value);
    return res;
}
