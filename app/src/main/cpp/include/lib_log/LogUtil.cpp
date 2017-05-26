//
// Created by glumes on 2017/5/26.
//

#include "LogUtil.h"
#include <string>
#include <android/log.h>
#define TAG "NativeCodec-looper"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

using namespace std;

LogUtil::LogUtil() {

}

void LogUtil::test(string msg) {
    LOGD("this is content two");
}


