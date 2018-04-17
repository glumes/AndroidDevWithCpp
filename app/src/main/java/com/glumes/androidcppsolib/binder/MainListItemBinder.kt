package com.glumes.androidcppsolib.binder

import android.content.Intent
import android.databinding.DataBindingUtil
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.databinding.ItemMainBinding
import com.glumes.androidcppsolib.ui.InfoManageActivity
import com.glumes.androidcppsolib.ui.JNIMethodActivity
import com.glumes.androidcppsolib.utils.JUMP_INFO_MANAGER_ACTIVITY
import com.glumes.androidcppsolib.utils.JUMP_JNI_METIOD_ACTIVITY
import com.glumes.databindingadapter.BindingViewHolder
import com.glumes.databindingadapter.ViewHolderBinder

/**
 * Created by glumes on 26/03/2018
 */

data class MainItem(var title: String, var type: Int)

class MainViewHolder(binding: ItemMainBinding) : BindingViewHolder<MainItem, ItemMainBinding>(binding) {

    override fun onBind(data: MainItem?, position: Int) {
        mBinding.model = data!!
        mBinding.executePendingBindings()
        mBinding.eventhandler = MainEventHandler()
    }

}


class MainListItemBinder : ViewHolderBinder<MainItem, MainViewHolder>() {

    override fun onBindViewHolder(holder: MainViewHolder?, data: MainItem?, position: Int) {
        holder!!.onBind(data, position)
    }

    override fun createViewHolder(inflater: LayoutInflater?, parent: ViewGroup?): MainViewHolder {
        val mBinding = DataBindingUtil.inflate(inflater!!, R.layout.item_main, parent, false) as ItemMainBinding
        return MainViewHolder(mBinding)
    }

}


class MainEventHandler {

    fun onClick(view: View, model: MainItem) {
        when (model.type) {
            JUMP_JNI_METIOD_ACTIVITY -> {
                view.context.startActivity(Intent(view.context, JNIMethodActivity::class.java))
            }

            JUMP_INFO_MANAGER_ACTIVITY -> {
                view.context.startActivity(Intent(view.context, InfoManageActivity::class.java))
            }
        }
    }

}




