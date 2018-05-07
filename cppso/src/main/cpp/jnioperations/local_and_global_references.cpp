//
// Created by glumes on 2018/5/4.
//

#include <jni.h>
#include <logutil.h>


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