//
// Created by glumes on 2018/5/20.
//

#include <jni.h>
#include <logutil.h>


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_androidcppsolib_activity_InfoManageActivity_loadData(JNIEnv *env,
                                                                     jobject instance) {

    jfieldID itemFid;
    jclass cls = env->GetObjectClass(instance);

    itemFid = env->GetFieldID(cls, "mItems", "Lcom/glumes/databindingadapter/Items;");

    if (itemFid == NULL) {
        return;
    }

    jobject mItems = env->GetObjectField(instance, itemFid);

    if (mItems == NULL) {
        return;
    }

    jclass itemCls = env->GetObjectClass(mItems);

    jmethodID addMid;

    addMid = env->GetMethodID(itemCls, "add", "(Ljava/lang/Object;)Z");

    if (addMid == NULL) {
        return;
    }

    jclass stuClass = env->FindClass("com/glumes/androidcppsolib/binder/Student");
    if (stuClass == NULL) {
        return;
    }

    jmethodID stuInitMid = env->GetMethodID(stuClass, "<init>",
                                            "(Ljava/lang/String;ILjava/lang/String;III)V");

    if (stuInitMid == NULL) {
        return;
    }

    jobject stu = env->NewObject(stuClass, stuInitMid, env->NewStringUTF("jni name"), 12,
                                 env->NewStringUTF("female"), 4, 123, 22);

    if (stu == NULL) {
        return;
    }

    jboolean result = env->CallBooleanMethod(mItems, addMid, stu);


    LOGD("add mid");

}


extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_androidcppsolib_activity_InfoManageActivity_minusData(JNIEnv *env,
                                                                      jobject instance) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_glumes_androidcppsolib_activity_InfoManageActivity_plusData(JNIEnv *env,
                                                                      jobject instance) {

}