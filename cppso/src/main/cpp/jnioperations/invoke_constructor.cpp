//
// Created by glumes on 2018/5/3.
//

#include <jni.h>
#include <logutil.h>


extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_jnioperations_InvokeConstructorOps_invokeStringConstructors(JNIEnv *env,
                                                                                  jobject instance) {

    jclass stringClass;
    jmethodID cid;
    jcharArray elemArr;
    jstring result;

    jstring temp = env->NewStringUTF("this is char array");

    const jchar *chars = env->GetStringChars(temp, NULL);

    int len = 10;
    stringClass = env->FindClass("java/lang/String");

    if (stringClass == NULL) {
        return NULL;
    }

    cid = env->GetMethodID(stringClass, "<init>", "([C)V");
    if (cid == NULL) {
        return NULL;
    }

    elemArr = env->NewCharArray(len);
    if (elemArr == NULL) {
        return NULL;
    }

    env->SetCharArrayRegion(elemArr, 0, len, chars);

    result = (jstring) env->NewObject(stringClass, cid, elemArr);

    env->DeleteLocalRef(elemArr);
    env->DeleteLocalRef(stringClass);

    return result;
}