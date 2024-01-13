#include "a.h"
#include "a/version.h"
#include "liba_version.h"

#undef L
#define L Java_liba_version
static struct
{
    jfieldID ctx;
} L = {NULL};

JNIEXPORT void JNICALL Java_liba_version_INIT(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "MAJOR", "I"), A_VERSION_MAJOR);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "MINOR", "I"), A_VERSION_MINOR);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "PATCH", "I"), A_VERSION_PATCH);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "TWEAK", "I"), A_VERSION_TWEAK);
    L.ctx = (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B");
}

JNIEXPORT void JNICALL Java_liba_version_init(JNIEnv *jenv, jobject jobj, jint major, jint minor, jint patch)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_version));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.major = (unsigned int)major;
    ctx.minor = (unsigned int)minor;
    ctx.patch = (unsigned int)patch;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, L.ctx, jctx);
}

JNIEXPORT jint JNICALL Java_liba_version_major__(JNIEnv *jenv, jobject jobj)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.major;
}

JNIEXPORT jobject JNICALL Java_liba_version_major__I(JNIEnv *jenv, jobject jobj, jint major)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.major = (unsigned int)major;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jint JNICALL Java_liba_version_minor__(JNIEnv *jenv, jobject jobj)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.minor;
}

JNIEXPORT jobject JNICALL Java_liba_version_minor__I(JNIEnv *jenv, jobject jobj, jint minor)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.minor = (unsigned int)minor;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jint JNICALL Java_liba_version_patch__(JNIEnv *jenv, jobject jobj)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.patch;
}

JNIEXPORT jobject JNICALL Java_liba_version_patch__I(JNIEnv *jenv, jobject jobj, jint patch)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.patch = (unsigned int)patch;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jint JNICALL Java_liba_version_extra__(JNIEnv *jenv, jobject jobj)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return (jint)ctx.extra;
}

JNIEXPORT jobject JNICALL Java_liba_version_extra__I(JNIEnv *jenv, jobject jobj, jint extra)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    ctx.extra = (unsigned int)extra;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL Java_liba_version_parse(JNIEnv *jenv, jobject jobj, jstring jver)
{
    a_version ctx;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    char const *ver = (*jenv)->GetStringUTFChars(jenv, jver, NULL);
    a_version_parse(&ctx, ver);
    (*jenv)->ReleaseStringUTFChars(jenv, jver, ver);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jboolean JNICALL Java_liba_version_lt(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version ctx;
    a_version other;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_lt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_gt(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version ctx;
    a_version other;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_gt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_le(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version ctx;
    a_version other;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_le(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ge(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version ctx;
    a_version other;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_ge(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_eq(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version ctx;
    a_version other;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_eq(&ctx, &other);
}

JNIEXPORT jboolean JNICALL Java_liba_version_ne(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version ctx;
    a_version other;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_ne(&ctx, &other);
}

JNIEXPORT jint JNICALL Java_liba_version_cmp(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version ctx;
    a_version other;
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, L.ctx);
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, L.ctx);
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version), (jbyte *)&other);
    return a_version_cmp(&ctx, &other);
}

JNIEXPORT jint JNICALL Java_liba_version_check(JNIEnv *jenv, jclass jcls, jint major, jint minor, jint patch)
{
#undef a_version_check
    return (void)(jenv), (void)(jcls), a_version_check((unsigned int)major, (unsigned int)minor, (unsigned int)patch);
}
