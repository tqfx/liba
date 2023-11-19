#include "a.h"
#include "a/mf.h"
#include "liba_mf.h"

JNIEXPORT void JNICALL JPACKAGE(mf_INIT)(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "NUL", "I"), A_MF_NUL);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "GAUSS", "I"), A_MF_GAUSS);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "GAUSS2", "I"), A_MF_GAUSS2);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "GBELL", "I"), A_MF_GBELL);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "SIG", "I"), A_MF_SIG);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "DSIG", "I"), A_MF_DSIG);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "PSIG", "I"), A_MF_PSIG);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "TRAP", "I"), A_MF_TRAP);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "TRI", "I"), A_MF_TRI);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "LINS", "I"), A_MF_LINS);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "LINZ", "I"), A_MF_LINZ);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "S", "I"), A_MF_S);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "Z", "I"), A_MF_Z);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "PI", "I"), A_MF_PI);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_gauss)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble sigma, jdouble c)
{
    return (void)(jenv), (void)(jcls), a_mf_gauss(x, sigma, c);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_gauss2)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble sigma1, jdouble c1, jdouble sigma2, jdouble c2)
{
    return (void)(jenv), (void)(jcls), a_mf_gauss2(x, sigma1, c1, sigma2, c2);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_gbell)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b, jdouble c)
{
    return (void)(jenv), (void)(jcls), a_mf_gbell(x, a, b, c);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_sig)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble c)
{
    return (void)(jenv), (void)(jcls), a_mf_sig(x, a, c);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_dsig)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a1, jdouble c1, jdouble a2, jdouble c2)
{
    return (void)(jenv), (void)(jcls), a_mf_dsig(x, a1, c1, a2, c2);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_psig)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a1, jdouble c1, jdouble a2, jdouble c2)
{
    return (void)(jenv), (void)(jcls), a_mf_psig(x, a1, c1, a2, c2);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_trap)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b, jdouble c, jdouble d)
{
    return (void)(jenv), (void)(jcls), a_mf_trap(x, a, b, c, d);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_tri)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b, jdouble c)
{
    return (void)(jenv), (void)(jcls), a_mf_tri(x, a, b, c);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_lins)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b)
{
    return (void)(jenv), (void)(jcls), a_mf_lins(x, a, b);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_linz)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b)
{
    return (void)(jenv), (void)(jcls), a_mf_linz(x, a, b);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_s)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b)
{
    return (void)(jenv), (void)(jcls), a_mf_s(x, a, b);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_z)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b)
{
    return (void)(jenv), (void)(jcls), a_mf_z(x, a, b);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_pi)(JNIEnv *jenv, jclass jcls, jdouble x, jdouble a, jdouble b, jdouble c, jdouble d)
{
    return (void)(jenv), (void)(jcls), a_mf_pi(x, a, b, c, d);
}
