#include "a.h"
#include "a/mf.h"
#include "liba_mf.h"

JNIEXPORT void JNICALL Java_liba_mf_INIT(JNIEnv *_env, jclass _cls)
{
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "NUL", "I"), A_MF_NUL);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "GAUSS", "I"), A_MF_GAUSS);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "GAUSS2", "I"), A_MF_GAUSS2);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "GBELL", "I"), A_MF_GBELL);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "SIG", "I"), A_MF_SIG);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "DSIG", "I"), A_MF_DSIG);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "PSIG", "I"), A_MF_PSIG);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "TRAP", "I"), A_MF_TRAP);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "TRI", "I"), A_MF_TRI);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "LINS", "I"), A_MF_LINS);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "LINZ", "I"), A_MF_LINZ);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "S", "I"), A_MF_S);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "Z", "I"), A_MF_Z);
    (*_env)->SetStaticIntField(_env, _cls, (*_env)->GetStaticFieldID(_env, _cls, "PI", "I"), A_MF_PI);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_gauss(JNIEnv *_env, jclass _cls, jdouble x, jdouble sigma, jdouble c)
{
    return (void)(_env), (void)(_cls), a_mf_gauss(x, sigma, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_gauss2(JNIEnv *_env, jclass _cls, jdouble x, jdouble sigma1, jdouble c1, jdouble sigma2, jdouble c2)
{
    return (void)(_env), (void)(_cls), a_mf_gauss2(x, sigma1, c1, sigma2, c2);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_gbell(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b, jdouble c)
{
    return (void)(_env), (void)(_cls), a_mf_gbell(x, a, b, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_sig(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble c)
{
    return (void)(_env), (void)(_cls), a_mf_sig(x, a, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_dsig(JNIEnv *_env, jclass _cls, jdouble x, jdouble a1, jdouble c1, jdouble a2, jdouble c2)
{
    return (void)(_env), (void)(_cls), a_mf_dsig(x, a1, c1, a2, c2);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_psig(JNIEnv *_env, jclass _cls, jdouble x, jdouble a1, jdouble c1, jdouble a2, jdouble c2)
{
    return (void)(_env), (void)(_cls), a_mf_psig(x, a1, c1, a2, c2);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_trap(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b, jdouble c, jdouble d)
{
    return (void)(_env), (void)(_cls), a_mf_trap(x, a, b, c, d);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_tri(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b, jdouble c)
{
    return (void)(_env), (void)(_cls), a_mf_tri(x, a, b, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_lins(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b)
{
    return (void)(_env), (void)(_cls), a_mf_lins(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_linz(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b)
{
    return (void)(_env), (void)(_cls), a_mf_linz(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_s(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b)
{
    return (void)(_env), (void)(_cls), a_mf_s(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_z(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b)
{
    return (void)(_env), (void)(_cls), a_mf_z(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_pi(JNIEnv *_env, jclass _cls, jdouble x, jdouble a, jdouble b, jdouble c, jdouble d)
{
    return (void)(_env), (void)(_cls), a_mf_pi(x, a, b, c, d);
}
