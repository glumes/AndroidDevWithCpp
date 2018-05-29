package com.glumes.androidcppsolib.activity


import android.graphics.Color
import android.os.Bundle
import android.support.v7.widget.RecyclerView
import android.support.v7.widget.Toolbar
import com.glumes.androidcppsolib.base.BaseListActivity
import com.glumes.androidcppsolib.binder.SampleBinder
import com.glumes.androidcppsolib.binder.SampleModel
import com.glumes.cppso.utils.*
import com.glumes.databindingadapter.DataBindingAdapter
import com.glumes.databindingadapter.Items

class JNIMethodActivity : BaseListActivity() {


    private val items = Items()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        initData()
    }

    override fun setUpToolbar(toolbar: Toolbar) {
        toolbar.title = "JNI 方法调用"
    }

    private fun initData() {
        items.add(SampleModel("JNI 动态注册", NATIVE_ON_LOAD))
        items.add(SampleModel("JNI 基础类型操作", NATIVE_BASIC_TYPE))
        items.add(SampleModel("JNI String 操作", NATIVE_STRING))
        items.add(SampleModel("JNI 数组操作", NATIVE_ARRAY))
        items.add(SampleModel("JNI 访问 Java 字段和方法", NATIVE_FIELD_AND_METHOD))
        items.add(SampleModel("JNI 调用构造方法", NATIVE_INVOKE_CONSTRUCTORS))
        items.add(SampleModel("JNI 缓存字段和方法", NATIVE_CACHE_FIELD_AND_METHOD))
        items.add(SampleModel("JNI 不同引用类型管理", NATIVE_LOCAL_AND_GLOBAL_REFERENCES))
        items.add(SampleModel("JNI 异常处理", NATIVE_EXCEPTIONS_OPERATIONS))
        items.add(SampleModel("JNI 线程操作", NATIVE_THREAD_OPS))
    }

    override fun initAdapter(): RecyclerView.Adapter<RecyclerView.ViewHolder> {

        val mAdapter = DataBindingAdapter()

        mAdapter.map(SampleModel::class.java, SampleBinder()).setItems(items)

        return mAdapter
    }

}
