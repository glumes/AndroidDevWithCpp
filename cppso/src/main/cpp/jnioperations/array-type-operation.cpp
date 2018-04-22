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

    jobjectArray result;
    jclass intArrayCls = env->FindClass("[I");

    if (intArrayCls == NULL) {
        return NULL;
    }

    result = env->NewObjectArray(size, intArrayCls, NULL);

    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        jint tmp[256];
        jintArray iarr = env->NewIntArray(size);
        if (iarr == NULL) {
            return NULL;
        }
        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }
        env->SetIntArrayRegion(iarr, 0, size, tmp);
        env->SetObjectArrayElement(result, i, iarr);
        env->DeleteLocalRef(iarr);
    }
    return result;

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