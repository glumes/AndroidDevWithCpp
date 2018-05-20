package com.glumes.cppso.infomanager;

/**
 * @Author glumes
 */
public class StudentInfoLoader {

    static {
        System.loadLibrary("info-manger");
    }

    public static native void loadData();

}
