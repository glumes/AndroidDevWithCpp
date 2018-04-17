package com.glumes.androidcppsolib.binder

import android.databinding.DataBindingComponent
import android.databinding.DataBindingUtil
import android.view.LayoutInflater
import android.view.ViewGroup
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.databinding.ItemStudentInfoBinding
import com.glumes.databindingadapter.BindingViewHolder
import com.glumes.databindingadapter.ViewHolderBinder

/**
 * Created by glumes on 26/03/2018
 */

data class Student(var name: String, var age: Int, var sex: String, var math: Int, var chinaese: Int, var computer: Int)

class InfoManagerViewHolder(binding: ItemStudentInfoBinding) : BindingViewHolder<Student, ItemStudentInfoBinding>(binding) {

    override fun onBind(data: Student?, position: Int) {

    }

}

class InfoManagerBinder : ViewHolderBinder<Student, InfoManagerViewHolder>() {

    override fun onBindViewHolder(holder: InfoManagerViewHolder?, data: Student?, position: Int) {
        holder!!.onBind(data, position)
    }

    override fun createViewHolder(inflater: LayoutInflater?, parent: ViewGroup?): InfoManagerViewHolder {
        val mBindind = DataBindingUtil.inflate<ItemStudentInfoBinding>(inflater!!, R.layout.item_student_info, parent, false)
        return InfoManagerViewHolder(mBindind)
    }

}

