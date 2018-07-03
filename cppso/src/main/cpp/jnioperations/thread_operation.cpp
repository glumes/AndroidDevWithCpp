//
// Created by glumes on 2018/5/29.
//

#include <stdio.h>
#include "thread_operation.h"
#include <commonutil.h>

void *run(void *);

void *printThreadHello(void *);

static jmethodID printThreadName;
static jmethodID printNativeMsg;

static JavaVM *gVm = NULL;
static jobject gObj = NULL;
static pthread_mutex_t mutex;
static const char *runtimeException = "java/lang/RuntimeException";


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

//    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        throwByName(env, runtimeException, "Unable to initialize mutex");
    }
}

JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ThreadOps_nativeFree(JNIEnv *env, jobject) {
    if (gObj != NULL) {
        env->DeleteGlobalRef(gObj);
        gObj = NULL;
    }
    if (pthread_mutex_destroy(&mutex) != 0) {
        throwByName(env, runtimeException, "Unable to destroy mutex");
    }
}


JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ThreadOps_createNativeThread(JNIEnv *, jobject) {
    pthread_t handles;
    int result = pthread_create(&handles, NULL, printThreadHello, NULL);
    if (result != 0) {
        LOGD("create thread failed");
    } else {
        LOGD("create thread success");
    }
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
            throwByName(env, runtimeException, "Unable to create thread");
        }
    }

    for (int i = 0; i < num; ++i) {
        void *result = NULL;
        if (pthread_join(handles[i], &result) != 0) {
            throwByName(env, runtimeException, "Unable to join thread");
        } else {
            LOGD("return value is %d",result);
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

        if (pthread_mutex_lock(&mutex) != 0) {
            throwByName(env, runtimeException, "Unable to lock mutex");
        }

        env->CallVoidMethod(gObj, printThreadName);

        if (pthread_mutex_unlock(&mutex)) {
            throwByName(env, runtimeException, "Unable to unlock mutex");
        }
        // 从 Java 虚拟机上分离当前线程
        gVm->DetachCurrentThread();
    }
    return (void *) threadRunArgs->result;
}


void *printThreadHello(void *) {
    LOGD("hello thread");
    return NULL;
}