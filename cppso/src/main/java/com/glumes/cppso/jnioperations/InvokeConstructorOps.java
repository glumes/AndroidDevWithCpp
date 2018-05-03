package com.glumes.cppso.jnioperations;

/**
 * @Author glumes
 */
public class InvokeConstructorOps extends BaseOperation {


    @Override
    public void invoke() {

        print(
                invokeStringConstructors()
        );
    }

    private native String invokeStringConstructors();

}
