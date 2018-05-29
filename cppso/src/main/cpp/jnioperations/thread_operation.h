//
// Created by glumes on 2018/5/29.
//
#include <jni.h>
#include <logutil.h>
#include <pthread.h>

#ifndef ANDROIDCPPSOLIB_THREAD_OPERATION_H
#define ANDROIDCPPSOLIB_THREAD_OPERATION_H


struct ThreadRunArgs {
    jint id;
    jint result;
};


#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_glumes_cppso_jnioperations_ThreadOps
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_nativeInit
        (JNIEnv *, jobject);

/*
 * Class:     com_glumes_cppso_jnioperations_ThreadOps
 * Method:    nativeFree
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_nativeFree
        (JNIEnv *, jobject);

/*
 * Class:     com_glumes_cppso_jnioperations_ThreadOps
 * Method:    nativeWorker
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_nativeWorker
        (JNIEnv *, jobject);

/*
 * Class:     com_glumes_cppso_jnioperations_ThreadOps
 * Method:    posixThreads
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_posixThreads
        (JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif //ANDROIDCPPSOLIB_THREAD_OPERATION_H
