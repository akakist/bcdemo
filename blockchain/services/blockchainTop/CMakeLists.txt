#cmake_minimum_required (VERSION 2.6)

add_library(blockchain1-top-service SHARED
    blockchainTop.cpp
    blockchainTopService.cpp
)

target_link_libraries(blockchain1-top-service blockchain-system-events megatron-core pthread sqlitecpp sqlite3)

install(TARGETS blockchain1-top-service DESTINATION ${PLUGIN_TARGET_DIR})

