//
// Created by glumes on 2018/5/3.
//

#include <jni.h>
#include <logutil.h>

// 全局变量，作为缓存方法 id
jmethodID InstanceMethodCache;

extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_CacheFieldAndMethodOps_staticCacheField(JNIEnv *env, jobject instance, jobject animal) {
    static jfieldID fid = NULL; // 声明为 static 变量进行缓存

    // 两种方法都行
//    jclass cls = env->GetObjectClass(animal);
    jclass cls = env->FindClass("com/glumes/cppso/model/Animal");

    jstring jstr;

    const char *c_str;
    // 从缓存中查找
    if (fid == NULL) {
        fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
        if (fid == NULL) {
            return;
        }
    } else {
        LOGD("field id is cached");
    }

    jstr = (jstring) env->GetObjectField(animal, fid);
    c_str = env->GetStringUTFChars(jstr, NULL);
    if (c_str == NULL) {
        return;
    }
    env->ReleaseStringUTFChars(jstr, c_str);
    jstr = env->NewStringUTF("new name");
    if (jstr == NULL) {
        return;
    }
    env->SetObjectField(animal, fid, jstr);
}

/**
 * 初始化加载时缓存方法 id
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_CacheFieldAndMethodOps_initCacheMethodId(JNIEnv *env,
                                                                             jclass type) {
    jclass cls = env->FindClass("com/glumes/cppso/model/Animal");
    InstanceMethodCache = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
}


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_CacheFieldAndMethodOps_callCacheMethod(JNIEnv *env, jobject instance, jobject animal) {
    jstring name = (jstring) env->CallObjectMethod(animal, InstanceMethodCache);
    const char *c_name = env->GetStringUTFChars(name, NULL);
    LOGD("call cache method and value is %s", c_name);
}