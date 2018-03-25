package com.glumes.androidcppsolib.adapter

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.bean.SampleItem
import com.glumes.androidcppsolib.bean.Student
import com.glumes.androidcppsolib.widget.ScoreItem

/**
 * @Author  glumes
 */
class StudentInfoAdapter : RecyclerView.Adapter<StudentInfoViewHolder>() {


    private var mItems: ArrayList<SampleItem> = ArrayList()

    init {

    }

    override fun onCreateViewHolder(parent: ViewGroup?, viewType: Int): StudentInfoViewHolder {
        return StudentInfoViewHolder(LayoutInflater.from(parent!!.context).inflate(R.layout.item_student_info, parent, false))
    }

    override fun getItemCount(): Int {
        return mItems.size
    }

    override fun onBindViewHolder(holder: StudentInfoViewHolder?, position: Int) {

    }
}

class StudentInfoViewHolder(var root: View) : RecyclerView.ViewHolder(root) {

    var scoreItem: ScoreItem = root.findViewById(R.id.math)

    fun bind(info: Student) {
        scoreItem.setScore(info.math)
    }
}