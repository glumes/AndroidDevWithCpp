package com.glumes.androidcppsolib.utils;

import android.databinding.BindingAdapter;

import com.glumes.androidcppsolib.widget.ScoreItem;

/**
 * @Author glumes
 */

public class DataBindingUtils {

    @BindingAdapter("app:score_value")
    public static void bindScoreValue(ScoreItem view, Integer value) {
        view.setScore(value);
    }
}
