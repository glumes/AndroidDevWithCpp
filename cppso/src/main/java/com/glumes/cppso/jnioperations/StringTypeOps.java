package com.glumes.cppso.jnioperations;

import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class StringTypeOps extends BaseOperation {


    @Override
    public void invoke() {

        String str = "hello";

        print(
                getAndReleaseString(str),

                reverseString(str),

                getHalfString(str)

        );

    }


    // Java 和 Native 字符串的相互转化
    private native String getAndReleaseString(String str);


    // 反转字符串操作
    private native String reverseString(String str);

    // 获得字符串一半内容
    private native String getHalfString(String str);

}
