package com.glumes.androidcppsolib.ui

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.LinearLayoutManager

import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.binder.InfoManagerBinder
import com.glumes.androidcppsolib.binder.Student
import com.glumes.databindingadapter.DataBindingAdapter
import com.glumes.databindingadapter.Items
import kotlinx.android.synthetic.main.activity_info_manager.*

class InfoManageActivity : AppCompatActivity() {


    var mItems = Items()


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_info_manager)

        initRecyclerView()
    }

    fun initRecyclerView() {
        mRecyclerView.setHasFixedSize(true)
        mRecyclerView.layoutManager = LinearLayoutManager(this)

        val mAdapter = DataBindingAdapter()
        mAdapter.map(Student::class.java, InfoManagerBinder()).setItems(mItems)
        mRecyclerView.adapter = mAdapter

        mItems.add(Student("name", 20, "man", 100, 100, 100))
        mItems.add(Student("name", 20, "man", 100, 100, 100))
        mItems.add(Student("name", 20, "man", 100, 100, 100))
        mItems.add(Student("name", 20, "man", 100, 100, 100))
        mItems.add(Student("name", 20, "man", 100, 100, 100))
    }
}
