//
// Created by glumes on 2018/5/14.
//

#include <jni.h>
#include <logutil.h>
#include <commonutil.h>


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



extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ExceptionOps_nativeThrowException(JNIEnv *env, jobject instance) {
    throwByName(env, "java/lang/IllegalArgumentException", "native throw exception");
}


/**
 * Native 代码调用 Java 的函数，引发了异常
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ExceptionOps_nativeInvokeJavaException(JNIEnv *env,
                                                                           jobject instance) {

    jclass cls = env->FindClass("com/glumes/cppso/jnioperations/ExceptionOps");
    jmethodID mid = env->GetMethodID(cls, "<init>", "()V");
    jobject obj = env->NewObject(cls, mid);


    mid = env->GetMethodID(cls, "operation", "()I");

    env->CallIntMethod(obj, mid);

    //检查是否发生了异常
    jthrowable exc = env->ExceptionOccurred();
//    jboolean result = env->ExceptionCheck();

    if (exc) {
        // 打印日志
        env->ExceptionDescribe();
        // 这代码才是关键不让应用崩溃的代码
        env->ExceptionClear();
        // 发生异常了要记得释放资源
        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(obj);
    }
}
