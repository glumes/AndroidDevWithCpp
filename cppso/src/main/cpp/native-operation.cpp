//
// Created by glumes on 2018/2/28.
//

#include <jni.h>
#include <string>

//#define TAG "NativeMethod"
//
//#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

#include "common/logutil.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeString(JNIEnv *env, jclass type) {

    // env 的 newXXX 方法可以生成各种类型
    jstring nativeString = env->NewStringUTF("hello native string");
    return nativeString;
}



extern "C"
JNIEXPORT jintArray JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeIntArray(JNIEnv *env, jclass type) {


    // TODO
    jsize arraySize = 10;

    jintArray intArray = env->NewIntArray(arraySize);

    for (int i = 0; i < arraySize; i++) {
//        intArray. = 0;
    }
    return intArray;

}


/**
 * 从 Native 层修改 Java Static 变量
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeCallStaticMethod(JNIEnv *env, jclass type) {

    // TODO
    jclass clazz;
    jfieldID fid;
    jint num;

    // 获得 JVM 中类的引用
    clazz = env->FindClass("com/glumes/cppso/callback/CallBackClass");
    if (clazz == NULL) {
        LOGD("can not find CallBackClass");
        return;
    }

    // 获得静态变量的属性 ID
    fid = env->GetStaticFieldID(clazz, "num", "I");
    if (fid == NULL) {
        LOGD("can not find field id");
        return;
    }

    // 获取静态变量 num 的值
    num = env->GetStaticIntField(clazz, fid);
    LOGD("CallBackClass int field value is %d", num);

    // 修改静态变量的值
    env->SetStaticIntField(clazz, fid, 88);

    // 删除属性引用
    env->DeleteLocalRef(clazz);
}




/**
 * 从 Native 层修改 Java 实例对象的属性值
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeCallInstanceMethod(JNIEnv *env, jclass type,
                                                                  jobject callback) {

    // TODO
    jclass clazz;
    jfieldID fid;
    jstring j_str;
    jstring j_newStr;
    const char *c_str = NULL;

    // 获得 JVM 中类的引用
    clazz = env->GetObjectClass(callback);

    if (clazz == NULL) {
        return;
    }

    // 获得类 的实例变量的属性 的引用 ID
    fid = env->GetFieldID(clazz, "str", "Ljava/lang/String;");
    if (fid == NULL) {
        return;
    }

    // 获得实例变量的值，转换为 jstring 类型
    j_str = (jstring) env->GetObjectField(callback, fid);


    // 将 unicode 编码的 java 字符串转换成 C 风格字符串
    c_str = env->GetStringUTFChars(j_str, NULL);

    if (c_str == NULL) {
        return;
    }

    env->ReleaseStringUTFChars(j_str, c_str);

    // 修改实例变量的值
    j_newStr = env->NewStringUTF("this is new string");

    if (j_newStr == NULL) {
        return;
    }

    env->SetObjectField(callback, fid, j_newStr);

    // 删除局部引用
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(j_str);
    env->DeleteLocalRef(j_newStr);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_SampleNativeMethod_NativeCallSuperMethod(JNIEnv *env, jclass type) {

    // TODO

    LOGD("Call super method");
    jclass cls_cat;
    jclass cls_animal;
    jmethodID mid_cat_init;
    jmethodID mid_run;
    jmethodID mid_getName;
    jstring c_str_name;
    jobject obj_cat;
    const char *name = NULL;

    // 获得 Cat 类的 class 引用
    cls_cat = env->FindClass("com/glumes/cppso/model/Cat");
    if (cls_cat == NULL) {
        return;
    }

    mid_cat_init = env->GetMethodID(cls_cat, "<init>", "(Ljava/lang/String;)V");

    if (mid_cat_init == NULL) {
        return;
    }

    c_str_name = env->NewStringUTF("cat");

    if (c_str_name == NULL) {
        return;
    }

    obj_cat = env->NewObject(cls_cat, mid_cat_init, c_str_name);
    if (obj_cat == NULL) {
        return;
    }


    cls_animal = env->FindClass("com/glumes/cppso/model/Animal");

    if (cls_animal == NULL) {
        return;
    }

    mid_run = env->GetMethodID(cls_animal, "run", "()V");

    if (mid_run == NULL) {
        return;
    }

    env->CallNonvirtualVoidMethod(obj_cat, cls_animal, mid_run);

    mid_getName = env->GetMethodID(cls_animal, "getName", "()Ljava/lang/String;");

    if (mid_getName == NULL) {
        return;
    }

    c_str_name = (jstring) env->CallNonvirtualObjectMethod(obj_cat, cls_animal, mid_getName);

    name = env->GetStringUTFChars(c_str_name, NULL);

    LOGD("In Cpp:Animal Name is %s\n", name);

    env->ReleaseStringUTFChars(c_str_name, name);
    env->DeleteLocalRef(cls_cat);
    env->DeleteLocalRef(cls_animal);
    env->DeleteLocalRef(obj_cat);

}


//extern "C"
//JNIEXPORT void JNICALL
//Java_com_glumes_cppso_SampleNativeMethod_NativeTest(JNIEnv *env, jobject instance) {
//
//    // TODO
//
//}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_SampleNativeMethod_getNativeString(JNIEnv *env, jclass type, jstring str_) {

    // 生成 jstring 类型的字符串
    jstring returnValue = env->NewStringUTF("hello native string");
    // 将 jstring 类型的字符串转换为 C 风格的字符串，会额外申请内存
    const char *str = env->GetStringUTFChars(str_, 0);
//    const char *strUnicode = env->GetStringChars()
    // 释放掉申请的 C 风格字符串的内存
    env->ReleaseStringUTFChars(str_, str);
    // 返回 jstring 类型字符串

    // 申请分配内存空间，jstring 转换为 C 风格字符串
    const char *utfStr = env->GetStringUTFChars(str_, NULL);
    // 做检查判断
    if (utfStr == NULL) {
        return NULL;
    }
    // 实际操作
    printf("%s", utfStr);
    // 操作结束后，释放内存
    env->ReleaseStringUTFChars(str_, utfStr);



//    env->GetStringUTFLength()

    jchar outbuf[128], inbuf[128];

    int len = env->GetStringLength(str_);

    env->GetStringRegion(str_, 0, len, outbuf);


    const jchar *c_str = NULL;
    c_str = env->GetStringCritical(str_, NULL);

    if (c_str == NULL) {
        // error handle
    }

    env->ReleaseStringCritical(str_, c_str);

    LOGD("%s", outbuf);


    return returnValue;
}

