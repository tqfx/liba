#include "a.h"
#include "a/crc.h"
#include "liba_crc64.h"

#undef L
#define L Java_liba_crc64
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_crc64_INIT(JNIEnv *_env, jclass _cls)
{
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

struct CRC64
{
    a_u64 table[0x100];
    a_u64 (*eval)(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value);
};

JNIEXPORT void JNICALL Java_liba_crc64_init(JNIEnv *_env, jobject _obj, jlong poly, jboolean reversed)
{
    struct CRC64 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC64));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC64), (jbyte *)&ctx);
    if (reversed)
    {
        a_crc64l_init(ctx.table, (A_U64)poly);
        ctx.eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(ctx.table, (A_U64)poly);
        ctx.eval = a_crc64m;
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC64), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jlongArray JNICALL Java_liba_crc64_table(JNIEnv *_env, jobject _obj)
{
    struct CRC64 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC64), (jbyte *)&ctx);
    jlongArray table = (*_env)->NewLongArray(_env, A_LEN(ctx.table));
    (*_env)->SetLongArrayRegion(_env, table, 0, A_LEN(ctx.table), (jlong *)ctx.table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc64_gen(JNIEnv *_env, jobject _obj, jlong poly, jboolean reversed)
{
    struct CRC64 ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(struct CRC64));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC64), (jbyte *)&ctx);
    if (reversed)
    {
        a_crc64l_init(ctx.table, (A_U64)poly);
        ctx.eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(ctx.table, (A_U64)poly);
        ctx.eval = a_crc64m;
    }
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC64), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    return _obj;
}

JNIEXPORT jlong JNICALL Java_liba_crc64_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jlong value)
{
    struct CRC64 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC64), (jbyte *)&ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jlong)ctx.eval(ctx.table, p, (a_size)n, (a_u64)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc64_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jlong value)
{
    struct CRC64 ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(struct CRC64), (jbyte *)&ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 4);
    jbyte *res_p = (*_env)->GetByteArrayElements(_env, res, NULL);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    a_copy(res_p, block_p, (a_size)block_n);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    value = (jlong)ctx.eval(ctx.table, res_p, (a_size)block_n, (a_u64)value);
    ctx.eval == a_crc64m
        ? a_u64_setb(res_p + block_n, (a_u64)value)
        : a_u64_setl(res_p + block_n, (a_u64)value);
    (*_env)->ReleaseByteArrayElements(_env, res, res_p, 0);
    return res;
}
