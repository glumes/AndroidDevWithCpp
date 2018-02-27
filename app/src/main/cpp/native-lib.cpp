#include <jni.h>
#include <string>
#include <lib_log/LogUtil.h>


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
