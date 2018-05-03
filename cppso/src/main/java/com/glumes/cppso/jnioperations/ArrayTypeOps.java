package com.glumes.cppso.jnioperations;

import com.glumes.cppso.model.Animal;
import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class ArrayTypeOps extends BaseOperation {


    @Override
    public void invoke() {

        int[] intArray = new int[]{1, 2, 3, 4, 5, 6};
        float[] floatArray = new float[]{1.0f, 2.0f, 3.0f};
        double[] doubleArray = new double[]{1.0, 2.0, 3.0};
        short[] shortArray = new short[]{1, 2, 3};
        long[] longArray = new long[]{1, 2, 3};
        boolean[] boolArray = new boolean[]{true, false, true};
        char[] charArray = new char[]{'a', 'b', 'c'};
        byte[] byteArray = new byte[]{2, 3, 4};

        primitiveTypeArray(intArray, floatArray, doubleArray, shortArray, longArray, boolArray, charArray, byteArray);


        Animal[] animals = new Animal[]{
                new Animal("cat"),
                new Animal("dog"),
                new Animal("pig"),
                new Animal("fish"),
        };

        print(
                intArraySum(intArray, 3)
        );


        for (Integer value : getIntArray(3)) {
            LogUtil.Companion.d("num is " + value);
        }

        // 对象数组的使用，相当于是一个一维数组，数组的每个内容都是一个数组
        int[][] data = getTwoDimensionalArray(3);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                LogUtil.Companion.d("data is " + data[i][j]);
            }
        }

        // 打印对象中的信息
        printAnimalsName(animals);

    }


    private native void primitiveTypeArray(int[] intArray,
                                           float[] floatArray,
                                           double[] doubleArray,
                                           short[] shortArray,
                                           long[] longArray,
                                           boolean[] boolArray,
                                           char[] charArray,
                                           byte[] byteArray);

    // Java 传递 数组 到 Native 进行数组求和
    private native int intArraySum(int[] intArray, int size);

    // 从 Native 返回基本数据类型数组
    private native int[] getIntArray(int num);

    // 从 Native 返回二维整型数组，相当于是一个一维整型数组，每个数组内容又是数组
    private native int[][] getTwoDimensionalArray(int size);

    private native void printAnimalsName(Animal[] animal);

}
