package com.glumes.cppso.utils

/**
 * Created by glumes on 28/02/2018
 */


// 主页面的跳转

const val JUMP_JNI_METHOD_ACTIVITY = 0x00
const val JUMP_INFO_MANAGER_ACTIVITY = 0x01
const val JUMP_GRAPHIC_API_ACTIVITY = 0x02
const val JUMP_BITMAP_OPERATION_ACTIVITY = 0x03

// JNI 操作相关

const val NO_NATIVE_OPERATION = 0x10
const val NATIVE_BASIC_TYPE = 0x13
const val NATIVE_STRING = 0x11
const val NATIVE_ARRAY = 0x12

const val NATIVE_FIELD_AND_METHOD = 0x17

const val NATIVE_CACHE_FIELD_AND_METHOD = 0x18

const val NATIVE_INVOKE_CONSTRUCTORS = 0x19

const val NATIVE_LOCAL_AND_GLOBAL_REFERENCES = 0x1a

const val NATIVE_EXCEPTIONS_OPERATIONS = 0x1b

const val NATIVE_ON_LOAD = 0x1c

const val NATIVE_THREAD_OPS = 0x1d

