package com.glumes.androidcppsolib.utils;

import android.content.res.Resources;
import android.databinding.BindingAdapter;
import android.graphics.drawable.Drawable;
import android.widget.ImageView;

import com.glumes.androidcppsolib.R;

/**
 * @Author glumes
 */

public class DataBindingUtils {

    @BindingAdapter("app:imageDrawableId")
    public static void bindImageDrawable(ImageView view, Integer drawableId) {

        try {
            Drawable drawable = view.getContext().getResources().getDrawable(drawableId);
            view.setImageDrawable(drawable);
        } catch (Resources.NotFoundException e) {
            view.setImageResource(R.drawable.woman_16);
        }
    }
}
