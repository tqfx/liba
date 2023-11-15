#include "version.h"
#include "liba_version.h"

j_version_s *j_version_new(JNIEnv *const jenv, jobject const jobj, j_version_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "version");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    jctx->jcls = jcls;
    jctx->major = (*jenv)->GetFieldID(jenv, jcls, "major", "I");
    jctx->minor = (*jenv)->GetFieldID(jenv, jcls, "minor", "I");
    jctx->patch = (*jenv)->GetFieldID(jenv, jcls, "patch", "I");
    return jctx;
}

jobject j_version_get(j_version_s const *const jctx, a_version_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    ctx->major = (unsigned int)(*jenv)->GetIntField(jenv, jobj, jctx->major);
    ctx->minor = (unsigned int)(*jenv)->GetIntField(jenv, jobj, jctx->minor);
    ctx->patch = (unsigned int)(*jenv)->GetIntField(jenv, jobj, jctx->patch);
    return jctx->jobj;
}

jobject j_version_set(j_version_s const *const jctx, a_version_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    (*jenv)->SetIntField(jenv, jobj, jctx->major, (jint)ctx->major);
    (*jenv)->SetIntField(jenv, jobj, jctx->minor, (jint)ctx->minor);
    (*jenv)->SetIntField(jenv, jobj, jctx->patch, (jint)ctx->patch);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(version_parse)(JNIEnv *jenv, jobject jobj, jstring jver)
{
    a_version_s ctx;
    j_version_s jctx;
    j_version_new(jenv, jobj, &jctx);
    char const *ver = (*jenv)->GetStringUTFChars(jenv, jver, NULL);
    a_version_parse(&ctx, ver);
    (*jenv)->ReleaseStringUTFChars(jenv, jver, ver);
    return j_version_set(&jctx, &ctx);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_lt)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    j_version_s jctx;
    a_version_s other;
    j_version_s jother;
    j_version_get(j_version_new(jenv, jobj, &jctx), &ctx);
    j_version_get(j_version_new(jenv, jver, &jother), &other);
    return a_version_lt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_gt)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    j_version_s jctx;
    a_version_s other;
    j_version_s jother;
    j_version_get(j_version_new(jenv, jobj, &jctx), &ctx);
    j_version_get(j_version_new(jenv, jver, &jother), &other);
    return a_version_gt(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_le)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    j_version_s jctx;
    a_version_s other;
    j_version_s jother;
    j_version_get(j_version_new(jenv, jobj, &jctx), &ctx);
    j_version_get(j_version_new(jenv, jver, &jother), &other);
    return a_version_le(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_ge)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    j_version_s jctx;
    a_version_s other;
    j_version_s jother;
    j_version_get(j_version_new(jenv, jobj, &jctx), &ctx);
    j_version_get(j_version_new(jenv, jver, &jother), &other);
    return a_version_ge(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_eq)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    j_version_s jctx;
    a_version_s other;
    j_version_s jother;
    j_version_get(j_version_new(jenv, jobj, &jctx), &ctx);
    j_version_get(j_version_new(jenv, jver, &jother), &other);
    return a_version_eq(&ctx, &other);
}

JNIEXPORT jboolean JNICALL JPACKAGE(version_ne)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    j_version_s jctx;
    a_version_s other;
    j_version_s jother;
    j_version_get(j_version_new(jenv, jobj, &jctx), &ctx);
    j_version_get(j_version_new(jenv, jver, &jother), &other);
    return a_version_ne(&ctx, &other);
}

JNIEXPORT jint JNICALL JPACKAGE(version_cmp)(JNIEnv *jenv, jobject jobj, jobject jver)
{
    a_version_s ctx;
    j_version_s jctx;
    a_version_s other;
    j_version_s jother;
    j_version_get(j_version_new(jenv, jobj, &jctx), &ctx);
    j_version_get(j_version_new(jenv, jver, &jother), &other);
    return a_version_cmp(&ctx, &other);
}
