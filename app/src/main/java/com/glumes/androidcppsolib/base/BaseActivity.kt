package com.glumes.androidcppsolib.base

import android.annotation.SuppressLint
import android.os.Bundle
import android.support.v7.widget.Toolbar
import com.glumes.androidcppsolib.R
import com.glumes.sampleutil.BaseToolbarActivity

/**
 * Created by glumes on 28/02/2018
 */
open class BaseActivity : BaseToolbarActivity() {

    @SuppressLint("MissingSuperCall")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_base)
    }

    override fun setUpToolbar(toolbar: Toolbar) {
        toolbar.title = getString(R.string.app_name)
    }
}