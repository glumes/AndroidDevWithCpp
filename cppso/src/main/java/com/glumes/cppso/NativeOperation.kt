package com.glumes.cppso

import com.glumes.cppso.cache.AccessCache
import com.glumes.cppso.callback.CallBackClass
import com.glumes.cppso.utils.LogUtil

/**
 * Created by glumes on 28/02/2018
 */
class NativeOperation {


    companion object {


        val callback = CallBackClass()

        init {
            callback.str = "callback"
            callback.num = 100
        }

        /**
         * 从 Native 中输出 String
         */
        fun getNativeString() {
            LogUtil.d("print string from native is " + SampleNativeMethod.NativeString())
        }


        /**
         * JNI 中的数组分为：基本类型数组 和 对象数组
         */
        fun getNativeIntArray() {
            var array = SampleNativeMethod.NativeIntArray()
            LogUtil.d("size is " + array.size)
            for (it in array) {
                LogUtil.d("num $it is $it")
            }
        }

        fun callStaticMethod() {
            LogUtil.d("before callback num is " + callback.num)
            SampleNativeMethod.NativeCallStaticMethod()
            LogUtil.d("after callback num is " + callback.num)
        }

        fun callInstanceMethod() {
            LogUtil.d("before callback str is " + callback.str)
            SampleNativeMethod.NativeCallInstanceMethod(callback)
            LogUtil.d("after callback str is " + callback.str)
        }


        fun callSuperMethod() {
            SampleNativeMethod.NativeCallSuperMethod()
        }

        fun accessCache() {
            val accessCache = AccessCache()
            accessCache.accessField()
            val chars = charArrayOf('c','a','c','h','e')

            val str = accessCache.newString(chars, 5)
            LogUtil.d(str)
        }
    }
}
