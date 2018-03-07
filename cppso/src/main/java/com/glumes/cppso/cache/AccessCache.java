package com.glumes.cppso.cache;

/**
 * @Author glumes
 */

public class AccessCache {

    static {
        System.loadLibrary("native-operation");
    }

    private String str = "Cache";

    public native void accessField();

    public native String newString(char[] chars,int len);


}
