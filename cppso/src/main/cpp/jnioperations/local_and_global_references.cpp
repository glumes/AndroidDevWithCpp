//
// Created by glumes on 2018/5/4.
//

#include <jni.h>
#include <logutil.h>


/**
 * 使用局部引用来缓存static的变量，会导致出现野指针的情况
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_jnioperations_LocalAndGlobalReferenceOps_errorCacheUseLocalReference(
        JNIEnv *env, jobject instance) {
    static jmethodID mid = NULL;
    static jclass cls;

    // 局部引用不能使用 static 来缓存，否则函数退出后，自动释放，成为野指针，程序 Crash
    if (cls == NULL) {
        cls = env->FindClass("java/lang/String");
        if (cls == NULL) {
            return NULL;
        }
    } else {
        LOGD("cls is not null but program will crash");
    }

    if (mid == NULL) {
        mid = env->GetMethodID(cls, "<init>", "([C)V");
        if (mid == NULL) {
            return NULL;
        }
    }

    jcharArray charEleArr = env->NewCharArray(10);

    const jchar *j_char = env->GetStringChars(env->NewStringUTF("LocalReference"), NULL);

    env->SetCharArrayRegion(charEleArr, 0, 10, j_char);

    jstring result = (jstring) env->NewObject(cls, mid, charEleArr);

    env->DeleteLocalRef(charEleArr);

    return result;

}

/**
 * 使用全局引用来缓存 static 的变量
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_jnioperations_LocalAndGlobalReferenceOps_cacheWithGlobalReference(JNIEnv *env,
                                                                                        jobject instance) {
    static jclass stringClass = NULL;
    if (stringClass == NULL) {
        jclass localRefs = env->FindClass("java/lang/String");
        if (localRefs == NULL) {
            return NULL;
        }
        stringClass = (jclass) env->NewGlobalRef(localRefs);
        env->DeleteLocalRef(localRefs);
        if (stringClass == NULL) {
            return NULL;
        }
    } else {
        LOGD("use stringClass cached");
    }

    static jmethodID stringMid = NULL;
    if (stringMid == NULL) {
        stringMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
        if (stringMid == NULL) {
            return NULL;
        }
    } else {
        LOGD("use method cached");
    }

    jstring str = env->NewStringUTF("string");
    return (jstring) env->NewObject(stringClass, stringMid, str);
}


/**
 * 弱全局引用的使用，要防止弱全局引用在使用时被 GC 回收了
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_LocalAndGlobalReferenceOps_useWeakGlobalReference(JNIEnv *env,
                                                                                      jobject instance) {

    static jclass stringClass = NULL;
    if (stringClass == NULL) {
        jclass localRefs = env->FindClass("java/lang/String");
        if (localRefs == NULL) {
            return;
        }
        stringClass = (jclass) env->NewWeakGlobalRef(localRefs);
        if (stringClass == NULL) {
            return;
        }
    }
    static jmethodID stringMid = NULL;
    if (stringMid == NULL) {
        stringMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
        if (stringMid == NULL) {
            return;
        }
    }

    jboolean isGC = env->IsSameObject(stringClass, NULL);
    if (isGC) {
        LOGD("weak reference has been gc");
    } else {
        jstring str = (jstring) env->NewObject(stringClass, stringMid,
                                               env->NewStringUTF("jstring"));
        LOGD("str is %s", env->GetStringUTFChars(str, NULL));
    }
}


/**
 * 使用 局部引用管理的一系列函数
 * 注释掉是因为暂时不能运行，未完善代码细节
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_LocalAndGlobalReferenceOps_useLocalReferenceManageFuntions(
        JNIEnv *env, jobject instance) {

    int len = 20;
    // Use EnsureLocalCapacity
//    if (env->EnsureLocalCapacity(len) < 0) {
//        // 创建失败，out of memory
//    }
//
//    for (int i = 0; i < len; ++i) {
//        jstring jstr = env->GetObjectArrayElement(arr, i);
//        // 处理 字符串
//        // 创建了足够多的局部引用，这里就不用删除了，显然占用更多的内存
//    }

    // Use PushLocalFrame & PopLocalFrame
//    for (int i = 0; i < len; ++i) {
//        if (env->PushLocalFrame(len)) { // 创建指定数据的局部引用空间
//            //out ot memory
//        }
//        jstring jstr = env->GetObjectArrayElement(arr, i);
//        // 处理字符串
//        env->PopLocalFrame(NULL); // 直接释放这个空间内的所有局部引用
//    }

}