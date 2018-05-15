//
// Created by glumes on 2018/5/14.
//

#include <jni.h>
#include <logutil.h>


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ExceptionOps_doit(JNIEnv *env, jobject instance) {


    jthrowable exc;
    jobject obj;
    jclass cls = env->FindClass("com/glumes/cppso/jnioperations/ExceptionOps");

    jmethodID initMid = env->GetMethodID(cls, "<init>", "()V");

    obj = env->NewObject(cls, initMid);

    jmethodID mid = env->GetMethodID(cls, "callback", "()V");

    if (mid == NULL) {
        return;
    }

    env->CallVoidMethod(obj, mid);

    exc = env->ExceptionOccurred();

    if (exc) {
        jclass newExcCls;
        env->ExceptionDescribe();
        env->ExceptionClear();
        newExcCls = env->FindClass("java/lang/IllegalArgumentException");
        if (newExcCls == NULL) {
            return;
        }
        env->ThrowNew(newExcCls, "Thrown from C++ code");
    }
}