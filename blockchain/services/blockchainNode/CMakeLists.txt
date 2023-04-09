#cmake_minimum_required (VERSION 2.6)

add_library(blockchain1-node-service SHARED
    blockchainNode.cpp
    blockchainNodeService.cpp
    initDB.cpp
)

if(ENABLE_QT_GUI)
target_link_libraries(blockchain1-node-service  blockchain-system-events megatron-core pthread sqlitecpp sqlite3  ${DL} ${Qt5Widgets_LIBRARIES})
else()
target_link_libraries(blockchain1-node-service  blockchain-system-events megatron-core pthread sqlitecpp sqlite3  ${DL})
endif()
install(TARGETS blockchain1-node-service DESTINATION ${PLUGIN_TARGET_DIR})


