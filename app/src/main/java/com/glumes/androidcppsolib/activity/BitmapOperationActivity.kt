package com.glumes.androidcppsolib.activity

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.glumes.androidcppsolib.R
import com.glumes.cppso.jnioperations.BitmapOps
import com.glumes.cppso.utils.LogUtil
import kotlinx.android.synthetic.main.activity_bitmap_operation.*

class BitmapOperationActivity : AppCompatActivity() {


    private val mBitmapOps = BitmapOps()
    lateinit var mBitmap: Bitmap
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_bitmap_operation)

        initBitmap()

        // 顺时针旋转 90° 的操作
        rotate.setOnClickListener { rotateBitmap(mBitmap) }
        // 上下翻转的操作
        convert.setOnClickListener { convertBitmap(mBitmap) }
        // 左右对调的操作
        mirror.setOnClickListener { mirrorBitmap(mBitmap) }
    }

    private fun initBitmap() {
        mBitmap = BitmapFactory.decodeResource(resources, R.drawable.avatar)
    }

    private fun rotateBitmap(bitmap: Bitmap) {
        val result = mBitmapOps.rotateBitmap(bitmap)
        updateBitmap(result)
    }

    private fun convertBitmap(bitmap: Bitmap) {
        val result = mBitmapOps.convertBitmap(bitmap)
        updateBitmap(result)
    }

    private fun mirrorBitmap(bitmap: Bitmap) {
        val result = mBitmapOps.mirrorBitmap(bitmap)
        updateBitmap(result)
    }

    private fun updateBitmap(bitmap: Bitmap?) {
        if (bitmap == null) {
            LogUtil.e("operation failed")
        }
        resultView.setImageBitmap(bitmap)
    }
}
