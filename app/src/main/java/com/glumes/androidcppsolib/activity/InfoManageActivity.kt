package com.glumes.androidcppsolib.activity

import android.os.Bundle
import android.support.design.widget.FloatingActionButton
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.base.BaseListActivity
import com.glumes.androidcppsolib.binder.InfoManagerBinder
import com.glumes.androidcppsolib.binder.SampleBinder
import com.glumes.androidcppsolib.binder.SampleModel
import com.glumes.androidcppsolib.binder.Student
import com.glumes.cppso.infomanager.StudentInfoLoader
import com.glumes.cppso.utils.*
import com.glumes.databindingadapter.DataBindingAdapter
import com.glumes.databindingadapter.Items

class InfoManageActivity : BaseListActivity(), View.OnClickListener {


    private var mItems = Items()

    lateinit var mPlus: FloatingActionButton
    lateinit var mMinus: FloatingActionButton

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        initData()
        mPlus = findViewById(R.id.plus)
        mMinus = findViewById(R.id.minus)
        mPlus.setOnClickListener(this)
        mMinus.setOnClickListener(this)
    }

    private fun initData() {
        mItems.add(Student("name", 1, "male", 12, 12, R.drawable.woman_16))
        loadData()
    }

    override fun getLayoutId(): Int {
        return R.layout.activity_info_manager
    }

    override fun initAdapter(): RecyclerView.Adapter<RecyclerView.ViewHolder> {
        val mAdapter = DataBindingAdapter()

        mAdapter
                .map(SampleModel::class.java, SampleBinder())
                .map(Student::class.java, InfoManagerBinder())
                .setItems(mItems)

        return mAdapter
    }

    override fun onClick(v: View) {
        when (v.id) {
            R.id.minus -> {
                minusData()
            }
            R.id.plus -> {
                plusData()
            }
        }
    }

    companion object {
        init {
            System.loadLibrary("info-manger")
        }
    }

    private external fun loadData()

    private external fun plusData()

    private external fun minusData()
}
