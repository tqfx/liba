#include "a.h"
#include "a/version.h"
#undef a_version_check
#include "liba_version.h"

#undef L
#define L Java_liba_version
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_version_INIT(JNIEnv *_env, jclass _cls)
{
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "MAJOR", "I"), A_VERSION_MAJOR);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "MINOR", "I"), A_VERSION_MINOR);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "PATCH", "I"), A_VERSION_PATCH);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "TWEAK", "I"), A_VERSION_TWEAK);
    L.ctx = (*_env)->GetFieldID(_env, _cls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_version_init(JNIEnv *_env, jobject _obj, jint major, jint minor, jint patch)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->NewByteArray(_env, sizeof(a_version));
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.major = (unsigned int)major;
    ctx.minor = (unsigned int)minor;
    ctx.patch = (unsigned int)patch;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->SetObjectField(_env, _obj, L.ctx, _ctx);
}

JNIEXPORT jint JNICALL Java_liba_version_major__(JNIEnv *_env, jobject _obj)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.major;
}

JNIEXPORT jobject JNICALL Java_liba_version_major__I(JNIEnv *_env, jobject _obj, jint major)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.major = (unsigned int)major;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_version_minor__(JNIEnv *_env, jobject _obj)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.minor;
}

JNIEXPORT jobject JNICALL Java_liba_version_minor__I(JNIEnv *_env, jobject _obj, jint minor)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.minor = (unsigned int)minor;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_version_patch__(JNIEnv *_env, jobject _obj)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.patch;
}

JNIEXPORT jobject JNICALL Java_liba_version_patch__I(JNIEnv *_env, jobject _obj, jint patch)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.patch = (unsigned int)patch;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jint JNICALL Java_liba_version_extra__(JNIEnv *_env, jobject _obj)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.extra;
}

JNIEXPORT jobject JNICALL Java_liba_version_extra__I(JNIEnv *_env, jobject _obj, jint extra)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.extra = (unsigned int)extra;
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jobject JNICALL Java_liba_version_parse(JNIEnv *_env, jobject _obj, jstring _ver)
{
    a_version ctx;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    char const *ver = (*_env)->GetStringUTFChars(_env, _ver, NULL);
    a_version_parse(&ctx, ver);
    (*_env)->ReleaseStringUTFChars(_env, _ver, ver);
    (*_env)->SetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return _obj;
}

JNIEXPORT jboolean JNICALL Java_liba_version_lt(JNIEnv *_env, jobject _obj, jobject _ver)
{
    a_version ctx;
    a_version other;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _other = (*_env)->GetObjectField(_env, _ver, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->GetByteArrayRegion(_env, _other, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_lt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_gt(JNIEnv *_env, jobject _obj, jobject _ver)
{
    a_version ctx;
    a_version other;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _other = (*_env)->GetObjectField(_env, _ver, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->GetByteArrayRegion(_env, _other, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_gt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_le(JNIEnv *_env, jobject _obj, jobject _ver)
{
    a_version ctx;
    a_version other;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _other = (*_env)->GetObjectField(_env, _ver, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->GetByteArrayRegion(_env, _other, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_le(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ge(JNIEnv *_env, jobject _obj, jobject _ver)
{
    a_version ctx;
    a_version other;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _other = (*_env)->GetObjectField(_env, _ver, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->GetByteArrayRegion(_env, _other, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_ge(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_eq(JNIEnv *_env, jobject _obj, jobject _ver)
{
    a_version ctx;
    a_version other;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _other = (*_env)->GetObjectField(_env, _ver, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->GetByteArrayRegion(_env, _other, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_eq(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ne(JNIEnv *_env, jobject _obj, jobject _ver)
{
    a_version ctx;
    a_version other;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _other = (*_env)->GetObjectField(_env, _ver, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->GetByteArrayRegion(_env, _other, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_ne(&ctx, &other);
}

JNIEXPORT jint JNICALL Java_liba_version_cmp(JNIEnv *_env, jobject _obj, jobject _ver)
{
    a_version ctx;
    a_version other;
    jbyteArray _ctx = (*_env)->GetObjectField(_env, _obj, L.ctx);
    jbyteArray _other = (*_env)->GetObjectField(_env, _ver, L.ctx);
    (*_env)->GetByteArrayRegion(_env, _ctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*_env)->GetByteArrayRegion(_env, _other, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_cmp(&ctx, &other);
}

JNIEXPORT jint JNICALL Java_liba_version_check(JNIEnv *_env, jclass _cls, jint major, jint minor, jint patch)
{
    return (void)(_env), (void)(_cls), a_version_check((unsigned int)major, (unsigned int)minor, (unsigned int)patch);
}
