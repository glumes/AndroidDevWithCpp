package com.glumes.androidcppsolib.base

import android.annotation.SuppressLint
import android.os.Bundle
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.support.v7.widget.Toolbar
import com.glumes.androidcppsolib.R
import com.glumes.sampleutil.BaseToolbarActivity

/**
 * Created by glumes on 28/02/2018
 */
abstract class BaseListActivity : BaseToolbarActivity() {


    lateinit var mRecyclerView: RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_base_list)

        mRecyclerView = findViewById(R.id.mRecyclerView)

        initRecyclerView()
    }


    fun initRecyclerView() {
        val layoutManager = LinearLayoutManager(this)
        layoutManager.orientation = LinearLayoutManager.VERTICAL
        mRecyclerView.layoutManager = layoutManager
        mRecyclerView.setHasFixedSize(true)

        mRecyclerView.adapter = initAdapter()
    }

    abstract fun initAdapter(): RecyclerView.Adapter<RecyclerView.ViewHolder>

    override fun setUpToolbar(toolbar: Toolbar) {
        toolbar.title = getString(R.string.app_name)
    }


}