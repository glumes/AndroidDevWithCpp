package com.glumes.cppso.jnioperations;

import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
abstract public class BaseOperation {

    static {
        System.loadLibrary("native-operation");
    }

    public abstract void invoke();

    public void print(Object... args) {
        if (args.length == 0) {
            return;
        }

        for (Object arg : args) {
            LogUtil.Companion.d("Java value is " + arg.toString() + "\n");
        }
    }
}
