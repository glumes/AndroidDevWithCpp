package com.glumes.cppso

import com.glumes.cppso.utils.LogUtil

/**
 * Created by glumes on 28/02/2018
 */
class NativeOperation {


    companion object {

        /**
         * 从 Native 中输出 String
         */
        fun getNativeString() {
            LogUtil.d("print string from native is " + SampleNativeMethod.NativeString())
        }


        /**
         * JNI 中的数组分为：基本类型数组 和 对象数组
         */
        fun getNativeIntArray(){
            var array = SampleNativeMethod.NativeIntArray()
            LogUtil.d("size is " + array.size)
            for (it in array){
                LogUtil.d("num $it is $it")
            }
        }

        fun nativeArray() {

        }
    }
}
