#cmake_minimum_required (VERSION 2.6)

include_directories(../../lib/miniupnp-master)

add_executable(generateRSA
mainGenerateKey.cpp
main_.cpp

)

target_link_libraries(generateRSA megatron-main   zsingle megatron-core crypto  z pthread dl)



