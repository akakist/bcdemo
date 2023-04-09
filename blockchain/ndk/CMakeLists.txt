#cmake_minimum_required (VERSION 2.6)

include_directories(
    ~/work/svs
)



add_library(ndk STATIC
lft_interface.cpp
lft_jni.cpp
ndkHandler.cpp

)

