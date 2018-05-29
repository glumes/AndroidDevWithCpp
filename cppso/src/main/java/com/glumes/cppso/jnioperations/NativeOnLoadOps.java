package com.glumes.cppso.jnioperations;

import com.glumes.cppso.utils.LogUtil;

/**
 * Created by glumes on 28/05/2018
 */
public class NativeOnLoadOps extends BaseOperation {


    @Override
    public void invoke() {
        //
//        LogUtil.Companion.d("msg is " + getMessage());
//        LogUtil.Companion.d("plus result is " + plus(3, 0));
    }


    private native String getMessage();

    private native int plus(int x, int y);

}
