package com.glumes.androidcppsolib.viewholder

import android.util.Log
import android.view.View
import com.glumes.androidcppsolib.utils.NATIVE_INT_ARRAY
import com.glumes.androidcppsolib.utils.NATIVE_STRING
import com.glumes.cppso.NativeOperation


/**
 * Created by glumes on 28/02/2018
 */
class EventHandler {

    fun onClick(view: View, model: SampleModel) {
        when (model.type) {
            NATIVE_STRING -> NativeOperation.getNativeString()
            NATIVE_INT_ARRAY -> NativeOperation.getNativeIntArray()
        }
    }
}