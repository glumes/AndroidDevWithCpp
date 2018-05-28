//
// Created by glumes on 2018/5/28.
//

#include <jni.h>
#include <logutil.h>

#include <pthread.h>

extern "C"
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_nativeInit
        (JNIEnv *, jobject) {
    LOGD("native init");
    
}


extern "C"
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_nativeFree
        (JNIEnv *, jobject) {

}

extern "C"
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_nativeWorker
        (JNIEnv *, jobject) {

}

extern "C"
JNIEXPORT void JNICALL Java_com_glumes_cppso_jnioperations_ThreadOps_posixThreads
        (JNIEnv *, jobject, jint, jint) {

}