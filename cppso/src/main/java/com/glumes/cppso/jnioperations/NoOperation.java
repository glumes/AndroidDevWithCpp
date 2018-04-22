package com.glumes.cppso.jnioperations;

import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class NoOperation extends BaseOperation {

    @Override
    public void invoke() {
        LogUtil.Companion.d("invoke no operation");
    }
}
