package com.glumes.androidcppsolib.viewholder

import android.databinding.DataBindingUtil
import android.view.LayoutInflater
import android.view.ViewGroup
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.databinding.SampleTypeBinding
import com.glumes.databindingadapter.ViewHolderBinder

/**
 * Created by glumes on 28/02/2018
 */
class SampleBinder : ViewHolderBinder<SampleModel, SampleViewHolder>() {


    override fun onBindViewHolder(holder: SampleViewHolder?, data: SampleModel?, position: Int) {
        holder!!.onBind(data,position)
    }

    override fun createViewHolder(inflater: LayoutInflater?, parent: ViewGroup?): SampleViewHolder {
        val mBinding = DataBindingUtil.inflate(inflater, R.layout.sample_type,parent,false) as SampleTypeBinding
        return SampleViewHolder(mBinding)
    }
}