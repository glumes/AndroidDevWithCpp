package com.glumes.androidcppsolib.activity

import android.support.v7.app.AppCompatActivity
import com.glumes.cppso.aviplayer.AviPlayer

/**
 * @Author  glumes
 */
abstract class AbstractPlayerActivity : AppCompatActivity() {

    protected var mAvi: Long = 0L


    override fun onStart() {
        super.onStart()
    }


    override fun onStop() {
        super.onStop()
        if (mAvi != 0L) {
            AviPlayer.close(mAvi)
            mAvi = 0
        }
    }
}