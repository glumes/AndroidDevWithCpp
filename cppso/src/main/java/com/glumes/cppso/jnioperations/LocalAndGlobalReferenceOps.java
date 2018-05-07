package com.glumes.cppso.jnioperations;

/**
 * Created by glumes on 04/05/2018
 */
public class LocalAndGlobalReferenceOps extends BaseOperation {


    @Override
    public void invoke() {
//        print(
//                cacheWithGlobalReference()
//                errorCacheUseLocalReference()
//        );

        useWeakGlobalReference();
    }

    private native void useWeakGlobalReference();

    private native String errorCacheUseLocalReference();

    // 全局引用
    private native String cacheWithGlobalReference();

}
