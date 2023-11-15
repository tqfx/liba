#include "a.h"
#include "a/mf.h"
#include "liba_mf.h"

JNIEXPORT void JNICALL JPACKAGE(mf_INIT)(JNIEnv *jenv, jclass jcls)
{
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "NUL", "I"), A_MF_NUL);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "GAUSS", "I"), A_MF_GAUSS);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "GBELL", "I"), A_MF_GBELL);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "SIG", "I"), A_MF_SIG);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "TRAP", "I"), A_MF_TRAP);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "TRI", "I"), A_MF_TRI);
    (*jenv)->SetStaticIntField(jenv, jcls, (*jenv)->GetStaticFieldID(jenv, jcls, "Z", "I"), A_MF_Z);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_gauss)(JNIEnv *jenv, jclass jcls, jdouble jx, jdouble jsigma, jdouble jc)
{
    return (void)(jenv), (void)(jcls), a_mf_gauss(jx, jsigma, jc);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_gbell)(JNIEnv *jenv, jclass jcls, jdouble jx, jdouble ja, jdouble jb, jdouble jc)
{
    return (void)(jenv), (void)(jcls), a_mf_gbell(jx, ja, jb, jc);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_sig)(JNIEnv *jenv, jclass jcls, jdouble jx, jdouble ja, jdouble jc)
{
    return (void)(jenv), (void)(jcls), a_mf_sig(jx, ja, jc);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_trap)(JNIEnv *jenv, jclass jcls, jdouble jx, jdouble ja, jdouble jb, jdouble jc, jdouble jd)
{
    return (void)(jenv), (void)(jcls), a_mf_trap(jx, ja, jb, jc, jd);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_tri)(JNIEnv *jenv, jclass jcls, jdouble jx, jdouble ja, jdouble jb, jdouble jc)
{
    return (void)(jenv), (void)(jcls), a_mf_tri(jx, ja, jb, jc);
}

JNIEXPORT jdouble JNICALL JPACKAGE(mf_z)(JNIEnv *jenv, jclass jcls, jdouble jx, jdouble ja, jdouble jb)
{
    return (void)(jenv), (void)(jcls), a_mf_z(jx, ja, jb);
}
