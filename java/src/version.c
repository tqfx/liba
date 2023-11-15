#include "a.h"
#include "a/version.h"
#include "liba_version.h"

JNIEXPORT void JNICALL JPACKAGE(version_ctor)(JNIEnv *jenv, jobject jobj, jint major, jint minor, jint patch)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->NewByteArray(jenv, sizeof(a_version_s));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    ctx.major = (unsigned int)major;
    ctx.minor = (unsigned int)minor;
    ctx.patch = (unsigned int)patch;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->SetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"), jctx);
}

JNIEXPORT jint JNICALL JPACKAGE(version_major)(JNIEnv *jenv, jobject jobj)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    return (jint)ctx.major;
}

JNIEXPORT jobject JNICALL JPACKAGE(version_set_1major)(JNIEnv *jenv, jobject jobj, jint major)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    ctx.major = (unsigned int)major;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jint JNICALL JPACKAGE(version_minor)(JNIEnv *jenv, jobject jobj)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    return (jint)ctx.minor;
}

JNIEXPORT jobject JNICALL JPACKAGE(version_set_1minor)(JNIEnv *jenv, jobject jobj, jint minor)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    ctx.minor = (unsigned int)minor;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jint JNICALL JPACKAGE(version_patch)(JNIEnv *jenv, jobject jobj)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    return (jint)ctx.patch;
}

JNIEXPORT jobject JNICALL JPACKAGE(version_set_1patch)(JNIEnv *jenv, jobject jobj, jint patch)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    ctx.patch = (unsigned int)patch;
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(version_parse)(JNIEnv *jenv, jobject jobj, jstring jver)
{
    a_version_s ctx;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    char const *ver = (*jenv)->GetStringUTFChars(jenv, jver, NULL);
    a_version_parse(&ctx, ver);
    (*jenv)->ReleaseStringUTFChars(jenv, jver, ver);
    (*jenv)->SetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    return jobj;
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_lt)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    a_version_s other;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version_s), (jbyte *)&other);
    return a_version_lt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_gt)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    a_version_s other;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version_s), (jbyte *)&other);
    return a_version_gt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_le)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    a_version_s other;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version_s), (jbyte *)&other);
    return a_version_le(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_ge)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    a_version_s other;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version_s), (jbyte *)&other);
    return a_version_ge(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_eq)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    a_version_s other;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version_s), (jbyte *)&other);
    return a_version_eq(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_ne)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    a_version_s other;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version_s), (jbyte *)&other);
    return a_version_ne(&ctx, &other);
}

JNIEXPORT jint JNICALL JPACKAGE(version_cmp)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    a_version_s other;
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jbyteArray jctx = (*jenv)->GetObjectField(jenv, jobj, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    jbyteArray jother = (*jenv)->GetObjectField(jenv, jver, (*jenv)->GetFieldID(jenv, jcls, "ctx", "[B"));
    (*jenv)->GetByteArrayRegion(jenv, jctx, 0, sizeof(a_version_s), (jbyte *)&ctx);
    (*jenv)->GetByteArrayRegion(jenv, jother, 0, sizeof(a_version_s), (jbyte *)&other);
    return a_version_cmp(&ctx, &other);
}
