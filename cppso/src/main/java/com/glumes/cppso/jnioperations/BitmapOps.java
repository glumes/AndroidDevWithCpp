package com.glumes.cppso.jnioperations;

import android.graphics.Bitmap;

/**
 * Created by glumes on 24/07/2018
 */

public class BitmapOps extends BaseOperation {

    // 顺时针旋转 90° 的操作
    public native Bitmap rotateBitmap(Bitmap bitmap);

    public native Bitmap convertBitmap(Bitmap bitmap);

    public native Bitmap mirrorBitmap(Bitmap bitmap);

    @Override
    public void invoke() {

    }
}
