//
// Created by glumes on 2018/5/30.
//

#include "AviPlayer.h"
#include <commonutil.h>
#include <android/bitmap.h>

JNIEXPORT jlong JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_open(JNIEnv *env, jclass, jstring fileName) {
    avi_t *avi = 0;
    const char *filename = env->GetStringUTFChars(fileName, NULL);
    if (filename == NULL) {
        return (jlong) avi;
    }

    avi = AVI_open_input_file(filename, 1);

    env->ReleaseStringUTFChars(fileName, filename);

    if (avi == 0) {
        throwByName(env, IOException, "debug info");
    }

    return (jlong) avi;

}

JNIEXPORT jint JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_getWidth(JNIEnv *env, jclass, jlong avi) {
    return AVI_video_width((avi_t *) avi);
}

JNIEXPORT jint JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_getHeight(JNIEnv *env, jclass, jlong avi) {
    return AVI_video_height((avi_t *) avi);
}

JNIEXPORT jdouble JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_getFrameRate(JNIEnv *env, jclass, jlong avi) {
    return AVI_frame_rate((avi_t *) avi);
}

JNIEXPORT void JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_close(JNIEnv *env, jclass, jlong avi) {
    AVI_close((avi_t *) avi);
}


JNIEXPORT jboolean JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_render(JNIEnv *env, jclass jcls, jlong avi,
                                                 jobject bitmap) {
    jboolean isFrameRead = JNI_FALSE;
    char *frameBuffer = 0;
    long frameSize = 0;
    int keyFrame = 0;

    if (AndroidBitmap_lockPixels(env, bitmap, (void **) &frameBuffer) < 0) {
        throwByName(env, IOException, "Unable to lock pixels.");
        return JNI_FALSE;
    }

    frameSize = AVI_read_frame((avi_t *) avi, frameBuffer, &keyFrame);

    if (AndroidBitmap_unlockPixels(env, bitmap) < 0) {
        throwByName(env, IOException, "Unable to unlock pixels.");
    }

    if (frameSize > 0) {
        isFrameRead = JNI_TRUE;
    }

    return isFrameRead;

}
