#include "a.h"
#include "a/mf.h"
#include "liba_mf.h"

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
