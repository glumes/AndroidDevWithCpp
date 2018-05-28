package com.glumes.cppso.jnioperations;

/**
 * Created by glumes on 28/05/2018
 */
public class ThreadOps extends BaseOperation {

    @Override
    public void invoke() {

    }

    private native void nativeInit();

    private native void nativeFree();

    private native void nativeWorker();

    private native void posixThreads(int threads, int iterations);
}
