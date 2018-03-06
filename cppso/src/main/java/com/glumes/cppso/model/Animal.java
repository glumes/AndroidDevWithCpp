package com.glumes.cppso.model;


import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */

public class Animal {


    protected String name;


    public Animal(String name) {
        this.name = name;
        LogUtil.Companion.d("Animal Construct call...");
    }


    public String getName() {
        LogUtil.Companion.d("Animal.getName Call...");
        return this.name;
    }


    public void run() {
        LogUtil.Companion.d("this is Animal Class");
    }
}
