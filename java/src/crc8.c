#include "a.h"
#include "a/crc.h"
#include "liba_crc8.h"

#undef L
#define L Java_liba_crc8
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_crc8_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

struct CRC8
{
    a_u8 table[0x100];
};

JNIEXPORT void JNICALL Java_liba_crc8_init(JNIEnv *_env, jobject _obj, jbyte poly, jboolean reversed)
{
    struct CRC8 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC8));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC8), (jbyte *)&ctx);
    reversed ? a_crc8l_init(ctx.table, (A_U8)poly)
             : a_crc8m_init(ctx.table, (A_U8)poly);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC8), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc8_table(JNIEnv *_env, jobject _obj)
{
    struct CRC8 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC8), (jbyte *)&ctx);
    jbyteArray table = (*_env)->NewByteArray(_env, A_LEN(ctx.table));
    (*_env)->SetByteArrayRegion(_env, table, 0, A_LEN(ctx.table), (jbyte *)ctx.table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc8_gen(JNIEnv *_env, jobject _obj, jbyte poly, jboolean reversed)
{
    struct CRC8 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC8));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC8), (jbyte *)&ctx);
    reversed ? a_crc8l_init(ctx.table, (A_U8)poly)
             : a_crc8m_init(ctx.table, (A_U8)poly);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC8), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    return _obj;
}

JNIEXPORT jbyte JNICALL Java_liba_crc8_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jbyte value)
{
    struct CRC8 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC8), (jbyte *)&ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jbyte)a_crc8(ctx.table, p, (a_size)n, (a_u8)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc8_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jbyte value)
{
    struct CRC8 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC8), (jbyte *)&ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 4);
    jbyte *res_p = (*_env)->GetByteArrayElements(_env, res, NULL);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    a_copy(res_p, block_p, (a_size)block_n);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    value = (jbyte)a_crc8(ctx.table, res_p, (a_size)block_n, (a_u8)value);
    res_p[block_n] = value;
    (*_env)->ReleaseByteArrayElements(_env, res, res_p, 0);
    return res;
}
