#cmake_minimum_required (VERSION 2.6)

add_library(core-geoip SHARED
    geoip.cpp
    geoip_reg.cpp
    geoip_impl.cpp
    CapsGeoIP.cpp
)

target_link_libraries(core-geoip megatron-core crypto pthread )

install(TARGETS core-geoip DESTINATION ${PLUGIN_TARGET_DIR})

