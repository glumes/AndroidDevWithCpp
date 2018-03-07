package com.glumes.androidcppsolib.viewholder

import android.util.Log
import android.view.View
import com.glumes.androidcppsolib.utils.*
import com.glumes.cppso.NativeOperation


/**
 * Created by glumes on 28/02/2018
 */
class EventHandler {

    fun onClick(view: View, model: SampleModel) {
        when (model.type) {
            NATIVE_STRING -> NativeOperation.getNativeString()
            NATIVE_INT_ARRAY -> NativeOperation.getNativeIntArray()
            NATIVE_CALL_STATIC_METHOD -> NativeOperation.callStaticMethod()
            NATIVE_CALL_INSTANCE_METHOD -> NativeOperation.callInstanceMethod()
            NATIVE_CALL_SUPER_METHOD -> NativeOperation.callSuperMethod()
            NATIVE_ACCESS_CACHE -> NativeOperation.accessCache()
        }
    }
}