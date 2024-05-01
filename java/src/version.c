#include "a.h"
#include "a/version.h"
#include "liba_version.h"

#undef L
#define L Java_liba_version
static struct
{
    jmethodID New;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_version_clinit(JNIEnv *Env, jclass Cls)
{
    jclass Nbb = (*Env)->FindClass(Env, "Ljava/nio/ByteBuffer;");
    L.New = (*Env)->GetStaticMethodID(Env, Nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*Env)->GetFieldID(Env, Cls, "ctx", "Ljava/nio/ByteBuffer;");
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "MAJOR", "I"), A_VERSION_MAJOR);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "MINOR", "I"), A_VERSION_MINOR);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "PATCH", "I"), A_VERSION_PATCH);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "TWEAK", "I"), A_VERSION_TWEAK);
}

JNIEXPORT void JNICALL Java_liba_version_init__Ljava_lang_String_2(JNIEnv *Env, jobject Obj, jstring Ver)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_version));
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    char const *ver = (*Env)->GetStringUTFChars(Env, Ver, NULL);
    ctx->alpha[0] = '.';
    a_version_parse(ctx, ver);
    (*Env)->ReleaseStringUTFChars(Env, Ver, ver);
}

JNIEXPORT void JNICALL Java_liba_version_init__IIII(JNIEnv *Env, jobject Obj, jint major, jint minor, jint third, jint extra)
{
    jobject Ctx = (*Env)->CallObjectMethod(Env, Obj, L.New, (jint)sizeof(a_version));
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    (*Env)->SetObjectField(Env, Obj, L.ctx, Ctx);
    ctx->major = (unsigned int)major;
    ctx->minor = (unsigned int)minor;
    ctx->third = (unsigned int)third;
    ctx->extra = (unsigned int)extra;
    ctx->alpha[0] = '.';
}

JNIEXPORT jint JNICALL Java_liba_version_check(JNIEnv *Env, jclass Cls, jint major, jint minor, jint patch)
{
    return (void)Env, (void)Cls, a_version_check((unsigned int)major, (unsigned int)minor, (unsigned int)patch);
}

JNIEXPORT jstring JNICALL Java_liba_version_toString(JNIEnv *Env, jobject Obj)
{
    char str[48];
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version_tostr(ctx, str, sizeof(str));
    return (*Env)->NewStringUTF(Env, str);
}

JNIEXPORT jint JNICALL Java_liba_version_major__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->major;
}

JNIEXPORT jobject JNICALL Java_liba_version_major__I(JNIEnv *Env, jobject Obj, jint major)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->major = (unsigned int)major;
    return Obj;
}

JNIEXPORT jint JNICALL Java_liba_version_minor__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->minor;
}

JNIEXPORT jobject JNICALL Java_liba_version_minor__I(JNIEnv *Env, jobject Obj, jint minor)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->minor = (unsigned int)minor;
    return Obj;
}

JNIEXPORT jint JNICALL Java_liba_version_third__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->third;
}

JNIEXPORT jobject JNICALL Java_liba_version_third__I(JNIEnv *Env, jobject Obj, jint third)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->third = (unsigned int)third;
    return Obj;
}

JNIEXPORT jint JNICALL Java_liba_version_extra__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    return (jint)ctx->extra;
}

JNIEXPORT jobject JNICALL Java_liba_version_extra__I(JNIEnv *Env, jobject Obj, jint extra)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    ctx->extra = (unsigned int)extra;
    return Obj;
}

JNIEXPORT jstring JNICALL Java_liba_version_alpha__(JNIEnv *Env, jobject Obj)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    char alpha[sizeof(ctx->alpha) + 1];
    a_version_alpha(ctx, alpha);
    return (*Env)->NewStringUTF(Env, alpha);
}

JNIEXPORT jobject JNICALL Java_liba_version_alpha__Ljava_lang_String_2(JNIEnv *Env, jobject Obj, jstring Alpha)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    char const *alpha = (*Env)->GetStringUTFChars(Env, Alpha, 0);
    a_version_set_alpha(ctx, alpha);
    (*Env)->ReleaseStringUTFChars(Env, Alpha, alpha);
    return Obj;
}

JNIEXPORT jobject JNICALL Java_liba_version_parse(JNIEnv *Env, jobject Obj, jstring Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    char const *ver = (*Env)->GetStringUTFChars(Env, Ver, NULL);
    a_version_parse(ctx, ver);
    (*Env)->ReleaseStringUTFChars(Env, Ver, ver);
    return Obj;
}

JNIEXPORT jboolean JNICALL Java_liba_version_lt(JNIEnv *Env, jobject Obj, jobject Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    jobject Rhs = (*Env)->GetObjectField(Env, Ver, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version *rhs = (a_version *)(*Env)->GetDirectBufferAddress(Env, Rhs);
    return a_version_lt(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_gt(JNIEnv *Env, jobject Obj, jobject Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    jobject Rhs = (*Env)->GetObjectField(Env, Ver, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version *rhs = (a_version *)(*Env)->GetDirectBufferAddress(Env, Rhs);
    return a_version_gt(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_le(JNIEnv *Env, jobject Obj, jobject Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    jobject Rhs = (*Env)->GetObjectField(Env, Ver, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version *rhs = (a_version *)(*Env)->GetDirectBufferAddress(Env, Rhs);
    return a_version_le(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ge(JNIEnv *Env, jobject Obj, jobject Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    jobject Rhs = (*Env)->GetObjectField(Env, Ver, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version *rhs = (a_version *)(*Env)->GetDirectBufferAddress(Env, Rhs);
    return a_version_ge(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_eq(JNIEnv *Env, jobject Obj, jobject Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    jobject Rhs = (*Env)->GetObjectField(Env, Ver, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version *rhs = (a_version *)(*Env)->GetDirectBufferAddress(Env, Rhs);
    return a_version_eq(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ne(JNIEnv *Env, jobject Obj, jobject Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    jobject Rhs = (*Env)->GetObjectField(Env, Ver, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version *rhs = (a_version *)(*Env)->GetDirectBufferAddress(Env, Rhs);
    return a_version_ne(ctx, rhs);
}

JNIEXPORT jint JNICALL Java_liba_version_cmp(JNIEnv *Env, jobject Obj, jobject Ver)
{
    jobject Ctx = (*Env)->GetObjectField(Env, Obj, L.ctx);
    jobject Rhs = (*Env)->GetObjectField(Env, Ver, L.ctx);
    a_version *ctx = (a_version *)(*Env)->GetDirectBufferAddress(Env, Ctx);
    a_version *rhs = (a_version *)(*Env)->GetDirectBufferAddress(Env, Rhs);
    return a_version_cmp(ctx, rhs);
}
