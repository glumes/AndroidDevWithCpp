//
// Created by glumes on 2018/4/22.
//

#include <jni.h>
#include <string>


#include <logutil.h>



/**
 * Java 传递 字符串到 Native，然后再从 Native 返回 字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_jnioperations_StringTypeOps_getAndReleaseString(JNIEnv *env, jobject instance,
                                                                      jstring str_) {
    // Java 的字符串并不能直接转成 C/C++ 风格的字符串
    // 需要用到 GetStringChars 或者 GetStringUTFChars 相应的函数来申请内存
    // 转成一个指向 JVM 地址的指针
    // 最后还要释放该指针的内存
    const char *str = env->GetStringUTFChars(str_, 0);
    // GetStringUTFChars 涉及到申请内存，最好做个检查，防止 OOM
    // Get 和 Release 要配套使用，避免内存泄漏
    env->ReleaseStringUTFChars(str_, str);

    // 从 Native 返回字符串，将 C/C++ 风格的字符串返回到 Java 层
    // 也需要用到特定的函数来转换 NewStringUTF 或者 NewString 等
    const char *c_str = "this is C style string";


//    env->GetStringRegion()

    return env->NewStringUTF(c_str);

}

/**
 * 反转字符串操作
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_jnioperations_StringTypeOps_reverseString(JNIEnv *env, jobject instance,
                                                                jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);

    int length = env->GetStringLength(str_);

    char reverseString[length];

    for (int i = 0; i < length; ++i) {
        reverseString[i] = str[length - 1 - i];
    }

    env->ReleaseStringUTFChars(str_, str);

    // 此处的使用会引起崩溃,传入的字符串是 hello str 时
    return env->NewStringUTF(reverseString);
}


/**
 * 得到字符串一半内容，使用 GetStringRegion 方法
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_glumes_cppso_jnioperations_StringTypeOps_getHalfString(JNIEnv *env, jobject instance,
                                                                jstring str_) {
    int len = env->GetStringLength(str_);

    jchar outputBuf[len / 2];

    // 截取一部分内容放到缓冲区里面去
    env->GetStringRegion(str_, 0, len / 2, outputBuf);

    // 再从缓冲区中得到 Java 字符串
    jstring ret = env->NewString(outputBuf, len / 2);

    return ret;
}