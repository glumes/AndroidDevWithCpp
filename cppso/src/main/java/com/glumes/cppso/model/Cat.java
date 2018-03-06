package com.glumes.cppso.model;

import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */

public class Cat extends Animal {


    public Cat(String name) {
        super(name);
        LogUtil.Companion.d("Cat Construct call....");
    }

    @Override
    public String getName() {
        return "My name is " + this.name;
    }

    @Override
    public void run() {
        LogUtil.Companion.d(name + " Cat.run...");
    }

}
