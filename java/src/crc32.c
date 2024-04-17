#include "a.h"
#include "a/crc.h"
#include "liba_crc32.h"

#undef L
#define L Java_liba_crc32
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_crc32_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

struct crc32
{
    a_u32 table[0x100];
    a_u32 (*eval)(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value);
};

JNIEXPORT void JNICALL Java_liba_crc32_init(JNIEnv *Env, jobject Obj, jint poly, jboolean reversed)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(struct crc32));
    struct crc32 *ctx = (struct crc32 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
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

JNIEXPORT jintArray JNICALL Java_liba_crc32_table(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jintArray table = (*Env)->NewIntArray(Env, A_LEN(ctx->table));
    (*Env)->SetIntArrayRegion(Env, table, 0, A_LEN(ctx->table), (jint *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc32_gen(JNIEnv *Env, jobject Obj, jint poly, jboolean reversed)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
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
    return Obj;
}

JNIEXPORT jint JNICALL Java_liba_crc32_eval(JNIEnv *Env, jobject Obj, jbyteArray block, jint value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize n = (*Env)->GetArrayLength(Env, block);
    jbyte *p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jint)ctx->eval(ctx->table, p, (a_size)n, (a_u32)value);
    (*Env)->ReleaseByteArrayElements(Env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc32_pack(JNIEnv *Env, jobject Obj, jbyteArray block, jint value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc32 *ctx = (struct crc32 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize block_n = (*Env)->GetArrayLength(Env, block);
    jbyteArray res = (*Env)->NewByteArray(Env, block_n + 4);
    jbyte *block_p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jint)ctx->eval(ctx->table, block_p, (a_size)block_n, (a_u32)value);
    ctx->eval == a_crc32m ? a_u32_setb(&value, (a_u32)value) : a_u32_setl(&value, (a_u32)value);
    (*Env)->SetByteArrayRegion(Env, res, 0, block_n, block_p);
    (*Env)->ReleaseByteArrayElements(Env, block, block_p, JNI_ABORT);
    (*Env)->SetByteArrayRegion(Env, res, block_n, 4, (jbyte *)&value);
    return res;
}
