//
// Created by glumes on 2018/5/30.
//
#include <jni.h>

#ifndef ANDROIDCPPSOLIB_AVIPLAYER_H
#define ANDROIDCPPSOLIB_AVIPLAYER_H


#ifdef __cplusplus
extern "C" {
#endif

#include <avilib.h>
// 导入自己写的带函数声明的 头文件，要在 cpp 里面导入，.h 里面导入没效果
//#include <commonutil.h>
#include <logutil.h>
/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    open
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_open
        (JNIEnv *, jclass, jstring);

/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    getWidth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_getWidth
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    getHeight
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_getHeight
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    getFrameRate
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_getFrameRate
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_close
        (JNIEnv *, jclass, jlong);


/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    render
 * Signature: (JLandroid/graphics/Bitmap;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_render
        (JNIEnv *, jclass, jlong, jobject);


/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    init
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_init
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    initSurface
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_initSurface
        (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    glRender
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_glRender
        (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_glumes_cppso_aviplayer_AviPlayer
 * Method:    free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_glumes_cppso_aviplayer_AviPlayer_free
        (JNIEnv *, jclass, jlong);
#ifdef __cplusplus
}
#endif

#endif //ANDROIDCPPSOLIB_AVIPLAYER_H
