package com.glumes.androidcppsolib.handler

import com.glumes.cppso.jnioperations.OperationsFactory

/**
 * @Author  glumes
 */

class JNIOperationHandler {

    companion object {

        fun handle(type: Int) {

            OperationsFactory.getInstance().getOperations(type).invoke()

        }
    }
}