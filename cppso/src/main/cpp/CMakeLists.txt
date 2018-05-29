# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.


add_library(

            native-operation

            SHARED

            # ${CMAKE_SOURCE_DIR}/native-operation.cpp
            # ${CMAKE_SOURCE_DIR}/access-cache.cpp

            ${CMAKE_SOURCE_DIR}/jnioperations/basic-type-operation.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/string-type-operation.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/array-type-operation.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/filed_and_method_operation.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/cache_filed_and_method.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/invoke_constructor.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/local_and_global_references.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/exceptions-operations.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/native_onload.cpp
            ${CMAKE_SOURCE_DIR}/jnioperations/thread_operation.cpp
            )

add_library(

            info-manger

            SHARED


            ${CMAKE_SOURCE_DIR}/jnioperations/basic-type-operation.cpp
            ${CMAKE_SOURCE_DIR}/infomanager/LoadManager.cpp

            )



include_directories(${CMAKE_SOURCE_DIR}/common/)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )




# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-operation

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )



target_link_libraries( # Specifies the target library.
                       info-manger

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )