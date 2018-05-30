package com.glumes.androidcppsolib.activity

import android.Manifest
import android.graphics.Bitmap
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.view.SurfaceHolder
import android.view.SurfaceView
import com.glumes.androidcppsolib.R
import com.glumes.cppso.aviplayer.AviPlayer
import com.glumes.cppso.utils.LogUtil
import com.tbruyelle.rxpermissions2.RxPermissions
import java.io.File
import java.util.concurrent.atomic.AtomicBoolean

class AviBitmapPlayerActivity : AppCompatActivity() {

    private val path = Environment.getExternalStorageDirectory().toString() + File.separator + "galleon.avi"

    private lateinit var mSurfaceView: SurfaceView

    private var isPlaying = AtomicBoolean()

    private var surfaceHolder: SurfaceHolder? = null

    private var mAvi: Long = 0L

    private lateinit var rxPermissions: RxPermissions

    private val surfaceHolderCallback = object : SurfaceHolder.Callback {

        override fun surfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
        }

        override fun surfaceDestroyed(holder: SurfaceHolder?) {
            isPlaying.set(false)
        }

        override fun surfaceCreated(holder: SurfaceHolder?) {
            isPlaying.set(true)
            Thread(renderer).start()
        }
    }

    private val renderer = Runnable {
        val bitmap = Bitmap.createBitmap(
                AviPlayer.getWidth(mAvi),
                AviPlayer.getHeight(mAvi),
                Bitmap.Config.RGB_565
        )
        val frameDelay = (1000 / AviPlayer.getFrameRate(mAvi)).toLong()

        while (isPlaying.get()) {
            AviPlayer.render(mAvi, bitmap)
            val canvas = surfaceHolder!!.lockCanvas()
            if (canvas != null) {
                canvas.drawBitmap(bitmap, 0f, 0f, null)
                surfaceHolder!!.unlockCanvasAndPost(canvas)
                Thread.sleep(frameDelay)
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_avi_player)

        mSurfaceView = findViewById(R.id.surfaceView)


        if (File(path).exists()) {

            rxPermissions.request(Manifest.permission.READ_EXTERNAL_STORAGE)

            mAvi = AviPlayer.open(path)

            printAVIInfo()

            surfaceHolder = mSurfaceView.holder

            surfaceHolder!!.addCallback(surfaceHolderCallback)
        }
    }

    private fun printAVIInfo() {
        LogUtil.d("file path is $path")
        LogUtil.d("get avi id is $mAvi")
        LogUtil.d("get avi width is " + AviPlayer.getWidth(mAvi))
        LogUtil.d("get avi height is " + AviPlayer.getHeight(mAvi))
        LogUtil.d("get avi frameRate is " + AviPlayer.getFrameRate(mAvi))
    }

}
