//
// Created by glumes on 2018/3/7.
//

#include <jni.h>
#include <string>

#include "logutil.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_cache_AccessCache_accessField(JNIEnv *env, jobject instance) {

    LOGD("access field");
    static jfieldID fid_str = NULL;
    jclass cls_AccessCache;
    jstring j_str;
    const char *c_str;
    cls_AccessCache = env->GetObjectClass(instance);

    if (cls_AccessCache == NULL) {
        return;
    }

    if (fid_str == NULL) {
        fid_str = env->GetFieldID(cls_AccessCache, "str", "Ljava/lang/String;");
        if (fid_str == NULL) {
            return;
        }
    }

    j_str = (jstring) env->GetObjectField(instance, fid_str);
    c_str = env->GetStringUTFChars(j_str, NULL);

    if (c_str == NULL){
        return;
    }

    LOGD("In C:\n str = \"%s\"\n", c_str);

    env->ReleaseStringUTFChars(j_str,c_str);

    j_str = env->NewStringUTF("12345");

    if (j_str == NULL){
        return;
    }

    env->SetObjectField(instance,fid_str,j_str);

    env->DeleteLocalRef(cls_AccessCache);
    env->DeleteLocalRef(j_str);

}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_cache_AccessCache_newString(JNIEnv *env, jobject instance, jcharArray chars_,
                                                  jint len) {

    jcharArray  elemArray;
    jchar  *chars = NULL;
    jstring j_str = NULL;
    static jclass  cls_string = NULL;
    static jmethodID cid_string = NULL;

    if (cls_string == NULL){
        cls_string = env->FindClass("java/lang/String");
        if (cls_string == NULL){
            return NULL;
        }
    }

    if (cid_string == NULL){
        cid_string = env -> GetMethodID(cls_string,"<init>","([C)V");
        if (cid_string == NULL){
            return NULL;
        }
    }

    LOGD("In C array Len: %d\n", len);

    elemArray = env->NewCharArray(len);

    if (elemArray == NULL){
        return NULL;
    }

    chars = env->GetCharArrayElements(chars_,NULL);

    if (chars == NULL){
        return NULL;
    }

    env->SetCharArrayRegion(elemArray,0,len,chars);

    j_str = (jstring) env->NewObject(cls_string, cid_string, elemArray);

    env->DeleteLocalRef(elemArray);

    return j_str;
}
