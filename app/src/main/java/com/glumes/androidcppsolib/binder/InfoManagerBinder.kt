package com.glumes.androidcppsolib.binder

import android.databinding.DataBindingUtil
import android.view.LayoutInflater
import android.view.ViewGroup
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.databinding.InfoCardBinding
import com.glumes.databindingadapter.BindingViewHolder
import com.glumes.databindingadapter.ViewHolderBinder

/**
 * Created by glumes on 26/03/2018
 */

data class Student(var name: String, var age: Int, var sex: String, var grade: Int, var stuId: Int, var avatarId: Int)

class InfoManagerViewHolder(binding: InfoCardBinding) : BindingViewHolder<Student, InfoCardBinding>(binding) {

    override fun onBind(data: Student?, position: Int) {
        mBinding.model = data
        mBinding.executePendingBindings()
    }
}

class InfoManagerBinder : ViewHolderBinder<Student, InfoManagerViewHolder>() {

    override fun onBindViewHolder(holder: InfoManagerViewHolder?, data: Student?, position: Int) {
        holder!!.onBind(data, position)
    }

    override fun createViewHolder(inflater: LayoutInflater?, parent: ViewGroup?): InfoManagerViewHolder {
        val mBindind = DataBindingUtil.inflate<InfoCardBinding>(inflater!!, R.layout.info_card, parent, false)
        return InfoManagerViewHolder(mBindind)
    }

}

