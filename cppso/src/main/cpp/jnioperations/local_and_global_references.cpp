//
// Created by glumes on 2018/5/4.
//

#include <jni.h>
#include <logutil.h>


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