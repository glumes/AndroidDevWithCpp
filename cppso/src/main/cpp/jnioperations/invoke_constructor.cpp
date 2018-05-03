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

    // 由 C++ 字符串创建一个 Java 字符串
    jstring temp = env->NewStringUTF("this is char array");
    // 再从 Java 字符串获得一个字符数组指针，作为 String 构造函数的参数
    const jchar *chars = env->GetStringChars(temp, NULL);
    int len = 10;

    stringClass = env->FindClass("java/lang/String"); // 找到具体的 String 类
    if (stringClass == NULL) {
        return NULL;
    }
    // 找到具体的方法，([C)V 表示选择 String 的 String(char value[]) 构造方法
    cid = env->GetMethodID(stringClass, "<init>", "([C)V");
    if (cid == NULL) {
        return NULL;
    }
    // 字符串数组作为参数
    elemArr = env->NewCharArray(len);
    if (elemArr == NULL) {
        return NULL;
    }
    // 给字符串数组赋值
    env->SetCharArrayRegion(elemArr, 0, len, chars);

    result = (jstring) env->NewObject(stringClass, cid, elemArr);

    env->DeleteLocalRef(elemArr);
    env->DeleteLocalRef(stringClass);

    return result;
}


/**
 * 创建一个 Java 的 Animal 类并返回
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_glumes_cppso_jnioperations_InvokeConstructorOps_invokeAnimalConstructors(JNIEnv *env,
                                                                                  jobject instance) {

    jclass animalClass;
    jmethodID mid;

    jobject result;
    animalClass = env->FindClass("com/glumes/cppso/model/Animal");
    if (animalClass == NULL) {
        return NULL;
    }

    mid = env->GetMethodID(animalClass, "<init>", "(Ljava/lang/String;)V");

    if (mid == NULL) {
        return NULL;
    }

    jstring args = env->NewStringUTF("this animal name");

    result = env->NewObject(animalClass, mid, args);

    env->DeleteLocalRef(animalClass);

    return result;

}