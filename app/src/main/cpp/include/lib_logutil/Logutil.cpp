//
// Created by glumes on 2017/5/26.
//

#include "Logutil.h"
#include <iostream>
#include <android/log.h>

using namespace std;

void Logutil::LogI(const char *tag) {
    __android_log_print(ANDROID_LOG_ERROR, tag, "foramt");
}
