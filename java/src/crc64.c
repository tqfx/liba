#include "a.h"
#include "a/crc.h"
#include "liba_crc64.h"

#undef L
#define L Java_liba_crc64
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

struct crc64
{
    a_u64 table[0x100];
    a_u64 (*eval)(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value);
};

JNIEXPORT void JNICALL Java_liba_crc64_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_crc64_init(JNIEnv *_env, jobject _obj, jlong poly, jboolean reversed)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(struct crc64));
    struct crc64 *ctx = (struct crc64 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    if (reversed)
    {
        a_crc64l_init(ctx->table, (a_u64)poly);
        ctx->eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(ctx->table, (a_u64)poly);
        ctx->eval = a_crc64m;
    }
}

JNIEXPORT jlongArray JNICALL Java_liba_crc64_table(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jlongArray table = (*_env)->NewLongArray(_env, A_LEN(ctx->table));
    (*_env)->SetLongArrayRegion(_env, table, 0, A_LEN(ctx->table), (jlong *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc64_gen(JNIEnv *_env, jobject _obj, jlong poly, jboolean reversed)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    if (reversed)
    {
        a_crc64l_init(ctx->table, (a_u64)poly);
        ctx->eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(ctx->table, (a_u64)poly);
        ctx->eval = a_crc64m;
    }
    return _obj;
}

JNIEXPORT jlong JNICALL Java_liba_crc64_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jlong value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jlong)ctx->eval(ctx->table, p, (a_size)n, (a_u64)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc64_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jlong value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 8);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jlong)ctx->eval(ctx->table, block_p, (a_size)block_n, (a_u64)value);
    ctx->eval == a_crc64m ? a_u64_setb(&value, (a_u64)value) : a_u64_setl(&value, (a_u64)value);
    (*_env)->SetByteArrayRegion(_env, res, 0, block_n, block_p);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    (*_env)->SetByteArrayRegion(_env, res, block_n, 8, (jbyte *)&value);
    return res;
}
