##cmake_minimum_required(2.8.11)
#cmake_minimum_required(VERSION 2.8.11)


#Qt/5.7/clang_64
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Multimedia REQUIRED)

if (APPLE) 
      set(CMAKE_MACOSX_RPATH ON) 
      SET(CMAKE_SKIP_BUILD_RPATH TRUE) 
      SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
      SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE) 
endif () 

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
#include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

include_directories(../../common ../../../megatron/main )

add_executable(blockchain-system-adm.exe 

GuiBlockchainHandler.cpp
main.cpp
mainwindow.cpp
../../common/blockchainHandler.cpp
)

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore blockchain-system-common
target_link_libraries(blockchain-system-adm.exe blockchain-system-events  megatron-main  zsingle megatron-core  dl pthread z sqlitecpp sqlite3 ssl crypto
    
    ${Qt5Widgets_LIBRARIES})
install(TARGETS blockchain-system-adm.exe  DESTINATION ${BIN_TARGET_DIR})
