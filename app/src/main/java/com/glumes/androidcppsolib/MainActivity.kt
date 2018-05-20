package com.glumes.androidcppsolib


import android.graphics.Color
import android.os.Bundle
import android.support.v7.widget.RecyclerView
import android.support.v7.widget.Toolbar
import com.glumes.androidcppsolib.base.BaseListActivity
import com.glumes.androidcppsolib.binder.MainItem
import com.glumes.androidcppsolib.binder.MainListItemBinder
import com.glumes.cppso.utils.JUMP_INFO_MANAGER_ACTIVITY
import com.glumes.cppso.utils.JUMP_JNI_METIOD_ACTIVITY
import com.glumes.databindingadapter.DataBindingAdapter
import com.glumes.databindingadapter.Items

class MainActivity : BaseListActivity() {


    private val items = Items()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        items.add(MainItem("JNI • 基础操作", JUMP_JNI_METIOD_ACTIVITY))
        items.add(MainItem("JNI 实践 • 学生信息管理", JUMP_INFO_MANAGER_ACTIVITY))
    }

    override fun setUpToolbar(toolbar: Toolbar) {
        toolbar.title = resources.getString(R.string.app_name)
        toolbar.setTitleTextColor(Color.WHITE)
    }


    override fun initAdapter(): RecyclerView.Adapter<RecyclerView.ViewHolder> {

        val mAdapter = DataBindingAdapter()
        mAdapter.map(MainItem::class.java, MainListItemBinder())
                .setItems(items)

        return mAdapter
    }

}
