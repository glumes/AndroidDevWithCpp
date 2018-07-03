package com.glumes.cppso.jnioperations;

import com.glumes.cppso.utils.LogUtil;

/**
 * Created by glumes on 28/05/2018
 */
public class ThreadOps extends BaseOperation {


    @Override
    public void invoke() {

        createNativeThread();
        nativeInit();
        posixThreads(3, 3);
    }

    private native void createNativeThread();

    private native void nativeInit();

    private native void nativeFree();

    private native void posixThreads(int threads, int iterations);

    /**
     * 打印线程名称，并且模拟耗时任务
     */
    private void printThreadName() {
        LogUtil.Companion.d("print thread name current thread name is " + Thread.currentThread().getName());
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    /**
     * Native 回到到 Java 的方法，打印当前线程名字
     *
     * @param msg
     */
    private void printNativeMsg(String msg) {
        LogUtil.Companion.d("native msg is " + msg);
        LogUtil.Companion.d("print native msg current thread name is " + Thread.currentThread().getName());
    }
}
