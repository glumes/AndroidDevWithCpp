package com.glumes.cppso.jnioperations;

/**
 * @Author glumes
 */


/**
 * 基础数据类型的操作
 */
public class BasicTypeOps extends BaseOperation {


    @Override
    public void invoke() {

        print(
                callNativeInt(100),
                callNativeByte((byte) 68),
                callNativeChar((char) 120),
                callNativeShort((short) 100),
                callNativeLong(1000),
                callNativeFloat((float) 1.0),
                callNativeDouble(100.0),
                callNativeBoolean(true)

        );
    }

    private native int callNativeInt(int num);

    private native byte callNativeByte(byte b);

    private native char callNativeChar(char ch);

    private native short callNativeShort(short sh);

    private native long callNativeLong(long l);

    private native float callNativeFloat(float f);

    private native double callNativeDouble(double d);

    private native boolean callNativeBoolean(boolean bool);


}
