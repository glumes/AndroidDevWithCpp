package com.glumes.androidcppsolib.nativefactory;

/**
 * @Author glumes
 */

public class NativeEngine {

    static {
        System.loadLibrary("cppso");
    }


    public static native void pringlog();
}
