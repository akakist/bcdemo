#cmake_minimum_required (VERSION 2.6)

#ADD_SUBDIRECTORY(test)

add_library(dfs-caps SHARED

dfsCaps.cpp
dfsCapsService.cpp
CapsAlgorithm.cpp

)
target_link_libraries(dfs-caps megatron-core   pthread)
install(TARGETS dfs-caps DESTINATION ${PLUGIN_TARGET_DIR})

