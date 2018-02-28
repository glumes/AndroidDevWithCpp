//
// Created by glumes on 2018/2/28.
//

#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "NativeMethod"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)


extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeString(JNIEnv *env, jclass type) {

    // env 的 newXXX 方法可以生成各种类型
    jstring nativeString = env->NewStringUTF("hello native string");
    return nativeString;
}



extern "C"
JNIEXPORT jintArray JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeIntArray(JNIEnv *env, jclass type) {


    // TODO
    jsize arraySize = 10;

    jintArray intArray = env->NewIntArray(arraySize);

    for (int i = 0; i < arraySize; i++) {
//        intArray. = 0;
    }

    return intArray;

}