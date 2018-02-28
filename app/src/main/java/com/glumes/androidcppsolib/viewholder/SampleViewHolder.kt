package com.glumes.androidcppsolib.viewholder

import com.glumes.androidcppsolib.databinding.SampleTypeBinding
import com.glumes.databindingadapter.BindingViewHolder

/**
 * Created by glumes on 28/02/2018
 */
class SampleViewHolder(binding: SampleTypeBinding?) : BindingViewHolder<SampleModel, SampleTypeBinding>(binding) {


    override fun onBind(data: SampleModel?, position: Int) {
        mBinding.model = data!!
        mBinding.executePendingBindings()
        mBinding.eventhandler = EventHandler()
    }
}