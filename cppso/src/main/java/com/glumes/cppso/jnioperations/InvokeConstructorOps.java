package com.glumes.cppso.jnioperations;

import com.glumes.cppso.model.Animal;
import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class InvokeConstructorOps extends BaseOperation {


    @Override
    public void invoke() {

        print(
                invokeStringConstructors()

        );

        Animal animal = invokeAnimalConstructors();
        if (animal == null) {
            LogUtil.Companion.d("invoke animal constructor failed");
        } else {
            LogUtil.Companion.d("value is " + animal.getName());
        }
    }

    private native String invokeStringConstructors();

    private native Animal invokeAnimalConstructors();
}
