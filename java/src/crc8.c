#include "a.h"
#include "a/crc.h"
#include "liba_crc8.h"

#undef L
#define L Java_liba_crc8
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_crc8_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
}

struct crc8
{
    a_u8 table[0x100];
};

JNIEXPORT void JNICALL Java_liba_crc8_init(JNIEnv *Env, jobject Obj, jbyte poly, jboolean reversed)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(struct crc8));
    struct crc8 *ctx = (struct crc8 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    reversed ? a_crc8l_init(ctx->table, (a_u8)poly)
             : a_crc8m_init(ctx->table, (a_u8)poly);
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc8_table(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc8 *ctx = (struct crc8 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jbyteArray table = (*Env)->NewByteArray(Env, A_LEN(ctx->table));
    (*Env)->SetByteArrayRegion(Env, table, 0, A_LEN(ctx->table), (jbyte *)ctx->table);
    return table;
}

JNIEXPORT jobject JNICALL Java_liba_crc8_gen(JNIEnv *Env, jobject Obj, jbyte poly, jboolean reversed)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc8 *ctx = (struct crc8 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    reversed ? a_crc8l_init(ctx->table, (a_u8)poly)
             : a_crc8m_init(ctx->table, (a_u8)poly);
    return Obj;
}

JNIEXPORT jbyte JNICALL Java_liba_crc8_eval(JNIEnv *Env, jobject Obj, jbyteArray block, jbyte value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc8 *ctx = (struct crc8 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize n = (*Env)->GetArrayLength(Env, block);
    jbyte *p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jbyte)a_crc8(ctx->table, p, (a_size)n, (a_u8)value);
    (*Env)->ReleaseByteArrayElements(Env, block, p, JNI_ABORT);
    return value;
}

JNIEXPORT jbyteArray JNICALL Java_liba_crc8_pack(JNIEnv *Env, jobject Obj, jbyteArray block, jbyte value)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    struct crc8 *ctx = (struct crc8 *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    jsize block_n = (*Env)->GetArrayLength(Env, block);
    jbyteArray res = (*Env)->NewByteArray(Env, block_n + 1);
    jbyte *block_p = (*Env)->GetByteArrayElements(Env, block, NULL);
    value = (jbyte)a_crc8(ctx->table, block_p, (a_size)block_n, (a_u8)value);
    (*Env)->SetByteArrayRegion(Env, res, 0, block_n, block_p);
    (*Env)->ReleaseByteArrayElements(Env, block, block_p, JNI_ABORT);
    (*Env)->SetByteArrayRegion(Env, res, block_n, 1, &value);
    return res;
}
