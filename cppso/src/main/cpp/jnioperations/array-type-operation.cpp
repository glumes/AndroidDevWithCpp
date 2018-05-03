//
// Created by glumes on 2018/4/22.
//
#include <jni.h>
#include <logutil.h>


extern "C"
JNIEXPORT jint JNICALL
Java_com_glumes_cppso_jnioperations_ArrayTypeOps_intArraySum(JNIEnv *env, jobject instance,
                                                             jintArray intArray_, jint num) {
    jint *intArray;
    int sum = 0;

    // 操作方法一：

    // 如同 getUTFString 一样，会申请 native 内存
    intArray = env->GetIntArrayElements(intArray_, NULL);

    if (intArray == NULL) {
        return 0;
    }

    // 得到数组的长度
    int length = env->GetArrayLength(intArray_);
    LOGD("array length is %d", length);

    for (int i = 0; i < length; ++i) {
        sum += intArray[i];
    }

    LOGD("sum is %d", sum);

    // 操作方法二：

    jint buf[num];

    env->GetIntArrayRegion(intArray_, 0, num, buf);

    sum = 0;
    for (int i = 0; i < num; ++i) {
        sum += buf[i];
    }

    LOGD("sum is %d", sum);

    // 使用完了别忘了释放内存
    env->ReleaseIntArrayElements(intArray_, intArray, 0);

    return sum;
}


/**
 * 从 Native 返回 int 数组，主要调用 set<Type>ArrayRegion 来填充数据，其他数据类型类似操作
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_glumes_cppso_jnioperations_ArrayTypeOps_getIntArray(JNIEnv *env, jobject instance,
                                                             jint num) {

    jintArray intArray;
    intArray = env->NewIntArray(num);

    jint buf[num];
    for (int i = 0; i < num; ++i) {
        buf[i] = i * 2;
    }

    // 使用 setIntArrayRegion 来赋值
    env->SetIntArrayRegion(intArray, 0, num, buf);
    return intArray;
}




/**
 * 从 Native 返回一个二维的整型数组
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_glumes_cppso_jnioperations_ArrayTypeOps_getTwoDimensionalArray(JNIEnv *env,
                                                                        jobject instance,
                                                                        jint size) {
    // 声明一个对象数组
    jobjectArray result;
    // 找到对象数组中具体的对象类型
    jclass intArrayCls = env->FindClass("[I");

    if (intArrayCls == NULL) {
        return NULL;
    }
    // 相当于初始化一个对象数组，用指定的对象类型
    result = env->NewObjectArray(size, intArrayCls, NULL);

    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        // 用来给整型数组填充数据的缓冲区
        jint tmp[256];
        // 声明一个整型数组
        jintArray iarr = env->NewIntArray(size);
        if (iarr == NULL) {
            return NULL;
        }
        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }
        // 给整型数组填充数据
        env->SetIntArrayRegion(iarr, 0, size, tmp);
        // 给对象数组指定位置填充数据，这个数据就是一个一维整型数组
        env->SetObjectArrayElement(result, i, iarr);
        // 释放局部引用
        env->DeleteLocalRef(iarr);
    }
    return result;
}




/**
 * 打印对象数组中的信息
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ArrayTypeOps_printAnimalsName(JNIEnv *env, jobject instance,
                                                                  jobjectArray animals) {

    jobject animal;
    // 数组长度
    int size = env->GetArrayLength(animals);
    // 数组中对应的类
    jclass cls = env->FindClass("com/glumes/cppso/model/Animal");
    // 类对应的字段描述
    jfieldID fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    // 类的字段具体的值
    jstring jstr;
    // 类字段具体值转换成 C/C++ 字符串
    const char *str;

    for (int i = 0; i < size; ++i) {
        // 得到数组中的每一个元素
        animal = env->GetObjectArrayElement(animals, i);
        // 每一个元素具体字段的值
        jstr = (jstring) (env->GetObjectField(animal, fid));

        str = env->GetStringUTFChars(jstr, NULL);

        if (str == NULL) {
            continue;
        }
        LOGD("str is %s", str);
        env->ReleaseStringUTFChars(jstr, str);
    }
}



/**
 * 基本类型的数据传递
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_ArrayTypeOps_primitiveTypeArray(JNIEnv *env, jobject instance,
                                                                    jintArray intArray_,
                                                                    jfloatArray floatArray_,
                                                                    jdoubleArray doubleArray_,
                                                                    jshortArray shortArray_,
                                                                    jlongArray longArray_,
                                                                    jbooleanArray boolArray_,
                                                                    jcharArray charArray_,
                                                                    jbyteArray byteArray_) {
    jint *intArray = env->GetIntArrayElements(intArray_, NULL);
    jfloat *floatArray = env->GetFloatArrayElements(floatArray_, NULL);
    jdouble *doubleArray = env->GetDoubleArrayElements(doubleArray_, NULL);
    jshort *shortArray = env->GetShortArrayElements(shortArray_, NULL);
    jlong *longArray = env->GetLongArrayElements(longArray_, NULL);
    jboolean *boolArray = env->GetBooleanArrayElements(boolArray_, NULL);
    jchar *charArray = env->GetCharArrayElements(charArray_, NULL);
    jbyte *byteArray = env->GetByteArrayElements(byteArray_, NULL);



    // 基础数据类型的操作，大同小异
    // 可用函数
    // 1、Get<Type>ArrayElements / Release<Type>ArrayElements
    // 2、Get<Type>ArrayRegion / Set<Type>ArrayRegion
    // 3、GetArrayLength


    env->ReleaseIntArrayElements(intArray_, intArray, 0);
    env->ReleaseFloatArrayElements(floatArray_, floatArray, 0);
    env->ReleaseDoubleArrayElements(doubleArray_, doubleArray, 0);
    env->ReleaseShortArrayElements(shortArray_, shortArray, 0);
    env->ReleaseLongArrayElements(longArray_, longArray, 0);
    env->ReleaseBooleanArrayElements(boolArray_, boolArray, 0);
    env->ReleaseCharArrayElements(charArray_, charArray, 0);
    env->ReleaseByteArrayElements(byteArray_, byteArray, 0);
}