//
// Created by glumes on 2018/3/7.
//

#include <android/log.h>

#ifndef ANDROIDCPPSOLIB_LOGUTIL_H
#define ANDROIDCPPSOLIB_LOGUTIL_H


#define LOG_TAG "NativeMethod"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)




#endif //ANDROIDCPPSOLIB_LOGUTIL_H
