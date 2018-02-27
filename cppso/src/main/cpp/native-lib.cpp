#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "NativeCodec-looper"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_androidcppsolib_MainActivity_outputString(JNIEnv *env, jobject instance,
                                                          jstring msg_) {
    const char *msg = env->GetStringUTFChars(msg_, 0);

    env->ReleaseStringUTFChars(msg_, msg);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_androidcppsolib_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_androidcppsolib_nativefactory_NativeEngine_pringlog(JNIEnv *env, jclass type) {

    // TODO
    LOGD("print log");
}