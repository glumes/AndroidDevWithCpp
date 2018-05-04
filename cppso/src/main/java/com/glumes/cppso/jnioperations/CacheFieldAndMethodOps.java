package com.glumes.cppso.jnioperations;

import com.glumes.cppso.model.Animal;
import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class CacheFieldAndMethodOps extends BaseOperation {

    static {
        initCacheMethodId();
    }

    @Override
    public void invoke() {
        Animal animal = new Animal("Cache");

        staticCacheField(animal);
        LogUtil.Companion.d("name is " + animal.getName());

        callCacheMethod(animal);

    }

    private native void staticCacheField(Animal animal);

    private native void callCacheMethod(Animal animal);

    private static native void initCacheMethodId();
}
