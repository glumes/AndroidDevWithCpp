//
// Created by glumes on 2018/5/29.
//

#include <jni.h>

#ifndef ANDROIDCPPSOLIB_COMMONUTIL_H
#define ANDROIDCPPSOLIB_COMMONUTIL_H


static const char *IOException = "java/io/IOException";
static const char *RuntimeException = "java/io/RuntimeException";

void throwByName(JNIEnv *env, const char *name, const char *msg);

#endif //ANDROIDCPPSOLIB_COMMONUTIL_H
