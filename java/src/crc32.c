#include "a.h"
#include "a/crc.h"
#include "liba_crc32.h"

#undef L
#define L Java_liba_crc32
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_crc32_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

struct crc32
{
    a_u32 table[0x100];
    a_u32 (*eval)(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value);
};

JNIEXPORT void JNICALL Java_liba_crc32_init(JNIEnv *_env, jobject _obj, jint poly, jboolean reversed)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(struct crc32));
    struct crc32 *ctx = (struct crc32 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    if (reversed)
    {
        a_crc32l_init(ctx->table, (a_u32)poly);
        ctx->eval = a_crc32l;
    }
    else
    {
        a_crc32m_init(ctx->table, (a_u32)poly);
        ctx->eval = a_crc32m;
    }
}

JNIEXPORT jintArray JNICALL Java_liba_crc32_table(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jintArray table = (*_env)->NewIntArray(_env, A_LEN(ctx->table));
    (*_env)->SetIntArrayRegion(_env, table, 0, A_LEN(ctx->table), (jint *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc32_gen(JNIEnv *_env, jobject _obj, jint poly, jboolean reversed)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    if (reversed)
    {
        a_crc32l_init(ctx->table, (a_u32)poly);
        ctx->eval = a_crc32l;
    }
    else
    {
        a_crc32m_init(ctx->table, (a_u32)poly);
        ctx->eval = a_crc32m;
    }
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_crc32_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jint value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jint)ctx->eval(ctx->table, p, (a_size)n, (a_u32)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc32_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jint value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 4);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jint)ctx->eval(ctx->table, block_p, (a_size)block_n, (a_u32)value);
    ctx->eval == a_crc32m ? a_u32_setb(&value, (a_u32)value) : a_u32_setl(&value, (a_u32)value);
    (*_env)->SetByteArrayRegion(_env, res, 0, block_n, block_p);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    (*_env)->SetByteArrayRegion(_env, res, block_n, 4, (jbyte *)&value);
    return res;
}
