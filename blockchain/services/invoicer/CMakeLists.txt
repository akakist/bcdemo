#cmake_minimum_required (VERSION 2.6)

add_library(im-invoice-service SHARED
    imInvoicer.cpp
    imInvoicerService.cpp
    ../../Events/blockchain/___blockchainEvent.cpp
)
target_link_libraries(im-invoice-service megatron-core pthread sqlitecpp sqlite3 ${DL})
#im-system-events 
install(TARGETS im-invoice-service DESTINATION ${PLUGIN_TARGET_DIR})

