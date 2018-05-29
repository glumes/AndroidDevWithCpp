//
// Created by glumes on 2018/5/28.
//

#include <jni.h>
#include <logutil.h>

#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

#define JAVA_CLASS "com/glumes/cppso/jnioperations/NativeOnLoadOps"

jstring getMessage(JNIEnv *env, jobject jobj) {
    return env->NewStringUTF("this is msg");
}


jint nativePlus(JNIEnv *env, jobject jobj, jint x, jint y) {
    return x + y;
}


static JNINativeMethod gMethods[] = {
        {"getMessage", "()Ljava/lang/String;", (void *) getMessage},
        {"plus",       "(II)I",                (void *) nativePlus}
};


int registerNativeMethods(JNIEnv *env, const char *clsName, JNINativeMethod *gMethods, int numMethods) {
    jclass jcls;
    jcls = env->FindClass(clsName);
    if (jcls == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(jcls, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

//
//JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
//    JNIEnv *env;
//    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
//        return JNI_ERR;
//    }
//
//    registerNativeMethods(env, JAVA_CLASS, gMethods, NELEM(gMethods));
//
//    LOGD("JNI OnLoad Call");
//
//    return JNI_VERSION_1_6;
//}

JNIEXPORT void JNI_OnUnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI OnUnLoad Call");
}

