package com.glumes.cppso.callback;

import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */

public class CallBackMethod {

    public static final String TAG  = "CallBackMethod";

    public static void staticMethod() {
        LogUtil.Companion.d("call back static method",TAG);
    }

    public void instanceMethod(){
        LogUtil.Companion.d("call back instance method",TAG);
    }

}
