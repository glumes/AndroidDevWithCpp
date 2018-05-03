package com.glumes.cppso.jnioperations;

import com.glumes.cppso.model.Animal;
import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class FieldAndMethodOps extends BaseOperation {


    @Override
    public void invoke() {
        Animal animal = new Animal("cat");

        // 访问实例的字段
        accessInstanceFiled(animal);

        LogUtil.Companion.d("after access instance field,the name is " + animal.getName());
        // 访问静态类的字段
        accessStaticField(animal);

        LogUtil.Companion.d("after access static field,the num is " + Animal.num);
        // 访问实例的方法
        callInstanceMethod(animal);
        // 访问静态类的方法
        callStaticMethod(animal);


    }

    private native void accessInstanceFiled(Animal animal);

    private native void accessStaticField(Animal animal);


    private native void callInstanceMethod(Animal animal);

    private native void callStaticMethod(Animal animal);

}
