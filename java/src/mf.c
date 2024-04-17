#include "a.h"
#include "a/mf.h"
#include "liba_mf.h"

JNIEXPORT void JNICALL Java_liba_mf_clinit(JNIEnv *Env, jclass Cls)
{
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "NUL", "I"), A_MF_NUL);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "GAUSS", "I"), A_MF_GAUSS);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "GAUSS2", "I"), A_MF_GAUSS2);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "GBELL", "I"), A_MF_GBELL);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "SIG", "I"), A_MF_SIG);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "DSIG", "I"), A_MF_DSIG);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "PSIG", "I"), A_MF_PSIG);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "TRAP", "I"), A_MF_TRAP);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "TRI", "I"), A_MF_TRI);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "LINS", "I"), A_MF_LINS);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "LINZ", "I"), A_MF_LINZ);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "S", "I"), A_MF_S);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "Z", "I"), A_MF_Z);
    (*Env)->SetStaticIntField(Env, Cls, (*Env)->GetStaticFieldID(Env, Cls, "PI", "I"), A_MF_PI);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_gauss(JNIEnv *Env, jclass Cls, jdouble x, jdouble sigma, jdouble c)
{
    return (void)Env, (void)Cls, a_mf_gauss(x, sigma, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_gauss2(JNIEnv *Env, jclass Cls, jdouble x, jdouble sigma1, jdouble c1, jdouble sigma2, jdouble c2)
{
    return (void)Env, (void)Cls, a_mf_gauss2(x, sigma1, c1, sigma2, c2);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_gbell(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b, jdouble c)
{
    return (void)Env, (void)Cls, a_mf_gbell(x, a, b, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_sig(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble c)
{
    return (void)Env, (void)Cls, a_mf_sig(x, a, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_dsig(JNIEnv *Env, jclass Cls, jdouble x, jdouble a1, jdouble c1, jdouble a2, jdouble c2)
{
    return (void)Env, (void)Cls, a_mf_dsig(x, a1, c1, a2, c2);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_psig(JNIEnv *Env, jclass Cls, jdouble x, jdouble a1, jdouble c1, jdouble a2, jdouble c2)
{
    return (void)Env, (void)Cls, a_mf_psig(x, a1, c1, a2, c2);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_trap(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b, jdouble c, jdouble d)
{
    return (void)Env, (void)Cls, a_mf_trap(x, a, b, c, d);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_tri(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b, jdouble c)
{
    return (void)Env, (void)Cls, a_mf_tri(x, a, b, c);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_lins(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b)
{
    return (void)Env, (void)Cls, a_mf_lins(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_linz(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b)
{
    return (void)Env, (void)Cls, a_mf_linz(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_s(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b)
{
    return (void)Env, (void)Cls, a_mf_s(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_z(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b)
{
    return (void)Env, (void)Cls, a_mf_z(x, a, b);
}

JNIEXPORT jdouble JNICALL Java_liba_mf_pi(JNIEnv *Env, jclass Cls, jdouble x, jdouble a, jdouble b, jdouble c, jdouble d)
{
    return (void)Env, (void)Cls, a_mf_pi(x, a, b, c, d);
}
