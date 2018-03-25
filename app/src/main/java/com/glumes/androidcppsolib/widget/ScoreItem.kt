package com.glumes.androidcppsolib.widget

import android.content.Context
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.View
import android.widget.LinearLayout
import android.widget.TextView
import com.glumes.androidcppsolib.R

/**
 * @Author  glumes
 */
class ScoreItem @JvmOverloads constructor(
        context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : LinearLayout(context, attrs, defStyleAttr) {

    val mRootView: View = LayoutInflater.from(context).inflate(R.layout.item_score_layout, this, true)
    var mTitle: TextView
    var mScore: TextView

    init {


        mTitle = mRootView.findViewById(R.id.score_title) as TextView
        mScore = mRootView.findViewById(R.id.score) as TextView
    }

    fun setScore(score: Int) {
        mScore.text = score.toString()
    }

    fun setTitle(title: String) {
        mTitle.text = title
    }

}