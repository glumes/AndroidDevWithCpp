//
// Created by glumes on 2018/5/30.
//

#include "AviPlayer.h"
#include <commonutil.h>
#include <android/bitmap.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <malloc.h>

struct Instance {
    char *buffer;
    GLuint texture;

    Instance() : buffer(0), texture(0) {

    }
};

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


// opengl 渲染相关
JNIEXPORT jlong JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_init(JNIEnv *env, jclass, jlong avi) {
    Instance *instance = 0;
    long frameSize = AVI_frame_size((avi_t *) avi, 0);
    if (frameSize <= 0) {
        throwByName(env, RuntimeException, "Unable to get the frame size.");
        return 0;
    }
    instance = new Instance();

    instance->buffer = (char *) malloc(frameSize);
    if (instance->buffer == 0) {
        throwByName(env, RuntimeException, "Unable to allocate buffer.");
        delete instance;
        instance = 0;
    }

    return (jlong) instance;
}

JNIEXPORT void JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_initSurface(JNIEnv *env, jclass clazz, jlong inst,
                                                      jlong avi) {
    Instance *instance = (Instance *) inst;
    glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &instance->texture);

    glBindTexture(GL_TEXTURE_2D, instance->texture);

    int frameWidth = AVI_video_width((avi_t *) avi);
    int frameHeight = AVI_video_height((avi_t *) avi);

    GLint rect[] = {0, frameHeight, frameWidth, -frameHeight};
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, rect);

    glColor4f(1.0, 1.0, 1.0, 1.0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth, frameHeight, 0, GL_RGB,
                 GL_UNSIGNED_SHORT_5_6_5, 0);

}

JNIEXPORT jboolean JNICALL
Java_com_glumes_cppso_aviplayer_AviPlayer_glRender(JNIEnv *env, jclass, jlong inst, jlong avi) {
    Instance *instance = (Instance *) inst;
    jboolean isFrameRead = JNI_FALSE;
    int keyFrame = 0;
    long frameSize = AVI_read_frame((avi_t *) avi, instance->buffer, &keyFrame);
    if (frameSize <= 0) {
        return JNI_FALSE;
    }
    isFrameRead = JNI_TRUE;
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                    AVI_video_width((avi_t *) avi),
                    AVI_video_height((avi_t *) avi),
                    GL_RGB,
                    GL_UNSIGNED_SHORT_5_6_5, instance->buffer);

//    glDrawTexiOES()
}
