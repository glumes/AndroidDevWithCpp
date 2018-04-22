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

    val mRootView: View = LayoutInflater.from(context).inflate(R.layout.view_score_item, this, true)
    var mTitle: TextView
    var mScore: TextView


    init {

        var typedArray = context.obtainStyledAttributes(attrs, R.styleable.ScoreItem)

        val title = typedArray.getString(R.styleable.ScoreItem_score_title)

        val score = typedArray.getInteger(R.styleable.ScoreItem_score_value, 0)

        typedArray.recycle()

        mTitle = mRootView.findViewById(R.id.score_title) as TextView

        mTitle.text = title

        mScore = mRootView.findViewById(R.id.score) as TextView

        mScore.text = score.toString()
    }

    fun setScore(score: Int) {
        mScore.text = score.toString()
    }

    fun setTitle(title: String) {
        mTitle.text = title
    }

}