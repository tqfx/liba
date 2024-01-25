#include "a.h"
#include "a/crc.h"
#include "liba_crc16.h"

#undef L
#define L Java_liba_crc16
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_crc16_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

struct CRC16
{
    a_u16 table[0x100];
    a_u16 (*eval)(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value);
};

JNIEXPORT void JNICALL Java_liba_crc16_init(JNIEnv *_env, jobject _obj, jshort poly, jboolean reversed)
{
    struct CRC16 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC16));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC16), (jbyte *)&ctx);
    if (reversed)
    {
        a_crc16l_init(ctx.table, (A_U16)poly);
        ctx.eval = a_crc16l;
    }
    else
    {
        a_crc16m_init(ctx.table, (A_U16)poly);
        ctx.eval = a_crc16m;
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC16), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jshortArray JNICALL Java_liba_crc16_table(JNIEnv *_env, jobject _obj)
{
    struct CRC16 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC16), (jbyte *)&ctx);
    jshortArray table = (*_env)->NewShortArray(_env, A_LEN(ctx.table));
    (*_env)->SetShortArrayRegion(_env, table, 0, A_LEN(ctx.table), (jshort *)ctx.table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc16_gen(JNIEnv *_env, jobject _obj, jshort poly, jboolean reversed)
{
    struct CRC16 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC16));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC16), (jbyte *)&ctx);
    if (reversed)
    {
        a_crc16l_init(ctx.table, (A_U16)poly);
        ctx.eval = a_crc16l;
    }
    else
    {
        a_crc16m_init(ctx.table, (A_U16)poly);
        ctx.eval = a_crc16m;
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC16), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    return _obj;
}

JNIEXPORT jshort JNICALL Java_liba_crc16_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jshort value)
{
    struct CRC16 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC16), (jbyte *)&ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jshort)ctx.eval(ctx.table, p, (a_size)n, (a_u16)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc16_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jshort value)
{
    struct CRC16 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC16), (jbyte *)&ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 4);
    jbyte *res_p = (*_env)->GetByteArrayElements(_env, res, NULL);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    a_copy(res_p, block_p, (a_size)block_n);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    value = (jshort)ctx.eval(ctx.table, res_p, (a_size)block_n, (a_u16)value);
    ctx.eval == a_crc16m
        ? a_u16_setb(res_p + block_n, (a_u16)value)
        : a_u16_setl(res_p + block_n, (a_u16)value);
    (*_env)->ReleaseByteArrayElements(_env, res, res_p, 0);
    return res;
}
