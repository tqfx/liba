#include "a.h"
#include "a/version.h"
#include "liba_version.h"

#undef L
#define L Java_liba_version
static struct
{
    jmethodID _new;
    jfieldID ctx;
} L = {NULL, NULL};

JNIEXPORT void JNICALL Java_liba_version_clinit(JNIEnv *_env, jclass _cls)
{
    jclass _nbb = (*_env)->FindClass(_env, "Ljava/nio/ByteBuffer;");
    L._new = (*_env)->GetStaticMethodID(_env, _nbb, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "Ljava/nio/ByteBuffer;");
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "MAJOR", "I"), A_VERSION_MAJOR);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "MINOR", "I"), A_VERSION_MINOR);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "PATCH", "I"), A_VERSION_PATCH);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "TWEAK", "I"), A_VERSION_TWEAK);
}

JNIEXPORT void JNICALL Java_liba_version_initS(JNIEnv *_env, jobject _obj, jstring _ver)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)sizeof(a_version));
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    char const *ver = (*_env)->GetStringUTFChars(_env, _ver, NULL);
    ctx->alpha[0] = '.';
    a_version_parse(ctx, ver);
    (*_env)->ReleaseStringUTFChars(_env, _ver, ver);
}

JNIEXPORT void JNICALL Java_liba_version_init(JNIEnv *_env, jobject _obj, jint major, jint minor, jint third, jint extra)
{
    jobject _ctx = (*_env)->CallObjectMethod(_env, _obj, L._new, (jint)sizeof(a_version));
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
    ctx->major = (unsigned int)major;
    ctx->minor = (unsigned int)minor;
    ctx->third = (unsigned int)third;
    ctx->extra = (unsigned int)extra;
    ctx->alpha[0] = '.';
}

JNIEXPORT jint JNICALL Java_liba_version_check(JNIEnv *_env, jclass _cls, jint major, jint minor, jint patch)
{
    return (void)_env, (void)_cls, a_version_check((unsigned int)major, (unsigned int)minor, (unsigned int)patch);
}

JNIEXPORT jstring JNICALL Java_liba_version_toString(JNIEnv *_env, jobject _obj)
{
    char str[48];
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version_tostr(ctx, str, sizeof(str));
    return (*_env)->NewStringUTF(_env, str);
}

JNIEXPORT jint JNICALL Java_liba_version_major__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return (jint)ctx->major;
}

JNIEXPORT jobject JNICALL Java_liba_version_major__I(JNIEnv *_env, jobject _obj, jint major)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->major = (unsigned int)major;
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_version_minor__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return (jint)ctx->minor;
}

JNIEXPORT jobject JNICALL Java_liba_version_minor__I(JNIEnv *_env, jobject _obj, jint minor)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->minor = (unsigned int)minor;
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_version_third__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return (jint)ctx->third;
}

JNIEXPORT jobject JNICALL Java_liba_version_third__I(JNIEnv *_env, jobject _obj, jint third)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->third = (unsigned int)third;
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_version_extra__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    return (jint)ctx->extra;
}

JNIEXPORT jobject JNICALL Java_liba_version_extra__I(JNIEnv *_env, jobject _obj, jint extra)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    ctx->extra = (unsigned int)extra;
    return _obj;
}

JNIEXPORT jstring JNICALL Java_liba_version_alpha__(JNIEnv *_env, jobject _obj)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    char alpha[sizeof(ctx->alpha) + 1];
    a_version_alpha(ctx, alpha);
    return (*_env)->NewStringUTF(_env, alpha);
}

JNIEXPORT jobject JNICALL Java_liba_version_alpha__Ljava_lang_String_2(JNIEnv *_env, jobject _obj, jstring _alpha)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    char const *alpha = (*_env)->GetStringUTFChars(_env, _alpha, 0);
    a_version_set_alpha(ctx, alpha);
    (*_env)->ReleaseStringUTFChars(_env, _alpha, alpha);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_version_parse(JNIEnv *_env, jobject _obj, jstring _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    char const *ver = (*_env)->GetStringUTFChars(_env, _ver, NULL);
    a_version_parse(ctx, ver);
    (*_env)->ReleaseStringUTFChars(_env, _ver, ver);
    return _obj;
}

JNIEXPORT jboolean JNICALL Java_liba_version_lt(JNIEnv *_env, jobject _obj, jobject _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jobject _rhs = (*_env)->GetObjectField(_env, _ver, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version *rhs = (a_version *)(*_env)->GetDirectBufferAddress(_env, _rhs);
    return a_version_lt(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_gt(JNIEnv *_env, jobject _obj, jobject _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jobject _rhs = (*_env)->GetObjectField(_env, _ver, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version *rhs = (a_version *)(*_env)->GetDirectBufferAddress(_env, _rhs);
    return a_version_gt(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_le(JNIEnv *_env, jobject _obj, jobject _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jobject _rhs = (*_env)->GetObjectField(_env, _ver, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version *rhs = (a_version *)(*_env)->GetDirectBufferAddress(_env, _rhs);
    return a_version_le(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ge(JNIEnv *_env, jobject _obj, jobject _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jobject _rhs = (*_env)->GetObjectField(_env, _ver, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version *rhs = (a_version *)(*_env)->GetDirectBufferAddress(_env, _rhs);
    return a_version_ge(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_eq(JNIEnv *_env, jobject _obj, jobject _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jobject _rhs = (*_env)->GetObjectField(_env, _ver, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version *rhs = (a_version *)(*_env)->GetDirectBufferAddress(_env, _rhs);
    return a_version_eq(ctx, rhs);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ne(JNIEnv *_env, jobject _obj, jobject _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jobject _rhs = (*_env)->GetObjectField(_env, _ver, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version *rhs = (a_version *)(*_env)->GetDirectBufferAddress(_env, _rhs);
    return a_version_ne(ctx, rhs);
}

JNIEXPORT jint JNICALL Java_liba_version_cmp(JNIEnv *_env, jobject _obj, jobject _ver)
{
    jobject _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jobject _rhs = (*_env)->GetObjectField(_env, _ver, L.ctx);
    a_version *ctx = (a_version *)(*_env)->GetDirectBufferAddress(_env, _ctx);
    a_version *rhs = (a_version *)(*_env)->GetDirectBufferAddress(_env, _rhs);
    return a_version_cmp(ctx, rhs);
}
