package com.glumes.androidcppsolib.adapter

import android.support.v7.widget.RecyclerView
import android.view.View
import android.widget.TextView
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.bean.SampleItem

/**
 * Created by glumes on 27/02/2018
 */


class ItemViewHolder(var root: View) : RecyclerView.ViewHolder(root) {

    var text: TextView = root.findViewById(R.id.item_text)

    fun bind(data: SampleItem) {
        text.text = data.title
        text.setOnClickListener(data.func)
    }
}