package com.glumes.androidcppsolib.bean

import android.util.Log
import android.view.View

/**
 * @Author glumes
 */
class SampleItem(var title:String,var func : View.OnClickListener)

class NativeCrashSample : View.OnClickListener {

    override fun onClick(p0: View?) {
        Log.d("SampleItem", "OnClick")
    }
}

