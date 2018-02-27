package com.glumes.androidcppsolib

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import com.glumes.androidcppsolib.adapter.SampleListAdapter
import kotlinx.android.synthetic.main.activity_sample_list.*

class SampleListActivity : AppCompatActivity() {

    private lateinit var mAdapter: SampleListAdapter

    private lateinit var mListView: RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sample_list)
        mListView = sample_list
        mAdapter = SampleListAdapter()
        mListView.layoutManager = LinearLayoutManager(this)
        mListView.setHasFixedSize(true)
        mListView.adapter = mAdapter
    }
}






