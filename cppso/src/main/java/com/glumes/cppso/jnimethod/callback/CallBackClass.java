package com.glumes.cppso.jnimethod.callback;

/**
 * @Author glumes
 */

public class CallBackClass {

    private static int num;

    private String str;

    public int getNum() {
        return num;
    }

    public void setNum(int num) {
        CallBackClass.num = num;
    }

    public String getStr() {
        return str;
    }

    public void setStr(String str) {
        this.str = str;
    }
}
