include_directories(Event) 



add_executable(test-referrer
mainTestReferrer.cpp
main_.cpp

)

target_link_libraries(test-referrer  megatron-main   zsingle megatron-core crypto  z pthread dl)


