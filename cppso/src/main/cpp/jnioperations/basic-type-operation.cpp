//
// Created by glumes on 2018/4/22.
//

#include <jni.h>
#include <string>


#include <logutil.h>


// 八种基本数据类型 从 Java 到 JNI 的类型转换操作

// JNI 的基础数据类型在 Java 的基础类型上加了一个 j
// 查看源码，JNI 的基础数据类型就是在 C/C++ 基础之上，通过 typedef 声明的别名

///* Primitive types that match up with Java equivalents. */
//typedef uint8_t  jboolean; /* unsigned 8 bits */
//typedef int8_t   jbyte;    /* signed 8 bits */
//typedef uint16_t jchar;    /* unsigned 16 bits */
//typedef int16_t  jshort;   /* signed 16 bits */
//typedef int32_t  jint;     /* signed 32 bits */
//typedef int64_t  jlong;    /* signed 64 bits */
//typedef float    jfloat;   /* 32-bit IEEE 754 */
//typedef double   jdouble;  /* 64-bit IEEE 754 */



extern "C"
JNIEXPORT jint JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeInt(JNIEnv *env, jobject instance,
                                                               jint num) {

    LOGD("java int value is %d", num);
    int c_num = num * 2;
    return c_num;
}


extern "C"
JNIEXPORT jbyte JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeByte(JNIEnv *env, jobject instance,
                                                                jbyte b) {

    LOGD("java byte value is %d", b);
    jbyte c_byte = b + (jbyte) 10;
    return c_byte;
}


extern "C"
JNIEXPORT jchar JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeChar(JNIEnv *env, jobject instance,
                                                                jchar ch) {

    LOGD("java char value is %c", ch);
    jchar c_char = ch + (jchar) 3;
    return c_char;
}


extern "C"
JNIEXPORT jshort JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeShort(JNIEnv *env, jobject instance,
                                                                 jshort sh) {

    LOGD("java char value is %d", sh);
    jshort c_short = sh + (jshort) 10;
    return c_short;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeLong(JNIEnv *env, jobject instance,
                                                                jlong l) {

    LOGD("java long value is %d", l);
    jlong c_long = l + 100;
    return c_long;
}



extern "C"
JNIEXPORT jfloat JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeFloat(JNIEnv *env, jobject instance,
                                                                 jfloat f) {

    LOGD("java float value is %f", f);
    jfloat c_float = f + (jfloat) 10.0;
    return c_float;
}



extern "C"
JNIEXPORT jdouble JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeDouble(JNIEnv *env, jobject instance,
                                                                  jdouble d) {

    LOGD("java double value is %f", d);
    jdouble c_double = d + 20.0;
    return c_double;
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_glumes_cppso_jnioperations_BasicTypeOps_callNativeBoolean(JNIEnv *env, jobject instance,
                                                                   jboolean value) {
    LOGD("java boolean value is %d", value);
    jboolean c_bool = (jboolean) !value;
    return c_bool;
}
