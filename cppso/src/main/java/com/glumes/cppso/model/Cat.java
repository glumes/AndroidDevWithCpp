package com.glumes.cppso.model;

import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */

public class Cat extends Animal {

    @Override
    public void run() {
        LogUtil.Companion.d("this is Cat Animal");
    }

}
