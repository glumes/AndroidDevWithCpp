package com.glumes.androidcppsolib


import android.os.Bundle
import android.support.v7.widget.RecyclerView
import android.support.v7.widget.Toolbar

import com.glumes.androidcppsolib.base.BaseListActivity
import com.glumes.androidcppsolib.utils.JUMP_JNI_METIOD_ACTIVITY
import com.glumes.androidcppsolib.viewholder.MainItem
import com.glumes.androidcppsolib.viewholder.MainListItemBinder
import com.glumes.databindingadapter.DataBindingAdapter
import com.glumes.databindingadapter.Items

class MainActivity : BaseListActivity() {

    private val items = Items()


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        items.add(MainItem("JNI相关操作", JUMP_JNI_METIOD_ACTIVITY))
    }

    override fun setUpToolbar(toolbar: Toolbar) {
        toolbar.title = "SoLib"
    }

    override fun initAdapter(): RecyclerView.Adapter<RecyclerView.ViewHolder> {

        val mAdapter = DataBindingAdapter()
        mAdapter.map(MainItem::class.java, MainListItemBinder())
                .setItems(items)

        return mAdapter
    }

}
