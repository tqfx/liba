#include "a.h"
#include "a/crc.h"
#include "liba_crc16.h"

#undef L
#define L Java_liba_crc16
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_crc16_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

struct crc16
{
    a_u16 table[0x100];
    a_u16 (*eval)(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value);
};

JNIEXPORT void JNICALL Java_liba_crc16_init(JNIEnv *Env, jobject Obj, jshort poly, jboolean reversed)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(struct crc16));
    struct crc16 *ctx = (struct crc16 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
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

JNIEXPORT jshortArray JNICALL Java_liba_crc16_table(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jshortArray table = (*Env)->NewShortArray(Env, A_LEN(ctx->table));
    (*Env)->SetShortArrayRegion(Env, table, 0, A_LEN(ctx->table), (jshort *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc16_gen(JNIEnv *Env, jobject Obj, jshort poly, jboolean reversed)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
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
    return Obj;
}

JNIEXPORT jshort JNICALL Java_liba_crc16_eval(JNIEnv *Env, jobject Obj, jbyteArray block, jshort value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize n = (*Env)->GetArrayLength(Env, block);
    jbyte *p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jshort)ctx->eval(ctx->table, p, (a_size)n, (a_u16)value);
    (*Env)->ReleaseByteArrayElements(Env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc16_pack(JNIEnv *Env, jobject Obj, jbyteArray block, jshort value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc16 *ctx = (struct crc16 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize block_n = (*Env)->GetArrayLength(Env, block);
    jbyteArray res = (*Env)->NewByteArray(Env, block_n + 2);
    jbyte *block_p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jshort)ctx->eval(ctx->table, block_p, (a_size)block_n, (a_u16)value);
    ctx->eval == a_crc16m ? a_u16_setb(&value, (a_u16)value) : a_u16_setl(&value, (a_u16)value);
    (*Env)->SetByteArrayRegion(Env, res, 0, block_n, block_p);
    (*Env)->ReleaseByteArrayElements(Env, block, block_p, JNI_ABORT);
    (*Env)->SetByteArrayRegion(Env, res, block_n, 2, (jbyte *)&value);
    return res;
}
