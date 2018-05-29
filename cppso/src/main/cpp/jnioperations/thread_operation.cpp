//
// Created by glumes on 2018/5/29.
//

#include <stdio.h>
#include "thread_operation.h"

void *run(void *);

static jmethodID printThreadName;
static jmethodID printNativeMsg;

static JavaVM *gVm = NULL;
static jobject gObj = NULL;


JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    gVm = vm;

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ThreadOps_nativeInit(JNIEnv *env, jobject jobj) {
    jclass jcls = env->GetObjectClass(jobj);
    printThreadName = env->GetMethodID(jcls, "printThreadName", "()V");
    printNativeMsg = env->GetMethodID(jcls, "printNativeMsg", "(Ljava/lang/String;)V");
    if (gObj == NULL) {
        gObj = env->NewGlobalRef(jobj);
    }
}

JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ThreadOps_nativeFree(JNIEnv *env, jobject) {
    if (gObj != NULL) {
        env->DeleteGlobalRef(gObj);
        gObj = NULL;
    }
}

JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ThreadOps_nativeWorker(JNIEnv *, jobject) {

}

JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ThreadOps_posixThreads(JNIEnv *env, jobject jobj, jint num,
                                                           jint iteration) {
    pthread_t *handles = new pthread_t[num];

    for (int i = 0; i < num; ++i) {
        pthread_t pthread;

        ThreadRunArgs *threadRunArgs = new ThreadRunArgs();
        threadRunArgs->id = i;
        threadRunArgs->result = i * i;
        // 创建一个线程，
        int result = pthread_create(&handles[i], NULL, run, (void *) threadRunArgs);
        if (result != 0) {
            jclass exceptionClazz = env->FindClass("java/lang/RuntimeException");
            env->ThrowNew(exceptionClazz, "Unable to create thread");
        }
    }

    for (int i = 0; i < num; ++i) {
        void *result = NULL;
        if (pthread_join(handles[i], &result) != 0) {
            jclass exceptionClazz = env->FindClass("java/lang/RuntimeException");
            env->ThrowNew(exceptionClazz, "Unable to join thread");
        } else {
            char message[26];
            sprintf(message, "Worker %d returned %d", i, result);
            jstring msg = env->NewStringUTF(message);
            env->CallVoidMethod(gObj, printNativeMsg, msg);
            if (env->ExceptionOccurred() != NULL) {
                return;
            }
        }
    }
}


/**
 * 相当于 Thread 的 run 方法
 * @param args
 * @return
 */
void *run(void *args) {

    JNIEnv *env = NULL;
    // 将当前线程添加到 Java 虚拟机上
    ThreadRunArgs *threadRunArgs = (ThreadRunArgs *) args;

    if (gVm->AttachCurrentThread(&env, NULL) == 0) {

        env->CallVoidMethod(gObj, printThreadName);
        // 从 Java 虚拟机上分离当前线程
        gVm->DetachCurrentThread();
    }
    return (void *) threadRunArgs->result;
}
