package com.glumes.cppso;

import com.glumes.cppso.jnimethod.callback.CallBackClass;

import org.jetbrains.annotations.NotNull;

/**
 * Created by glumes on 28/02/2018
 */

public class SampleNativeMethod {

    static {
        System.loadLibrary("native-operation");
    }

    public static native String NativeString();

    public static native int[] NativeIntArray();


    public static native void NativeCallStaticMethod();

    public static native void NativeCallInstanceMethod(@NotNull CallBackClass callback);

    public static native void NativeCallSuperMethod();

    public static native int[][] NativeArray();

    public native void NativeTest();

}
