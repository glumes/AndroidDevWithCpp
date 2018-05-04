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


/**
 * 通过 AllocObject 方法来创建一个类
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_glumes_cppso_jnioperations_InvokeConstructorOps_allocObjectConstructor(JNIEnv *env,
                                                                                jobject instance) {
    jclass animalClass;
    jobject result;
    jmethodID mid;
    // 获得对应的 列
    animalClass = env->FindClass("com/glumes/cppso/model/Animal");
    if (animalClass == NULL) {
        return NULL;
    }
    // 获得构造方法 id
    mid = env->GetMethodID(animalClass, "<init>", "(Ljava/lang/String;)V");
    if (mid == NULL) {
        return NULL;
    }
    // 构造方法的参数
    jstring args = env->NewStringUTF("use AllocObject");
    // 创建对象，此时创建的对象未初始化的对象
    result = env->AllocObject(animalClass);
    if (result == NULL) {
        return NULL;
    }
    // 调用 CallNonvirtualVoidMethod 方法去调用类的构造方法
    env->CallNonvirtualVoidMethod(result, animalClass, mid, args);
    if (env->ExceptionCheck()) {
        env->DeleteLocalRef(result);
        return NULL;
    }
    return result;
}


/**
 * 调用父类的方法
 * 创建一个子类，由子类去调用父类的方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_InvokeConstructorOps_callSuperMethod(JNIEnv *env, jobject instance) {

    jclass cat_cls; // Cat 类的类型
    jmethodID cat_cid; // Cat 类的构造方法 id
    jstring cat_name; // Cat 类的构造方法参数
    jobject cat;
    // 获得对应的 类
    cat_cls = env->FindClass("com/glumes/cppso/model/Cat");
    if (cat_cls == NULL) {
        return;
    }
    // 获得构造方法 id
    cat_cid = env->GetMethodID(cat_cls, "<init>", "(Ljava/lang/String;)V");
    if (cat_cid == NULL) {
        return;
    }
    // 准备构造方法的参数
    cat_name = env->NewStringUTF("this is cat name");
    // 创建 Cat 类
    cat = env->NewObject(cat_cls, cat_cid, cat_name);
    if (cat == NULL) {
        return;
    }

    //调用父类的 getName 参数
    jclass animal_cls; // 父类的类型
    jmethodID animal_mid; // 被调用的父类的方法 id
    // 获得父类对应的类
    animal_cls = env->FindClass("com/glumes/cppso/model/Animal");
    if (animal_cls == NULL) {
        return;
    }
    // 获得父类被调用的方法 id
    animal_mid = env->GetMethodID(animal_cls, "getName", "()Ljava/lang/String;");
    if (animal_mid == NULL) {
        return;
    }

    jstring name = (jstring) env->CallNonvirtualObjectMethod(cat, animal_cls, animal_mid);

    if (name == NULL) {
        return;
    }

    LOGD("getName method value is %s", env->GetStringUTFChars(name, NULL));

    // 调用父类的其他方法
    animal_mid = env->GetMethodID(animal_cls, "callInstanceMethod", "(I)V");
    if (animal_mid == NULL) {
        return;
    }
    env->CallNonvirtualVoidMethod(cat, animal_cls, animal_mid);

}