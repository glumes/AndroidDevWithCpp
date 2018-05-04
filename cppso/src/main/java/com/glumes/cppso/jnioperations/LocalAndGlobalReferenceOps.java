package com.glumes.cppso.jnioperations;

/**
 * Created by glumes on 04/05/2018
 */
public class LocalAndGlobalReferenceOps extends BaseOperation {


    @Override
    public void invoke() {
        print(
                cacheWithGlobalReference()
        );
    }

    private native void deleteLocalReferences();

    private native String cacheWithGlobalReference();

}
