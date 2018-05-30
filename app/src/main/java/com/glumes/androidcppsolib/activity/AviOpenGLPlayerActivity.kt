package com.glumes.androidcppsolib.activity

import android.opengl.GLSurfaceView
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.glumes.androidcppsolib.R
import com.glumes.cppso.aviplayer.AviPlayer
import java.util.concurrent.atomic.AtomicBoolean
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class AviOpenGLPlayerActivity : AppCompatActivity() {


    private var isPlaying = AtomicBoolean()

    private var instance: Long = 0
    private var mAvi: Long = 0L

    private lateinit var glSurfaceView: GLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_avi_open_glplayer)

        glSurfaceView = findViewById(R.id.glsurfaceview)


    }

    override fun onStart() {
        super.onStart()
        instance = AviPlayer.init(mAvi)
    }

    override fun onResume() {
        super.onResume()
    }

    override fun onPause() {
        super.onPause()
    }

    override fun onStop() {
        super.onStop()
    }

    private val renderer  = object :GLSurfaceView.Renderer{

        override fun onDrawFrame(gl: GL10?) {
        }

        override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        }

        override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
//            initSurface(instance,mAvi)
        }

    }
}
