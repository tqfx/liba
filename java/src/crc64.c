#include "a.h"
#include "a/crc.h"
#include "liba_crc64.h"

#undef L
#define L Java_liba_crc64
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

struct crc64
{
    a_u64 table[0x100];
    a_u64 (*eval)(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value);
};

JNIEXPORT void JNICALL Java_liba_crc64_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

JNIEXPORT void JNICALL Java_liba_crc64_init(JNIEnv *Env, jobject Obj, jlong poly, jboolean reversed)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(struct crc64));
    struct crc64 *ctx = (struct crc64 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
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

JNIEXPORT jlongArray JNICALL Java_liba_crc64_table(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jlongArray table = (*Env)->NewLongArray(Env, A_LEN(ctx->table));
    (*Env)->SetLongArrayRegion(Env, table, 0, A_LEN(ctx->table), (jlong *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc64_gen(JNIEnv *Env, jobject Obj, jlong poly, jboolean reversed)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
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
    return Obj;
}

JNIEXPORT jlong JNICALL Java_liba_crc64_eval(JNIEnv *Env, jobject Obj, jbyteArray block, jlong value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize n = (*Env)->GetArrayLength(Env, block);
    jbyte *p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jlong)ctx->eval(ctx->table, p, (a_size)n, (a_u64)value);
    (*Env)->ReleaseByteArrayElements(Env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc64_pack(JNIEnv *Env, jobject Obj, jbyteArray block, jlong value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc64 *ctx = (struct crc64 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize block_n = (*Env)->GetArrayLength(Env, block);
    jbyteArray New = (*Env)->NewByteArray(Env, block_n + 8);
    jbyte *block_p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jlong)ctx->eval(ctx->table, block_p, (a_size)block_n, (a_u64)value);
    ctx->eval == a_crc64m ? a_u64_setb(&value, (a_u64)value) : a_u64_setl(&value, (a_u64)value);
    (*Env)->SetByteArrayRegion(Env, New, 0, block_n, block_p);
    (*Env)->ReleaseByteArrayElements(Env, block, block_p, JNI_ABORT);
    (*Env)->SetByteArrayRegion(Env, New, block_n, 8, (jbyte *)&value);
    return New;
}
