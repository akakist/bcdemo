#cmake_minimum_required (VERSION 2.6)

include_directories(../../lib/miniupnp-master)

add_executable(test-http 
mainTestHTTP.cpp
main_.cpp
testWebServerService.cpp

)

target_link_libraries(test-http megatron-main   zsingle megatron-core crypto  z pthread dl)


#install(TARGETS test-http DESTINATION ${PLUGIN_TARGET_DIR} )
add_test(NAME test-http
         COMMAND test-http)


