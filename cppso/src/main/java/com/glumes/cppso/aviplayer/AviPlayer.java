package com.glumes.cppso.aviplayer;

import android.graphics.Bitmap;

import java.io.IOException;

/**
 * Created by glumes on 30/05/2018
 */
public class AviPlayer {


    static {
        System.loadLibrary("aviplayer");
    }

    /**
     * 打开指定的 AVI 文件并且返回一个文件描述符
     *
     * @param fileName
     * @return
     * @throws IOException
     */
    public static native long open(String fileName) throws IOException;

    /**
     * 获得视频的宽度
     *
     * @param avi
     * @return
     */
    public static native int getWidth(long avi);

    /**
     * 获得视频的高度
     *
     * @param avi
     * @return
     */
    public static native int getHeight(long avi);

    /**
     * 获得帧速
     *
     * @param avi
     * @return
     */
    public static native double getFrameRate(long avi);

    /**
     * 基于给定的文件描述符关闭指定的 AVI 文件
     *
     * @param avi
     */
    public static native void close(long avi);


    public static native boolean render(long avi, Bitmap bitmap);
}
