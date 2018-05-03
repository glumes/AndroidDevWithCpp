//
// Created by glumes on 2018/4/26.
//

#include <jni.h>
#include <logutil.h>

// 访问类的实例的字段
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_FieldAndMethodOps_accessInstanceFiled(JNIEnv *env,
                                                                          jobject instance,
                                                                          jobject animal) {

    jfieldID fid;
    jstring jstr;
    const char *str;

    jclass cls = env->GetObjectClass(animal);

    fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");

    if (fid == NULL) {
        return;
    }

    jstr = (jstring) env->GetObjectField(animal, fid);

    str = env->GetStringUTFChars(jstr, NULL);

    if (str == NULL) {
        return;
    }

    LOGD("name is %s", str);

    env->ReleaseStringUTFChars(jstr, str);

    jstr = env->NewStringUTF("replaced name");

    if (jstr == NULL) {
        return;
    }

    env->SetObjectField(animal, fid, jstr);

}


// 访问类的静态字段
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_FieldAndMethodOps_accessStaticField(JNIEnv *env,
                                                                        jobject instance,
                                                                        jobject animal) {

    jfieldID fid;
    jint num;

    jclass cls = env->GetObjectClass(animal);

    fid = env->GetStaticFieldID(cls, "num", "I");

    if (fid == NULL) {
        return;
    }

    num = env->GetStaticIntField(cls, fid);

    LOGD("get static field num is %d", num);

    env->SetStaticIntField(cls, fid, ++num);


}


// Native 访问 Java 的类实例方法
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_FieldAndMethodOps_callInstanceMethod(JNIEnv *env,
                                                                         jobject instance,
                                                                         jobject animal) {

    jclass cls = env->GetObjectClass(animal);

    jmethodID mid = env->GetMethodID(cls, "callInstanceMethod", "(I)V");

    if (mid == NULL) {
        return;
    }

    env->CallVoidMethod(animal, mid, 2);

}


// Native 访问 Java 的静态方法
extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_cppso_jnioperations_FieldAndMethodOps_callStaticMethod(JNIEnv *env,
                                                                       jobject instance,
                                                                       jobject animal) {
    jclass cls = env->GetObjectClass(animal);

    jmethodID argsmid = env->GetStaticMethodID(cls, "callStaticMethod",
                                               "(Ljava/lang/String;)Ljava/lang/String;");

    if (argsmid == NULL) {
        return;
    }

    jstring jstr = env->NewStringUTF("jstring");

    env->CallStaticObjectMethod(cls, argsmid, jstr);

    // ----

    argsmid = env->GetStaticMethodID(cls, "callStaticMethod",
                                     "([Ljava/lang/String;I)Ljava/lang/String;");

    if (argsmid == NULL) {
        return;
    }

    jobjectArray objArray;

    jclass objclass = env->FindClass("java/lang/String");

    if (objclass == NULL) {
        return;
    }

    int size = 3;
    objArray = env->NewObjectArray(size, objclass, NULL);

    if (objArray == NULL) {
        return;
    }

    jstring strElement;

    for (int i = 0; i < size; ++i) {

        strElement = env->NewStringUTF("str in c");

        env->SetObjectArrayElement(objArray, i, strElement);
    }

    env->CallStaticObjectMethod(cls, argsmid, objArray, 3);

}
