package com.glumes.androidcppsolib

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import com.glumes.androidcppsolib.bean.NativeCrashSample
import com.glumes.androidcppsolib.bean.SampleItem
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


class SampleListAdapter : RecyclerView.Adapter<ItemViewHolder>() {


    private var mItems: ArrayList<SampleItem> = ArrayList()

    init {
        mItems.add(SampleItem("title", func = NativeCrashSample()))
    }

    override fun onBindViewHolder(holder: ItemViewHolder, position: Int) {
        holder.bind(mItems[position])
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ItemViewHolder {
        return ItemViewHolder(LayoutInflater.from(parent.context).inflate(R.layout.sample_list_item, parent, false))
    }

    override fun getItemCount(): Int {
        return mItems.size
    }

}


class ItemViewHolder(var root: View) : RecyclerView.ViewHolder(root) {

    var text: TextView = root.findViewById(R.id.item_text)

    fun bind(data: SampleItem) {
        text.text = data.title
        text.setOnClickListener(data.func)
    }
}



