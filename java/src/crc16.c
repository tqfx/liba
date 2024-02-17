#include "a.h"
#include "a/crc.h"
#include "liba_crc16.h"

#undef L
#define L Java_liba_crc16
static struct
{
    jmethodID alloc;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_crc16_INIT(JNIEnv *_env, jclass _cls)
{
    jclass _bb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    L.alloc = (*_env)->GetStaticMethodID(_env, _bb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
}

struct crc16
{
    a_u16 table[0x100];
    a_u16 (*eval)(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value);
};

JNIEXPORT void JNICALL Java_liba_crc16_init(JNIEnv *_env, jobject _obj, jshort poly, jboolean reversed)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L.alloc, (jint)sizeof(struct crc16));
    struct crc16 *ctx = (struct crc16 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    if (reversed)
    {
        a_crc16l_init(ctx->table, (a_u16)poly);
        ctx->eval = a_crc16l;
    }
    else
    {
        a_crc16m_init(ctx->table, (a_u16)poly);
        ctx->eval = a_crc16m;
    }
}

JNIEXPORT jshortArray JNICALL Java_liba_crc16_table(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jshortArray table = (*_env)->NewShortArray(_env, A_LEN(ctx->table));
    (*_env)->SetShortArrayRegion(_env, table, 0, A_LEN(ctx->table), (jshort *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc16_gen(JNIEnv *_env, jobject _obj, jshort poly, jboolean reversed)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    if (reversed)
    {
        a_crc16l_init(ctx->table, (a_u16)poly);
        ctx->eval = a_crc16l;
    }
    else
    {
        a_crc16m_init(ctx->table, (a_u16)poly);
        ctx->eval = a_crc16m;
    }
    return _obj;
}

JNIEXPORT jshort JNICALL Java_liba_crc16_eval(JNIEnv *_env, jobject _obj, jbyteArray block, jshort value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize n = (*_env)->GetArrayLength(_env, block);
    jbyte *p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jshort)ctx->eval(ctx->table, p, (a_size)n, (a_u16)value);
    (*_env)->ReleaseByteArrayElements(_env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc16_pack(JNIEnv *_env, jobject _obj, jbyteArray block, jshort value)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    jsize block_n = (*_env)->GetArrayLength(_env, block);
    jbyteArray res = (*_env)->NewByteArray(_env, block_n + 2);
    jbyte *block_p = (*_env)->GetByteArrayElements(_env, block, NULL);
    value = (jshort)ctx->eval(ctx->table, block_p, (a_size)block_n, (a_u16)value);
    ctx->eval == a_crc16m ? a_u16_setb(&value, (a_u16)value) : a_u16_setl(&value, (a_u16)value);
    (*_env)->SetByteArrayRegion(_env, res, 0, block_n, block_p);
    (*_env)->ReleaseByteArrayElements(_env, block, block_p, JNI_ABORT);
    (*_env)->SetByteArrayRegion(_env, res, block_n, 2, (jbyte *)&value);
    return res;
}
