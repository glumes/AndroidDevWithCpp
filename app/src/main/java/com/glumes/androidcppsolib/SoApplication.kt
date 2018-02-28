package com.glumes.androidcppsolib

import android.app.Application
import com.squareup.leakcanary.LeakCanary
import timber.log.Timber.DebugTree
import timber.log.Timber



/**
 * Created by glumes on 28/02/2018
 */
class SoApplication : Application() {

    override fun onCreate() {
        super.onCreate()
        initLeakCanary()
        initTimber()

    }

    private fun initTimber() {
        if (BuildConfig.DEBUG) {
            Timber.plant(DebugTree())
        }
    }

    private fun initLeakCanary() {
        if (LeakCanary.isInAnalyzerProcess(this)) {
            // This process is dedicated to LeakCanary for heap analysis.
            // You should not init your app in this process.
            return
        }
        LeakCanary.install(this)
    }

}