package com.glumes.cppso.jnioperations;

import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class ExceptionOps extends BaseOperation {

    @Override
    public void invoke() {
        try {
            doit();
        } catch (Exception e) {
            LogUtil.Companion.d("In Java: " + e.getMessage());
        }
    }

    private native void doit() throws IllegalArgumentException;

    private void callback() throws NullPointerException {
        throw new NullPointerException("CatchThrow.callback");
    }
}
