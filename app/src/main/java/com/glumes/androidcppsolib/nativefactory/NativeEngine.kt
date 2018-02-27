package com.glumes.androidcppsolib.nativefactory

/**
 * Created by glumes on 27/02/2018
 */
class NativeEngine {

    init {
        System.loadLibrary("native-lib")
    }

    external fun intFromJnI()
}