#include "a.h"
#include "a/crc.h"
#include "liba_crc32.h"

#undef L
#define L Java_liba_crc32
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_crc32_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

struct CRC32
{
    a_u32 table[0x100];
    a_u32 (*eval)(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value);
};

JNIEXPORT void JNICALL Java_liba_crc32_init(JNIEnv *_env, jobject _obj, jint poly, jboolean reversed)
{
    struct CRC32 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC32));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC32), (jbyte *)&ctx);
    if (reversed)
    {
        a_crc32l_init(ctx.table, (A_U32)poly);
        ctx.eval = a_crc32l;
    }
    else
    {
        a_crc32m_init(ctx.table, (A_U32)poly);
        ctx.eval = a_crc32m;
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC32), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jintArray JNICALL Java_liba_crc32_table(JNIEnv *_env, jobject _obj)
{
    struct CRC32 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC32), (jbyte *)&ctx);
    jintArray table = (*_env)->NewIntArray(_env, A_LEN(ctx.table));
    (*_env)->SetIntArrayRegion(_env, table, 0, A_LEN(ctx.table), (jint *)ctx.table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc32_gen(JNIEnv *_env, jobject _obj, jint poly, jboolean reversed)
{
    struct CRC32 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC32));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC32), (jbyte *)&ctx);
    if (reversed)
    {
        a_crc32l_init(ctx.table, (A_U32)poly);
        ctx.eval = a_crc32l;
    }
    else
    {
        a_crc32m_init(ctx.table, (A_U32)poly);
        ctx.eval = a_crc32m;
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC32), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_crc32_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jint value)
{
    struct CRC32 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC32), (jbyte *)&ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jint)ctx.eval(ctx.table, p, (a_size)n, (a_u32)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc32_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jint value)
{
    struct CRC32 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC32), (jbyte *)&ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 4);
    jbyte *res_p = (*_env)->GetByteArrayElements(_env, res, NULL);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    a_copy(res_p, block_p, (a_size)block_n);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    value = (jint)ctx.eval(ctx.table, res_p, (a_size)block_n, (a_u32)value);
    ctx.eval == a_crc32m
        ? a_u32_setb(res_p + block_n, (a_u32)value)
        : a_u32_setl(res_p + block_n, (a_u32)value);
    (*_env)->ReleaseByteArrayElements(_env, res, res_p, 0);
    return res;
}
